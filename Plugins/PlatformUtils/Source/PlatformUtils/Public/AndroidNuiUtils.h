// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#if PLATFORM_ANDROID

#include "CoreMinimal.h"
#include "GenericPlatformNuiUtils.h"

struct PLATFORMUTILS_API FAndroidNuiUtils : public FGenericPlatformNuiUtils
{
	FAndroidNuiUtils();
	virtual int InitNuiSpeech() override;
	virtual bool CheckNuiInitState() override;
	virtual int OnNuiStart() override;
	virtual int OnNuiStop() override;
	virtual int StartDialog() override;
	virtual int StopDialog() override;
};

#endif