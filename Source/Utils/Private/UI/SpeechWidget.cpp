// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SpeechWidget.h"

#include "NuiUtils.h"

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