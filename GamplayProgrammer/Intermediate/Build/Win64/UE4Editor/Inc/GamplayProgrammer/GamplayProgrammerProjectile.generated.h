// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class UPrimitiveComponent;
class AActor;
struct FVector;
struct FHitResult;
#ifdef GAMPLAYPROGRAMMER_GamplayProgrammerProjectile_generated_h
#error "GamplayProgrammerProjectile.generated.h already included, missing '#pragma once' in GamplayProgrammerProjectile.h"
#endif
#define GAMPLAYPROGRAMMER_GamplayProgrammerProjectile_generated_h

#define GamplayProgrammer_Source_GamplayProgrammer_GamplayProgrammerProjectile_h_12_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execOnHit) \
	{ \
		P_GET_OBJECT(UPrimitiveComponent,Z_Param_HitComp); \
		P_GET_OBJECT(AActor,Z_Param_OtherActor); \
		P_GET_OBJECT(UPrimitiveComponent,Z_Param_OtherComp); \
		P_GET_STRUCT(FVector,Z_Param_NormalImpulse); \
		P_GET_STRUCT_REF(FHitResult,Z_Param_Out_Hit); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		P_THIS->OnHit(Z_Param_HitComp,Z_Param_OtherActor,Z_Param_OtherComp,Z_Param_NormalImpulse,Z_Param_Out_Hit); \
		P_NATIVE_END; \
	}


#define GamplayProgrammer_Source_GamplayProgrammer_GamplayProgrammerProjectile_h_12_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execOnHit) \
	{ \
		P_GET_OBJECT(UPrimitiveComponent,Z_Param_HitComp); \
		P_GET_OBJECT(AActor,Z_Param_OtherActor); \
		P_GET_OBJECT(UPrimitiveComponent,Z_Param_OtherComp); \
		P_GET_STRUCT(FVector,Z_Param_NormalImpulse); \
		P_GET_STRUCT_REF(FHitResult,Z_Param_Out_Hit); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		P_THIS->OnHit(Z_Param_HitComp,Z_Param_OtherActor,Z_Param_OtherComp,Z_Param_NormalImpulse,Z_Param_Out_Hit); \
		P_NATIVE_END; \
	}


#define GamplayProgrammer_Source_GamplayProgrammer_GamplayProgrammerProjectile_h_12_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAGamplayProgrammerProjectile(); \
	friend struct Z_Construct_UClass_AGamplayProgrammerProjectile_Statics; \
public: \
	DECLARE_CLASS(AGamplayProgrammerProjectile, AActor, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/GamplayProgrammer"), NO_API) \
	DECLARE_SERIALIZER(AGamplayProgrammerProjectile) \
	static const TCHAR* StaticConfigName() {return TEXT("Game");} \



#define GamplayProgrammer_Source_GamplayProgrammer_GamplayProgrammerProjectile_h_12_INCLASS \
private: \
	static void StaticRegisterNativesAGamplayProgrammerProjectile(); \
	friend struct Z_Construct_UClass_AGamplayProgrammerProjectile_Statics; \
public: \
	DECLARE_CLASS(AGamplayProgrammerProjectile, AActor, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/GamplayProgrammer"), NO_API) \
	DECLARE_SERIALIZER(AGamplayProgrammerProjectile) \
	static const TCHAR* StaticConfigName() {return TEXT("Game");} \



#define GamplayProgrammer_Source_GamplayProgrammer_GamplayProgrammerProjectile_h_12_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API AGamplayProgrammerProjectile(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(AGamplayProgrammerProjectile) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AGamplayProgrammerProjectile); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AGamplayProgrammerProjectile); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AGamplayProgrammerProjectile(AGamplayProgrammerProjectile&&); \
	NO_API AGamplayProgrammerProjectile(const AGamplayProgrammerProjectile&); \
public:


#define GamplayProgrammer_Source_GamplayProgrammer_GamplayProgrammerProjectile_h_12_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AGamplayProgrammerProjectile(AGamplayProgrammerProjectile&&); \
	NO_API AGamplayProgrammerProjectile(const AGamplayProgrammerProjectile&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AGamplayProgrammerProjectile); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AGamplayProgrammerProjectile); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(AGamplayProgrammerProjectile)


#define GamplayProgrammer_Source_GamplayProgrammer_GamplayProgrammerProjectile_h_12_PRIVATE_PROPERTY_OFFSET \
	FORCEINLINE static uint32 __PPO__CollisionComp() { return STRUCT_OFFSET(AGamplayProgrammerProjectile, CollisionComp); } \
	FORCEINLINE static uint32 __PPO__ProjectileMovement() { return STRUCT_OFFSET(AGamplayProgrammerProjectile, ProjectileMovement); }


#define GamplayProgrammer_Source_GamplayProgrammer_GamplayProgrammerProjectile_h_9_PROLOG
#define GamplayProgrammer_Source_GamplayProgrammer_GamplayProgrammerProjectile_h_12_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	GamplayProgrammer_Source_GamplayProgrammer_GamplayProgrammerProjectile_h_12_PRIVATE_PROPERTY_OFFSET \
	GamplayProgrammer_Source_GamplayProgrammer_GamplayProgrammerProjectile_h_12_RPC_WRAPPERS \
	GamplayProgrammer_Source_GamplayProgrammer_GamplayProgrammerProjectile_h_12_INCLASS \
	GamplayProgrammer_Source_GamplayProgrammer_GamplayProgrammerProjectile_h_12_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define GamplayProgrammer_Source_GamplayProgrammer_GamplayProgrammerProjectile_h_12_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	GamplayProgrammer_Source_GamplayProgrammer_GamplayProgrammerProjectile_h_12_PRIVATE_PROPERTY_OFFSET \
	GamplayProgrammer_Source_GamplayProgrammer_GamplayProgrammerProjectile_h_12_RPC_WRAPPERS_NO_PURE_DECLS \
	GamplayProgrammer_Source_GamplayProgrammer_GamplayProgrammerProjectile_h_12_INCLASS_NO_PURE_DECLS \
	GamplayProgrammer_Source_GamplayProgrammer_GamplayProgrammerProjectile_h_12_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> GAMPLAYPROGRAMMER_API UClass* StaticClass<class AGamplayProgrammerProjectile>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID GamplayProgrammer_Source_GamplayProgrammer_GamplayProgrammerProjectile_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
