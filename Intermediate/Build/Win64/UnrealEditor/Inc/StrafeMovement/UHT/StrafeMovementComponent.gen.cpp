// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "StrafeMovement/Public/StrafeMovementComponent.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeStrafeMovementComponent() {}

// Begin Cross Module References
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FVector();
ENGINE_API UClass* Z_Construct_UClass_UCharacterMovementComponent();
STRAFEMOVEMENT_API UClass* Z_Construct_UClass_UStrafeMovementComponent();
STRAFEMOVEMENT_API UClass* Z_Construct_UClass_UStrafeMovementComponent_NoRegister();
STRAFEMOVEMENT_API UEnum* Z_Construct_UEnum_StrafeMovement_EStrafeMovementPreset();
UPackage* Z_Construct_UPackage__Script_StrafeMovement();
// End Cross Module References

// Begin Enum EStrafeMovementPreset
static FEnumRegistrationInfo Z_Registration_Info_UEnum_EStrafeMovementPreset;
static UEnum* EStrafeMovementPreset_StaticEnum()
{
	if (!Z_Registration_Info_UEnum_EStrafeMovementPreset.OuterSingleton)
	{
		Z_Registration_Info_UEnum_EStrafeMovementPreset.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_StrafeMovement_EStrafeMovementPreset, (UObject*)Z_Construct_UPackage__Script_StrafeMovement(), TEXT("EStrafeMovementPreset"));
	}
	return Z_Registration_Info_UEnum_EStrafeMovementPreset.OuterSingleton;
}
template<> STRAFEMOVEMENT_API UEnum* StaticEnum<EStrafeMovementPreset>()
{
	return EStrafeMovementPreset_StaticEnum();
}
struct Z_Construct_UEnum_StrafeMovement_EStrafeMovementPreset_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ClassicQuake.DisplayName", "Classic Quake" },
		{ "ClassicQuake.Name", "EStrafeMovementPreset::ClassicQuake" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * Enum for movement presets\n */" },
#endif
		{ "Custom.DisplayName", "Custom" },
		{ "Custom.Name", "EStrafeMovementPreset::Custom" },
		{ "ModuleRelativePath", "Public/StrafeMovementComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Enum for movement presets" },
#endif
	};
#endif // WITH_METADATA
	static constexpr UECodeGen_Private::FEnumeratorParam Enumerators[] = {
		{ "EStrafeMovementPreset::ClassicQuake", (int64)EStrafeMovementPreset::ClassicQuake },
		{ "EStrafeMovementPreset::Custom", (int64)EStrafeMovementPreset::Custom },
	};
	static const UECodeGen_Private::FEnumParams EnumParams;
};
const UECodeGen_Private::FEnumParams Z_Construct_UEnum_StrafeMovement_EStrafeMovementPreset_Statics::EnumParams = {
	(UObject*(*)())Z_Construct_UPackage__Script_StrafeMovement,
	nullptr,
	"EStrafeMovementPreset",
	"EStrafeMovementPreset",
	Z_Construct_UEnum_StrafeMovement_EStrafeMovementPreset_Statics::Enumerators,
	RF_Public|RF_Transient|RF_MarkAsNative,
	UE_ARRAY_COUNT(Z_Construct_UEnum_StrafeMovement_EStrafeMovementPreset_Statics::Enumerators),
	EEnumFlags::None,
	(uint8)UEnum::ECppForm::EnumClass,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UEnum_StrafeMovement_EStrafeMovementPreset_Statics::Enum_MetaDataParams), Z_Construct_UEnum_StrafeMovement_EStrafeMovementPreset_Statics::Enum_MetaDataParams)
};
UEnum* Z_Construct_UEnum_StrafeMovement_EStrafeMovementPreset()
{
	if (!Z_Registration_Info_UEnum_EStrafeMovementPreset.InnerSingleton)
	{
		UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_EStrafeMovementPreset.InnerSingleton, Z_Construct_UEnum_StrafeMovement_EStrafeMovementPreset_Statics::EnumParams);
	}
	return Z_Registration_Info_UEnum_EStrafeMovementPreset.InnerSingleton;
}
// End Enum EStrafeMovementPreset

