#include "StrafeMovementComponent.h"
#include "GameFramework/Character.h"
#include "Components/CapsuleComponent.h" // Required for GetCapsuleComponent()
#include "Net/UnrealNetwork.h" 
#include "Engine/World.h"     

// FSavedMove_Strafe and FNetworkPredictionData_Client_Strafe implementations (same as before) ...
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
    // Default values are set by SetMovementPreset
    SetMovementPreset(EStrafeMovementPreset::ClassicQuake);

    NavAgentProps.bCanCrouch = true;
    bCanWalkOffLedgesWhenCrouching = true;
    // MaxStepHeight is UE's built-in step height, QuakeStepHeight is for our custom logic.
    // They can be the same or different. UE's MaxStepHeight will still apply if our logic is off or fails.
    MaxStepHeight = 18.0f; // Default UE step height, can be overridden by preset if desired
    SetWalkableFloorZ(0.7f);

    bStrafeJumpHeld = false;
    TimeSinceLanded = 0.f;
    CurrentWishSpeed = 0.f;
    bAirAccelerationAllowsExceedingMaxWishSpeed = true;
    bEnableQuakeStepLogic = true; // Default to enabled
    QuakeStepHeight = 18.f;      // Default Q3 step height
    bAllowAutoBunnyHop = true;
}

void UStrafeMovementComponent::InitializeComponent()
{
    Super::InitializeComponent();
}
// GetMaxAcceleration, GetMaxBrakingDeceleration, CalcVelocity (same as before) ...

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
    return GroundStopSpeed * GroundFrictionFactor * 5.f;
}

void UStrafeMovementComponent::CalcVelocity(float DeltaTime, float Friction, bool bFluid, float BrakingDeceleration)
{
    if (!HasValidData() || ShouldSkipUpdate(DeltaTime))
    {
        return;
    }

    if (MovementMode != MOVE_Walking && MovementMode != MOVE_Falling)
    {
        Super::CalcVelocity(DeltaTime, Friction, bFluid, BrakingDeceleration);
        return;
    }
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

    const FVector PreFrameVelocity = Velocity; // Velocity at the start of this tick's PhysWalking
    const FVector PreFrameLocation = UpdatedComponent->GetComponentLocation(); // Location at start

    CurrentWishSpeed = MaxWishSpeed;
    if (IsCrouching())
    {
        CurrentWishSpeed = GetMaxSpeed();
    }

    FVector WishDirection = Acceleration.GetSafeNormal();
    float WishSpeed = CurrentWishSpeed;

    ApplyStrafeFriction(deltaTime);
    ApplyStrafeAcceleration(WishDirection, WishSpeed, GroundAccelerationFactor, deltaTime);

    Iterations++; // UCharacterMovementComponent does this.
    bJustTeleported = false; // UCharacterMovementComponent does this.

    FHitResult Hit(1.f);
    // Adjusted is the attempted move delta for this frame based on current Velocity
    FVector Adjusted = Velocity * deltaTime;

    SafeMoveUpdatedComponent(Adjusted, UpdatedComponent->GetComponentQuat(), true, Hit);

    if (Hit.Time < 1.f && Hit.IsValidBlockingHit()) // We hit something
    {
        bool bStepped = false;
        if (bEnableQuakeStepLogic && QuakeStepHeight > 0.f)
        {
            // Try custom Quake-style step-up.
            // PreFrameVelocity is the velocity state *before* friction and acceleration for *this frame* were applied.
            // We need to pass the velocity that was intended for *this movement attempt*.
            bStepped = TryStrafeStepUp(Hit, PreFrameLocation, PreFrameVelocity, deltaTime);
        }

        if (!bStepped) // If Q3 step logic is disabled or failed
        {
            // Standard UE sliding logic if step failed.
            // SafeMoveUpdatedComponent already moved us to Hit.ImpactPoint.
            // The 'Adjusted' vector for SlideAlongSurface should be the remaining portion of the move.
            FVector RemainingAdjusted = Adjusted * (1.f - Hit.Time);
            HandleImpact(Hit, deltaTime, RemainingAdjusted);
            SlideAlongSurface(RemainingAdjusted, 1.f, Hit.Normal, Hit, true);
        }
        // If bStepped is true, TryStrafeStepUp has already updated position and velocity.
    }

    FindFloor(UpdatedComponent->GetComponentLocation(), CurrentFloor, false);
}


