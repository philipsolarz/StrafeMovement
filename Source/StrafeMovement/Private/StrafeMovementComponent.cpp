#include "StrafeMovementComponent.h"
#include "GameFramework/Character.h"
#include "Net/UnrealNetwork.h" 
#include "Engine/World.h"     

#pragma region FSavedMove_Strafe

void FSavedMove_Strafe::Clear()
{
    Super::Clear();
    bSavedStrafeJumpHeld = false;
    SavedTimeSinceLanded = 0.f;
}

uint8 FSavedMove_Strafe::GetCompressedFlags() const
{
    uint8 Result = Super::GetCompressedFlags();
    return Result;
}

bool FSavedMove_Strafe::CanCombineWith(const FSavedMovePtr& NewMove, ACharacter* InCharacter, float MaxDelta) const
{
    const FSavedMove_Strafe* NewStrafeMove = static_cast<const FSavedMove_Strafe*>(NewMove.Get());
    if (bSavedStrafeJumpHeld != NewStrafeMove->bSavedStrafeJumpHeld)
    {
        return false;
    }
    return Super::CanCombineWith(NewMove, InCharacter, MaxDelta);
}

void FSavedMove_Strafe::SetMoveFor(ACharacter* C, float InDeltaTime, FVector const& NewAccel, FNetworkPredictionData_Client_Character& ClientData)
{
    Super::SetMoveFor(C, InDeltaTime, NewAccel, ClientData);

    UStrafeMovementComponent* StrafeComp = Cast<UStrafeMovementComponent>(C->GetCharacterMovement());
    if (StrafeComp)
    {
        bSavedStrafeJumpHeld = StrafeComp->GetIsStrafeJumpHeld();
        SavedTimeSinceLanded = StrafeComp->GetTimeSinceLanded();
    }
}

void FSavedMove_Strafe::PrepMoveFor(ACharacter* C)
{
    Super::PrepMoveFor(C);

    UStrafeMovementComponent* StrafeComp = Cast<UStrafeMovementComponent>(C->GetCharacterMovement());
    if (StrafeComp)
    {
        StrafeComp->SetIsStrafeJumpHeld(bSavedStrafeJumpHeld);
        StrafeComp->SetTimeSinceLanded(SavedTimeSinceLanded);
    }
}

#pragma endregion FSavedMove_Strafe

#pragma region FNetworkPredictionData_Client_Strafe

FNetworkPredictionData_Client_Strafe::FNetworkPredictionData_Client_Strafe(const UCharacterMovementComponent& ClientMovement)
    : Super(ClientMovement)
{
}

FSavedMovePtr FNetworkPredictionData_Client_Strafe::AllocateNewMove()
{
    return FSavedMovePtr(new FSavedMove_Strafe());
}

#pragma endregion FNetworkPredictionData_Client_Strafe


UStrafeMovementComponent::UStrafeMovementComponent(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    SetMovementPreset(EStrafeMovementPreset::ClassicQuake);

    NavAgentProps.bCanCrouch = true;
    bCanWalkOffLedgesWhenCrouching = true;
    MaxStepHeight = 18.0f;
    SetWalkableFloorZ(0.7f);

    bStrafeJumpHeld = false;
    TimeSinceLanded = 0.f;
    CurrentWishSpeed = 0.f;
    bAirAccelerationAllowsExceedingMaxWishSpeed = true;
}

void UStrafeMovementComponent::InitializeComponent()
{
    Super::InitializeComponent();
}


float UStrafeMovementComponent::GetMaxAcceleration() const
{
    if (IsMovingOnGround())
    {
        return GroundAccelerationFactor * MaxWishSpeed * 10.f;
    }
    return AirAccelerationFactor * MaxWishSpeed * 10.f;
}

float UStrafeMovementComponent::GetMaxBrakingDeceleration() const
{
    // This is less directly used due to custom friction, but provide a value.
    // Q3's pm_stopspeed and pm_friction determine braking.
    // For UE's system, this should be large enough if it were to be used by other parts of UE.
    return GroundStopSpeed * GroundFrictionFactor * 5.f; // Approximate a strong deceleration
}

