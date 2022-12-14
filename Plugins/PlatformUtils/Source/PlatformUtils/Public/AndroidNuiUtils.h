// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#if PLATFORM_ANDROID

#include "CoreMinimal.h"
#include "NuiUtils.h"

class FAndroidNuiUtils : public FNuiUtilsBase
{
public:
	FAndroidNuiUtils();
	virtual ~FAndroidNuiUtils();
	virtual void InitNuiSpeech(FString AppKey, FString AccessKeyId, FString AccessKeySecret) override;
	virtual void ReleaseNuiSpeech() override;
	virtual bool StartDialog() override;
	virtual bool StopDialog() override;
	virtual bool CheckDialog() override;
	virtual void ReleaseDialog() override;
	virtual void DialogAudioPermissions() override;
	virtual bool StartTts(FString TtsText) override;
	virtual bool QuitTts() override;
	virtual bool CancelTts() override;
	virtual bool PauseTts() override;
	virtual bool ResumeTts() override;
	virtual bool CheckTts() override;
	virtual void ReleaseTts() override;
	virtual void SetFontNameTts() override;
};

#endif