#pragma once

#if PLATFORM_ANDROID
#include "NuiSpeechBase.h"
#include "Android/AndroidJNI.h"
#include "Android/AndroidJava.h"
#include "NuiTypes.h"

class FAndroidSpeechRecognizer : public FJavaClassObject, public FNuiSpeechRecognizerBase
{
public:
	FAndroidSpeechRecognizer();
	virtual ~FAndroidSpeechRecognizer();
	void Initialize() override;
	void Destroy() override;
	void RequestPermissionAudio() override;
	void SetRecognizerVadMode(bool bVad) override;
	void StartDialog() override;
	void StopDialog() override;

private:
	static FName GetClassName();

	FJavaClassMethod InitializeMethod;
	FJavaClassMethod DestroyMethod;
	FJavaClassMethod RequestPermissionAudioMethod;
	FJavaClassMethod SetRecognizerVadModeMethod;
	FJavaClassMethod StartDialogMethod;
	FJavaClassMethod StopDialogMethod;
};

#endif