// Fill out your copyright notice in the Description page of Project Settings.


#include "NuiInstance.h"

#include "AndroidNuiUtils.h"
#include "IOSNuiUtils.h"

UNuiInstance* UNuiInstance::NuiInstance = nullptr;

UNuiInstance* UNuiInstance::GetNuiInstance()
{
	if (nullptr == NuiInstance)
	{
		NuiInstance = NewObject<UNuiInstance>();
	}
	return NuiInstance;
}

void UNuiInstance::InitNuiSpeech(FString AppKey, FString AccessKeyId, FString AccessKeySecret)
{
#if PLATFORM_ANDROID
	NuiUtils = MakeShareable(new FAndroidNuiUtils());
#elif PLATFORM_IOS
	NuiUtils = MakeShareable(new FIOSNuiUtils());
#else
	NuiUtils = MakeShareable(new FNuiUtilsBase());
#endif

	NuiUtils->InitNuiSpeech(AppKey, AccessKeyId, AccessKeySecret);
}

void UNuiInstance::ReleaseNuiSpeech()
{
	NuiUtils->ReleaseNuiSpeech();
	NuiUtils = nullptr;
}

bool UNuiInstance::StartDialog()
{
	if (NuiUtils.IsValid())
	{
		NuiUtils->StartDialog();
	}
	return false;
}

bool UNuiInstance::StopDialog()
{
	if (NuiUtils.IsValid())
	{
		NuiUtils->StopDialog();
	}
	return false;
}

bool UNuiInstance::CheckDialog()
{
	if (NuiUtils.IsValid())
	{
		NuiUtils->CheckDialog();
	}
	return false;
}

void UNuiInstance::ReleaseDialog()
{
	if (NuiUtils.IsValid())
	{
		NuiUtils->ReleaseDialog();
	}
}

void UNuiInstance::DialogAudioPermissions()
{
	if (NuiUtils.IsValid())
	{
		NuiUtils->DialogAudioPermissions();
	}
}

bool UNuiInstance::StartTts(FString TtsText)
{
	if (NuiUtils.IsValid())
	{
		NuiUtils->StartTts(TtsText);
	}
	return false;
}

bool UNuiInstance::QuitTts()
{
	if (NuiUtils.IsValid())
	{
		NuiUtils->QuitTts();
	}
	return false;
}

bool UNuiInstance::CancelTts()
{
	if (NuiUtils.IsValid())
	{
		NuiUtils->CancelTts();
	}
	return false;
}

bool UNuiInstance::PauseTts()
{
	if (NuiUtils.IsValid())
	{
		NuiUtils->PauseTts();
	}
	return false;
}

bool UNuiInstance::ResumeTts()
{
	if (NuiUtils.IsValid())
	{
		NuiUtils->ResumeTts();
	}
	return false;
}

bool UNuiInstance::CheckTts()
{
	if (NuiUtils.IsValid())
	{
		NuiUtils->CheckTts();
	}
	return false;
}

void UNuiInstance::ReleaseTts()
{
	if (NuiUtils.IsValid())
	{
		NuiUtils->ReleaseTts();
	}
}

void UNuiInstance::SetFontNameTts()
{
	if (NuiUtils.IsValid())
	{
		NuiUtils->SetFontNameTts();
	}
}
