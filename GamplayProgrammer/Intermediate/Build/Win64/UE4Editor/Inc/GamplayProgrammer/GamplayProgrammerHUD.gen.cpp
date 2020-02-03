// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "GamplayProgrammer/GamplayProgrammerHUD.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeGamplayProgrammerHUD() {}
// Cross Module References
	GAMPLAYPROGRAMMER_API UClass* Z_Construct_UClass_AGamplayProgrammerHUD_NoRegister();
	GAMPLAYPROGRAMMER_API UClass* Z_Construct_UClass_AGamplayProgrammerHUD();
	ENGINE_API UClass* Z_Construct_UClass_AHUD();
	UPackage* Z_Construct_UPackage__Script_GamplayProgrammer();
// End Cross Module References
	void AGamplayProgrammerHUD::StaticRegisterNativesAGamplayProgrammerHUD()
	{
	}
	UClass* Z_Construct_UClass_AGamplayProgrammerHUD_NoRegister()
	{
		return AGamplayProgrammerHUD::StaticClass();
	}
	struct Z_Construct_UClass_AGamplayProgrammerHUD_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AGamplayProgrammerHUD_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AHUD,
		(UObject* (*)())Z_Construct_UPackage__Script_GamplayProgrammer,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AGamplayProgrammerHUD_Statics::Class_MetaDataParams[] = {
		{ "HideCategories", "Rendering Actor Input Replication" },
		{ "IncludePath", "GamplayProgrammerHUD.h" },
		{ "ModuleRelativePath", "GamplayProgrammerHUD.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_AGamplayProgrammerHUD_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AGamplayProgrammerHUD>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_AGamplayProgrammerHUD_Statics::ClassParams = {
		&AGamplayProgrammerHUD::StaticClass,
		"Game",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x008002ACu,
		METADATA_PARAMS(Z_Construct_UClass_AGamplayProgrammerHUD_Statics::Class_MetaDataParams, ARRAY_COUNT(Z_Construct_UClass_AGamplayProgrammerHUD_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_AGamplayProgrammerHUD()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_AGamplayProgrammerHUD_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(AGamplayProgrammerHUD, 274357719);
	template<> GAMPLAYPROGRAMMER_API UClass* StaticClass<AGamplayProgrammerHUD>()
	{
		return AGamplayProgrammerHUD::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_AGamplayProgrammerHUD(Z_Construct_UClass_AGamplayProgrammerHUD, &AGamplayProgrammerHUD::StaticClass, TEXT("/Script/GamplayProgrammer"), TEXT("AGamplayProgrammerHUD"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(AGamplayProgrammerHUD);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
