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
static jmethodID gMidGetCurrentHandleCode;

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

		gMidStartDialog = FJavaWrapper::FindMethod(gEnv, FJavaWrapper::GameActivityClassID, "startDialog", "()V",
		                                           bIsOptional);
		gMidStopDialog = FJavaWrapper::FindMethod(gEnv, FJavaWrapper::GameActivityClassID, "stopDialog", "()V",
		                                          bIsOptional);
		gMidCheckDialog = FJavaWrapper::FindMethod(gEnv, FJavaWrapper::GameActivityClassID, "checkDialog", "()Z",
		                                           bIsOptional);
		gMidReleaseDialog = FJavaWrapper::FindMethod(gEnv, FJavaWrapper::GameActivityClassID, "releaseDialog", "()I",
		                                             bIsOptional);
		gMidDialogAudioPermissions = FJavaWrapper::FindMethod(gEnv, FJavaWrapper::GameActivityClassID,
		                                                      "dialogAudioPermissions", "()V", bIsOptional);
		gMidGetCurrentHandleCode = FJavaWrapper::FindMethod(gEnv, FJavaWrapper::GameActivityClassID, "getCurrentHandleCode", "()I",
													 bIsOptional);

		gMidStartTts = FJavaWrapper::FindMethod(gEnv, FJavaWrapper::GameActivityClassID, "startTts",
		                                        "(Ljava/lang/String;)I", bIsOptional);
		gMidQuitTts = FJavaWrapper::FindMethod(gEnv, FJavaWrapper::GameActivityClassID, "quitTts", "()I", bIsOptional);
		gMidCancelTts = FJavaWrapper::FindMethod(gEnv, FJavaWrapper::GameActivityClassID, "cancelTts", "()I",
		                                         bIsOptional);
		gMidPauseTts = FJavaWrapper::FindMethod(gEnv, FJavaWrapper::GameActivityClassID, "pauseTts", "()I",
		                                        bIsOptional);
		gMidResumeTts = FJavaWrapper::FindMethod(gEnv, FJavaWrapper::GameActivityClassID, "resumeTts", "()I",
		                                         bIsOptional);
		gMidCheckTts = FJavaWrapper::FindMethod(gEnv, FJavaWrapper::GameActivityClassID, "checkTts", "()Z",
		                                        bIsOptional);
		gMidReleaseTts = FJavaWrapper::FindMethod(gEnv, FJavaWrapper::GameActivityClassID, "releaseTts", "()I",
		                                          bIsOptional);
		gMidSetFontNameTts = FJavaWrapper::FindMethod(gEnv, FJavaWrapper::GameActivityClassID, "setFontName",
		                                              "(Ljava/lang/String;)I", bIsOptional);
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
	return false;
}

int FAndroidNuiUtils::ReleaseDialog()
{
	if (gEnv)
	{
		return FJavaWrapper::CallIntMethod(gEnv, FJavaWrapper::GameActivityThis, gMidReleaseDialog);
	}
	return -1;
}

void FAndroidNuiUtils::DialogAudioPermissions()
{
	if (gEnv)
	{
		FJavaWrapper::CallVoidMethod(gEnv, FJavaWrapper::GameActivityThis, gMidDialogAudioPermissions);
	}
}

int FAndroidNuiUtils::GetCurrentHandleCode()
{
	if (gEnv)
	{
		return FJavaWrapper::CallIntMethod(gEnv, FJavaWrapper::GameActivityThis, gMidGetCurrentHandleCode);
	}
	return -1;
}

void FAndroidNuiUtils::StartDialog()
{
	if (gEnv)
	{
		FJavaWrapper::CallVoidMethod(gEnv, FJavaWrapper::GameActivityThis, gMidStartDialog);
	}
}

void FAndroidNuiUtils::StopDialog()
{
	if (gEnv)
	{
		FJavaWrapper::CallVoidMethod(gEnv, FJavaWrapper::GameActivityThis, gMidStopDialog);
	}
}

int FAndroidNuiUtils::ReleaseTts()
{
	if (gEnv)
	{
		return FJavaWrapper::CallIntMethod(gEnv, FJavaWrapper::GameActivityThis, gMidReleaseTts);
	}
	return -1;
}

int FAndroidNuiUtils::StartTts(FString TtsText)
{
	if (gEnv)
	{
		auto jText = FJavaHelper::ToJavaString(gEnv, TtsText);
		return FJavaWrapper::CallIntMethod(gEnv, FJavaWrapper::GameActivityThis, gMidStartTts, *jText);
	}
	return -1;
}

int FAndroidNuiUtils::QuitTts()
{
	if (gEnv)
	{
		return FJavaWrapper::CallIntMethod(gEnv, FJavaWrapper::GameActivityThis, gMidQuitTts);
	}
	return -1;
}

int FAndroidNuiUtils::CancelTts()
{
	if (gEnv)
	{
		return FJavaWrapper::CallIntMethod(gEnv, FJavaWrapper::GameActivityThis, gMidCancelTts);
	}
	return -1;
}

int FAndroidNuiUtils::PauseTts()
{
	if (gEnv)
	{
		return FJavaWrapper::CallIntMethod(gEnv, FJavaWrapper::GameActivityThis, gMidPauseTts);
	}
	return -1;
}

int FAndroidNuiUtils::ResumeTts()
{
	if (gEnv)
	{
		return FJavaWrapper::CallIntMethod(gEnv, FJavaWrapper::GameActivityThis, gMidResumeTts);
	}
	return -1;
}

bool FAndroidNuiUtils::CheckTts()
{
	if (gEnv)
	{
		return FJavaWrapper::CallBooleanMethod(gEnv, FJavaWrapper::GameActivityThis, gMidCheckTts);
	}
	return false;
}

int FAndroidNuiUtils::SetFontNameTts(FString Name)
{
	if (gEnv)
	{
		auto jName = FJavaHelper::ToJavaString(gEnv, Name);
		return FJavaWrapper::CallIntMethod(gEnv, FJavaWrapper::GameActivityThis, gMidSetFontNameTts, *jName);
	}
	return -1;
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