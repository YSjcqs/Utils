// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "NuiUtils.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogNuiDebug, Log, All);

UENUM(BlueprintType)
enum class ENuiVadMode : uint8
{
	MODE_VAD,
	MODE_P2T,
	MODE_KWS,
	MODE_PARALLEL,
	MODE_KWS2PARALLEL,
	MODE_AUTO_CONTINUAL,
	MODE_KWS_CONTINUAL,
	MODE_KWS2TALK
};

UENUM(BlueprintType)
enum class ENuiLogLevel : uint8
{
	LOG_LEVEL_VERBOSE,
	LOG_LEVEL_DEBUG,
	LOG_LEVEL_INFO,
	LOG_LEVEL_WARNING,
	LOG_LEVEL_ERROR,
	LOG_LEVEL_NONE
};

UENUM(BlueprintType)
enum class EAudioState : uint8
{
	STATE_OPEN,
	STATE_PAUSE,
	STATE_CLOSE
};

UENUM(BlueprintType)
enum class ENuiEvent : uint8
{
	EVENT_VAD_START,
	EVENT_VAD_TIMEOUT,
	EVENT_VAD_END,
	EVENT_WUW,
	EVENT_WUW_TRUSTED,
	EVENT_WUW_CONFIRMED,
	EVENT_WUW_REJECTED,
	EVENT_WUW_END,
	EVENT_ASR_PARTIAL_RESULT,
	EVENT_ASR_RESULT,
	EVENT_ASR_ERROR,
	EVENT_DIALOG_ERROR,
	EVENT_ONESHOT_TIMEOUT,
	EVENT_DIALOG_RESULT,
	EVENT_WUW_HINT,
	EVENT_VPR_RESULT,
	EVENT_TEXT2ACTION_DIALOG_RESULT,
	EVENT_TEXT2ACTION_ERROR,
	EVENT_ATTR_RESULT,
	EVENT_MIC_ERROR,
	EVENT_DIALOG_EX,
	EVENT_WUW_ERROR,
	EVENT_BEFORE_CONNECTION,
	EVENT_SENTENCE_START,
	EVENT_SENTENCE_END,
	EVENT_SENTENCE_SEMANTICS,
	EVENT_TRANSCRIBER_COMPLETE,
	EVENT_FILE_TRANS_CONNECTED,
	EVENT_FILE_TRANS_UPLOADED,
	EVENT_FILE_TRANS_RESULT,
	EVENT_FILE_TRANS_UPLOAD_PROGRESS
};

UENUM(BlueprintType)
enum class ENuiVprEvent : uint8
{
	EVENT_VPR_NONE = 0,
	EVENT_VPR_REGISTER_START,
	EVENT_VPR_REGISTER_DONE,
	EVENT_VPR_REGISTER_FAILED,
	EVENT_VPR_UPDATE_START,
	EVENT_VPR_UPDATE_DONE,
	EVENT_VPR_UPDATE_FAIL,
	EVENT_VPR_DELETE_DONE,
	EVENT_VPR_DELETE_FAIL,
	DEFAULT_ERROR
};

UENUM(BlueprintType)
enum class EWuwType : uint8
{
	TYPE_UNKNOWN = static_cast<uint8>(-1),
	TYPE_MAIN = 0,
	TYPE_ACTION = 1,
	TYPE_PREFIX = 2,
	TYPE_DANAMIC = 3,
	TYPE_ONESHOT = 4
};

UENUM(BlueprintType)
enum class ETtsEvent : uint8
{
	TTS_EVENT_START = 0,
	TTS_EVENT_END = 1,
	TTS_EVENT_CANCEL = 2,
	TTS_EVENT_PAUSE = 3,
	TTS_EVENT_RESUME = 4,
	TTS_EVENT_ERROR = 5
};

// package com.epicgames.unreal.speechrec;->NuiSpeechManager
// public static native void DialogEventCallback(int NuiEvent, int resultCode, String asrString);
// public static native void DialogAudioStateChanged(int var1);
// public static native void DialogAudioRMSChanged(float var1);
// public static native void DialogVprEventCallback(int var1);
//
// public static native void TtsEventCallback(int var1, String var2, int var3);
// public static native void TtsVolCallback(int var1);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FDialogEventCallbackDelegate, ENuiEvent, NuiEvent, int, ResultCode, FString, AsrString);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDialogAudioStateChangedDelegate, EAudioState, AudioState);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDialogAudioRMSChangedDelegate, float, Value);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDialogVprEventCallbackDelegate, ENuiVprEvent, NuiVprEvent);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FTtsEventCallbackDelegate, ETtsEvent, TtsEvent, FString, TaskID, int, ResultCode);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTtsVolCallbackDelegate, int, Value);


UCLASS(Abstract)
class PLATFORMUTILS_API UNuiUtils : public UObject
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Nui")
	void InitNuiSpeech();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Nui")
	void ReleaseNuiSpeech();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Access")
	FString AppKey = TEXT("J8PkaDSNkxymRdPh");
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Access")
	FString AccessKeyId = TEXT("LTAI5tQqNzJRwYnMMinoAuUN");
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Access")
	FString AccessKeySecret = TEXT("R9wuHhUQmocckKPIAS3HxXuLqIeWUw");
};

UCLASS()
class PLATFORMUTILS_API UNuiDialogUtilsBase : public UNuiUtils
{
	GENERATED_BODY()
public:
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
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Nui|Dialog")
	bool StartDialog();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Nui|Dialog")
	bool StopDialog();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Nui|Dialog")
	bool CheckDialog();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Nui|Dialog")
	void ReleaseDialog();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Nui|Dialog")
	void DialogAudioPermissions();

	UPROPERTY(BlueprintAssignable)
	FDialogEventCallbackDelegate DialogEventCallbackDelegate;
	UPROPERTY(BlueprintAssignable)
	FDialogAudioStateChangedDelegate DialogAudioStateChangedDelegate;
	UPROPERTY(BlueprintAssignable)
	FDialogAudioRMSChangedDelegate DialogAudioRmsChangedDelegate;
	UPROPERTY(BlueprintAssignable)
	FDialogVprEventCallbackDelegate DialogVprEventCallbackDelegate;
};


UCLASS()
class PLATFORMUTILS_API UNuiTtsUtilsBase : public UNuiUtils
{
	GENERATED_BODY()
public:

	FORCEINLINE void OnTtsEventCallback(ETtsEvent TtsEvent, FString TaskID, int ResultCode)
	{
		TtsEventCallbackDelegate.Broadcast(TtsEvent, TaskID, ResultCode);
	}

	FORCEINLINE void OnTtsVolCallback(int Vol)
	{
		TtsVolCallbackDelegate.Broadcast(Vol);
	}

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Nui|Tts")
	bool StartTts(FString TtsText);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Nui|Tts")
	bool QuitTts();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Nui|Tts")
	bool CancelTts();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Nui|Tts")
	bool PauseTts();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Nui|Tts")
	bool ResumeTts();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Nui|Tts")
	bool CheckTts();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Nui|Tts")
	void ReleaseTts();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Nui|Tts")
	void SetFontNameTts();
	
	UPROPERTY(BlueprintAssignable)
	FTtsEventCallbackDelegate TtsEventCallbackDelegate;
	UPROPERTY(BlueprintAssignable)
	FTtsVolCallbackDelegate TtsVolCallbackDelegate;
};
