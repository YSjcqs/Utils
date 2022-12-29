#pragma once
#if PLATFORM_IOS
#include "NuiSpeechBase.h"

class FIOSSpeechTranscriber : public FNuiSpeechTranscriberBase
{
public:
	FIOSSpeechTranscriber();
	virtual ~FIOSSpeechTranscriber() override;
	virtual void Initialize() override;
	virtual void Destroy() override;
	virtual void RequestPermissionAudio() override;
	virtual void SetTranscriberVadMode(bool bVad) override;
	virtual void StartDialog() override;
	virtual void StopDialog() override;
};
#endif