void UStrafeMovementComponent::CalcVelocity(float DeltaTime, float Friction, bool bFluid, float BrakingDeceleration)
{
    if (!HasValidData() || ShouldSkipUpdate(DeltaTime))
    {
        return;
    }

    // Our primary velocity calculation happens in PhysWalking and PhysFalling.
    // If for some reason this function is called for those modes,
    // it implies we might be missing some control flow.
    // For other modes, defer to base class.
    if (MovementMode != MOVE_Walking && MovementMode != MOVE_Falling)
    {
        Super::CalcVelocity(DeltaTime, Friction, bFluid, BrakingDeceleration);
        return;
    }
    // If UE's CalcVelocity is called unexpectedly for Walking/Falling,
    // ensure that it doesn't undo our custom velocity calculations.
    // However, PhysWalking/Falling should be the primary drivers.
}


void UStrafeMovementComponent::PhysWalking(float deltaTime, int32 Iterations)
{
    if (deltaTime < MIN_TICK_TIME)
    {
        return;
    }

    if (!CharacterOwner || (!CharacterOwner->Controller && !bRunPhysicsWithNoController && !HasAnimRootMotion() && !CurrentRootMotion.HasOverrideVelocity() && (CharacterOwner->GetLocalRole() != ROLE_SimulatedProxy)))
    {
        Acceleration = FVector::ZeroVector;
        Velocity = FVector::ZeroVector;
        return;
    }

    CurrentWishSpeed = MaxWishSpeed;
    if (IsCrouching())
    {
        // GetMaxSpeed() on UCharacterMovementComponent correctly returns MaxWalkSpeedCrouched
        CurrentWishSpeed = GetMaxSpeed();
    }

    FVector WishDirection = Acceleration.GetSafeNormal();
    float WishSpeed = CurrentWishSpeed;

    ApplyStrafeFriction(deltaTime);
    ApplyStrafeAcceleration(WishDirection, WishSpeed, GroundAccelerationFactor, deltaTime);

    Iterations++;
    bJustTeleported = false;

    FVector OldLocation = UpdatedComponent->GetComponentLocation();

    FHitResult Hit(1.f);
    FVector Adjusted = Velocity * deltaTime;
    SafeMoveUpdatedComponent(Adjusted, UpdatedComponent->GetComponentQuat(), true, Hit);

    if (Hit.Time < 1.f)
    {
        const FVector GravDir = FVector(0.f, 0.f, -1.f);
        const FVector VelDir = Velocity.GetSafeNormal();
        const float UpDown = GravDir | VelDir;

        bool bSteppedUp = false;
        if ((FMath::Abs(Hit.ImpactNormal.Z) < 0.2f) && (UpDown < 0.5f) && (UpDown > -0.2f) && CanStepUp(Hit))
        {
            float stepZ = UpdatedComponent->GetComponentLocation().Z;
            bSteppedUp = StepUp(GravDir, Adjusted * (1.f - Hit.Time), Hit);
            if (bSteppedUp)
            {
                // Adjust OldLocation to prevent sudden large change in vertical speed
                OldLocation.Z = UpdatedComponent->GetComponentLocation().Z + (OldLocation.Z - stepZ);
            }
        }

        if (!bSteppedUp)
        {
            HandleImpact(Hit, deltaTime, Adjusted);
            SlideAlongSurface(Adjusted, (1.f - Hit.Time), Hit.Normal, Hit, true);
        }
    }

    // If we didn't move, or very little
    if (UpdatedComponent->GetComponentLocation() == OldLocation && !Velocity.IsNearlyZero())
    {
        // This might indicate being stuck or a very small delta.
        // Consider if Velocity should be zeroed if truly stuck.
        // For now, FindFloor will update grounding.
    }
    FindFloor(UpdatedComponent->GetComponentLocation(), CurrentFloor, false);
}

