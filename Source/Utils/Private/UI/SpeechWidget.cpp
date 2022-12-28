// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SpeechWidget.h"

#include "NuiUtils.h"
#include "Misc/CoreMiscDefines.h"
#include "Misc/CoreMiscDefines.h"

PRAGMA_DISABLE_OPTIMIZATION

void USpeechWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	SpeechRecognizer = NewObject<UNuiSpeechRecognizer>(this, TEXT("SpeechRecognizer"));
	SpeechTts = NewObject<UNuiSpeechTts>(this, TEXT("SpeechTts"));
}

void USpeechWidget::StartSpeech()
{
	SpeechRecognizer->RequestPermissionAudio();
	SpeechRecognizer->Initialize();
	SpeechRecognizer->StartDialog();
}

void USpeechWidget::StopSpeech()
{
	SpeechRecognizer->StopDialog();
	SpeechRecognizer->Destroy();
}
PRAGMA_ENABLE_OPTIMIZATION