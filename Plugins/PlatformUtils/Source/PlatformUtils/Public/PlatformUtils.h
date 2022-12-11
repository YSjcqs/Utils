// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "NuiUtilsHeader.h"
#include "Modules/ModuleManager.h"

class PLATFORMUTILS_API FPlatformUtilsModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	TSharedPtr<FNuiUtils> GetNuiUtils();

private:
	TSharedPtr<FNuiUtils> NuiUtilsInstance = nullptr;
};
