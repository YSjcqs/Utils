// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GenericPlatformNuiUtils.generated.h"

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
enum class EWuwType : uint8
{
	TYPE_UNKNOWN = static_cast<uint8>(-1),
	TYPE_MAIN = 0,
	TYPE_ACTION = 1,
	TYPE_PREFIX = 2,
	TYPE_DANAMIC = 3,
	TYPE_ONESHOT = 4
};

USTRUCT(BlueprintType)
struct PLATFORMUTILS_API FKwsResult
{
	GENERATED_BODY()

public:
	EWuwType Type;
	FString Kws;

	FKwsResult(): Type(EWuwType::TYPE_UNKNOWN)
	{
	}

	FKwsResult(int type, FString kws)
	{
		Type = static_cast<EWuwType>(type);
		Kws = kws;
	}
};

USTRUCT(BlueprintType)
struct PLATFORMUTILS_API FAsrResult
{
	GENERATED_BODY()

public:
	bool bFinish;
	int ResultCode;
	FString AsrResult;

	FAsrResult(): bFinish(false), ResultCode(-1)
	{
	}

	FAsrResult(bool finish, int resultCode, FString result)
	{
		bFinish = finish;
		ResultCode = resultCode;
		AsrResult = result;
	}
};

DECLARE_MULTICAST_DELEGATE_FiveParams(FNuiEventDelegate, ENuiEvent, int, int, FKwsResult, FAsrResult);
DECLARE_MULTICAST_DELEGATE_OneParam(FNuiAudioStateChangedDelegate, EAudioState);
DECLARE_MULTICAST_DELEGATE_OneParam(FNuiAudioRMSChangedDelegate, float);
DECLARE_MULTICAST_DELEGATE_OneParam(FNuiVprEventCallbackDelegate, ENuiEvent);

struct PLATFORMUTILS_API INativeNuiCallback
{
public:
	virtual ~INativeNuiCallback()
	{
	}

	virtual void onNuiEventCallback(ENuiEvent event, int resultCode, int arg2, FKwsResult kwsResult,
	                                FAsrResult asrResult)
	{
		NuiEventDelegate.Broadcast(event, resultCode, arg2, kwsResult, asrResult);
	}

	// UE不处理该接口，全权由平台自己处理
	virtual void onNuiNeedAudioData(char* buffer, int var2)
	{
	};

	virtual void onNuiAudioStateChanged(EAudioState var1)
	{
		NuiAudioStateChangedDelegate.Broadcast(var1);
	}

	virtual void onNuiAudioRMSChanged(float var1)
	{
		NuiAudioRMSChangedDelegate.Broadcast(var1);
	}

	virtual void onNuiVprEventCallback(ENuiEvent var1)
	{
		NuiVprEventCallbackDelegate.Broadcast(var1);
	}

	FNuiEventDelegate NuiEventDelegate;
	FNuiAudioStateChangedDelegate NuiAudioStateChangedDelegate;
	FNuiAudioRMSChangedDelegate NuiAudioRMSChangedDelegate;
	FNuiVprEventCallbackDelegate NuiVprEventCallbackDelegate;
};

struct PLATFORMUTILS_API FGenericPlatformNuiUtils : public INativeNuiCallback
{
public:
	static void NulDebugLog(FString DebugMessage, int TimeToDisplay = 30.f);

public:
	FGenericPlatformNuiUtils();

	virtual ~FGenericPlatformNuiUtils()
	{
	}

	virtual int InitNuiSpeech()
	{
		return -1;
	}

	virtual bool CheckNuiInitState()
	{
		return false;
	}

	virtual int OnNuiStart()
	{
		return -1;
	}

	virtual int OnNuiStop()
	{
		return -1;
	}

	virtual int StartDialog()
	{
		return -1;
	}

	virtual int StopDialog()
	{
		return -1;
	}

protected:
	bool bSaveLog = true;
	ENuiLogLevel NuiLogLevel = ENuiLogLevel::LOG_LEVEL_VERBOSE;
	ENuiVadMode NuiVadMode = ENuiVadMode::MODE_P2T;
	FString NuiUrl = TEXT("wss://nls-gateway.cn-shanghai.aliyuncs.com:443/ws/v1");
	FString AppKey = TEXT("J8PkaDSNkxymRdPh");
	FString AppToken = TEXT("a54492ca01a349938ff5636f9942889e");

	// const char* const AccessKeyId = "LTAI5tQqNzJRwYnMMinoAuUN";
	// const char* const AccessKeySecret = "R9wuHhUQmocckKPIAS3HxXuLqIeWUw";
};
