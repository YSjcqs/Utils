// Fill out your copyright notice in the Description page of Project Settings.


#include "IOSNuiUtils.h"

int FIOSNuiUtils::InitNuiSpeech()
{
	return FGenericPlatformNuiUtils::InitNuiSpeech();
}

bool FIOSNuiUtils::CheckNuiInitState()
{
	return FGenericPlatformNuiUtils::CheckNuiInitState();
}

int FIOSNuiUtils::OnNuiStart()
{
	return FGenericPlatformNuiUtils::OnNuiStart();
}

int FIOSNuiUtils::OnNuiStop()
{
	return FGenericPlatformNuiUtils::OnNuiStop();
}

int FIOSNuiUtils::StartDialog()
{
	return FGenericPlatformNuiUtils::StartDialog();
}

int FIOSNuiUtils::StopDialog()
{
	return FGenericPlatformNuiUtils::StopDialog();
}