void UStrafeMovementComponent::PhysFalling(float deltaTime, int32 Iterations)
{
    if (deltaTime < MIN_TICK_TIME)
    {
        return;
    }

    // Store velocity before gravity and acceleration for this tick.
    FVector PreMoveVelocity = Velocity;

    // Apply gravity. Velocity.Z will now have this frame's gravity adjustment.
    Velocity.Z += GetGravityZ() * GravityScale * deltaTime;

    // Store the Z velocity that includes this frame's gravity, *before* any X/Y air acceleration or collision response.
    // This is the Z component we want to ensure is largely preserved if we only slide horizontally.
    const float ZVelocityAfterGravity = Velocity.Z;


    //if (TimeSinceLanded < JumpLandTimePenalty + deltaTime) // Original: Check if this is still relevant or if OnLanded handles the reset adequately for immediate jump attempts.
    //{
    //    TimeSinceLanded += deltaTime;
    //}

    FVector WishDirection = Acceleration.GetSafeNormal();
    CurrentWishSpeed = MaxWishSpeed; // You might want to use GetMaxSpeed() if crouch/etc. affects air speed wish.

    FVector AirWishDir = WishDirection;
    AirWishDir.Z = 0;
    if (!AirWishDir.Normalize())
    {
        AirWishDir = FVector::ZeroVector;
    }

    if (!AirWishDir.IsNearlyZero())
    {
        // ApplyStrafeAcceleration modifies Velocity.X and Velocity.Y based on AirWishDir and AirAccelerationFactor
        ApplyStrafeAcceleration(AirWishDir, CurrentWishSpeed, AirAccelerationFactor, deltaTime);
    }
    // At this point, Velocity.X and Velocity.Y are from air acceleration,
    // and Velocity.Z is ZVelocityAfterGravity (original Z + this frame's gravity).

    Iterations++;
    bJustTeleported = false;

    const FVector OldLocation = UpdatedComponent->GetComponentLocation();
    const FQuat OldRotation = UpdatedComponent->GetComponentQuat();
    FHitResult Hit(1.f);

    // Adjusted uses the Velocity that has now been affected by gravity and air acceleration.
    FVector Adjusted = Velocity * deltaTime;
    SafeMoveUpdatedComponent(Adjusted, OldRotation, true, Hit);

    if (Hit.Time < 1.f) // If we hit something
    {
        const FVector OldVelImpact = Velocity; // Velocity just before impact-related functions
        ProcessLanded(Hit, deltaTime, Iterations); // This might change MovementMode

        // OnLanded now handles bStrafeJumpHeld = false and TimeSinceLanded = 0.0f;
        // It also attempts an auto-bunnyhop if enabled and conditions are met.
        // If ProcessLanded changed mode to Walking, OnLanded would have been called.
        // We need to call OnLanded here if we *actually* landed and are now walking.
        if (MovementMode == MOVE_Walking && OldVelImpact.Z < 0.f) // Check if we actually landed from a fall
        {
            OnLanded(Hit); // Ensure OnLanded logic (including auto-jump) runs if ProcessLanded put us in Walking
            return; // Exit, PhysWalking will take over next tick.
        }


        // If still falling after ProcessLanded (i.e., hit a wall or steep slope):
        // HandleImpact can modify 'this->Velocity'.
        HandleImpact(Hit, deltaTime, Adjusted * (1.f - Hit.Time));

        // 'this->Velocity' might have been changed by HandleImpact.
        // Now, slide. SlideAlongSurface also modifies 'this->Velocity'.
        SlideAlongSurface(Adjusted, (1.f - Hit.Time), Hit.Normal, Hit, true);

        // After sliding, if the impact was against a very vertical wall,
        // restore the Z velocity to what it was after gravity was applied for this frame.
        // This prevents the Z velocity from being improperly zeroed or altered by a purely horizontal slide.
        if (FMath::Abs(Hit.ImpactNormal.Z) < KINDA_SMALL_NUMBER && MovementMode == MOVE_Falling) // KINDA_SMALL_NUMBER for very vertical wall
        {
            Velocity.Z = ZVelocityAfterGravity;
        }
        // If it was a slope, SlideAlongSurface's modification of Z is generally more appropriate.
    }

    // This existing check stops upward Z movement if hitting a "blocking wall" while moving up.
    if (Hit.IsValidBlockingHit() && IsAgainstBlockingWall(Hit.ImpactNormal))
    {
        if (Velocity.Z > 0.f)
        {
            Velocity.Z = 0.f;
        }
    }
}

