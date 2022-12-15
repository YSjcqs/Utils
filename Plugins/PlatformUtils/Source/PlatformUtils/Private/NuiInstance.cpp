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

void UNuiInstance::StartDialog()
{
	if (NuiUtils.IsValid())
	{
		NuiUtils->StartDialog();
	}
}

void UNuiInstance::StopDialog()
{
	if (NuiUtils.IsValid())
	{
		NuiUtils->StopDialog();
	}
}

bool UNuiInstance::CheckDialog()
{
	if (NuiUtils.IsValid())
	{
		return NuiUtils->CheckDialog();
	}
	return false;
}

int UNuiInstance::ReleaseDialog()
{
	if (NuiUtils.IsValid())
	{
		return NuiUtils->ReleaseDialog();
	}
	return -1;
}

void UNuiInstance::DialogAudioPermissions()
{
	if (NuiUtils.IsValid())
	{
		NuiUtils->DialogAudioPermissions();
	}
}

int UNuiInstance::GetCurrentHandleCode()
{
	if (NuiUtils.IsValid())
	{
		return NuiUtils->GetCurrentHandleCode();
	}
	return -1;
}

int UNuiInstance::StartTts(FString TtsText)
{
	if (NuiUtils.IsValid())
	{
		return NuiUtils->StartTts(TtsText);
	}
	return -1;
}

int UNuiInstance::QuitTts()
{
	if (NuiUtils.IsValid())
	{
		return NuiUtils->QuitTts();
	}
	return -1;
}

int UNuiInstance::CancelTts()
{
	if (NuiUtils.IsValid())
	{
		return NuiUtils->CancelTts();
	}
	return -1;
}

int UNuiInstance::PauseTts()
{
	if (NuiUtils.IsValid())
	{
		return NuiUtils->PauseTts();
	}
	return -1;
}

int UNuiInstance::ResumeTts()
{
	if (NuiUtils.IsValid())
	{
		return NuiUtils->ResumeTts();
	}
	return -1;
}

bool UNuiInstance::CheckTts()
{
	if (NuiUtils.IsValid())
	{
		return NuiUtils->CheckTts();
	}
	return false;
}

int UNuiInstance::ReleaseTts()
{
	if (NuiUtils.IsValid())
	{
		return NuiUtils->ReleaseTts();
	}
	return -1;
}

int UNuiInstance::SetFontNameTts(FString Name)
{
	if (NuiUtils.IsValid())
	{
		return NuiUtils->SetFontNameTts(Name);
	}
	return -1;
}
