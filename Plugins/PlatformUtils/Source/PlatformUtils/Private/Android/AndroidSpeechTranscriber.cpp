#if PLATFORM_ANDROID

#include "AndroidSpeechTranscriber.h"

#include "Android/AndroidApplication.h"
#include "Android/AndroidJNI.h"

FName FAndroidSpeechTranscriber::GetClassName()
{
	if (FAndroidMisc::GetAndroidBuildVersion() >= 14)
	{
		return FName("com/epicgames/unreal/speechrec/AliSpeechTranscriber");
	}
	else
	{
		return FName("");
	}
}

FAndroidSpeechTranscriber::FAndroidSpeechTranscriber()
	: FJavaClassObject(GetClassName(), "()V")
	, InitializeMethod(GetClassMethod("initialize", "()V"))
	, DestroyMethod(GetClassMethod("destroy", "()V"))
	, RequestPermissionAudioMethod(GetClassMethod("requestPermissionAudio", "()V"))
	, SetTranscriberVadModeMethod(GetClassMethod("setTranscriberVadMode", "(Z)V"))
	, StartDialogMethod(GetClassMethod("startDialog", "()V"))
	, StopDialogMethod(GetClassMethod("stopDialog", "()V"))
{
	JNIEnv* JEnv = FAndroidApplication::GetJavaEnv();

	jfieldID fid = JEnv->GetFieldID(Class, "UEObject", "J");
	JEnv->SetLongField(Object, fid, (jlong)this);
}

FAndroidSpeechTranscriber::~FAndroidSpeechTranscriber()
{
}

void FAndroidSpeechTranscriber::Initialize()
{
	CallMethod<void>(InitializeMethod);
}
void FAndroidSpeechTranscriber::Destroy()
{
	CallMethod<void>(DestroyMethod);
}
void FAndroidSpeechTranscriber::RequestPermissionAudio()
{
	CallMethod<void>(RequestPermissionAudioMethod);
}
void FAndroidSpeechTranscriber::SetTranscriberVadMode(bool bVad)
{
	CallMethod<void>(SetTranscriberVadModeMethod, bVad);
}
void FAndroidSpeechTranscriber::StartDialog()
{
	CallMethod<void>(StartDialogMethod);
}
void FAndroidSpeechTranscriber::StopDialog()
{
	CallMethod<void>(StopDialogMethod);
}

extern "C"
{
FAndroidSpeechTranscriber* getUESpeechTranscriberObject(JNIEnv* jenv, jobject thiz)
{
	jclass clazz = jenv->GetObjectClass(thiz);
	jfieldID fid = jenv->GetFieldID(clazz, "UEObject", "J");
	jlong addr = jenv->GetLongField(thiz, fid);
	return (FAndroidSpeechTranscriber*)addr;
}
JNI_METHOD void Java_com_epicgames_unreal_speechrec_AliSpeechTranscriber_nativeTranscriberErrorCallback(
	JNIEnv* jenv, jobject thiz, jint errorCode, jstring errorMessage)
{
	FAndroidSpeechTranscriber* SpeechTranscriberPtr = getUESpeechTranscriberObject(jenv, thiz);
	if (SpeechTranscriberPtr)
	{
		FString ErrorMessage = FJavaHelper::FStringFromLocalRef(jenv, errorMessage);
		SpeechTranscriberPtr->OnTranscriberErrorDelegate.ExecuteIfBound(static_cast<int>(errorCode), ErrorMessage);
	}
}

JNI_METHOD void Java_com_epicgames_unreal_speechrec_AliSpeechTranscriber_nativeTranscriberEventCallback(
	JNIEnv* jenv, jobject thiz, jint event, jint resultCode, jint arg2, jint kwsType, jstring kwsString, jboolean asrFinish, jint asrResultCode, jstring asrString)
{
	FAndroidSpeechTranscriber* SpeechTranscriberPtr = getUESpeechTranscriberObject(jenv, thiz);
	if (SpeechTranscriberPtr)
	{
		FKwsResult KwsResult(static_cast<int>(kwsType), FJavaHelper::FStringFromLocalRef(jenv, kwsString));
		FAsrResult AsrResult(asrFinish == JNI_TRUE, static_cast<int>(asrResultCode), FJavaHelper::FStringFromLocalRef(jenv, asrString));
		
		SpeechTranscriberPtr->OnTranscriberEventDelegate.ExecuteIfBound(static_cast<int>(event), static_cast<int>(resultCode),
			static_cast<int>(arg2), KwsResult, AsrResult);
	}
}

JNI_METHOD void Java_com_epicgames_unreal_speechrec_AliSpeechTranscriber_nativeTranscriberAudioStateChanged(
	JNIEnv* jenv, jobject thiz, jint state)
{
	FAndroidSpeechTranscriber* SpeechTranscriberPtr = getUESpeechTranscriberObject(jenv, thiz);
	if (SpeechTranscriberPtr)
	{
		SpeechTranscriberPtr->OnTranscriberAudioStateChangedDelegate.ExecuteIfBound(static_cast<int>(state));
	}
}
}
#endif