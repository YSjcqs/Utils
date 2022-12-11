// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/GlobalDataInstance.h"

#include "PlatformUtils.h"


void UGlobalDataInstance::Init()
{
	Super::Init();
	if (FPlatformUtilsModule* Module = FModuleManager::LoadModulePtr<
		FPlatformUtilsModule>(FName(TEXT("PlatformUtils"))))
	{
		NuiUtils = Module->GetNuiUtils();
		NuiUtils->InitNuiSpeech();
		NuiUtils->NuiEventDelegate.AddUObject(this, &UGlobalDataInstance::OnNuiEventCallback);
		NuiUtils->OnNuiStart();
	}
}

int UGlobalDataInstance::InitNuiSpeech()
{
	if (NuiUtils.IsValid())
	{
		return NuiUtils->InitNuiSpeech();
	}
	return -1;
}

bool UGlobalDataInstance::CheckNuiInitState()
{
	if (NuiUtils.IsValid())
	{
		return NuiUtils->CheckNuiInitState();
	}
	return false;
}

int UGlobalDataInstance::OnNuiStart()
{
	if (NuiUtils.IsValid())
	{
		return NuiUtils->OnNuiStart();
	}
	return -1;
}

int UGlobalDataInstance::OnNuiStop()
{
	if (NuiUtils.IsValid())
	{
		return NuiUtils->OnNuiStop();
	}
	return -1;
}

int UGlobalDataInstance::StartDialog()
{
	if (NuiUtils.IsValid())
	{
		return NuiUtils->StartDialog();
	}
	return -1;
}

int UGlobalDataInstance::StopDialog()
{
	if (NuiUtils.IsValid())
	{
		return NuiUtils->StopDialog();
	}
	return -1;
}

void UGlobalDataInstance::OnNuiEventCallback(ENuiEvent event, int resultCode, int arg2, FKwsResult kwsResult,
	FAsrResult asrResult)
{
	if (event == ENuiEvent::EVENT_TRANSCRIBER_COMPLETE)
	{
		GEngine->AddOnScreenDebugMessage(-1, 30.f, FColor::Yellow, FString::FromInt(static_cast<int>(event)));
	}
	else if(event == ENuiEvent::EVENT_ASR_PARTIAL_RESULT || event == ENuiEvent::EVENT_SENTENCE_END)
	{
		GEngine->AddOnScreenDebugMessage(-1, 30.f, FColor::Yellow, asrResult.AsrResult);
	}
	else if(event == ENuiEvent::EVENT_ASR_ERROR)
	{
		GEngine->AddOnScreenDebugMessage(-1, 30.f, FColor::Red, kwsResult.Kws + FString::FromInt(resultCode));
	}
}