void UStrafeMovementComponent::PhysFalling(float deltaTime, int32 Iterations)
{
    if (deltaTime < MIN_TICK_TIME)
    {
        return;
    }

    // Apply gravity
    Velocity += FVector(0.f, 0.f, GetGravityZ()) * GravityScale * deltaTime;

    // Update timers
    if (TimeSinceLanded < JumpLandTimePenalty + deltaTime)
    {
        TimeSinceLanded += deltaTime;
    }

    FVector WishDirection = Acceleration.GetSafeNormal();
    CurrentWishSpeed = MaxWishSpeed;

    FVector AirWishDir = WishDirection;
    AirWishDir.Z = 0;
    if (!AirWishDir.Normalize()) // Normalize returns false if vector is too small
    {
        AirWishDir = FVector::ZeroVector; // Ensure it's zero if normalization failed
    }


    if (!AirWishDir.IsNearlyZero())
    {
        ApplyStrafeAcceleration(AirWishDir, CurrentWishSpeed, AirAccelerationFactor, deltaTime);
    }

    Iterations++;
    bJustTeleported = false;

    const FVector OldLocation = UpdatedComponent->GetComponentLocation();
    const FQuat OldRotation = UpdatedComponent->GetComponentQuat();

    FHitResult Hit(1.f);
    FVector Adjusted = Velocity * deltaTime;
    SafeMoveUpdatedComponent(Adjusted, OldRotation, true, Hit);

    if (Hit.Time < 1.f) // If we hit something
    {
        const FVector OldVel = Velocity; // Save old velocity for landing adjustments if any.
        ProcessLanded(Hit, deltaTime, Iterations); // This will change MovementMode to Walking if landed on walkable surface
        OnLanded(Hit); // Custom land logic

        if (MovementMode == MOVE_Walking) // Check if landed and mode changed
        {
            return; // Stop falling physics if now walking
        }
        // If still falling after impact (e.g. glancing blow, or landed on unwalkable surface)
        HandleImpact(Hit, deltaTime, Adjusted);
        SlideAlongSurface(Adjusted, (1.f - Hit.Time), Hit.Normal, Hit, true);
    }

    // If we're against a blocking wall (steep slope/vertical wall) while falling, Zero Z velocity to prevent "sticking" upwards
    if (Hit.IsValidBlockingHit() && IsAgainstBlockingWall(Hit.ImpactNormal)) // Check if hit something and it's a blocking wall
    {
        // Only zero out upward velocity if hitting a wall, allow downward
        if (Velocity.Z > 0.f) Velocity.Z = 0.f;
    }
}

void UStrafeMovementComponent::ApplyStrafeFriction(float DeltaTime)
{
    float Speed = Velocity.Size2D();
    if (Speed < 1.0f) // Q3 uses 1.0f as a threshold for "almost still"
    {
        Velocity.X = 0.f;
        Velocity.Y = 0.f;
        // Note: Q3 logic "allow sinking underwater" implies Z is not zeroed by friction.
        // Here, we only affect X and Y, Z is handled by gravity/jumping.
        return;
    }

    float Drop = 0.f;
    // In Q3: control = speed < pm_stopspeed ? pm_stopspeed : speed;
    // This means friction is stronger if speed is below stopspeed.
    float Control = Speed < GroundStopSpeed ? GroundStopSpeed : Speed;
    Drop += Control * GroundFrictionFactor * DeltaTime;

    float NewSpeed = Speed - Drop;
    if (NewSpeed < 0.f)
    {
        NewSpeed = 0.f;
    }

    if (Speed > 0.f) // Avoid division by zero
    {
        NewSpeed /= Speed; // Get the scale factor
        Velocity.X *= NewSpeed;
        Velocity.Y *= NewSpeed;
    }
    else // Should be caught by Speed < 1.0f, but as a safeguard
    {
        Velocity.X = 0.f;
        Velocity.Y = 0.f;
    }
}

