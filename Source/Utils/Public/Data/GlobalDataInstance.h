// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NuiUtilsHeader.h"
#include "Engine/GameInstance.h"
#include "GlobalDataInstance.generated.h"

UCLASS()
class UTILS_API UGlobalDataInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	virtual void Init() override;

	// UFUNCTION(BlueprintCallable, Category = "NUI")
	// int InitNuiSpeech();
	//
	// UFUNCTION(BlueprintCallable, Category = "NUI")
	// bool CheckNuiInitState();
	//
	// UFUNCTION(BlueprintCallable, Category = "NUI")
	// virtual int OnNuiStart();
	//
	// UFUNCTION(BlueprintCallable, Category = "NUI")
	// virtual int OnNuiStop();
	//
	// UFUNCTION(BlueprintCallable, Category = "NUI")
	// virtual int StartDialog();
	//
	// UFUNCTION(BlueprintCallable, Category = "NUI")
	// virtual int StopDialog();
	//
	// UFUNCTION()
	// void OnNuiEventCallback(ENuiEvent event, int resultCode, int arg2, FKwsResult kwsResult, FAsrResult asrResult);

protected:
	TSharedPtr<FNuiUtils> NuiUtils;
};
