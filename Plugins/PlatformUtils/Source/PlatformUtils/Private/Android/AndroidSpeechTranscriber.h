#pragma once

#if PLATFORM_ANDROID
#include "NuiSpeechBase.h"
#include "Android/AndroidJNI.h"
#include "Android/AndroidJava.h"
#include "NuiTypes.h"

class FAndroidSpeechTranscriber : public FJavaClassObject, public FNuiSpeechTranscriberBase
{
public:
	static FAndroidSpeechTranscriber* GetTranscriber(jobject SpeechObject)
	{
		FAndroidSpeechTranscriber* TranscriberPtr = nullptr;
		if (SpeechObject && GTranscribers.Contains(SpeechObject))
		{
			TranscriberPtr = *GTranscribers.Find(SpeechObject);
		}
		return TranscriberPtr;
	}

public:
	FAndroidSpeechTranscriber();
	virtual ~FAndroidSpeechTranscriber();
	void Initialize() override;
	void Destroy() override;
	void RequestPermissionAudio() override;
	void SetTranscriberVadMode(bool bVad) override;
	void StartDialog() override;
	void StopDialog() override;

private:
	static FName GetClassName();
	static TMap<jobject, FAndroidSpeechTranscriber*> GTranscribers;

	FJavaClassMethod InitializeMethod;
	FJavaClassMethod DestroyMethod;
	FJavaClassMethod RequestPermissionAudioMethod;
	FJavaClassMethod SetTranscriberVadModeMethod;
	FJavaClassMethod StartDialogMethod;
	FJavaClassMethod StopDialogMethod;
};
#endif