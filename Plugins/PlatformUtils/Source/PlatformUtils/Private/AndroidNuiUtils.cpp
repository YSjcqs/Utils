// Fill out your copyright notice in the Description page of Project Settings.
#if PLATFORM_ANDROID

#include "AndroidNuiUtils.h"
#include "Android/AndroidJNI.h"
#include "Android/AndroidApplication.h"
#include "NuiInstance.h"

static JNIEnv* gEnv = nullptr;
static jmethodID gMidInitNuiSpeech;
static jmethodID gMidReleaseNuiSpeech;

static jmethodID gMidStartDialog;
static jmethodID gMidStopDialog;
static jmethodID gMidCheckDialog;
static jmethodID gMidReleaseDialog;
static jmethodID gMidDialogAudioPermissions;

static jmethodID gMidStartTts;
static jmethodID gMidQuitTts;
static jmethodID gMidCancelTts;
static jmethodID gMidPauseTts;
static jmethodID gMidResumeTts;
static jmethodID gMidCheckTts;
static jmethodID gMidReleaseTts;
static jmethodID gMidSetFontNameTts;

FAndroidNuiUtils::FAndroidNuiUtils()
{
	gEnv = FAndroidApplication::GetJavaEnv();
	if (gEnv)
	{
		bool bIsOptional = false;

		gMidInitNuiSpeech = FJavaWrapper::FindMethod(gEnv, FJavaWrapper::GameActivityClassID, "initNuiSdk",
		                                             "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V",
		                                             bIsOptional);
		gMidReleaseNuiSpeech = FJavaWrapper::FindMethod(gEnv, FJavaWrapper::GameActivityClassID, "releaseNuiSdk", "()V",
		                                                bIsOptional);

		gMidStartDialog = FJavaWrapper::FindMethod(gEnv, FJavaWrapper::GameActivityClassID, "startDialog", "()Z",
		                                           bIsOptional);
		gMidStopDialog = FJavaWrapper::FindMethod(gEnv, FJavaWrapper::GameActivityClassID, "stopDialog", "()Z",
		                                          bIsOptional);
		gMidCheckDialog = FJavaWrapper::FindMethod(gEnv, FJavaWrapper::GameActivityClassID, "checkDialog", "()Z",
		                                           bIsOptional);
		gMidReleaseDialog = FJavaWrapper::FindMethod(gEnv, FJavaWrapper::GameActivityClassID, "releaseDialog", "()V",
		                                             bIsOptional);
		gMidDialogAudioPermissions = FJavaWrapper::FindMethod(gEnv, FJavaWrapper::GameActivityClassID,
		                                                      "dialogAudioPermissions", "()V", bIsOptional);

		gMidStartTts = FJavaWrapper::FindMethod(gEnv, FJavaWrapper::GameActivityClassID, "startTts",
		                                        "(Ljava/lang/String;)Z", bIsOptional);
		gMidQuitTts = FJavaWrapper::FindMethod(gEnv, FJavaWrapper::GameActivityClassID, "quitTts", "()Z", bIsOptional);
		gMidCancelTts = FJavaWrapper::FindMethod(gEnv, FJavaWrapper::GameActivityClassID, "cancelTts", "()Z",
		                                         bIsOptional);
		gMidPauseTts = FJavaWrapper::FindMethod(gEnv, FJavaWrapper::GameActivityClassID, "pauseTts", "()Z",
		                                        bIsOptional);
		gMidResumeTts = FJavaWrapper::FindMethod(gEnv, FJavaWrapper::GameActivityClassID, "resumeTts", "()Z",
		                                         bIsOptional);
		gMidCheckTts = FJavaWrapper::FindMethod(gEnv, FJavaWrapper::GameActivityClassID, "checkTts", "()Z",
		                                        bIsOptional);
		gMidReleaseTts = FJavaWrapper::FindMethod(gEnv, FJavaWrapper::GameActivityClassID, "releaseTts", "()V",
		                                          bIsOptional);
		gMidSetFontNameTts = FJavaWrapper::FindMethod(gEnv, FJavaWrapper::GameActivityClassID, "setFontName",
		                                              "(Ljava/lang/String;)V", bIsOptional);
	}
}

FAndroidNuiUtils::~FAndroidNuiUtils()
{
	gEnv = nullptr;
}


void FAndroidNuiUtils::InitNuiSpeech(FString AppKey, FString AccessKeyId, FString AccessKeySecret)
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
	return FNuiUtilsBase::CheckDialog();
}