// Begin Class UStrafeMovementComponent Function ApplyStrafeImpulse
struct Z_Construct_UFunction_UStrafeMovementComponent_ApplyStrafeImpulse_Statics
{
	struct StrafeMovementComponent_eventApplyStrafeImpulse_Parms
	{
		FVector Impulse;
		bool bVelocityChange;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Strafe Movement|Impulses" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Applies a velocity impulse, useful for knockback or special jump pads. */" },
#endif
		{ "ModuleRelativePath", "Public/StrafeMovementComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Applies a velocity impulse, useful for knockback or special jump pads." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Impulse_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStructPropertyParams NewProp_Impulse;
	static void NewProp_bVelocityChange_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bVelocityChange;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UStrafeMovementComponent_ApplyStrafeImpulse_Statics::NewProp_Impulse = { "Impulse", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(StrafeMovementComponent_eventApplyStrafeImpulse_Parms, Impulse), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Impulse_MetaData), NewProp_Impulse_MetaData) };
void Z_Construct_UFunction_UStrafeMovementComponent_ApplyStrafeImpulse_Statics::NewProp_bVelocityChange_SetBit(void* Obj)
{
	((StrafeMovementComponent_eventApplyStrafeImpulse_Parms*)Obj)->bVelocityChange = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UStrafeMovementComponent_ApplyStrafeImpulse_Statics::NewProp_bVelocityChange = { "bVelocityChange", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(StrafeMovementComponent_eventApplyStrafeImpulse_Parms), &Z_Construct_UFunction_UStrafeMovementComponent_ApplyStrafeImpulse_Statics::NewProp_bVelocityChange_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UStrafeMovementComponent_ApplyStrafeImpulse_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UStrafeMovementComponent_ApplyStrafeImpulse_Statics::NewProp_Impulse,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UStrafeMovementComponent_ApplyStrafeImpulse_Statics::NewProp_bVelocityChange,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UStrafeMovementComponent_ApplyStrafeImpulse_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UStrafeMovementComponent_ApplyStrafeImpulse_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UStrafeMovementComponent, nullptr, "ApplyStrafeImpulse", nullptr, nullptr, Z_Construct_UFunction_UStrafeMovementComponent_ApplyStrafeImpulse_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UStrafeMovementComponent_ApplyStrafeImpulse_Statics::PropPointers), sizeof(Z_Construct_UFunction_UStrafeMovementComponent_ApplyStrafeImpulse_Statics::StrafeMovementComponent_eventApplyStrafeImpulse_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04C20401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UStrafeMovementComponent_ApplyStrafeImpulse_Statics::Function_MetaDataParams), Z_Construct_UFunction_UStrafeMovementComponent_ApplyStrafeImpulse_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_UStrafeMovementComponent_ApplyStrafeImpulse_Statics::StrafeMovementComponent_eventApplyStrafeImpulse_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UStrafeMovementComponent_ApplyStrafeImpulse()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UStrafeMovementComponent_ApplyStrafeImpulse_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UStrafeMovementComponent::execApplyStrafeImpulse)
{
	P_GET_STRUCT_REF(FVector,Z_Param_Out_Impulse);
	P_GET_UBOOL(Z_Param_bVelocityChange);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ApplyStrafeImpulse(Z_Param_Out_Impulse,Z_Param_bVelocityChange);
	P_NATIVE_END;
}
// End Class UStrafeMovementComponent Function ApplyStrafeImpulse

// Begin Class UStrafeMovementComponent Function GetWishSpeed
struct Z_Construct_UFunction_UStrafeMovementComponent_GetWishSpeed_Statics
{
	struct StrafeMovementComponent_eventGetWishSpeed_Parms
	{
		float ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Strafe Movement|Debug" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Get current wish speed (max speed player is trying to achieve through input) */" },
#endif
		{ "ModuleRelativePath", "Public/StrafeMovementComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Get current wish speed (max speed player is trying to achieve through input)" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFloatPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UStrafeMovementComponent_GetWishSpeed_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(StrafeMovementComponent_eventGetWishSpeed_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UStrafeMovementComponent_GetWishSpeed_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UStrafeMovementComponent_GetWishSpeed_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UStrafeMovementComponent_GetWishSpeed_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UStrafeMovementComponent_GetWishSpeed_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UStrafeMovementComponent, nullptr, "GetWishSpeed", nullptr, nullptr, Z_Construct_UFunction_UStrafeMovementComponent_GetWishSpeed_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UStrafeMovementComponent_GetWishSpeed_Statics::PropPointers), sizeof(Z_Construct_UFunction_UStrafeMovementComponent_GetWishSpeed_Statics::StrafeMovementComponent_eventGetWishSpeed_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UStrafeMovementComponent_GetWishSpeed_Statics::Function_MetaDataParams), Z_Construct_UFunction_UStrafeMovementComponent_GetWishSpeed_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_UStrafeMovementComponent_GetWishSpeed_Statics::StrafeMovementComponent_eventGetWishSpeed_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UStrafeMovementComponent_GetWishSpeed()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UStrafeMovementComponent_GetWishSpeed_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UStrafeMovementComponent::execGetWishSpeed)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(float*)Z_Param__Result=P_THIS->GetWishSpeed();
	P_NATIVE_END;
}
// End Class UStrafeMovementComponent Function GetWishSpeed

