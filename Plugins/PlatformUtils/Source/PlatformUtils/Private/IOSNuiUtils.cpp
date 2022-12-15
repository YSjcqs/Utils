// Fill out your copyright notice in the Description page of Project Settings.
#if PLATFORM_IOS

#include "IOSNuiUtils.h"

FIOSNuiUtils::~FIOSNuiUtils() {}

void FIOSNuiUtils::StartDialog()
{
	FNuiUtilsBase::StartDialog();
}

void FIOSNuiUtils::StopDialog()
{
	FNuiUtilsBase::StopDialog();
}

int FIOSNuiUtils::ReleaseDialog()
{
	return FNuiUtilsBase::ReleaseDialog();
}

bool FIOSNuiUtils::CheckDialog()
{
	return FNuiUtilsBase::CheckDialog();
}

void FIOSNuiUtils::DialogAudioPermissions()
{
	FNuiUtilsBase::DialogAudioPermissions();
}

int FIOSNuiUtils::GetCurrentHandleCode()
{
	return FNuiUtilsBase::GetCurrentHandleCode();
}

int FIOSNuiUtils::StartTts(FString TtsText)
{
	return FNuiUtilsBase::StartTts(TtsText);
}

int FIOSNuiUtils::QuitTts()
{
	return FNuiUtilsBase::QuitTts();
}

int FIOSNuiUtils::CancelTts()
{
	return FNuiUtilsBase::CancelTts();
}

int FIOSNuiUtils::PauseTts()
{
	return FNuiUtilsBase::PauseTts();
}

int FIOSNuiUtils::ResumeTts()
{
	return FNuiUtilsBase::ResumeTts();
}

bool FIOSNuiUtils::CheckTts()
{
	return FNuiUtilsBase::CheckTts();
}

int FIOSNuiUtils::ReleaseTts()
{
	return FNuiUtilsBase::ReleaseTts();
}

int FIOSNuiUtils::SetFontNameTts(FString Name)
{
	return FNuiUtilsBase::SetFontNameTts(Name);
}

void FIOSNuiUtils::InitNuiSpeech(FString AppKey, FString AccessKeyId, FString AccessKeySecret)
{
}

void FIOSNuiUtils::ReleaseNuiSpeech()
{
}

#endif