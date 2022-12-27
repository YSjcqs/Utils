#if PLATFORM_ANDROID

#include "AndroidSpeechRecognizer.h"

#include "Android/AndroidApplication.h"
#include "Android/AndroidJNI.h"

TMap<jobject, FAndroidSpeechRecognizer*> FAndroidSpeechRecognizer::GRecognizers;

FName FAndroidSpeechRecognizer::GetClassName()
{
	if (FAndroidMisc::GetAndroidBuildVersion() >= 14)
	{
		return FName("com/epicgames/unreal/speechrec/AliSpeechRecognizer");
	}
	else
	{
		return FName("");
	}
}

FAndroidSpeechRecognizer::FAndroidSpeechRecognizer()
	: FJavaClassObject(GetClassName(), "()V")
	, InitializeMethod(GetClassMethod("initialize", "()V"))
	, DestroyMethod(GetClassMethod("destroy", "()V"))
	, RequestPermissionAudioMethod(GetClassMethod("requestPermissionAudio", "()V"))
	, SetRecognizerVadModeMethod(GetClassMethod("setRecognizerVadMode", "(Z)V"))
	, StartDialogMethod(GetClassMethod("startDialog", "()V"))
	, StopDialogMethod(GetClassMethod("stopDialog", "()V"))
{
	if (Object)
	{
		GRecognizers.Add(Object, this);
	}
}

FAndroidSpeechRecognizer::~FAndroidSpeechRecognizer()
{
	if (Object)
	{
		GRecognizers.Remove(Object);
	}
}

void FAndroidSpeechRecognizer::Initialize()
{
	CallMethod<void>(InitializeMethod);
}
void FAndroidSpeechRecognizer::Destroy()
{
	CallMethod<void>(DestroyMethod);
}
void FAndroidSpeechRecognizer::RequestPermissionAudio()
{
	CallMethod<void>(RequestPermissionAudioMethod);
}
void FAndroidSpeechRecognizer::SetRecognizerVadMode(bool bVad)
{
	CallMethod<void>(SetRecognizerVadModeMethod, bVad);
}
void FAndroidSpeechRecognizer::StartDialog()
{
	CallMethod<void>(StartDialogMethod);
}
void FAndroidSpeechRecognizer::StopDialog()
{
	CallMethod<void>(StopDialogMethod);
}

extern "C"
{
JNI_METHOD void Java_com_epicgames_unreal_speechrec_AliSpeechRecognizer_nativeRecognizerErrorCallback(
	JNIEnv* jenv, jobject thiz, jint errorCode, jstring errorMessage)
{
	FAndroidSpeechRecognizer* SpeechRecognizerPtr = FAndroidSpeechRecognizer::GetRecognizer(thiz);
	if (SpeechRecognizerPtr)
	{
		FString ErrorMessage = FJavaHelper::FStringFromLocalRef(jenv, errorMessage);
		SpeechRecognizerPtr->OnRecognizerErrorDelegate.ExecuteIfBound(static_cast<int>(errorCode), ErrorMessage);
	}
}

JNI_METHOD void Java_com_epicgames_unreal_speechrec_AliSpeechRecognizer_nativeRecognizerEventCallback(
	JNIEnv* jenv, jobject thiz, jint event, jint resultCode, jint arg2, jint kwsType, jstring kwsString, jboolean asrFinish, jint asrResultCode, jstring asrString)
{
	FAndroidSpeechRecognizer* SpeechRecognizerPtr = FAndroidSpeechRecognizer::GetRecognizer(thiz);
	if (SpeechRecognizerPtr)
	{
		FKwsResult KwsResult(static_cast<int>(kwsType), FJavaHelper::FStringFromLocalRef(jenv, kwsString));
		FAsrResult AsrResult(asrFinish == JNI_TRUE, static_cast<int>(asrResultCode), FJavaHelper::FStringFromLocalRef(jenv, asrString));
		
		SpeechRecognizerPtr->OnRecognizerEventDelegate.ExecuteIfBound(static_cast<int>(event), static_cast<int>(resultCode),
			static_cast<int>(arg2), KwsResult, AsrResult);
	}
}

JNI_METHOD void Java_com_epicgames_unreal_speechrec_AliSpeechRecognizer_nativeRecognizerAudioStateChanged(
	JNIEnv* jenv, jobject thiz, jint state)
{
	FAndroidSpeechRecognizer* SpeechRecognizerPtr = FAndroidSpeechRecognizer::GetRecognizer(thiz);
	if (SpeechRecognizerPtr)
	{
		SpeechRecognizerPtr->OnRecognizerAudioStateChangedDelegate.ExecuteIfBound(static_cast<int>(state));
	}
}
}
#endif