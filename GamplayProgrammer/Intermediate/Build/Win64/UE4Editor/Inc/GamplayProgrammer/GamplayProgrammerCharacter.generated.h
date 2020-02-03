// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef GAMPLAYPROGRAMMER_GamplayProgrammerCharacter_generated_h
#error "GamplayProgrammerCharacter.generated.h already included, missing '#pragma once' in GamplayProgrammerCharacter.h"
#endif
#define GAMPLAYPROGRAMMER_GamplayProgrammerCharacter_generated_h

#define GamplayProgrammer_Source_GamplayProgrammer_GamplayProgrammerCharacter_h_14_RPC_WRAPPERS
#define GamplayProgrammer_Source_GamplayProgrammer_GamplayProgrammerCharacter_h_14_RPC_WRAPPERS_NO_PURE_DECLS
#define GamplayProgrammer_Source_GamplayProgrammer_GamplayProgrammerCharacter_h_14_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAGamplayProgrammerCharacter(); \
	friend struct Z_Construct_UClass_AGamplayProgrammerCharacter_Statics; \
public: \
	DECLARE_CLASS(AGamplayProgrammerCharacter, ACharacter, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/GamplayProgrammer"), NO_API) \
	DECLARE_SERIALIZER(AGamplayProgrammerCharacter)


#define GamplayProgrammer_Source_GamplayProgrammer_GamplayProgrammerCharacter_h_14_INCLASS \
private: \
	static void StaticRegisterNativesAGamplayProgrammerCharacter(); \
	friend struct Z_Construct_UClass_AGamplayProgrammerCharacter_Statics; \
public: \
	DECLARE_CLASS(AGamplayProgrammerCharacter, ACharacter, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/GamplayProgrammer"), NO_API) \
	DECLARE_SERIALIZER(AGamplayProgrammerCharacter)


#define GamplayProgrammer_Source_GamplayProgrammer_GamplayProgrammerCharacter_h_14_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API AGamplayProgrammerCharacter(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(AGamplayProgrammerCharacter) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AGamplayProgrammerCharacter); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AGamplayProgrammerCharacter); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AGamplayProgrammerCharacter(AGamplayProgrammerCharacter&&); \
	NO_API AGamplayProgrammerCharacter(const AGamplayProgrammerCharacter&); \
public:


#define GamplayProgrammer_Source_GamplayProgrammer_GamplayProgrammerCharacter_h_14_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AGamplayProgrammerCharacter(AGamplayProgrammerCharacter&&); \
	NO_API AGamplayProgrammerCharacter(const AGamplayProgrammerCharacter&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AGamplayProgrammerCharacter); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AGamplayProgrammerCharacter); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(AGamplayProgrammerCharacter)


#define GamplayProgrammer_Source_GamplayProgrammer_GamplayProgrammerCharacter_h_14_PRIVATE_PROPERTY_OFFSET \
	FORCEINLINE static uint32 __PPO__Mesh1P() { return STRUCT_OFFSET(AGamplayProgrammerCharacter, Mesh1P); } \
	FORCEINLINE static uint32 __PPO__FP_Gun() { return STRUCT_OFFSET(AGamplayProgrammerCharacter, FP_Gun); } \
	FORCEINLINE static uint32 __PPO__FP_MuzzleLocation() { return STRUCT_OFFSET(AGamplayProgrammerCharacter, FP_MuzzleLocation); } \
	FORCEINLINE static uint32 __PPO__VR_Gun() { return STRUCT_OFFSET(AGamplayProgrammerCharacter, VR_Gun); } \
	FORCEINLINE static uint32 __PPO__VR_MuzzleLocation() { return STRUCT_OFFSET(AGamplayProgrammerCharacter, VR_MuzzleLocation); } \
	FORCEINLINE static uint32 __PPO__FirstPersonCameraComponent() { return STRUCT_OFFSET(AGamplayProgrammerCharacter, FirstPersonCameraComponent); } \
	FORCEINLINE static uint32 __PPO__R_MotionController() { return STRUCT_OFFSET(AGamplayProgrammerCharacter, R_MotionController); } \
	FORCEINLINE static uint32 __PPO__L_MotionController() { return STRUCT_OFFSET(AGamplayProgrammerCharacter, L_MotionController); }


#define GamplayProgrammer_Source_GamplayProgrammer_GamplayProgrammerCharacter_h_11_PROLOG
#define GamplayProgrammer_Source_GamplayProgrammer_GamplayProgrammerCharacter_h_14_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	GamplayProgrammer_Source_GamplayProgrammer_GamplayProgrammerCharacter_h_14_PRIVATE_PROPERTY_OFFSET \
	GamplayProgrammer_Source_GamplayProgrammer_GamplayProgrammerCharacter_h_14_RPC_WRAPPERS \
	GamplayProgrammer_Source_GamplayProgrammer_GamplayProgrammerCharacter_h_14_INCLASS \
	GamplayProgrammer_Source_GamplayProgrammer_GamplayProgrammerCharacter_h_14_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define GamplayProgrammer_Source_GamplayProgrammer_GamplayProgrammerCharacter_h_14_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	GamplayProgrammer_Source_GamplayProgrammer_GamplayProgrammerCharacter_h_14_PRIVATE_PROPERTY_OFFSET \
	GamplayProgrammer_Source_GamplayProgrammer_GamplayProgrammerCharacter_h_14_RPC_WRAPPERS_NO_PURE_DECLS \
	GamplayProgrammer_Source_GamplayProgrammer_GamplayProgrammerCharacter_h_14_INCLASS_NO_PURE_DECLS \
	GamplayProgrammer_Source_GamplayProgrammer_GamplayProgrammerCharacter_h_14_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> GAMPLAYPROGRAMMER_API UClass* StaticClass<class AGamplayProgrammerCharacter>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID GamplayProgrammer_Source_GamplayProgrammer_GamplayProgrammerCharacter_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