// Begin Class UStrafeMovementComponent Function SetMovementPreset
struct Z_Construct_UFunction_UStrafeMovementComponent_SetMovementPreset_Statics
{
	struct StrafeMovementComponent_eventSetMovementPreset_Parms
	{
		EStrafeMovementPreset NewPreset;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Strafe Movement|Presets" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Sets movement parameters based on a preset. */" },
#endif
		{ "ModuleRelativePath", "Public/StrafeMovementComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Sets movement parameters based on a preset." },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FBytePropertyParams NewProp_NewPreset_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_NewPreset;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UStrafeMovementComponent_SetMovementPreset_Statics::NewProp_NewPreset_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UStrafeMovementComponent_SetMovementPreset_Statics::NewProp_NewPreset = { "NewPreset", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(StrafeMovementComponent_eventSetMovementPreset_Parms, NewPreset), Z_Construct_UEnum_StrafeMovement_EStrafeMovementPreset, METADATA_PARAMS(0, nullptr) }; // 1533859899
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UStrafeMovementComponent_SetMovementPreset_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UStrafeMovementComponent_SetMovementPreset_Statics::NewProp_NewPreset_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UStrafeMovementComponent_SetMovementPreset_Statics::NewProp_NewPreset,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UStrafeMovementComponent_SetMovementPreset_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UStrafeMovementComponent_SetMovementPreset_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UStrafeMovementComponent, nullptr, "SetMovementPreset", nullptr, nullptr, Z_Construct_UFunction_UStrafeMovementComponent_SetMovementPreset_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UStrafeMovementComponent_SetMovementPreset_Statics::PropPointers), sizeof(Z_Construct_UFunction_UStrafeMovementComponent_SetMovementPreset_Statics::StrafeMovementComponent_eventSetMovementPreset_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UStrafeMovementComponent_SetMovementPreset_Statics::Function_MetaDataParams), Z_Construct_UFunction_UStrafeMovementComponent_SetMovementPreset_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_UStrafeMovementComponent_SetMovementPreset_Statics::StrafeMovementComponent_eventSetMovementPreset_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UStrafeMovementComponent_SetMovementPreset()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UStrafeMovementComponent_SetMovementPreset_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UStrafeMovementComponent::execSetMovementPreset)
{
	P_GET_ENUM(EStrafeMovementPreset,Z_Param_NewPreset);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->SetMovementPreset(EStrafeMovementPreset(Z_Param_NewPreset));
	P_NATIVE_END;
}
// End Class UStrafeMovementComponent Function SetMovementPreset

// Begin Class UStrafeMovementComponent
void UStrafeMovementComponent::StaticRegisterNativesUStrafeMovementComponent()
{
	UClass* Class = UStrafeMovementComponent::StaticClass();
	static const FNameNativePtrPair Funcs[] = {
		{ "ApplyStrafeImpulse", &UStrafeMovementComponent::execApplyStrafeImpulse },
		{ "GetWishSpeed", &UStrafeMovementComponent::execGetWishSpeed },
		{ "SetMovementPreset", &UStrafeMovementComponent::execSetMovementPreset },
	};
	FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UStrafeMovementComponent);
