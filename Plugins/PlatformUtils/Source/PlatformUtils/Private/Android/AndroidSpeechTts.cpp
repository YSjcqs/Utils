#if PLATFORM_ANDROID
#include "AndroidSpeechTts.h"

#include "Android/AndroidApplication.h"
#include "Android/AndroidJNI.h"

FName FAndroidSpeechTts::GetClassName()
{
	if (FAndroidMisc::GetAndroidBuildVersion() >= 14)
	{
		return FName("com/epicgames/unreal/speechrec/AliSpeechTts");
	}
	else
	{
		return FName("");
	}
}
FAndroidSpeechTts::FAndroidSpeechTts()
	: FJavaClassObject(GetClassName(), "()V")
	, InitializeMethod(GetClassMethod("initialize", "()V"))
	, DestroyMethod(GetClassMethod("destroy", "()V"))
	, StartTtsMethod(GetClassMethod("startTts", "(Ljava/lang/String;)I"))
	, QuitTtsMethod(GetClassMethod("quitTts", "()I"))
	, CancelTtsMethod(GetClassMethod("cancelTts", "()I"))
	, PauseTtsMethod(GetClassMethod("pauseTts", "()I"))
	, ResumeTtsMethod(GetClassMethod("resumeTts", "()I"))
	, SetParamTtsMethod(GetClassMethod("setparamTts", "(Ljava/lang/String;Ljava/lang/String;)I"))
{
	JNIEnv* JEnv = FAndroidApplication::GetJavaEnv();

	jfieldID fid = JEnv->GetFieldID(Class, "UEObject", "J");
	JEnv->SetLongField(Object, fid, (jlong)this);
}
FAndroidSpeechTts::~FAndroidSpeechTts()
{

}
void FAndroidSpeechTts::Initialize()
{
	CallMethod<void>(InitializeMethod);
}
void FAndroidSpeechTts::Destroy()
{
	CallMethod<void>(DestroyMethod);
}
int FAndroidSpeechTts::StartTts(FString TtsText)
{
	return CallMethod<int>(StartTtsMethod, *GetJString(TtsText));
}
int FAndroidSpeechTts::QuitTts()
{
	return CallMethod<int>(QuitTtsMethod);
}
int FAndroidSpeechTts::CancelTts()
{
	return CallMethod<int>(CancelTtsMethod);
}
int FAndroidSpeechTts::PauseTts()
{
	return CallMethod<int>(PauseTtsMethod);
}
int FAndroidSpeechTts::ResumeTts()
{
	return CallMethod<int>(ResumeTtsMethod);
}
int FAndroidSpeechTts::SetParamTts(FString Key, FString Value)
{
	return CallMethod<int>(SetParamTtsMethod, *GetJString(Key), *GetJString(Value));
}


extern "C"
{
FAndroidSpeechTts* getUESpeechTtsObject(JNIEnv* jenv, jobject thiz)
{
	jclass clazz = jenv->GetObjectClass(thiz);
	jfieldID fid = jenv->GetFieldID(clazz, "UEObject", "J");
	jlong addr = jenv->GetLongField(thiz, fid);
	return (FAndroidSpeechTts*)addr;
}
JNI_METHOD void Java_com_epicgames_unreal_speechrec_AliSpeechTts_nativeTtsErrorCallback(
	JNIEnv* jenv, jobject thiz, jint errorCode, jstring errorMessage)
{
	FAndroidSpeechTts* TtsPtr = getUESpeechTtsObject(jenv, thiz);
	if (TtsPtr)
	{
		FString ErrorMessage = FJavaHelper::FStringFromLocalRef(jenv, errorMessage);
		TtsPtr->OnTtsErrorDelegate.ExecuteIfBound(static_cast<int>(errorCode), ErrorMessage);
	}
}

JNI_METHOD void Java_com_epicgames_unreal_speechrec_AliSpeechTts_nativeTtsEventCallback(
	JNIEnv* jenv, jobject thiz, jint event, jstring task_id, jint ret_code, jstring errorMsg)
{
	FAndroidSpeechTts* TtsPtr = getUESpeechTtsObject(jenv, thiz);
	if (TtsPtr)
	{
		FString TaskID = FJavaHelper::FStringFromLocalRef(jenv, task_id);
		FString ErrorMessage = FJavaHelper::FStringFromLocalRef(jenv, errorMsg);
		TtsPtr->OnTtsEventDelegate.ExecuteIfBound(static_cast<int>(event), TaskID, static_cast<int>(ret_code), ErrorMessage);
	}
}
}

#endif