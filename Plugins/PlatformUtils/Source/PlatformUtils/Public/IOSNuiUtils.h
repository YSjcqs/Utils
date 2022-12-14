// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NuiUtils.h"
#include "IOSNuiUtils.generated.h"

UCLASS()
class PLATFORMUTILS_API UIOSNuiDialogUtils : public UNuiDialogUtilsBase
{
	GENERATED_BODY()

public:
	virtual void InitNuiSpeech_Implementation() override;
	virtual void ReleaseNuiSpeech_Implementation() override;
	
	virtual bool StartDialog_Implementation() override;
	virtual bool StopDialog_Implementation() override;
	virtual bool CheckDialog_Implementation() override;
	virtual void ReleaseDialog_Implementation() override;
	virtual void DialogAudioPermissions_Implementation() override;
};

UCLASS()
class PLATFORMUTILS_API UIOSNuiTtsUtils : public UNuiTtsUtilsBase
{
	GENERATED_BODY()

public:
	virtual void InitNuiSpeech_Implementation() override;
	virtual void ReleaseNuiSpeech_Implementation() override;
	
	virtual bool CancelTts_Implementation() override;
	virtual bool CheckTts_Implementation() override;
	virtual bool PauseTts_Implementation() override;
	virtual bool QuitTts_Implementation() override;
	virtual void ReleaseTts_Implementation() override;
	virtual bool ResumeTts_Implementation() override;
	virtual void SetFontNameTts_Implementation() override;
	virtual bool StartTts_Implementation(FString TtsText) override;
};