UClass* Z_Construct_UClass_UStrafeMovementComponent_NoRegister()
{
	return UStrafeMovementComponent::StaticClass();
}
struct Z_Construct_UClass_UStrafeMovementComponent_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * UStrafeMovementComponent\n *\n * Replicates Quake III Arena's core movement mechanics within the Unreal Engine framework.\n * Focuses on ground/air acceleration, friction, jumping, and maintaining the \"feel\"\n * of strafe-jumping, bunny-hopping, and step-sliding.\n */" },
#endif
		{ "IncludePath", "StrafeMovementComponent.h" },
		{ "ModuleRelativePath", "Public/StrafeMovementComponent.h" },
		{ "ObjectInitializerConstructorDeclared", "" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "UStrafeMovementComponent\n\nReplicates Quake III Arena's core movement mechanics within the Unreal Engine framework.\nFocuses on ground/air acceleration, friction, jumping, and maintaining the \"feel\"\nof strafe-jumping, bunny-hopping, and step-sliding." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CurrentMovementPreset_MetaData[] = {
		{ "ModuleRelativePath", "Public/StrafeMovementComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MaxWishSpeed_MetaData[] = {
		{ "Category", "Strafe Movement|Core" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Maximum speed the player wishes to achieve via input (equivalent to Q3's g_speed or ps->speed). */" },
#endif
		{ "ModuleRelativePath", "Public/StrafeMovementComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Maximum speed the player wishes to achieve via input (equivalent to Q3's g_speed or ps->speed)." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_GroundFrictionFactor_MetaData[] = {
		{ "Category", "Strafe Movement|Ground" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Ground friction factor (equivalent to Q3's pm_friction). Applied when on ground. */" },
#endif
		{ "ModuleRelativePath", "Public/StrafeMovementComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Ground friction factor (equivalent to Q3's pm_friction). Applied when on ground." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_GroundStopSpeed_MetaData[] = {
		{ "Category", "Strafe Movement|Ground" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Speed below which ground friction brings the player to a full stop (equivalent to Q3's pm_stopspeed). */" },
#endif
		{ "ModuleRelativePath", "Public/StrafeMovementComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Speed below which ground friction brings the player to a full stop (equivalent to Q3's pm_stopspeed)." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_GroundAccelerationFactor_MetaData[] = {
		{ "Category", "Strafe Movement|Ground" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Acceleration factor when on ground (equivalent to Q3's pm_accelerate). */" },
#endif
		{ "ModuleRelativePath", "Public/StrafeMovementComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Acceleration factor when on ground (equivalent to Q3's pm_accelerate)." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_AirAccelerationFactor_MetaData[] = {
		{ "Category", "Strafe Movement|Air" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Acceleration factor when in air (equivalent to Q3's pm_airaccelerate). */" },
#endif
		{ "ModuleRelativePath", "Public/StrafeMovementComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Acceleration factor when in air (equivalent to Q3's pm_airaccelerate)." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bAirAccelerationAllowsExceedingMaxWishSpeed_MetaData[] = {
		{ "Category", "Strafe Movement|Air" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** If true, air acceleration is not limited by the MaxWishSpeed. This allows for traditional bunny hopping/strafe jumping. */" },
#endif
		{ "ModuleRelativePath", "Public/StrafeMovementComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "If true, air acceleration is not limited by the MaxWishSpeed. This allows for traditional bunny hopping/strafe jumping." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_StrafeJumpImpulse_MetaData[] = {
		{ "Category", "Strafe Movement|Jumping" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Initial vertical velocity for a jump (equivalent to Q3's JUMP_VELOCITY). */" },
#endif
		{ "ModuleRelativePath", "Public/StrafeMovementComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Initial vertical velocity for a jump (equivalent to Q3's JUMP_VELOCITY)." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bEnableQuakeStepLogic_MetaData[] = {
		{ "Category", "Strafe Movement|Stepping" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// --- Quake Step Logic Parameters ---\n" },
#endif
		{ "ModuleRelativePath", "Public/StrafeMovementComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "--- Quake Step Logic Parameters ---" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_QuakeStepHeight_MetaData[] = {
		{ "Category", "Strafe Movement|Stepping" },
		{ "ClampMin", "0.0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Height for the Quake-style step-up logic (similar to Q3's STEPSIZE). */" },
#endif
		{ "EditCondition", "bEnableQuakeStepLogic" },
		{ "ModuleRelativePath", "Public/StrafeMovementComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Height for the Quake-style step-up logic (similar to Q3's STEPSIZE)." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ClassicQuake_MaxWishSpeed_MetaData[] = {
		{ "Category", "Strafe Movement|Presets|ClassicQuake" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// --- Movement Presets Data (Example) ---\n" },
#endif
		{ "ModuleRelativePath", "Public/StrafeMovementComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "--- Movement Presets Data (Example) ---" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ClassicQuake_GroundFrictionFactor_MetaData[] = {
		{ "Category", "Strafe Movement|Presets|ClassicQuake" },
		{ "ModuleRelativePath", "Public/StrafeMovementComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ClassicQuake_GroundStopSpeed_MetaData[] = {
		{ "Category", "Strafe Movement|Presets|ClassicQuake" },
		{ "ModuleRelativePath", "Public/StrafeMovementComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ClassicQuake_GroundAccelerationFactor_MetaData[] = {
		{ "Category", "Strafe Movement|Presets|ClassicQuake" },
		{ "ModuleRelativePath", "Public/StrafeMovementComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ClassicQuake_AirAccelerationFactor_MetaData[] = {
		{ "Category", "Strafe Movement|Presets|ClassicQuake" },
		{ "ModuleRelativePath", "Public/StrafeMovementComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ClassicQuake_bAirAccelerationAllowsExceedingMaxWishSpeed_MetaData[] = {
		{ "Category", "Strafe Movement|Presets|ClassicQuake" },
		{ "ModuleRelativePath", "Public/StrafeMovementComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ClassicQuake_StrafeJumpImpulse_MetaData[] = {
		{ "Category", "Strafe Movement|Presets|ClassicQuake" },
		{ "ModuleRelativePath", "Public/StrafeMovementComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ClassicQuake_bEnableQuakeStepLogic_MetaData[] = {
		{ "Category", "Strafe Movement|Presets|ClassicQuake" },
		{ "ModuleRelativePath", "Public/StrafeMovementComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ClassicQuake_QuakeStepHeight_MetaData[] = {
		{ "Category", "Strafe Movement|Presets|ClassicQuake" },
		{ "ModuleRelativePath", "Public/StrafeMovementComponent.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FBytePropertyParams NewProp_CurrentMovementPreset_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_CurrentMovementPreset;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_MaxWishSpeed;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_GroundFrictionFactor;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_GroundStopSpeed;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_GroundAccelerationFactor;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_AirAccelerationFactor;
	static void NewProp_bAirAccelerationAllowsExceedingMaxWishSpeed_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bAirAccelerationAllowsExceedingMaxWishSpeed;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_StrafeJumpImpulse;
	static void NewProp_bEnableQuakeStepLogic_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bEnableQuakeStepLogic;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_QuakeStepHeight;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_ClassicQuake_MaxWishSpeed;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_ClassicQuake_GroundFrictionFactor;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_ClassicQuake_GroundStopSpeed;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_ClassicQuake_GroundAccelerationFactor;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_ClassicQuake_AirAccelerationFactor;
	static void NewProp_ClassicQuake_bAirAccelerationAllowsExceedingMaxWishSpeed_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ClassicQuake_bAirAccelerationAllowsExceedingMaxWishSpeed;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_ClassicQuake_StrafeJumpImpulse;
	static void NewProp_ClassicQuake_bEnableQuakeStepLogic_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ClassicQuake_bEnableQuakeStepLogic;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_ClassicQuake_QuakeStepHeight;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UStrafeMovementComponent_ApplyStrafeImpulse, "ApplyStrafeImpulse" }, // 2124166882
		{ &Z_Construct_UFunction_UStrafeMovementComponent_GetWishSpeed, "GetWishSpeed" }, // 1490127425
		{ &Z_Construct_UFunction_UStrafeMovementComponent_SetMovementPreset, "SetMovementPreset" }, // 1918605566
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UStrafeMovementComponent>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FBytePropertyParams Z_Construct_UClass_UStrafeMovementComponent_Statics::NewProp_CurrentMovementPreset_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UClass_UStrafeMovementComponent_Statics::NewProp_CurrentMovementPreset = { "CurrentMovementPreset", nullptr, (EPropertyFlags)0x0020080000000000, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UStrafeMovementComponent, CurrentMovementPreset), Z_Construct_UEnum_StrafeMovement_EStrafeMovementPreset, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CurrentMovementPreset_MetaData), NewProp_CurrentMovementPreset_MetaData) }; // 1533859899
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UStrafeMovementComponent_Statics::NewProp_MaxWishSpeed = { "MaxWishSpeed", nullptr, (EPropertyFlags)0x0010000000004005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UStrafeMovementComponent, MaxWishSpeed), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MaxWishSpeed_MetaData), NewProp_MaxWishSpeed_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UStrafeMovementComponent_Statics::NewProp_GroundFrictionFactor = { "GroundFrictionFactor", nullptr, (EPropertyFlags)0x0010000000004005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UStrafeMovementComponent, GroundFrictionFactor), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_GroundFrictionFactor_MetaData), NewProp_GroundFrictionFactor_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UStrafeMovementComponent_Statics::NewProp_GroundStopSpeed = { "GroundStopSpeed", nullptr, (EPropertyFlags)0x0010000000004005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UStrafeMovementComponent, GroundStopSpeed), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_GroundStopSpeed_MetaData), NewProp_GroundStopSpeed_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UStrafeMovementComponent_Statics::NewProp_GroundAccelerationFactor = { "GroundAccelerationFactor", nullptr, (EPropertyFlags)0x0010000000004005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UStrafeMovementComponent, GroundAccelerationFactor), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_GroundAccelerationFactor_MetaData), NewProp_GroundAccelerationFactor_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UStrafeMovementComponent_Statics::NewProp_AirAccelerationFactor = { "AirAccelerationFactor", nullptr, (EPropertyFlags)0x0010000000004005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UStrafeMovementComponent, AirAccelerationFactor), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_AirAccelerationFactor_MetaData), NewProp_AirAccelerationFactor_MetaData) };
void Z_Construct_UClass_UStrafeMovementComponent_Statics::NewProp_bAirAccelerationAllowsExceedingMaxWishSpeed_SetBit(void* Obj)
{
	((UStrafeMovementComponent*)Obj)->bAirAccelerationAllowsExceedingMaxWishSpeed = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UStrafeMovementComponent_Statics::NewProp_bAirAccelerationAllowsExceedingMaxWishSpeed = { "bAirAccelerationAllowsExceedingMaxWishSpeed", nullptr, (EPropertyFlags)0x0010000000004005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(UStrafeMovementComponent), &Z_Construct_UClass_UStrafeMovementComponent_Statics::NewProp_bAirAccelerationAllowsExceedingMaxWishSpeed_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bAirAccelerationAllowsExceedingMaxWishSpeed_MetaData), NewProp_bAirAccelerationAllowsExceedingMaxWishSpeed_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UStrafeMovementComponent_Statics::NewProp_StrafeJumpImpulse = { "StrafeJumpImpulse", nullptr, (EPropertyFlags)0x0010000000004005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UStrafeMovementComponent, StrafeJumpImpulse), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_StrafeJumpImpulse_MetaData), NewProp_StrafeJumpImpulse_MetaData) };
void Z_Construct_UClass_UStrafeMovementComponent_Statics::NewProp_bEnableQuakeStepLogic_SetBit(void* Obj)
{
	((UStrafeMovementComponent*)Obj)->bEnableQuakeStepLogic = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UStrafeMovementComponent_Statics::NewProp_bEnableQuakeStepLogic = { "bEnableQuakeStepLogic", nullptr, (EPropertyFlags)0x0010000000004005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(UStrafeMovementComponent), &Z_Construct_UClass_UStrafeMovementComponent_Statics::NewProp_bEnableQuakeStepLogic_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bEnableQuakeStepLogic_MetaData), NewProp_bEnableQuakeStepLogic_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UStrafeMovementComponent_Statics::NewProp_QuakeStepHeight = { "QuakeStepHeight", nullptr, (EPropertyFlags)0x0010000000004005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UStrafeMovementComponent, QuakeStepHeight), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_QuakeStepHeight_MetaData), NewProp_QuakeStepHeight_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UStrafeMovementComponent_Statics::NewProp_ClassicQuake_MaxWishSpeed = { "ClassicQuake_MaxWishSpeed", nullptr, (EPropertyFlags)0x0010000000010001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UStrafeMovementComponent, ClassicQuake_MaxWishSpeed), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ClassicQuake_MaxWishSpeed_MetaData), NewProp_ClassicQuake_MaxWishSpeed_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UStrafeMovementComponent_Statics::NewProp_ClassicQuake_GroundFrictionFactor = { "ClassicQuake_GroundFrictionFactor", nullptr, (EPropertyFlags)0x0010000000010001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UStrafeMovementComponent, ClassicQuake_GroundFrictionFactor), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ClassicQuake_GroundFrictionFactor_MetaData), NewProp_ClassicQuake_GroundFrictionFactor_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UStrafeMovementComponent_Statics::NewProp_ClassicQuake_GroundStopSpeed = { "ClassicQuake_GroundStopSpeed", nullptr, (EPropertyFlags)0x0010000000010001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UStrafeMovementComponent, ClassicQuake_GroundStopSpeed), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ClassicQuake_GroundStopSpeed_MetaData), NewProp_ClassicQuake_GroundStopSpeed_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UStrafeMovementComponent_Statics::NewProp_ClassicQuake_GroundAccelerationFactor = { "ClassicQuake_GroundAccelerationFactor", nullptr, (EPropertyFlags)0x0010000000010001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UStrafeMovementComponent, ClassicQuake_GroundAccelerationFactor), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ClassicQuake_GroundAccelerationFactor_MetaData), NewProp_ClassicQuake_GroundAccelerationFactor_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UStrafeMovementComponent_Statics::NewProp_ClassicQuake_AirAccelerationFactor = { "ClassicQuake_AirAccelerationFactor", nullptr, (EPropertyFlags)0x0010000000010001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UStrafeMovementComponent, ClassicQuake_AirAccelerationFactor), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ClassicQuake_AirAccelerationFactor_MetaData), NewProp_ClassicQuake_AirAccelerationFactor_MetaData) };
void Z_Construct_UClass_UStrafeMovementComponent_Statics::NewProp_ClassicQuake_bAirAccelerationAllowsExceedingMaxWishSpeed_SetBit(void* Obj)
{
	((UStrafeMovementComponent*)Obj)->ClassicQuake_bAirAccelerationAllowsExceedingMaxWishSpeed = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UStrafeMovementComponent_Statics::NewProp_ClassicQuake_bAirAccelerationAllowsExceedingMaxWishSpeed = { "ClassicQuake_bAirAccelerationAllowsExceedingMaxWishSpeed", nullptr, (EPropertyFlags)0x0010000000010001, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(UStrafeMovementComponent), &Z_Construct_UClass_UStrafeMovementComponent_Statics::NewProp_ClassicQuake_bAirAccelerationAllowsExceedingMaxWishSpeed_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ClassicQuake_bAirAccelerationAllowsExceedingMaxWishSpeed_MetaData), NewProp_ClassicQuake_bAirAccelerationAllowsExceedingMaxWishSpeed_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UStrafeMovementComponent_Statics::NewProp_ClassicQuake_StrafeJumpImpulse = { "ClassicQuake_StrafeJumpImpulse", nullptr, (EPropertyFlags)0x0010000000010001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UStrafeMovementComponent, ClassicQuake_StrafeJumpImpulse), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ClassicQuake_StrafeJumpImpulse_MetaData), NewProp_ClassicQuake_StrafeJumpImpulse_MetaData) };
void Z_Construct_UClass_UStrafeMovementComponent_Statics::NewProp_ClassicQuake_bEnableQuakeStepLogic_SetBit(void* Obj)
{
	((UStrafeMovementComponent*)Obj)->ClassicQuake_bEnableQuakeStepLogic = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UStrafeMovementComponent_Statics::NewProp_ClassicQuake_bEnableQuakeStepLogic = { "ClassicQuake_bEnableQuakeStepLogic", nullptr, (EPropertyFlags)0x0010000000010001, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(UStrafeMovementComponent), &Z_Construct_UClass_UStrafeMovementComponent_Statics::NewProp_ClassicQuake_bEnableQuakeStepLogic_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ClassicQuake_bEnableQuakeStepLogic_MetaData), NewProp_ClassicQuake_bEnableQuakeStepLogic_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UStrafeMovementComponent_Statics::NewProp_ClassicQuake_QuakeStepHeight = { "ClassicQuake_QuakeStepHeight", nullptr, (EPropertyFlags)0x0010000000010001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UStrafeMovementComponent, ClassicQuake_QuakeStepHeight), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ClassicQuake_QuakeStepHeight_MetaData), NewProp_ClassicQuake_QuakeStepHeight_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UStrafeMovementComponent_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UStrafeMovementComponent_Statics::NewProp_CurrentMovementPreset_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UStrafeMovementComponent_Statics::NewProp_CurrentMovementPreset,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UStrafeMovementComponent_Statics::NewProp_MaxWishSpeed,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UStrafeMovementComponent_Statics::NewProp_GroundFrictionFactor,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UStrafeMovementComponent_Statics::NewProp_GroundStopSpeed,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UStrafeMovementComponent_Statics::NewProp_GroundAccelerationFactor,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UStrafeMovementComponent_Statics::NewProp_AirAccelerationFactor,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UStrafeMovementComponent_Statics::NewProp_bAirAccelerationAllowsExceedingMaxWishSpeed,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UStrafeMovementComponent_Statics::NewProp_StrafeJumpImpulse,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UStrafeMovementComponent_Statics::NewProp_bEnableQuakeStepLogic,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UStrafeMovementComponent_Statics::NewProp_QuakeStepHeight,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UStrafeMovementComponent_Statics::NewProp_ClassicQuake_MaxWishSpeed,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UStrafeMovementComponent_Statics::NewProp_ClassicQuake_GroundFrictionFactor,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UStrafeMovementComponent_Statics::NewProp_ClassicQuake_GroundStopSpeed,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UStrafeMovementComponent_Statics::NewProp_ClassicQuake_GroundAccelerationFactor,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UStrafeMovementComponent_Statics::NewProp_ClassicQuake_AirAccelerationFactor,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UStrafeMovementComponent_Statics::NewProp_ClassicQuake_bAirAccelerationAllowsExceedingMaxWishSpeed,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UStrafeMovementComponent_Statics::NewProp_ClassicQuake_StrafeJumpImpulse,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UStrafeMovementComponent_Statics::NewProp_ClassicQuake_bEnableQuakeStepLogic,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UStrafeMovementComponent_Statics::NewProp_ClassicQuake_QuakeStepHeight,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UStrafeMovementComponent_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_UStrafeMovementComponent_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UCharacterMovementComponent,
	(UObject* (*)())Z_Construct_UPackage__Script_StrafeMovement,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UStrafeMovementComponent_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UStrafeMovementComponent_Statics::ClassParams = {
	&UStrafeMovementComponent::StaticClass,
	"Game",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_UStrafeMovementComponent_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_UStrafeMovementComponent_Statics::PropPointers),
	0,
	0x00B000A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UStrafeMovementComponent_Statics::Class_MetaDataParams), Z_Construct_UClass_UStrafeMovementComponent_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UStrafeMovementComponent()
{
	if (!Z_Registration_Info_UClass_UStrafeMovementComponent.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UStrafeMovementComponent.OuterSingleton, Z_Construct_UClass_UStrafeMovementComponent_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UStrafeMovementComponent.OuterSingleton;
}
template<> STRAFEMOVEMENT_API UClass* StaticClass<UStrafeMovementComponent>()
{
	return UStrafeMovementComponent::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(UStrafeMovementComponent);
UStrafeMovementComponent::~UStrafeMovementComponent() {}
// End Class UStrafeMovementComponent

// Begin Registration
struct Z_CompiledInDeferFile_FID_Users_phili_Documents_Unreal_Projects_Strafe_Plugins_StrafeMovement_Source_StrafeMovement_Public_StrafeMovementComponent_h_Statics
{
	static constexpr FEnumRegisterCompiledInInfo EnumInfo[] = {
		{ EStrafeMovementPreset_StaticEnum, TEXT("EStrafeMovementPreset"), &Z_Registration_Info_UEnum_EStrafeMovementPreset, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 1533859899U) },
	};
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UStrafeMovementComponent, UStrafeMovementComponent::StaticClass, TEXT("UStrafeMovementComponent"), &Z_Registration_Info_UClass_UStrafeMovementComponent, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UStrafeMovementComponent), 3429911703U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_phili_Documents_Unreal_Projects_Strafe_Plugins_StrafeMovement_Source_StrafeMovement_Public_StrafeMovementComponent_h_4053210541(TEXT("/Script/StrafeMovement"),
	Z_CompiledInDeferFile_FID_Users_phili_Documents_Unreal_Projects_Strafe_Plugins_StrafeMovement_Source_StrafeMovement_Public_StrafeMovementComponent_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_phili_Documents_Unreal_Projects_Strafe_Plugins_StrafeMovement_Source_StrafeMovement_Public_StrafeMovementComponent_h_Statics::ClassInfo),
	nullptr, 0,
	Z_CompiledInDeferFile_FID_Users_phili_Documents_Unreal_Projects_Strafe_Plugins_StrafeMovement_Source_StrafeMovement_Public_StrafeMovementComponent_h_Statics::EnumInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_phili_Documents_Unreal_Projects_Strafe_Plugins_StrafeMovement_Source_StrafeMovement_Public_StrafeMovementComponent_h_Statics::EnumInfo));
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
