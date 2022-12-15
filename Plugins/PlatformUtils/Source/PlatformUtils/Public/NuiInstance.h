// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "NuiUtils.h"
#include "NuiInstance.generated.h"

// 禁止在改下委托中修改UI数据
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FDialogEventCallbackDelegate, ENuiEvent, NuiEvent, int, ResultCode, FString, AsrString);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDialogAudioStateChangedDelegate, EAudioState, AudioState);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDialogAudioRMSChangedDelegate, float, Value);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDialogVprEventCallbackDelegate, ENuiVprEvent, NuiVprEvent);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FTtsEventCallbackDelegate, ETtsEvent, TtsEvent, FString, TaskID, int, ResultCode);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTtsVolCallbackDelegate, int, Value);


UCLASS(Blueprintable, BlueprintType)
class PLATFORMUTILS_API UNuiInstance : public UObject
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	static UNuiInstance* GetNuiInstance();

	FORCEINLINE void OnDialogEventCallback(ENuiEvent NuiEvent, int ResultCode, FString AsrString)
	{
		DialogEventCallbackDelegate.Broadcast(NuiEvent, ResultCode, AsrString);
	}

	FORCEINLINE void OnDialogAudioStateChanged(EAudioState AudioState)
	{
		DialogAudioStateChangedDelegate.Broadcast(AudioState);
	}

	FORCEINLINE void OnDialogAudioRMSChanged(float Value)
	{
		DialogAudioRmsChangedDelegate.Broadcast(Value);
	}

	FORCEINLINE void OnDialogVprEventCallback(ENuiVprEvent NuiVprEvent)
	{
		DialogVprEventCallbackDelegate.Broadcast(NuiVprEvent);
	}
	
	FORCEINLINE void OnTtsEventCallback(ETtsEvent TtsEvent, FString TaskID, int ResultCode)
	{
		TtsEventCallbackDelegate.Broadcast(TtsEvent, TaskID, ResultCode);
	}

	FORCEINLINE void OnTtsVolCallback(int Vol)
	{
		TtsVolCallbackDelegate.Broadcast(Vol);
	}
	
	UFUNCTION(BlueprintCallable, Category = "Nui")
	void InitNuiSpeech(FString AppKey, FString AccessKeyId, FString AccessKeySecret);
	UFUNCTION(BlueprintCallable, Category = "Nui")
	void ReleaseNuiSpeech();
	
	UFUNCTION(BlueprintCallable, Category = "Nui|Dialog")
	void StartDialog();
	UFUNCTION(BlueprintCallable, Category = "Nui|Dialog")
	void StopDialog();
	UFUNCTION(BlueprintCallable, Category = "Nui|Dialog")
	bool CheckDialog();
	UFUNCTION(BlueprintCallable, Category = "Nui|Dialog")
	int ReleaseDialog();
	UFUNCTION(BlueprintCallable, Category = "Nui|Dialog")
	void DialogAudioPermissions();
	UFUNCTION(BlueprintCallable, Category = "Nui|Dialog")
	int GetCurrentHandleCode();

	UFUNCTION(BlueprintCallable, Category = "Nui|Tts")
	int StartTts(FString TtsText);
	UFUNCTION(BlueprintCallable, Category = "Nui|Tts")
	int QuitTts();
	UFUNCTION(BlueprintCallable, Category = "Nui|Tts")
	int CancelTts();
	UFUNCTION(BlueprintCallable, Category = "Nui|Tts")
	int PauseTts();
	UFUNCTION(BlueprintCallable, Category = "Nui|Tts")
	int ResumeTts();
	UFUNCTION(BlueprintCallable, Category = "Nui|Tts")
	bool CheckTts();
	UFUNCTION(BlueprintCallable, Category = "Nui|Tts")
	int ReleaseTts();
	UFUNCTION(BlueprintCallable, Category = "Nui|Tts")
	int SetFontNameTts(FString Name);

	UPROPERTY(BlueprintAssignable)
	FDialogEventCallbackDelegate DialogEventCallbackDelegate;
	UPROPERTY(BlueprintAssignable)
	FDialogAudioStateChangedDelegate DialogAudioStateChangedDelegate;
	UPROPERTY(BlueprintAssignable)
	FDialogAudioRMSChangedDelegate DialogAudioRmsChangedDelegate;
	UPROPERTY(BlueprintAssignable)
	FDialogVprEventCallbackDelegate DialogVprEventCallbackDelegate;
	
	UPROPERTY(BlueprintAssignable)
	FTtsEventCallbackDelegate TtsEventCallbackDelegate;
	UPROPERTY(BlueprintAssignable)
	FTtsVolCallbackDelegate TtsVolCallbackDelegate;
	
private:
	static UNuiInstance* NuiInstance;
	TSharedPtr<FNuiUtilsBase> NuiUtils;
};
