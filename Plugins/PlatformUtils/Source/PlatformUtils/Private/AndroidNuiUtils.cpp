// Fill out your copyright notice in the Description page of Project Settings.

#if PLATFORM_ANDROID

#include "AndroidNuiUtils.h"
#include "Android/AndroidJNI.h"
#include "Android/AndroidApplication.h"
#include "PlatformUtils.h"

static JNIEnv* gEnv = nullptr;
static FAndroidNuiUtils* gAndroidUtils = nullptr;
static jmethodID gMidInitNuiSpeech;
static jmethodID gMidReleaseNuiSpeech;

static jmethodID gMidStartDialog;
static jmethodID gMidStopDialog;
static jmethodID gMidCheckDialog;
static jmethodID gMidDialogAudioPermissions;

static jmethodID gMidStartTts;
static jmethodID gMidQuitTts;
static jmethodID gMidCancelTts;
static jmethodID gMidPauseTts;
static jmethodID gMidResumeTts;
static jmethodID gMidCheckTts;

FAndroidNuiUtils::FAndroidNuiUtils()
{
	gEnv = FAndroidApplication::GetJavaEnv();
	if (gEnv)
	{
		gAndroidUtils = this;
		bool bIsOptional = false;
		gMidInitNuiSpeech = FJavaWrapper::FindMethod(gEnv, FJavaWrapper::GameActivityClassID, "initNuiSdk",
			"(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V", bIsOptional);
		gMidReleaseNuiSpeech = FJavaWrapper::FindMethod(gEnv, FJavaWrapper::GameActivityClassID, "releaseNuiSdk", "()V", bIsOptional);
		gMidStartDialog = FJavaWrapper::FindMethod(gEnv, FJavaWrapper::GameActivityClassID, "startDialog", "()Z", bIsOptional);
		gMidStopDialog = FJavaWrapper::FindMethod(gEnv, FJavaWrapper::GameActivityClassID, "stopDialog", "()Z", bIsOptional);
		gMidCheckDialog = FJavaWrapper::FindMethod(gEnv, FJavaWrapper::GameActivityClassID, "checkDialog", "()Z", bIsOptional);
		gMidDialogAudioPermissions = FJavaWrapper::FindMethod(gEnv, FJavaWrapper::GameActivityClassID, "dialogAudioPermissions", "()V", bIsOptional);
		gMidStartTts = FJavaWrapper::FindMethod(gEnv, FJavaWrapper::GameActivityClassID, "startTts", "(Ljava/lang/String;)Z", bIsOptional);
		gMidQuitTts = FJavaWrapper::FindMethod(gEnv, FJavaWrapper::GameActivityClassID, "quitTts", "()Z", bIsOptional);
		gMidCancelTts = FJavaWrapper::FindMethod(gEnv, FJavaWrapper::GameActivityClassID, "cancelTts", "()Z", bIsOptional);
		gMidPauseTts = FJavaWrapper::FindMethod(gEnv, FJavaWrapper::GameActivityClassID, "pauseTts", "()Z", bIsOptional);
		gMidResumeTts = FJavaWrapper::FindMethod(gEnv, FJavaWrapper::GameActivityClassID, "resumeTts", "()Z", bIsOptional);
		gMidCheckTts = FJavaWrapper::FindMethod(gEnv, FJavaWrapper::GameActivityClassID, "checkTts", "()Z", bIsOptional);
	}
}

FAndroidNuiUtils::~FAndroidNuiUtils()
{
	gAndroidUtils = nullptr;
}

void FAndroidNuiUtils::InitNuiSpeech()
{
	if (gEnv)
	{
		auto app_key = FJavaHelper::ToJavaString(gEnv, AppKey);
		auto accessKeyId = FJavaHelper::ToJavaString(gEnv, AccessKeyId);
		auto accessKeySecret = FJavaHelper::ToJavaString(gEnv, AccessKeySecret);
		FJavaWrapper::CallVoidMethod(gEnv, FJavaWrapper::GameActivityThis,
		                                   gMidInitNuiSpeech, *app_key, *accessKeyId, *accessKeySecret);
	}
}

void FAndroidNuiUtils::ReleaseNuiSpeech()
{
	if (gEnv)
	{
		FJavaWrapper::CallVoidMethod(gEnv, FJavaWrapper::GameActivityThis, gMidReleaseNuiSpeech);
	}
}

bool FAndroidNuiUtils::CheckDialog()
{
	if (gEnv)
	{
		return FJavaWrapper::CallBooleanMethod(gEnv, FJavaWrapper::GameActivityThis, gMidCheckDialog);
	}
	return FGenericPlatformNuiUtils::CheckDialog();
}

void FAndroidNuiUtils::DialogAudioPermissions()
{
	if (gEnv)
	{
		FJavaWrapper::CallVoidMethod(gEnv, FJavaWrapper::GameActivityThis, gMidDialogAudioPermissions);
	}
}

