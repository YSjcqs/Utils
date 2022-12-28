// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SpeechWidget.generated.h"

class UNuiSpeechTts;
class UNuiSpeechRecognizer;
/**
 * 
 */
UCLASS()
class UTILS_API USpeechWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeOnInitialized() override;

	UFUNCTION(BlueprintCallable)
	void StartSpeech();

	UFUNCTION(BlueprintCallable)
	void StopSpeech();
	
protected:
	UPROPERTY(BlueprintReadOnly)
	UNuiSpeechRecognizer* SpeechRecognizer;

	UPROPERTY(BlueprintReadOnly)
	UNuiSpeechTts* SpeechTts;
};
