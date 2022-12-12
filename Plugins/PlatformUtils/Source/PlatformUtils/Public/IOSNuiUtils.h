// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GenericPlatformNuiUtils.h"

struct PLATFORMUTILS_API FIOSNuiUtils : public FGenericPlatformNuiUtils
{
	virtual void InitNuiSpeech() override;
	virtual void ReleaseNuiSpeech() override;
	virtual bool StartDialog() override;
	virtual bool StopDialog() override;
	virtual bool CheckDialog() override;
	virtual void DialogAudioPermissions() override;
	virtual bool StartTts(FString TtsText) override;
	virtual bool QuitTts() override;
	virtual bool CancelTts() override;
	virtual bool PauseTts() override;
	virtual bool ResumeTts() override;
	virtual bool CheckTts() override;
};