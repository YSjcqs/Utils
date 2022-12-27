#pragma once
#include "NuiTypes.h"


DECLARE_DELEGATE_TwoParams(FOnRecognizerErrorDelegate, int, FString);
DECLARE_DELEGATE_FiveParams(FOnRecognizerEventDelegate, int, int, int, FKwsResult, FAsrResult);
DECLARE_DELEGATE_OneParam(FOnRecognizerAudioStateChangedDelegate, int);
class FNuiSpeechRecognizerBase
{
public:
	FNuiSpeechRecognizerBase(){}
	virtual ~FNuiSpeechRecognizerBase() {}
	virtual void Initialize() = 0;
	virtual void Destroy() = 0;
	virtual void RequestPermissionAudio() = 0;
	virtual void SetRecognizerVadMode(bool bVad) = 0;
	virtual void StartDialog() = 0;
	virtual void StopDialog() = 0;
	
	FOnRecognizerErrorDelegate OnRecognizerErrorDelegate;
	FOnRecognizerEventDelegate OnRecognizerEventDelegate;
	FOnRecognizerAudioStateChangedDelegate OnRecognizerAudioStateChangedDelegate;
};

DECLARE_DELEGATE_TwoParams(FOnTranscriberErrorDelegate, int, FString);
DECLARE_DELEGATE_FiveParams(FOnTranscriberEventDelegate, int, int, int, FKwsResult, FAsrResult);
DECLARE_DELEGATE_OneParam(FOnTranscriberAudioStateChangedDelegate, int);
class FNuiSpeechTranscriberBase
{
public:
	FNuiSpeechTranscriberBase(){}
	virtual ~FNuiSpeechTranscriberBase() {}
	virtual void Initialize() = 0;
	virtual void Destroy() = 0;
	virtual void RequestPermissionAudio() = 0;
	virtual void SetTranscriberVadMode(bool bVad) = 0;
	virtual void StartDialog() = 0;
	virtual void StopDialog() = 0;

	FOnTranscriberErrorDelegate OnTranscriberErrorDelegate;
	FOnTranscriberEventDelegate OnTranscriberEventDelegate;
	FOnTranscriberAudioStateChangedDelegate OnTranscriberAudioStateChangedDelegate;
};


DECLARE_DELEGATE_TwoParams(FOnTtsErrorDelegate, int, FString);
DECLARE_DELEGATE_FourParams(FOnTtsEventDelegate, int, FString, int, FString);
class FNuiSpeechTtsBase
{
public:
	FNuiSpeechTtsBase(){}
	virtual ~FNuiSpeechTtsBase() {}
	virtual void Initialize() = 0;
	virtual void Destroy() = 0;
	virtual int StartTts(FString TtsText) = 0;
	virtual int QuitTts() = 0;
	virtual int CancelTts() = 0;
	virtual int PauseTts() = 0;
	virtual int ResumeTts() = 0;
	virtual int SetParamTts(FString Key, FString Value) = 0;

	FOnTtsErrorDelegate OnTtsErrorDelegate;
	FOnTtsEventDelegate OnTtsEventDelegate;
};