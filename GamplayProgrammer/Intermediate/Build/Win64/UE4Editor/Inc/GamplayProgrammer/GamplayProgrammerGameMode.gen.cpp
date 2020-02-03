// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "GamplayProgrammer/GamplayProgrammerGameMode.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeGamplayProgrammerGameMode() {}
// Cross Module References
	GAMPLAYPROGRAMMER_API UClass* Z_Construct_UClass_AGamplayProgrammerGameMode_NoRegister();
	GAMPLAYPROGRAMMER_API UClass* Z_Construct_UClass_AGamplayProgrammerGameMode();
	ENGINE_API UClass* Z_Construct_UClass_AGameModeBase();
	UPackage* Z_Construct_UPackage__Script_GamplayProgrammer();
// End Cross Module References
	void AGamplayProgrammerGameMode::StaticRegisterNativesAGamplayProgrammerGameMode()
	{
	}
	UClass* Z_Construct_UClass_AGamplayProgrammerGameMode_NoRegister()
	{
		return AGamplayProgrammerGameMode::StaticClass();
	}
	struct Z_Construct_UClass_AGamplayProgrammerGameMode_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AGamplayProgrammerGameMode_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AGameModeBase,
		(UObject* (*)())Z_Construct_UPackage__Script_GamplayProgrammer,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AGamplayProgrammerGameMode_Statics::Class_MetaDataParams[] = {
		{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering Utilities|Transformation" },
		{ "IncludePath", "GamplayProgrammerGameMode.h" },
		{ "ModuleRelativePath", "GamplayProgrammerGameMode.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_AGamplayProgrammerGameMode_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AGamplayProgrammerGameMode>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_AGamplayProgrammerGameMode_Statics::ClassParams = {
		&AGamplayProgrammerGameMode::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x008802A8u,
		METADATA_PARAMS(Z_Construct_UClass_AGamplayProgrammerGameMode_Statics::Class_MetaDataParams, ARRAY_COUNT(Z_Construct_UClass_AGamplayProgrammerGameMode_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_AGamplayProgrammerGameMode()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_AGamplayProgrammerGameMode_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(AGamplayProgrammerGameMode, 232219613);
	template<> GAMPLAYPROGRAMMER_API UClass* StaticClass<AGamplayProgrammerGameMode>()
	{
		return AGamplayProgrammerGameMode::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_AGamplayProgrammerGameMode(Z_Construct_UClass_AGamplayProgrammerGameMode, &AGamplayProgrammerGameMode::StaticClass, TEXT("/Script/GamplayProgrammer"), TEXT("AGamplayProgrammerGameMode"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(AGamplayProgrammerGameMode);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
