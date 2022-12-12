// Fill out your copyright notice in the Description page of Project Settings.


#include "IOSNuiUtils.h"

void FIOSNuiUtils::InitNuiSpeech()
{
	FGenericPlatformNuiUtils::InitNuiSpeech();
}

void FIOSNuiUtils::ReleaseNuiSpeech()
{
	FGenericPlatformNuiUtils::ReleaseNuiSpeech();
}

bool FIOSNuiUtils::StartDialog()
{
	return FGenericPlatformNuiUtils::StartDialog();
}

bool FIOSNuiUtils::StopDialog()
{
	return FGenericPlatformNuiUtils::StopDialog();
}

bool FIOSNuiUtils::CheckDialog()
{
	return FGenericPlatformNuiUtils::CheckDialog();
}

void FIOSNuiUtils::DialogAudioPermissions()
{
	FGenericPlatformNuiUtils::DialogAudioPermissions();
}

bool FIOSNuiUtils::StartTts(FString TtsText)
{
	return FGenericPlatformNuiUtils::StartTts(TtsText);
}

bool FIOSNuiUtils::QuitTts()
{
	return FGenericPlatformNuiUtils::QuitTts();
}

bool FIOSNuiUtils::CancelTts()
{
	return FGenericPlatformNuiUtils::CancelTts();
}

bool FIOSNuiUtils::PauseTts()
{
	return FGenericPlatformNuiUtils::PauseTts();
}

bool FIOSNuiUtils::ResumeTts()
{
	return FGenericPlatformNuiUtils::ResumeTts();
}

bool FIOSNuiUtils::CheckTts()
{
	return FGenericPlatformNuiUtils::CheckTts();
}