void FAndroidNuiUtils::ReleaseDialog()
{
	if (gEnv)
	{
		FJavaWrapper::CallVoidMethod(gEnv, FJavaWrapper::GameActivityThis, gMidReleaseDialog);
	}
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

void FAndroidNuiUtils::ReleaseTts()
{
	if (gEnv)
	{
		FJavaWrapper::CallVoidMethod(gEnv, FJavaWrapper::GameActivityThis, gMidReleaseTts);
	}
}

bool FAndroidNuiUtils::StartTts(FString TtsText)
{
	if (gEnv)
	{
		return FJavaWrapper::CallBooleanMethod(gEnv, FJavaWrapper::GameActivityThis, gMidStartTts);
	}
	return false;
}

bool FAndroidNuiUtils::QuitTts()
{
	if (gEnv)
	{
		return FJavaWrapper::CallBooleanMethod(gEnv, FJavaWrapper::GameActivityThis, gMidQuitTts);
	}
	return false;
}

bool FAndroidNuiUtils::CancelTts()
{
	if (gEnv)
	{
		return FJavaWrapper::CallBooleanMethod(gEnv, FJavaWrapper::GameActivityThis, gMidCancelTts);
	}
	return false;
}

bool FAndroidNuiUtils::PauseTts()
{
	if (gEnv)
	{
		return FJavaWrapper::CallBooleanMethod(gEnv, FJavaWrapper::GameActivityThis, gMidPauseTts);
	}
	return false;
}

bool FAndroidNuiUtils::ResumeTts()
{
	if (gEnv)
	{
		return FJavaWrapper::CallBooleanMethod(gEnv, FJavaWrapper::GameActivityThis, gMidResumeTts);
	}
	return false;
}

bool FAndroidNuiUtils::CheckTts()
{
	if (gEnv)
	{
		return FJavaWrapper::CallBooleanMethod(gEnv, FJavaWrapper::GameActivityThis, gMidCheckTts);
	}
	return false;
}

void FAndroidNuiUtils::SetFontNameTts()
{
	if (gEnv)
	{
		FJavaWrapper::CallBooleanMethod(gEnv, FJavaWrapper::GameActivityThis, gMidSetFontNameTts);
	}
}

extern "C" {
JNI_METHOD void Java_com_epicgames_unreal_speechrec_NuiSpeechManager_DialogEventCallback(
	JNIEnv* jenv, jobject thiz, jint NuiEvent, jint resultCode, jstring asrString)
{
	if (UNuiInstance::GetNuiInstance())
	{
		ENuiEvent eNuiEvent = static_cast<ENuiEvent>(NuiEvent);
		UNuiInstance::GetNuiInstance()->OnDialogEventCallback(eNuiEvent, static_cast<int>(resultCode),
		                                                      FJavaHelper::FStringFromLocalRef(jenv, asrString));
	}
}

JNI_METHOD void Java_com_epicgames_unreal_speechrec_NuiSpeechManager_DialogAudioStateChanged(
	JNIEnv* jenv, jobject thiz, jint var1)
{
	if (UNuiInstance::GetNuiInstance())
	{
		UNuiInstance::GetNuiInstance()->OnDialogAudioStateChanged(static_cast<EAudioState>(var1));
	}
}

JNI_METHOD void Java_com_epicgames_unreal_speechrec_NuiSpeechManager_DialogAudioRMSChanged(
	JNIEnv* jenv, jobject thiz, jfloat var1)
{
	if (UNuiInstance::GetNuiInstance())
	{
		UNuiInstance::GetNuiInstance()->OnDialogAudioRMSChanged(static_cast<float>(var1));
	}
}

JNI_METHOD void Java_com_epicgames_unreal_speechrec_NuiSpeechManager_DialogVprEventCallback(
	JNIEnv* jenv, jobject thiz, jint var1)
{
	if (UNuiInstance::GetNuiInstance())
	{
		UNuiInstance::GetNuiInstance()->OnDialogVprEventCallback(static_cast<ENuiVprEvent>(var1));
	}
}

JNI_METHOD void Java_com_epicgames_unreal_speechrec_NuiSpeechManager_TtsEventCallback(
	JNIEnv* jenv, jobject thiz, jint TtsEvent, jstring taskID, jint resultCode)
{
	if (UNuiInstance::GetNuiInstance())
	{
		ETtsEvent eTtsEvent = static_cast<ETtsEvent>(TtsEvent);
		UNuiInstance::GetNuiInstance()->OnTtsEventCallback(eTtsEvent, FJavaHelper::FStringFromLocalRef(jenv, taskID),
		                                                   static_cast<int>(resultCode));
	}
}

JNI_METHOD void Java_com_epicgames_unreal_speechrec_NuiSpeechManager_TtsVolCallback(
	JNIEnv* jenv, jobject thiz, jint var1)
{
	if (UNuiInstance::GetNuiInstance())
	{
		UNuiInstance::GetNuiInstance()->OnTtsVolCallback(static_cast<int>(var1));
	}
}
}

#endif