void UStrafeMovementComponent::ApplyStrafeAcceleration(const FVector& WishDirection, float WishSpeed, float AccelerationParam, float DeltaTime)
{
    if (WishDirection.IsNearlyZero() || WishSpeed <= 0.f || AccelerationParam <= 0.f || DeltaTime <= 0.f)
    {
        return;
    }

    FVector CurrentVelocityForAccel = Velocity;
    // For air acceleration, Q3 PM_AirMove projects velocity onto the XY plane for CurrentSpeedAlongWishDir calculation implicitly
    // because WishDirection for air is purely horizontal.
    // For ground, we use the full 2D velocity.
    if (MovementMode == MOVE_Falling)
    {
        // Use 2D velocity for dot product with horizontal wish direction
        CurrentVelocityForAccel = FVector(Velocity.X, Velocity.Y, 0.f);
    }


    float CurrentSpeedAlongWishDir = FVector::DotProduct(CurrentVelocityForAccel, WishDirection);
    float AddSpeed = WishSpeed - CurrentSpeedAlongWishDir;

    // Original Q3 logic: if (addspeed <= 0) return;
    // This is crucial for how strafe jumping accumulates speed.
    // If you are already moving faster than wishspeed IN THE WISH DIRECTION, no more accel in that direction.
    // Exception: if bAirAccelerationAllowsExceedingMaxWishSpeed is true, we might still accelerate to change direction,
    // even if the projection onto wishdir is high. The key is that the *applied* acceleration amount
    // (AccelSpeed) is proportional to WishSpeed, not AddSpeed.
    if (AddSpeed <= 0.f && !(bAirAccelerationAllowsExceedingMaxWishSpeed && MovementMode == MOVE_Falling))
    {
        return; // No speed to add, or on ground and already at/exceeding wishspeed in this direction
    }

    float AccelAmount = AccelerationParam * DeltaTime * WishSpeed; // Q3 uses WishSpeed here, not AddSpeed

    // This clamp is also from Q3: accelspeed = accel*pml.frametime*wishspeed; if (accelspeed > addspeed) accelspeed = addspeed;
    // This should apply if not in "exceed max wish speed" air mode.
    if (MovementMode == MOVE_Walking || (MovementMode == MOVE_Falling && !bAirAccelerationAllowsExceedingMaxWishSpeed)) {
        if (AccelAmount > AddSpeed && AddSpeed > 0) { // Only clamp if AddSpeed is positive (actually trying to add speed)
            AccelAmount = AddSpeed;
        }
    }
    // If bAirAccelerationAllowsExceedingMaxWishSpeed and in air, AccelAmount is NOT clamped by AddSpeed.
    // This is what makes strafe jumping possible to exceed MaxWishSpeed.

    if (AccelAmount <= 0.f && AddSpeed <= 0.f && !(bAirAccelerationAllowsExceedingMaxWishSpeed && MovementMode == MOVE_Falling)) {
        // If after all calculations, we decided not to accelerate (e.g. AccelAmount became negative or zero due to AddSpeed clamp)
        return;
    }

    FVector AddedVelocity = AccelAmount * WishDirection;

    Velocity.X += AddedVelocity.X;
    Velocity.Y += AddedVelocity.Y;
    // Z velocity is handled by gravity and jumping, not by this lateral acceleration.

    // Speed clamping on ground after acceleration (Q3 clamps if ducking/wading)
    // UE's GetMaxSpeed() already considers crouching for input speed.
    // If a hard cap post-acceleration is needed for ground movement:
    if (IsMovingOnGround()) {
        float MaxGroundSpeed = GetMaxSpeed(); // Considers crouching
        FVector XYVel = FVector(Velocity.X, Velocity.Y, 0);
        if (XYVel.SizeSquared() > FMath::Square(MaxGroundSpeed)) {
            XYVel = XYVel.GetSafeNormal() * MaxGroundSpeed;
            Velocity.X = XYVel.X;
            Velocity.Y = XYVel.Y;
        }
    }
}


