#pragma once

#if PLATFORM_ANDROID
#include "NuiSpeechBase.h"
#include "Android/AndroidJNI.h"
#include "Android/AndroidJava.h"
#include "NuiTypes.h"

class FAndroidSpeechRecognizer : public FJavaClassObject, public FNuiSpeechRecognizerBase
{
public:
	static FAndroidSpeechRecognizer* GetRecognizer(jobject SpeechObject)
	{
		FAndroidSpeechRecognizer* RecognizerPtr = nullptr;
		if (SpeechObject && GRecognizers.Contains(SpeechObject))
		{
			RecognizerPtr = *GRecognizers.Find(SpeechObject);
		}
		return RecognizerPtr;
	}

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
	static TMap<jobject, FAndroidSpeechRecognizer*> GRecognizers;

	FJavaClassMethod InitializeMethod;
	FJavaClassMethod DestroyMethod;
	FJavaClassMethod RequestPermissionAudioMethod;
	FJavaClassMethod SetRecognizerVadModeMethod;
	FJavaClassMethod StartDialogMethod;
	FJavaClassMethod StopDialogMethod;
};

#endif