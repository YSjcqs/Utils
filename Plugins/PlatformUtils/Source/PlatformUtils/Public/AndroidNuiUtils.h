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
	virtual void StartDialog() override;
	virtual void StopDialog() override;
	virtual int ReleaseDialog() override;
	virtual bool CheckDialog() override;
	virtual void DialogAudioPermissions() override;
	virtual int GetCurrentHandleCode() override;
	virtual int StartTts(FString TtsText) override;
	virtual int QuitTts() override;
	virtual int CancelTts() override;
	virtual int PauseTts() override;
	virtual int ResumeTts() override;
	virtual bool CheckTts() override;
	virtual int ReleaseTts() override;
	virtual int SetFontNameTts(FString Name) override;
};

#endif