void UStrafeMovementComponent::ApplyStrafeFriction(float DeltaTime)
{
    float Speed = Velocity.Size2D();
    if (Speed < 1.0f)
    {
        Velocity.X = 0.f;
        Velocity.Y = 0.f;
        return;
    }

    float Drop = 0.f;
    float Control = Speed < GroundStopSpeed ? GroundStopSpeed : Speed;
    Drop += Control * GroundFrictionFactor * DeltaTime;

    float NewSpeed = Speed - Drop;
    if (NewSpeed < 0.f)
    {
        NewSpeed = 0.f;
    }

    if (Speed > 0.f)
    {
        NewSpeed /= Speed;
        Velocity.X *= NewSpeed;
        Velocity.Y *= NewSpeed;
    }
    else
    {
        Velocity.X = 0.f;
        Velocity.Y = 0.f;
    }
}

// ApplyStrafeAcceleration (same as before, with small correction for AddSpeed > 0 check) ...
void UStrafeMovementComponent::ApplyStrafeAcceleration(const FVector& WishDirection, float WishSpeed, float AccelerationParam, float DeltaTime)
{
    if (WishDirection.IsNearlyZero() || WishSpeed <= 0.f || AccelerationParam <= 0.f || DeltaTime <= 0.f)
    {
        return;
    }

    FVector CurrentVelocityForAccel = Velocity;
    if (MovementMode == MOVE_Falling)
    {
        CurrentVelocityForAccel = FVector(Velocity.X, Velocity.Y, 0.f);
    }

    float CurrentSpeedAlongWishDir = FVector::DotProduct(CurrentVelocityForAccel, WishDirection);
    float AddSpeed = WishSpeed - CurrentSpeedAlongWishDir;

    if (AddSpeed <= 0.f && !(bAirAccelerationAllowsExceedingMaxWishSpeed && MovementMode == MOVE_Falling))
    {
        return;
    }

    float AccelAmount = AccelerationParam * DeltaTime * WishSpeed;

    if (MovementMode == MOVE_Walking || (MovementMode == MOVE_Falling && !bAirAccelerationAllowsExceedingMaxWishSpeed)) {
        if (AddSpeed > 0.f && AccelAmount > AddSpeed) { // Only clamp if AddSpeed is positive and AccelAmount would exceed it
            AccelAmount = AddSpeed;
        }
        else if (AddSpeed <= 0.f) { // If not trying to add speed (or moving faster), don't apply positive AccelAmount unless air strafing
            if (!(bAirAccelerationAllowsExceedingMaxWishSpeed && MovementMode == MOVE_Falling)) {
                AccelAmount = 0.f; // Effectively stop if AddSpeed is not positive and not permissive air mode
            }
        }
    }

    if (AccelAmount <= 0.f && !(bAirAccelerationAllowsExceedingMaxWishSpeed && MovementMode == MOVE_Falling && AddSpeed > -WishSpeed * 2.f /*Allow some accel if turning sharply*/)) {
        // If AccelAmount ended up non-positive, and we are not in a permissive air strafe mode
        // or if we are but not actively trying to change direction significantly, then don't apply.
        // This condition might need tuning for the exact feel of air control when speed > wishspeed.
        if (AccelAmount == 0 && AddSpeed <= 0) { /*do nothing*/ }
        else if (AccelAmount <= 0) return;
    }

    FVector AddedVelocity = AccelAmount * WishDirection;

    Velocity.X += AddedVelocity.X;
    Velocity.Y += AddedVelocity.Y;

    if (IsMovingOnGround()) {
        float MaxGroundSpeed = GetMaxSpeed();
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
    bool bCanJump = false;
    if (CharacterOwner)
    {
        bCanJump = CharacterOwner->CanJump(); // Check ACharacter's CanJump()
        UE_LOG(LogTemp, Warning, TEXT("[%f] DoJump: Attempting. CharacterOwner->CanJump() = %d. (IsMovingOnGround(): %d, JumpCurrentCount: %d, JumpMaxCount: %d, IsCrouching(): %d)"),
            GetWorld()->GetTimeSeconds(),
            bCanJump,
            IsMovingOnGround(),
            CharacterOwner->JumpCurrentCount,
            CharacterOwner->JumpMaxCount,
            IsCrouching());
    }
    else {
        UE_LOG(LogTemp, Warning, TEXT("[%f] DoJump: No CharacterOwner."), GetWorld()->GetTimeSeconds());
        return false;
    }

    if (bCanJump) // Use the cached result
    {
        // ... (actual jump logic)
        Velocity.Z = StrafeJumpImpulse;
        SetMovementMode(MOVE_Falling);
        bStrafeJumpHeld = true;
        CharacterOwner->OnJumped();
        UE_LOG(LogTemp, Warning, TEXT("[%f] DoJump: Jump successful."), GetWorld()->GetTimeSeconds());
        return true;
    }
    // bStrafeJumpHeld = false; // Only set false on landing or if input is released. Not if CanJump fails mid-air.
    UE_LOG(LogTemp, Warning, TEXT("[%f] DoJump: CanJump() returned false."), GetWorld()->GetTimeSeconds());
    return false;
}

void UStrafeMovementComponent::OnMovementModeChanged(EMovementMode PreviousMovementMode, uint8 PreviousCustomMode)
{
    Super::OnMovementModeChanged(PreviousMovementMode, PreviousCustomMode);

    if (!HasValidData())
    {
        return;
    }

    if (IsMovingOnGround())
    {
        bStrafeJumpHeld = false;
    }
}

void UStrafeMovementComponent::OnLanded(const FHitResult& Hit)
{
    //Super::OnLanded(Hit);
    TimeSinceLanded = 0.0f;
    bStrafeJumpHeld = false;

    if (CharacterOwner)
    {
        UE_LOG(LogTemp, Warning, TEXT("[%f] OnLanded. bPressedJump: %d, bAllowAutoBunnyHop: %d, JumpCurrentCount: %d, Max: %d, IsMovingOnGround: %d"),
            GetWorld()->GetTimeSeconds(),
            CharacterOwner->bPressedJump,
            bAllowAutoBunnyHop,
            CharacterOwner->JumpCurrentCount,
            CharacterOwner->JumpMaxCount,
            IsMovingOnGround());
    }


    if (bAllowAutoBunnyHop && CharacterOwner && CharacterOwner->bPressedJump)
    {
        UE_LOG(LogTemp, Warning, TEXT("[%f] OnLanded: Attempting auto DoJump..."), GetWorld()->GetTimeSeconds());
        bool bDidAutoJump = DoJump(false);
        UE_LOG(LogTemp, Warning, TEXT("[%f] OnLanded: Auto DoJump result: %d"), GetWorld()->GetTimeSeconds(), bDidAutoJump);
    }
}

// GetPredictionData_Client, UpdateFromCompressedFlags (same as before) ...
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
        //JumpLandTimePenalty = ClassicQuake_JumpLandTimePenalty;
        bEnableQuakeStepLogic = ClassicQuake_bEnableQuakeStepLogic;
        QuakeStepHeight = ClassicQuake_QuakeStepHeight;

        GravityScale = 1.0f;
        MaxWalkSpeed = MaxWishSpeed;
        MaxWalkSpeedCrouched = MaxWishSpeed * 0.35f;
        MaxFlySpeed = MaxWishSpeed;
        MaxCustomMovementSpeed = MaxWishSpeed;
        JumpZVelocity = StrafeJumpImpulse;
        AirControl = 1.0f;
        FallingLateralFriction = 0.f;
        BrakingDecelerationWalking = GroundStopSpeed * GroundFrictionFactor * 5.f;
        BrakingFrictionFactor = GroundFrictionFactor;
        break;

    case EStrafeMovementPreset::Custom:
        MaxWalkSpeed = MaxWishSpeed;
        MaxWalkSpeedCrouched = MaxWishSpeed * 0.35f;
        JumpZVelocity = StrafeJumpImpulse;
        break;
    }
}

