#pragma once
#if PLATFORM_IOS
#include "NuiSpeechBase.h"

class FIOSSpeechRecognizer : public FNuiSpeechRecognizerBase
{
public:
	FIOSSpeechRecognizer();
	virtual ~FIOSSpeechRecognizer() override;
	virtual void Initialize() override;
	virtual void Destroy() override;
	virtual void RequestPermissionAudio() override;
	virtual void SetRecognizerVadMode(bool bVad) override;
	virtual void StartDialog() override;
	virtual void StopDialog() override;
};
#endif