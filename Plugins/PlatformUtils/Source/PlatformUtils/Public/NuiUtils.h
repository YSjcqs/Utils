// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "NuiTypes.h"
#include "NuiUtils.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnNuiErrorDelegate, int, ErrorCode, FString, ErrorMessage);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FiveParams(FOnNuiEventDelegate, int, Event, int, ResultCode, int, Arg2, FKwsResult, KwsResult, FAsrResult, AsrResult);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnNuiAudioStateChangedDelegate, int, State);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnNuiTtsEventDelegate, int, Event, FString, TaskID, int, RetCode, FString, ErrorMsg);

class FNuiSpeechTtsBase;
class FNuiSpeechTranscriberBase;
class FNuiSpeechRecognizerBase;

UCLASS(BlueprintType)
class PLATFORMUTILS_API UNuiSpeechRecognizer : public UObject
{
	GENERATED_BODY()
public:
	UNuiSpeechRecognizer();
	UFUNCTION(BlueprintCallable)
	void Initialize();
	UFUNCTION(BlueprintCallable)
	void Destroy();
	UFUNCTION(BlueprintCallable)
	void RequestPermissionAudio();
	UFUNCTION(BlueprintCallable)
	void SetRecognizerVadMode(bool bVad);
	UFUNCTION(BlueprintCallable)
	void StartDialog();
	UFUNCTION(BlueprintCallable)
	void StopDialog();

	UPROPERTY(BlueprintAssignable)
	FOnNuiErrorDelegate ErrorDelegate;
	UPROPERTY(BlueprintAssignable)
	FOnNuiEventDelegate EventDelegate;
	UPROPERTY(BlueprintAssignable)
	FOnNuiAudioStateChangedDelegate AudioStateChangedDelegate;

private:
	TSharedPtr<FNuiSpeechRecognizerBase> SpeechRecognizerPtr;
};

UCLASS(BlueprintType)
class PLATFORMUTILS_API UNuiSpeechTranscriber : public UObject
{
	GENERATED_BODY()
public:
	UNuiSpeechTranscriber();
	UFUNCTION(BlueprintCallable)
	void Initialize();
	UFUNCTION(BlueprintCallable)
	void Destroy();
	UFUNCTION(BlueprintCallable)
	void RequestPermissionAudio();
	UFUNCTION(BlueprintCallable)
	void SetTranscriberVadMode(bool bVad);
	UFUNCTION(BlueprintCallable)
	void StartDialog();
	UFUNCTION(BlueprintCallable)
	void StopDialog();

	UPROPERTY(BlueprintAssignable)
	FOnNuiErrorDelegate ErrorDelegate;
	UPROPERTY(BlueprintAssignable)
	FOnNuiEventDelegate EventDelegate;
	UPROPERTY(BlueprintAssignable)
	FOnNuiAudioStateChangedDelegate AudioStateChangedDelegate;
private:
	TSharedPtr<FNuiSpeechTranscriberBase> SpeechTranscriberPtr;
};

UCLASS(BlueprintType)
class PLATFORMUTILS_API UNuiSpeechTts : public UObject
{
	GENERATED_BODY()
public:
	UNuiSpeechTts();

	UFUNCTION(BlueprintCallable)
	void Initialize();
	UFUNCTION(BlueprintCallable)
	void Destroy();
	UFUNCTION(BlueprintCallable)
	int StartTts(FString TtsText);
	UFUNCTION(BlueprintCallable)
	int StartEmotionTts(FString TtsText, FString Category, float Intensity = 1.0f, FString Voice = "zhitian_emo");
	UFUNCTION(BlueprintCallable)
	int QuitTts();
	UFUNCTION(BlueprintCallable)
	int CancelTts();
	UFUNCTION(BlueprintCallable)
	int PauseTts();
	UFUNCTION(BlueprintCallable)
	int ResumeTts();
	UFUNCTION(BlueprintCallable)
	int SetParamTts(FString Key, FString Value);

	UPROPERTY(BlueprintAssignable)
	FOnNuiErrorDelegate ErrorDelegate;
	UPROPERTY(BlueprintAssignable)
	FOnNuiTtsEventDelegate TtsEventDelegate;
private:
	TSharedPtr<FNuiSpeechTtsBase> SpeechTtsPtr;
};
