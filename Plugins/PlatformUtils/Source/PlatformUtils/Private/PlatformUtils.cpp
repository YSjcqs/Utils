﻿// Copyright Epic Games, Inc. All Rights Reserved.

#include "PlatformUtils.h"

#define LOCTEXT_NAMESPACE "FPlatformUtilsModule"

void FPlatformUtilsModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
}

void FPlatformUtilsModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

TSharedPtr<FNuiUtils> FPlatformUtilsModule::GetNuiUtils()
{
	if (!NuiUtilsInstance.IsValid())
	{
		NuiUtilsInstance = MakeShareable(new FNuiUtils);
	}
	return NuiUtilsInstance;
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FPlatformUtilsModule, PlatformUtils)