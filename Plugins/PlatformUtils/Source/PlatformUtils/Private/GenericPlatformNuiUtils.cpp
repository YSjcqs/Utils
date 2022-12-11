// Fill out your copyright notice in the Description page of Project Settings.


#include "GenericPlatformNuiUtils.h"

DEFINE_LOG_CATEGORY(LogNuiDebug)

FGenericPlatformNuiUtils::FGenericPlatformNuiUtils()
{
}

void FGenericPlatformNuiUtils::NulDebugLog(FString DebugMessage, int TimeToDisplay)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, TimeToDisplay, FColor::Yellow, DebugMessage);
	}
	UE_LOG(LogNuiDebug, Warning, TEXT("%s"), *DebugMessage);
}