bool FAndroidNuiUtils::StartDialog()
{
	if (gEnv)
	{
		return FJavaWrapper::CallBooleanMethod(gEnv, FJavaWrapper::GameActivityThis, gMidStartDialog);
	}
	return false;
}

bool FAndroidNuiUtils::StopDialog()
{
	if (gEnv)
	{
		return FJavaWrapper::CallBooleanMethod(gEnv, FJavaWrapper::GameActivityThis, gMidStopDialog);
	}
	return false;
}

bool FAndroidNuiUtils::StartTts(FString TtsText)
{
	if (gEnv)
	{
		return FJavaWrapper::CallBooleanMethod(gEnv, FJavaWrapper::GameActivityThis, gMidStartTts);
	}
	return FGenericPlatformNuiUtils::StartTts(TtsText);
}

bool FAndroidNuiUtils::QuitTts()
{
	if (gEnv)
	{
		return FJavaWrapper::CallBooleanMethod(gEnv, FJavaWrapper::GameActivityThis, gMidQuitTts);
	}
	return FGenericPlatformNuiUtils::QuitTts();
}

bool FAndroidNuiUtils::CancelTts()
{
	if (gEnv)
	{
		return FJavaWrapper::CallBooleanMethod(gEnv, FJavaWrapper::GameActivityThis, gMidCancelTts);
	}
	return FGenericPlatformNuiUtils::CancelTts();
}

bool FAndroidNuiUtils::PauseTts()
{
	if (gEnv)
	{
		return FJavaWrapper::CallBooleanMethod(gEnv, FJavaWrapper::GameActivityThis, gMidPauseTts);
	}
	return FGenericPlatformNuiUtils::PauseTts();
}

bool FAndroidNuiUtils::ResumeTts()
{
	if (gEnv)
	{
		return FJavaWrapper::CallBooleanMethod(gEnv, FJavaWrapper::GameActivityThis, gMidResumeTts);
	}
	return FGenericPlatformNuiUtils::ResumeTts();
}

bool FAndroidNuiUtils::CheckTts()
{
	if (gEnv)
	{
		return FJavaWrapper::CallBooleanMethod(gEnv, FJavaWrapper::GameActivityThis, gMidCheckTts);
	}
	return FGenericPlatformNuiUtils::CheckTts();
}

extern "C"
{
JNI_METHOD void Java_com_epicgames_unreal_speechrec_NuiSpeechManager_DialogEventCallback(
	JNIEnv* jenv, jobject thiz, jint NuiEvent, jint resultCode, jstring asrString)
{
	if (gAndroidUtils)
	{
		ENuiEvent eNuiEvent = static_cast<ENuiEvent>(NuiEvent);
		gAndroidUtils->OnDialogEventCallback(eNuiEvent, static_cast<int>(resultCode),
			FJavaHelper::FStringFromLocalRef(jenv, asrString));
	}
}

JNI_METHOD void Java_com_epicgames_unreal_speechrec_NuiSpeechManager_DialogAudioStateChanged(
	JNIEnv* jenv, jobject thiz, jint var1)
{
	if (gAndroidUtils)
	{
		gAndroidUtils->OnDialogAudioStateChanged(static_cast<EAudioState>(var1));
	}
}

JNI_METHOD void Java_com_epicgames_unreal_speechrec_NuiSpeechManager_DialogAudioRMSChanged(
	JNIEnv* jenv, jobject thiz, jfloat var1)
{
	if (gAndroidUtils)
	{
		gAndroidUtils->OnDialogAudioRMSChanged(static_cast<float>(var1));
	}
}

JNI_METHOD void Java_com_epicgames_unreal_speechrec_NuiSpeechManager_DialogVprEventCallback(
	JNIEnv* jenv, jobject thiz, jint var1)
{
	if (gAndroidUtils)
	{
		gAndroidUtils->OnDialogVprEventCallback(static_cast<ENuiVprEvent>(var1));
	}
}

JNI_METHOD void Java_com_epicgames_unreal_speechrec_NuiSpeechManager_TtsEventCallback(
	JNIEnv* jenv, jobject thiz, jint TtsEvent, jstring taskID, jint resultCode)
{
	if (gAndroidUtils)
	{
		ETtsEvent eTtsEvent = static_cast<ETtsEvent>(TtsEvent);
		gAndroidUtils->OnTtsEventCallback(eTtsEvent, FJavaHelper::FStringFromLocalRef(jenv, taskID),
			static_cast<int>(resultCode));
	}
}

JNI_METHOD void Java_com_epicgames_unreal_speechrec_NuiSpeechManager_TtsVolCallback(
	JNIEnv* jenv, jobject thiz, jint var1)
{
	if (gAndroidUtils)
	{
		gAndroidUtils->OnTtsVolCallback(static_cast<int>(var1));
	}
}

}
#endif
