// Fill out your copyright notice in the Description page of Project Settings.


#include "AndroidNuiUtils.h"
#include "Android/AndroidJNI.h"
#include "Android/AndroidApplication.h"
#include "PlatformUtils.h"

static JNIEnv* gEnv = nullptr;
static UAndroidNuiDialogUtils* gAndroidDialogUtils = nullptr;
static UAndroidNuiTtsUtils* gAndroidTtsUtils = nullptr;
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

static void InitEnv()
{
	if (!gEnv)
	{
		bool bIsOptional = false;
		gEnv = FAndroidApplication::GetJavaEnv();
		if (gEnv)
		{
			gMidInitNuiSpeech = FJavaWrapper::FindMethod(gEnv, FJavaWrapper::GameActivityClassID, "initNuiSdk",
				"(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V", bIsOptional);
			gMidReleaseNuiSpeech = FJavaWrapper::FindMethod(gEnv, FJavaWrapper::GameActivityClassID, "releaseNuiSdk", "()V", bIsOptional);
		}
	}
}

UAndroidNuiDialogUtils::UAndroidNuiDialogUtils()
{
	InitEnv();
	if (gEnv)
	{
		gAndroidDialogUtils = this;
		bool bIsOptional = false;
		gMidStartDialog = FJavaWrapper::FindMethod(gEnv, FJavaWrapper::GameActivityClassID, "startDialog", "()Z", bIsOptional);
		gMidStopDialog = FJavaWrapper::FindMethod(gEnv, FJavaWrapper::GameActivityClassID, "stopDialog", "()Z", bIsOptional);
		gMidCheckDialog = FJavaWrapper::FindMethod(gEnv, FJavaWrapper::GameActivityClassID, "checkDialog", "()Z", bIsOptional);
		gMidReleaseDialog = FJavaWrapper::FindMethod(gEnv, FJavaWrapper::GameActivityClassID, "releaseDialog", "()V", bIsOptional);
		gMidDialogAudioPermissions = FJavaWrapper::FindMethod(gEnv, FJavaWrapper::GameActivityClassID, "dialogAudioPermissions", "()V", bIsOptional);
	}
}

UAndroidNuiDialogUtils::~UAndroidNuiDialogUtils()
{
	gAndroidDialogUtils = nullptr;
}

void UAndroidNuiDialogUtils::InitNuiSpeech_Implementation()
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

void UAndroidNuiDialogUtils::ReleaseNuiSpeech_Implementation()
{
	if (gEnv)
	{
		FJavaWrapper::CallVoidMethod(gEnv, FJavaWrapper::GameActivityThis, gMidReleaseNuiSpeech);
	}
}

bool UAndroidNuiDialogUtils::CheckDialog_Implementation()
{
	if (gEnv)
	{
		return FJavaWrapper::CallBooleanMethod(gEnv, FJavaWrapper::GameActivityThis, gMidCheckDialog);
	}
	return FGenericPlatformNuiUtils::CheckDialog();
}

void UAndroidNuiDialogUtils::ReleaseDialog_Implementation()
{
	if (gEnv)
	{
		FJavaWrapper::CallVoidMethod(gEnv, FJavaWrapper::GameActivityThis, gMidReleaseDialog);
	}
}

void UAndroidNuiDialogUtils::DialogAudioPermissions_Implementation()
{
	if (gEnv)
	{
		FJavaWrapper::CallVoidMethod(gEnv, FJavaWrapper::GameActivityThis, gMidDialogAudioPermissions);
	}
}

bool UAndroidNuiDialogUtils::StartDialog_Implementation()
{
	if (gEnv)
	{
		return FJavaWrapper::CallBooleanMethod(gEnv, FJavaWrapper::GameActivityThis, gMidStartDialog);
	}
	return false;
}

bool UAndroidNuiDialogUtils::StopDialog_Implementation()
{
	if (gEnv)
	{
		return FJavaWrapper::CallBooleanMethod(gEnv, FJavaWrapper::GameActivityThis, gMidStopDialog);
	}
	return false;
}

UAndroidNuiTtsUtils::UAndroidNuiTtsUtils()
{
	InitEnv();
	if (gEnv)
	{
		gAndroidTtsUtils = this;
		bool bIsOptional = false;
		gMidStartTts = FJavaWrapper::FindMethod(gEnv, FJavaWrapper::GameActivityClassID, "startTts", "(Ljava/lang/String;)Z", bIsOptional);
		gMidQuitTts = FJavaWrapper::FindMethod(gEnv, FJavaWrapper::GameActivityClassID, "quitTts", "()Z", bIsOptional);
		gMidCancelTts = FJavaWrapper::FindMethod(gEnv, FJavaWrapper::GameActivityClassID, "cancelTts", "()Z", bIsOptional);
		gMidPauseTts = FJavaWrapper::FindMethod(gEnv, FJavaWrapper::GameActivityClassID, "pauseTts", "()Z", bIsOptional);
		gMidResumeTts = FJavaWrapper::FindMethod(gEnv, FJavaWrapper::GameActivityClassID, "resumeTts", "()Z", bIsOptional);
		gMidCheckTts = FJavaWrapper::FindMethod(gEnv, FJavaWrapper::GameActivityClassID, "checkTts", "()Z", bIsOptional);
		gMidReleaseTts = FJavaWrapper::FindMethod(gEnv, FJavaWrapper::GameActivityClassID, "releaseTts", "()V", bIsOptional);
		gMidSetFontNameTts = FJavaWrapper::FindMethod(gEnv, FJavaWrapper::GameActivityClassID, "setFontName", "(Ljava/lang/String;)V", bIsOptional);
	}
}

