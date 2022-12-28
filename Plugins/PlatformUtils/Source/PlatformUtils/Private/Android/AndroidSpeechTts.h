#pragma once

#if PLATFORM_ANDROID
#include "NuiSpeechBase.h"
#include "Android/AndroidJNI.h"
#include "Android/AndroidJava.h"
#include "NuiTypes.h"

class FAndroidSpeechTts : public FJavaClassObject, public FNuiSpeechTtsBase
{
public:
	FAndroidSpeechTts();
	virtual ~FAndroidSpeechTts();
	void Initialize() override;
	void Destroy() override;
	int StartTts(FString TtsText) override;
	int QuitTts() override;
	int CancelTts() override;
	int PauseTts() override;
	int ResumeTts() override;
	int SetParamTts(FString Key, FString Value) override;

private:
	static FName GetClassName();

	FJavaClassMethod InitializeMethod;
	FJavaClassMethod DestroyMethod;
	FJavaClassMethod StartTtsMethod;
	FJavaClassMethod QuitTtsMethod;
	FJavaClassMethod CancelTtsMethod;
	FJavaClassMethod PauseTtsMethod;
	FJavaClassMethod ResumeTtsMethod;
	FJavaClassMethod SetParamTtsMethod;
};

#endif