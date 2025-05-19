// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "StrafeMovementComponent.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
enum class EStrafeMovementPreset : uint8;
#ifdef STRAFEMOVEMENT_StrafeMovementComponent_generated_h
#error "StrafeMovementComponent.generated.h already included, missing '#pragma once' in StrafeMovementComponent.h"
#endif
#define STRAFEMOVEMENT_StrafeMovementComponent_generated_h

#define FID_Users_phili_Documents_Unreal_Projects_Strafe_Plugins_StrafeMovement_Source_StrafeMovement_Public_StrafeMovementComponent_h_30_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execGetWishSpeed); \
	DECLARE_FUNCTION(execSetMovementPreset); \
	DECLARE_FUNCTION(execApplyStrafeImpulse);


#define FID_Users_phili_Documents_Unreal_Projects_Strafe_Plugins_StrafeMovement_Source_StrafeMovement_Public_StrafeMovementComponent_h_30_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUStrafeMovementComponent(); \
	friend struct Z_Construct_UClass_UStrafeMovementComponent_Statics; \
public: \
	DECLARE_CLASS(UStrafeMovementComponent, UCharacterMovementComponent, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/StrafeMovement"), NO_API) \
	DECLARE_SERIALIZER(UStrafeMovementComponent) \
	static const TCHAR* StaticConfigName() {return TEXT("Game");} \



#define FID_Users_phili_Documents_Unreal_Projects_Strafe_Plugins_StrafeMovement_Source_StrafeMovement_Public_StrafeMovementComponent_h_30_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	UStrafeMovementComponent(UStrafeMovementComponent&&); \
	UStrafeMovementComponent(const UStrafeMovementComponent&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UStrafeMovementComponent); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UStrafeMovementComponent); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UStrafeMovementComponent) \
	NO_API virtual ~UStrafeMovementComponent();


#define FID_Users_phili_Documents_Unreal_Projects_Strafe_Plugins_StrafeMovement_Source_StrafeMovement_Public_StrafeMovementComponent_h_27_PROLOG
#define FID_Users_phili_Documents_Unreal_Projects_Strafe_Plugins_StrafeMovement_Source_StrafeMovement_Public_StrafeMovementComponent_h_30_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Users_phili_Documents_Unreal_Projects_Strafe_Plugins_StrafeMovement_Source_StrafeMovement_Public_StrafeMovementComponent_h_30_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Users_phili_Documents_Unreal_Projects_Strafe_Plugins_StrafeMovement_Source_StrafeMovement_Public_StrafeMovementComponent_h_30_INCLASS_NO_PURE_DECLS \
	FID_Users_phili_Documents_Unreal_Projects_Strafe_Plugins_StrafeMovement_Source_StrafeMovement_Public_StrafeMovementComponent_h_30_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> STRAFEMOVEMENT_API UClass* StaticClass<class UStrafeMovementComponent>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Users_phili_Documents_Unreal_Projects_Strafe_Plugins_StrafeMovement_Source_StrafeMovement_Public_StrafeMovementComponent_h


#define FOREACH_ENUM_ESTRAFEMOVEMENTPRESET(op) \
	op(EStrafeMovementPreset::ClassicQuake) \
	op(EStrafeMovementPreset::Custom) 

enum class EStrafeMovementPreset : uint8;
template<> struct TIsUEnumClass<EStrafeMovementPreset> { enum { Value = true }; };
template<> STRAFEMOVEMENT_API UEnum* StaticEnum<EStrafeMovementPreset>();

PRAGMA_ENABLE_DEPRECATION_WARNINGS
