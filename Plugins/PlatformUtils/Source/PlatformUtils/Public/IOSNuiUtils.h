// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GenericPlatformNuiUtils.h"

struct PLATFORMUTILS_API FIOSNuiUtils : public FGenericPlatformNuiUtils
{
	virtual int InitNuiSpeech() override;
	virtual bool CheckNuiInitState() override;
	virtual int OnNuiStart() override;
	virtual int OnNuiStop() override;
	virtual int StartDialog() override;
	virtual int StopDialog() override;
};