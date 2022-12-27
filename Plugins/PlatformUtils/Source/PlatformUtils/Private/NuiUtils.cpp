// Fill out your copyright notice in the Description page of Project Settings.


#include "NuiUtils.h"

#include "Android/AndroidSpeechRecognizer.h"
#include "Android/AndroidSpeechTranscriber.h"
#include "Android/AndroidSpeechTts.h"
#include "OtherPlatform/OtherSpeechRecognizer.h"
#include "OtherPlatform/OtherSpeechTranscriber.h"
#include "OtherPlatform/OtherSpeechTts.h"

UNuiSpeechRecognizer::UNuiSpeechRecognizer()
{
#if PLATFORM_ANDROID
	SpeechRecognizerPtr = MakeShareable(new FAndroidSpeechRecognizer);
#else
	SpeechRecognizerPtr = MakeShareable(new FOtherSpeechRecognizer);
#endif
	SpeechRecognizerPtr->OnRecognizerErrorDelegate.BindLambda([this](int ErrorCode, FString ErrorMessage)
	{
		ErrorDelegate.Broadcast(ErrorCode, ErrorMessage);
	});
	SpeechRecognizerPtr->OnRecognizerEventDelegate.BindLambda([this](int Event, int ResultCode, int Arg2, FKwsResult KwsResult, FAsrResult AsrResult)
	{
		EventDelegate.Broadcast(Event, ResultCode, Arg2, KwsResult, AsrResult);
	});
	SpeechRecognizerPtr->OnRecognizerAudioStateChangedDelegate.BindLambda([this](int State)
	{
		AudioStateChangedDelegate.Broadcast(State);
	});
}

void UNuiSpeechRecognizer::Initialize()
{
	SpeechRecognizerPtr->Initialize();
}

void UNuiSpeechRecognizer::Destroy()
{
	SpeechRecognizerPtr->Destroy();
}

void UNuiSpeechRecognizer::RequestPermissionAudio()
{
	SpeechRecognizerPtr->RequestPermissionAudio();
}

void UNuiSpeechRecognizer::SetRecognizerVadMode(bool bVad)
{
	SpeechRecognizerPtr->SetRecognizerVadMode(bVad);
}

void UNuiSpeechRecognizer::StartDialog()
{
	SpeechRecognizerPtr->StartDialog();
}

void UNuiSpeechRecognizer::StopDialog()
{
	SpeechRecognizerPtr->StopDialog();
}

UNuiSpeechTranscriber::UNuiSpeechTranscriber()
{
#if PLATFORM_ANDROID
	SpeechTranscriberPtr = MakeShareable(new FAndroidSpeechTranscriber);
#else
	SpeechTranscriberPtr = MakeShareable(new FOtherSpeechTranscriber);
#endif
	SpeechTranscriberPtr->OnTranscriberErrorDelegate.BindLambda([this](int ErrorCode, FString ErrorMessage)
	{
		ErrorDelegate.Broadcast(ErrorCode, ErrorMessage);
	});
	SpeechTranscriberPtr->OnTranscriberEventDelegate.BindLambda([this](int Event, int ResultCode, int Arg2, FKwsResult KwsResult, FAsrResult AsrResult)
	{
		EventDelegate.Broadcast(Event, ResultCode, Arg2, KwsResult, AsrResult);
	});
	SpeechTranscriberPtr->OnTranscriberAudioStateChangedDelegate.BindLambda([this](int State)
	{
		AudioStateChangedDelegate.Broadcast(State);
	});
}

void UNuiSpeechTranscriber::Initialize()
{
	SpeechTranscriberPtr->Initialize();
}

void UNuiSpeechTranscriber::Destroy()
{
	SpeechTranscriberPtr->Destroy();
}

void UNuiSpeechTranscriber::RequestPermissionAudio()
{
	SpeechTranscriberPtr->RequestPermissionAudio();
}

void UNuiSpeechTranscriber::SetTranscriberVadMode(bool bVad)
{
	SpeechTranscriberPtr->SetTranscriberVadMode(bVad);
}

void UNuiSpeechTranscriber::StartDialog()
{
	SpeechTranscriberPtr->StartDialog();
}

void UNuiSpeechTranscriber::StopDialog()
{
	SpeechTranscriberPtr->StopDialog();
}

UNuiSpeechTts::UNuiSpeechTts()
{
#if PLATFORM_ANDROID
	SpeechTtsPtr = MakeShareable(new FAndroidSpeechTts);
#else
	SpeechTtsPtr = MakeShareable(new FOtherSpeechTts);
#endif
	SpeechTtsPtr->OnTtsErrorDelegate.BindLambda([this](int ErrorCode, FString ErrorMessage)
	{
		ErrorDelegate.Broadcast(ErrorCode, ErrorMessage);
	});
	SpeechTtsPtr->OnTtsEventDelegate.BindLambda([this](int Event, FString TaskID, int RetCode, FString ErrorMsg)
	{
		TtsEventDelegate.Broadcast(Event, TaskID, RetCode, ErrorMsg);
	});
}

void UNuiSpeechTts::Initialize()
{
	SpeechTtsPtr->Initialize();
}

void UNuiSpeechTts::Destroy()
{
	SpeechTtsPtr->Destroy();
}

int UNuiSpeechTts::StartTts(FString TtsText)
{
	return SpeechTtsPtr->StartTts(TtsText);
}

int UNuiSpeechTts::StartEmotionTts(FString TtsText, FString Category, float Intensity, FString Voice)
{
	FString EmotionText = FString::Printf(
		TEXT("<speak voice=\"%ls\"><emotion category=\"%ls\" intensity=\"%0.2f\">%ls</emotion></speak>"),
		*Voice, *Category, Intensity, *TtsText);
	return StartTts(EmotionText);
}

int UNuiSpeechTts::QuitTts()
{
	return SpeechTtsPtr->QuitTts();
}

int UNuiSpeechTts::CancelTts()
{
	return SpeechTtsPtr->CancelTts();
}

int UNuiSpeechTts::PauseTts()
{
	return SpeechTtsPtr->PauseTts();
}

int UNuiSpeechTts::ResumeTts()
{
	return SpeechTtsPtr->ResumeTts();
}

int UNuiSpeechTts::SetParamTts(FString Key, FString Value)
{
	return SpeechTtsPtr->SetParamTts(Key, Value);
}