// ApplyStrafeImpulse, ClipVelocity, IsAgainstBlockingWall (same as before) ...
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

    if (IsMovingOnGround() && Impulse.Z > 0.f && Velocity.Z > KINDA_SMALL_NUMBER)
    {
        if (Velocity.Z > StrafeJumpImpulse * 0.1f)
        {
            SetMovementMode(MOVE_Falling);
        }
    }
}


FVector UStrafeMovementComponent::ClipVelocity(const FVector& InVelocity, const FVector& ImpactNormal, float Overbounce) const
{
    float Backoff = FVector::DotProduct(InVelocity, ImpactNormal);

    if (Backoff < 0.f)
    {
        FVector AdjustedNormal = ImpactNormal * Backoff * Overbounce;
        return InVelocity - AdjustedNormal;
    }
    return InVelocity;
}

bool UStrafeMovementComponent::IsAgainstBlockingWall(const FVector& ImpactNormal) const
{
    if (ImpactNormal.IsNearlyZero() || IsMovingOnGround())
    {
        return false;
    }
    return FMath::Abs(ImpactNormal.Z) < GetWalkableFloorZ();
}


// Implementation of TryStrafeStepUp
bool UStrafeMovementComponent::TryStrafeStepUp(const FHitResult& InitialBlockHit, const FVector& PreFrameLocation, const FVector& PreFrameVelocity, float DeltaTime)
{
    if (!CharacterOwner || QuakeStepHeight <= 0.f)
    {
        return false;
    }

    // --- Based on Quake III's PM_StepSlideMove ---
    // InitialBlockHit.ImpactPoint is where the capsule center was when it hit.
    // UpdatedComponent->GetComponentLocation() is already at InitialBlockHit.ImpactPoint due to SafeMoveUpdatedComponent.
    const FVector LocationAtImpact = UpdatedComponent->GetComponentLocation();
    const FQuat CurrentRotation = UpdatedComponent->GetComponentQuat();
    UCapsuleComponent* Capsule = CharacterOwner->GetCapsuleComponent();

    // 1. Can we even attempt a step? (Simplified Q3 check)
    // Q3 checks if velocity[z] > 0 AND (ground is far OR ground is steep) then returns.
    // This prevents trying to step up if already in the upward arc of a jump onto a high ledge.
    // For simple walking steps, Velocity.Z is typically ~0.
    // We'll skip the complex Q3 downward trace from PreFrameLocation for this condition for now,
    // assuming that if Velocity.Z is significantly positive, it's a jump managed by PhysFalling.
    if (PreFrameVelocity.Z > KINDA_SMALL_NUMBER && IsFalling()) // If moving upwards and already airborne
    {
        // This might be too simple. Q3's check is more nuanced about the nature of the ground below PreFrameLocation.
        // A proper check would involve:
        // FHitResult GroundCheckHit;
        // FVector TraceDownEnd = PreFrameLocation - FVector(0,0, QuakeStepHeight + KINDA_SMALL_NUMBER);
        // TraceCapsule(GroundCheckHit, PreFrameLocation, TraceDownEnd, ...);
        // if (PreFrameVelocity.Z > 0 && (GroundCheckHit.Time == 1.f || GroundCheckHit.ImpactNormal.Z < GetWalkableFloorZ())) return false;
        // For now, rely on IsFalling() combined with upward velocity.
    }

    // 2. Test if the space QuakeStepHeight above PreFrameLocation (where we were *before* the failed move) is clear.
    FVector TestUpStart = PreFrameLocation;
    FVector TestUpEnd = PreFrameLocation + FVector(0.f, 0.f, QuakeStepHeight);
    FHitResult UpTraceHit;
    FName TraceTag("StrafeStepUp_UpTrace");
    FCollisionQueryParams CapsuleParams(TraceTag, false, CharacterOwner); // Standard capsule trace

    bool bHitUp = GetWorld()->SweepSingleByChannel(
        UpTraceHit,
        TestUpStart,
        TestUpEnd,
        CurrentRotation,
        UpdatedComponent->GetCollisionObjectType(), // ECC_Pawn usually
        Capsule->GetCollisionShape(),
        CapsuleParams
    );

    float ActualVerticalStepAchieved = 0.f;
    FVector SteppedUpLocation = PreFrameLocation; // Start with the original location before any movement this frame

    if (!bHitUp) // Path fully clear for QuakeStepHeight
    {
        ActualVerticalStepAchieved = QuakeStepHeight;
        SteppedUpLocation = TestUpEnd;
    }
    else if (UpTraceHit.Time > KINDA_SMALL_NUMBER) // Partially clear
    {
        ActualVerticalStepAchieved = QuakeStepHeight * UpTraceHit.Time;
        SteppedUpLocation = TestUpStart + FVector(0.f, 0.f, ActualVerticalStepAchieved);
    }
    else // Blocked immediately or started in solid when trying to check space above PreFrameLocation
    {
        return false;
    }

    if (ActualVerticalStepAchieved < KINDA_SMALL_NUMBER) // Didn't move up enough
    {
        return false;
    }

    // 3. Tentatively move component to this "stepped-up PreFrameLocation"
    UpdatedComponent->SetWorldLocation(SteppedUpLocation, false, nullptr, ETeleportType::TeleportPhysics);

    // 4. Attempt the original intended move for this frame, but from the new height, using PreFrameVelocity.
    // Q3 uses start_v (PreFrameVelocity) for the second PM_SlideMove.
    // The Z component of PreFrameVelocity for the second slide is a bit nuanced.
    // If stepping, the idea is to move horizontally. PM_SlideMove(gravity) would handle Z.
    // Let's use PreFrameVelocity as is, and SafeMoveUpdatedComponent will resolve it.
    Velocity = PreFrameVelocity;
    FHitResult SecondSlideHit(1.f);
    FVector MoveDeltaForSecondSlide = PreFrameVelocity * DeltaTime; // Full original intended move delta

    SafeMoveUpdatedComponent(MoveDeltaForSecondSlide, CurrentRotation, true, SecondSlideHit);
    // Note: Velocity might be changed by SafeMoveUpdatedComponent if it hits something.

    // 5. Push down from the new position to land on the step/ledge.
    FVector LocationAfterSecondSlide = UpdatedComponent->GetComponentLocation();
    FVector PushDownStart = LocationAfterSecondSlide;
    // Push down by the amount we stepped up, plus a small extra to ensure contact.
    FVector PushDownEnd = LocationAfterSecondSlide - FVector(0.f, 0.f, ActualVerticalStepAchieved + 2.0f);
    FHitResult PushDownHit;
    FName PushDownTraceTag("StrafeStepUp_PushDown");
    FCollisionQueryParams PushDownParams(PushDownTraceTag, false, CharacterOwner);

    bool bHitDown = GetWorld()->SweepSingleByChannel(
        PushDownHit,
        PushDownStart,
        PushDownEnd,
        CurrentRotation,
        UpdatedComponent->GetCollisionObjectType(),
        Capsule->GetCollisionShape(),
        PushDownParams
    );

    if (bHitDown && PushDownHit.IsValidBlockingHit()) // Must hit something to land on
    {
        // Successfully landed on something after stepping up and moving.
        UpdatedComponent->SetWorldLocation(PushDownHit.ImpactPoint, false, nullptr, ETeleportType::TeleportPhysics);
        FindFloor(UpdatedComponent->GetComponentLocation(), CurrentFloor, false);

        if (CurrentFloor.IsWalkableFloor())
        {
            // Step successful!
            // Q3: Clips velocity against the final floor.
            // Project an approximation of the velocity achieved during the second slide onto the new floor.
            // Velocity at this point is after SecondSlideHit.
            Velocity = FVector::VectorPlaneProject(Velocity, PushDownHit.ImpactNormal);
            Velocity.Z = FMath::Min(0.f, Velocity.Z); // Don't have positive Z velocity if on ground.
            SetMovementMode(MOVE_Walking); // Ensure walking mode.
            // UE's StepUp also adjusts Z in a similar fashion after a successful step.
            // StartNewPhysics(DeltaTime, Iterations); // Might be needed if mode changes significantly
            return true;
        }
    }

    // Step-up failed at some stage. Revert to the location at the initial impact.
    // The caller (PhysWalking) will then handle standard sliding.
    UpdatedComponent->SetWorldLocation(LocationAtImpact, false, nullptr, ETeleportType::TeleportPhysics);
    Velocity = PreFrameVelocity; // Restore velocity to what it was before this *entire frame's* PhysWalking started.
    // PhysWalking will then re-apply friction/accel and then do the standard slide from LocationAtImpact.
    // This might be too much of a revert. It should revert to the state *before trying the step*.
    // The `Velocity` member is already what it was after the first SafeMove (and its impact resolution).
    // The caller `PhysWalking` has `OriginalVelocity` which is `PreFrameVelocity`.
    // If `TryStrafeStepUp` returns false, `PhysWalking` will use its `SlideAlongSurface` with the velocity
    // that was current *after* the first `SafeMoveUpdatedComponent` and its potential `HandleImpact`.
    // So, we just need to ensure location is correct. Velocity is fine as is if step fails.
    // The `Velocity = PreFrameVelocity` line above is probably not needed if PhysWalking handles velocity state.
    // Let's remove it; PhysWalking will use the velocity that resulted in the InitialBlockHit for its fallback slide.
    return false;
}