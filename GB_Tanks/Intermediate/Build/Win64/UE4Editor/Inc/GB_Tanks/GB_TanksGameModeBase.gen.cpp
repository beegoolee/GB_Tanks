// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "GB_Tanks/GB_TanksGameModeBase.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeGB_TanksGameModeBase() {}
// Cross Module References
	GB_TANKS_API UClass* Z_Construct_UClass_AGB_TanksGameModeBase_NoRegister();
	GB_TANKS_API UClass* Z_Construct_UClass_AGB_TanksGameModeBase();
	ENGINE_API UClass* Z_Construct_UClass_AGameModeBase();
	UPackage* Z_Construct_UPackage__Script_GB_Tanks();
// End Cross Module References
	void AGB_TanksGameModeBase::StaticRegisterNativesAGB_TanksGameModeBase()
	{
	}
	UClass* Z_Construct_UClass_AGB_TanksGameModeBase_NoRegister()
	{
		return AGB_TanksGameModeBase::StaticClass();
	}
	struct Z_Construct_UClass_AGB_TanksGameModeBase_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AGB_TanksGameModeBase_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AGameModeBase,
		(UObject* (*)())Z_Construct_UPackage__Script_GB_Tanks,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AGB_TanksGameModeBase_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * \n */" },
		{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering Utilities|Transformation" },
		{ "IncludePath", "GB_TanksGameModeBase.h" },
		{ "ModuleRelativePath", "GB_TanksGameModeBase.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_AGB_TanksGameModeBase_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AGB_TanksGameModeBase>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_AGB_TanksGameModeBase_Statics::ClassParams = {
		&AGB_TanksGameModeBase::StaticClass,
		"Game",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x009002ACu,
		METADATA_PARAMS(Z_Construct_UClass_AGB_TanksGameModeBase_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_AGB_TanksGameModeBase_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_AGB_TanksGameModeBase()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_AGB_TanksGameModeBase_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(AGB_TanksGameModeBase, 188753368);
	template<> GB_TANKS_API UClass* StaticClass<AGB_TanksGameModeBase>()
	{
		return AGB_TanksGameModeBase::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_AGB_TanksGameModeBase(Z_Construct_UClass_AGB_TanksGameModeBase, &AGB_TanksGameModeBase::StaticClass, TEXT("/Script/GB_Tanks"), TEXT("AGB_TanksGameModeBase"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(AGB_TanksGameModeBase);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