bool UStrafeMovementComponent::DoJump(bool bReplayingMoves)
{
    if (CharacterOwner && CharacterOwner->CanJump()) // CanJump checks if MovementMode allows jumping (e.g. on ground)
    {
        if (TimeSinceLanded < JumpLandTimePenalty && JumpLandTimePenalty > 0.f)
        {
            return false;
        }

        // Ensure we are on ground or have air jumps if that was a feature (not for base Q3)
        // UCharacterOwner::CanJump already considers things like JumpMaxCount, IsFalling etc.
        // For Q3, jump is primarily from ground.
        //if (!IsMovingOnGround() && JumpCurrentCount >= JumpMaxCount) // If not on ground and no air jumps left
        //{
        //    //return false; // This would prevent multi-jumps if JumpMaxCount is > 1.
        //    // Let UE's CanJump logic, which checks JumpMaxCount, handle this.
        //}


        Velocity.Z = StrafeJumpImpulse;
        SetMovementMode(MOVE_Falling); // Set to falling as soon as jump impulse is applied
        bStrafeJumpHeld = true;
        TimeSinceLanded = 0.f; // Reset land timer as we've just taken off

        // UE's DoJump also calls CharacterOwner->OnJumped().
        CharacterOwner->OnJumped(); // Call the character's OnJumped event.
        return true;
    }
    return false;
}

void UStrafeMovementComponent::OnMovementModeChanged(EMovementMode PreviousMovementMode, uint8 PreviousCustomMode)
{
    Super::OnMovementModeChanged(PreviousMovementMode, PreviousCustomMode);

    if (!HasValidData())
    {
        return;
    }

    // If we are no longer pressing jump, clear the bStrafeJumpHeld flag
    // This is typically handled by ACharacter::CheckJumpInput which clears CharacterOwner->bPressedJump
    if (CharacterOwner && !CharacterOwner->bPressedJump)
    {
        bStrafeJumpHeld = false;
    }

    // If landed on ground
    if (IsMovingOnGround())
    {
        bStrafeJumpHeld = false; // Can't be "holding" a jump if on ground.
        // TimeSinceLanded is reset in OnLanded/ProcessLanded
    }
}

void UStrafeMovementComponent::OnLanded(const FHitResult& Hit)
{
    // This is called by ProcessLanded.
    // Super::OnLanded(Hit); // Base UCMC OnLanded is empty.
    TimeSinceLanded = 0.0f; // Reset timer for PMF_TIME_LAND behavior
    bStrafeJumpHeld = false; // Jump action is complete upon landing
}


FNetworkPredictionData_Client* UStrafeMovementComponent::GetPredictionData_Client() const
{
    if (ClientPredictionData == nullptr)
    {
        UStrafeMovementComponent* MutableThis = const_cast<UStrafeMovementComponent*>(this);
        MutableThis->ClientPredictionData = new FNetworkPredictionData_Client_Strafe(*this);
    }
    return ClientPredictionData;
}

void UStrafeMovementComponent::UpdateFromCompressedFlags(uint8 Flags)
{
    Super::UpdateFromCompressedFlags(Flags);
    // CharacterMovementComponent handles FLAG_JumpPressed (0x01) -> bPressedJump
    // bStrafeJumpHeld is intended to mirror bPressedJump for our logic.
    if (CharacterOwner)
    {
        bStrafeJumpHeld = CharacterOwner->bPressedJump;
    }
}

