// Fill out your copyright notice in the Description page of Project Settings.

#if PLATFORM_ANDROID

#include "AndroidNuiUtils.h"
#include "Android/AndroidJNI.h"
#include "Android/AndroidApplication.h"
#include "PlatformUtils.h"

static JNIEnv* gEnv = nullptr;
static jmethodID gMidInitNuiSpeech;
static jmethodID gMidOnNuiStart;
static jmethodID gMidOnNuiStop;
static jmethodID gMidStartDialog;
static jmethodID gMidStopDialog;
static jmethodID gMidCheckNuiInitState;

FAndroidNuiUtils::FAndroidNuiUtils()
{
	gEnv = FAndroidApplication::GetJavaEnv();
	if (gEnv)
	{
		bool bIsOptional = false;
		gMidInitNuiSpeech = FJavaWrapper::FindMethod(gEnv, FJavaWrapper::GameActivityClassID, "initNuiSpeech", "(IIZ)I",
		                                             bIsOptional);
		gMidOnNuiStart = FJavaWrapper::FindMethod(gEnv, FJavaWrapper::GameActivityClassID, "nuiStart",
		                                          "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)I",
		                                          bIsOptional);
		gMidOnNuiStop =
			FJavaWrapper::FindMethod(gEnv, FJavaWrapper::GameActivityClassID, "nuiStop", "()I", bIsOptional);
		gMidStartDialog = FJavaWrapper::FindMethod(gEnv, FJavaWrapper::GameActivityClassID, "startDialog", "()I",
		                                           bIsOptional);
		gMidStopDialog = FJavaWrapper::FindMethod(gEnv, FJavaWrapper::GameActivityClassID, "stopDialog", "()I",
		                                          bIsOptional);
		gMidCheckNuiInitState = FJavaWrapper::FindMethod(gEnv, FJavaWrapper::GameActivityClassID, "checkNuiInitState",
		                                                 "()Z", bIsOptional);
	}
}

int FAndroidNuiUtils::InitNuiSpeech()
{
	if (gEnv)
	{
		jint jvad_mode = static_cast<jint>(static_cast<int>(NuiVadMode));
		jint jlog_level = static_cast<jint>(static_cast<int>(NuiLogLevel));
		return FJavaWrapper::CallIntMethod(gEnv, FJavaWrapper::GameActivityThis,
		                                   gMidInitNuiSpeech, jvad_mode, jlog_level, bSaveLog ? JNI_TRUE : JNI_FALSE);
	}
	return -1;
}

bool FAndroidNuiUtils::CheckNuiInitState()
{
	if (gEnv)
	{
		return FJavaWrapper::CallBooleanMethod(gEnv, FJavaWrapper::GameActivityThis, gMidCheckNuiInitState);
	}
	return false;
}

int FAndroidNuiUtils::OnNuiStart()
{
	if (gEnv)
	{
		auto app_key = FJavaHelper::ToJavaString(gEnv, AppKey);
		auto app_token = FJavaHelper::ToJavaString(gEnv, AppToken);
		auto nui_url = FJavaHelper::ToJavaString(gEnv, NuiUrl);

		return FJavaWrapper::CallIntMethod(gEnv, FJavaWrapper::GameActivityThis, gMidOnNuiStart,
			*app_key, *app_token, *nui_url);
	}
	return -1;
}

int FAndroidNuiUtils::OnNuiStop()
{
	if (gEnv)
	{
		return FJavaWrapper::CallIntMethod(gEnv, FJavaWrapper::GameActivityThis, gMidOnNuiStop);
	}
	return -1;
}

int FAndroidNuiUtils::StartDialog()
{
	if (gEnv)
	{
		return FJavaWrapper::CallIntMethod(gEnv, FJavaWrapper::GameActivityThis, gMidStartDialog);
	}
	return -1;
}

int FAndroidNuiUtils::StopDialog()
{
	if (gEnv)
	{
		return FJavaWrapper::CallIntMethod(gEnv, FJavaWrapper::GameActivityThis, gMidStopDialog);
	}
	return -1;
}

extern "C" {
JNI_METHOD void Java_com_epicgames_unreal_NuiSpeechManager_NuiEventCallback(
JNIEnv* jenv, jobject thiz, jint NuiEvent, jint resultCode, jint arg2,
jint WuwType, jstring Kws,
jboolean finish, jint asrCode, jstring asrString)
{
	if (FPlatformUtilsModule* Module = FModuleManager::LoadModulePtr<
		FPlatformUtilsModule>(FName(TEXT("PlatformUtils"))))
	{
		if (Module->GetNuiUtils().IsValid())
		{
			ENuiEvent eNuiEvent = static_cast<ENuiEvent>(NuiEvent);
			FKwsResult kwsResult(static_cast<int>(WuwType), FJavaHelper::FStringFromLocalRef(jenv, Kws));
			FAsrResult asrResult(finish == JNI_TRUE, static_cast<int>(asrCode),
			                     FJavaHelper::FStringFromLocalRef(jenv, asrString));
			Module->GetNuiUtils()->onNuiEventCallback(eNuiEvent, static_cast<int>(resultCode),
				static_cast<int>(arg2), kwsResult, asrResult);
		}
	}
}

JNI_METHOD void Java_com_epicgames_unreal_NuiSpeechManager_NuiAudioStateChanged(
JNIEnv* jenv, jobject thiz, jint var1)
{
	if (FPlatformUtilsModule* Module = FModuleManager::LoadModulePtr<
		FPlatformUtilsModule>(FName(TEXT("PlatformUtils"))))
	{
		if (Module->GetNuiUtils().IsValid())
		{
			Module->GetNuiUtils()->onNuiAudioStateChanged(static_cast<EAudioState>(var1));
		}
	}
}

JNI_METHOD void Java_com_epicgames_unreal_NuiSpeechManager_NuiAudioRMSChanged(
JNIEnv* jenv, jobject thiz, jfloat var1)
{
	if (FPlatformUtilsModule* Module = FModuleManager::LoadModulePtr<
		FPlatformUtilsModule>(FName(TEXT("PlatformUtils"))))
	{
		if (Module->GetNuiUtils().IsValid())
		{
			Module->GetNuiUtils()->onNuiAudioRMSChanged(static_cast<float>(var1));
		}
	}
}

JNI_METHOD void Java_com_epicgames_unreal_NuiSpeechManager_NuiVprEventCallback(
JNIEnv* jenv, jobject thiz, jint var1)
{
	if (FPlatformUtilsModule* Module = FModuleManager::LoadModulePtr<
		FPlatformUtilsModule>(FName(TEXT("PlatformUtils"))))
	{
		if (Module->GetNuiUtils().IsValid())
		{
			Module->GetNuiUtils()->onNuiVprEventCallback(static_cast<ENuiEvent>(var1));
		}
	}
}

JNI_METHOD void Java_com_epicgames_unreal_NuiSpeechManager_UEDebug(
JNIEnv* jenv, jobject thiz, jstring debugMessage)
{
	FGenericPlatformNuiUtils::NulDebugLog(FJavaHelper::FStringFromLocalRef(jenv, debugMessage));
}
}
#endif
