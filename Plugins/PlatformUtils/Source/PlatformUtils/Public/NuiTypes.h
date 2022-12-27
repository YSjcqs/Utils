// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NuiTypes.generated.h"


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


USTRUCT(BlueprintType)
struct FKwsResult
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly)
	int Type;
	UPROPERTY(BlueprintReadOnly)
	FString Kws;

	FKwsResult() : Type(-1) {}
	FKwsResult(int type, FString kws) :
		Type(type), Kws(kws)
	{
	}
};

USTRUCT(BlueprintType)
struct FAsrResult
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly)
	bool Finish;
	UPROPERTY(BlueprintReadOnly)
	int ResultCode;
	UPROPERTY(BlueprintReadOnly)
	FString AsrString;

	FAsrResult() : Finish(false), ResultCode(-1) {}
	FAsrResult(bool finish, int resultCode, FString result) :
		Finish(finish), ResultCode(resultCode), AsrString(result)
	{
	}
};