void UStrafeMovementComponent::SetMovementPreset(EStrafeMovementPreset NewPreset)
{
    CurrentMovementPreset = NewPreset;
    switch (NewPreset)
    {
    case EStrafeMovementPreset::ClassicQuake:
        MaxWishSpeed = ClassicQuake_MaxWishSpeed;
        GroundFrictionFactor = ClassicQuake_GroundFrictionFactor;
        GroundStopSpeed = ClassicQuake_GroundStopSpeed;
        GroundAccelerationFactor = ClassicQuake_GroundAccelerationFactor;
        AirAccelerationFactor = ClassicQuake_AirAccelerationFactor;
        bAirAccelerationAllowsExceedingMaxWishSpeed = ClassicQuake_bAirAccelerationAllowsExceedingMaxWishSpeed;
        StrafeJumpImpulse = ClassicQuake_StrafeJumpImpulse;
        JumpLandTimePenalty = ClassicQuake_JumpLandTimePenalty;

        // Configure base UCharacterMovementComponent properties to align
        GravityScale = 1.0f; // Default UE gravity is -980. Q3 used -800. Adjust if exact match needed: 800/980 = ~0.816f
        MaxWalkSpeed = MaxWishSpeed;
        MaxWalkSpeedCrouched = MaxWishSpeed * 0.35f; // Q3 ducked speed is ~1/3rd
        MaxFlySpeed = MaxWishSpeed; // For noclip mode
        MaxCustomMovementSpeed = MaxWishSpeed;
        JumpZVelocity = StrafeJumpImpulse; // Ensure UE's JumpZVelocity matches for consistency if other systems use it
        AirControl = 1.0f; // We want our air acceleration logic to have full effect.
        FallingLateralFriction = 0.f; // Q3 has no lateral air friction; pm_airaccelerate provides control.
        BrakingDecelerationWalking = GroundStopSpeed * GroundFrictionFactor * 5.f; // Approximate, as our friction is custom
        BrakingFrictionFactor = GroundFrictionFactor; // Approximate
        break;

    case EStrafeMovementPreset::Custom:
        // For Custom, values are expected to be set directly on the component instance
        // Ensure base UCMC props are also updated if they depend on our custom ones.
        MaxWalkSpeed = MaxWishSpeed;
        MaxWalkSpeedCrouched = MaxWishSpeed * 0.35f; // Or whatever custom scale is desired
        JumpZVelocity = StrafeJumpImpulse;
        // Other UCMC props like GravityScale, AirControl might also need to be set by user for "Custom"
        break;
    }
    // No need for `this->MaxSpeed = GetMaxSpeed();` here as GetMaxSpeed() will reflect the changes
    // made to MaxWalkSpeed, MaxWalkSpeedCrouched etc.
}


void UStrafeMovementComponent::ApplyStrafeImpulse(const FVector& Impulse, bool bVelocityChange)
{
    if (bVelocityChange)
    {
        Velocity = Impulse;
    }
    else
    {
        Velocity += Impulse;
    }

    // If impulse is primarily upward and strong enough, force falling mode to ensure physics updates correctly
    if (IsMovingOnGround() && Impulse.Z > 0.f && Velocity.Z > KINDA_SMALL_NUMBER)
    {
        // Check if the upward component of the impulse is significant enough to lift off
        if (Velocity.Z > StrafeJumpImpulse * 0.1f) // Small threshold
        {
            SetMovementMode(MOVE_Falling);
        }
    }
}


FVector UStrafeMovementComponent::ClipVelocity(const FVector& InVelocity, const FVector& ImpactNormal, float Overbounce) const
{
    float Backoff = FVector::DotProduct(InVelocity, ImpactNormal);

    if (Backoff < 0.f) // Moving into the plane
    {
        FVector AdjustedNormal = ImpactNormal * Backoff * Overbounce;
        return InVelocity - AdjustedNormal;
    }
    // If moving away or parallel, no clipping needed in this specific Quake-style function.
    // UE's SlideAlongSurface handles general cases.
    return InVelocity;
}

bool UStrafeMovementComponent::IsAgainstBlockingWall(const FVector& ImpactNormal) const
{
    if (ImpactNormal.IsNearlyZero() || IsMovingOnGround())
    {
        return false;
    }
    // A "blocking wall" for falling Z-velocity purposes is one that is steep enough.
    // WalkableFloorZ is the Z component of the normal. If impact normal Z is less than this, it's too steep to be a floor.
    return FMath::Abs(ImpactNormal.Z) < GetWalkableFloorZ();
}