UAndroidNuiTtsUtils::~UAndroidNuiTtsUtils()
{
	gAndroidTtsUtils = nullptr;
}

void UAndroidNuiTtsUtils::InitNuiSpeech_Implementation()
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

void UAndroidNuiTtsUtils::ReleaseNuiSpeech_Implementation()
{
	if (gEnv)
	{
		FJavaWrapper::CallVoidMethod(gEnv, FJavaWrapper::GameActivityThis, gMidReleaseNuiSpeech);
	}
}

void UAndroidNuiTtsUtils::ReleaseTts_Implementation()
{
	if (gEnv)
	{
		FJavaWrapper::CallVoidMethod(gEnv, FJavaWrapper::GameActivityThis, gMidReleaseTts);
	}
}

bool UAndroidNuiTtsUtils::StartTts_Implementation(FString TtsText)
{
	if (gEnv)
	{
		return FJavaWrapper::CallBooleanMethod(gEnv, FJavaWrapper::GameActivityThis, gMidStartTts);
	}
	return FGenericPlatformNuiUtils::StartTts(TtsText);
}

bool UAndroidNuiTtsUtils::QuitTts_Implementation()
{
	if (gEnv)
	{
		return FJavaWrapper::CallBooleanMethod(gEnv, FJavaWrapper::GameActivityThis, gMidQuitTts);
	}
	return FGenericPlatformNuiUtils::QuitTts();
}

bool UAndroidNuiTtsUtils::CancelTts_Implementation()
{
	if (gEnv)
	{
		return FJavaWrapper::CallBooleanMethod(gEnv, FJavaWrapper::GameActivityThis, gMidCancelTts);
	}
	return FGenericPlatformNuiUtils::CancelTts();
}

bool UAndroidNuiTtsUtils::PauseTts_Implementation()
{
	if (gEnv)
	{
		return FJavaWrapper::CallBooleanMethod(gEnv, FJavaWrapper::GameActivityThis, gMidPauseTts);
	}
	return FGenericPlatformNuiUtils::PauseTts();
}

bool UAndroidNuiTtsUtils::ResumeTts_Implementation()
{
	if (gEnv)
	{
		return FJavaWrapper::CallBooleanMethod(gEnv, FJavaWrapper::GameActivityThis, gMidResumeTts);
	}
	return FGenericPlatformNuiUtils::ResumeTts();
}

bool UAndroidNuiTtsUtils::CheckTts_Implementation()
{
	if (gEnv)
	{
		return FJavaWrapper::CallBooleanMethod(gEnv, FJavaWrapper::GameActivityThis, gMidCheckTts);
	}
	return FGenericPlatformNuiUtils::CheckTts();
}

void UAndroidNuiTtsUtils::SetFontNameTts_Implementation()
{
#if PLATFORM_ANDROID
	if (gEnv)
	{
		FJavaWrapper::CallBooleanMethod(gEnv, FJavaWrapper::GameActivityThis, gMidSetFontNameTts);
	}
#endif
}

#if PLATFORM_ANDROID
extern "C"
{
JNI_METHOD void Java_com_epicgames_unreal_speechrec_NuiSpeechManager_DialogEventCallback(
	JNIEnv* jenv, jobject thiz, jint NuiEvent, jint resultCode, jstring asrString)
{
	if (gAndroidDialogUtils)
	{
		ENuiEvent eNuiEvent = static_cast<ENuiEvent>(NuiEvent);
		gAndroidDialogUtils->OnDialogEventCallback(eNuiEvent, static_cast<int>(resultCode),
			FJavaHelper::FStringFromLocalRef(jenv, asrString));
	}
}

JNI_METHOD void Java_com_epicgames_unreal_speechrec_NuiSpeechManager_DialogAudioStateChanged(
	JNIEnv* jenv, jobject thiz, jint var1)
{
	if (gAndroidDialogUtils)
	{
		gAndroidDialogUtils->OnDialogAudioStateChanged(static_cast<EAudioState>(var1));
	}
}

JNI_METHOD void Java_com_epicgames_unreal_speechrec_NuiSpeechManager_DialogAudioRMSChanged(
	JNIEnv* jenv, jobject thiz, jfloat var1)
{
	if (gAndroidDialogUtils)
	{
		gAndroidDialogUtils->OnDialogAudioRMSChanged(static_cast<float>(var1));
	}
}

JNI_METHOD void Java_com_epicgames_unreal_speechrec_NuiSpeechManager_DialogVprEventCallback(
	JNIEnv* jenv, jobject thiz, jint var1)
{
	if (gAndroidDialogUtils)
	{
		gAndroidDialogUtils->OnDialogVprEventCallback(static_cast<ENuiVprEvent>(var1));
	}
}

JNI_METHOD void Java_com_epicgames_unreal_speechrec_NuiSpeechManager_TtsEventCallback(
	JNIEnv* jenv, jobject thiz, jint TtsEvent, jstring taskID, jint resultCode)
{
	if (gAndroidTtsUtils)
	{
		ETtsEvent eTtsEvent = static_cast<ETtsEvent>(TtsEvent);
		gAndroidTtsUtils->OnTtsEventCallback(eTtsEvent, FJavaHelper::FStringFromLocalRef(jenv, taskID),
			static_cast<int>(resultCode));
	}
}

JNI_METHOD void Java_com_epicgames_unreal_speechrec_NuiSpeechManager_TtsVolCallback(
	JNIEnv* jenv, jobject thiz, jint var1)
{
	if (gAndroidTtsUtils)
	{
		gAndroidTtsUtils->OnTtsVolCallback(static_cast<int>(var1));
	}
}

}
#endif
