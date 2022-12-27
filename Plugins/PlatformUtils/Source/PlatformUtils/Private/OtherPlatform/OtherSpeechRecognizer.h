#pragma once
#include "NuiSpeechBase.h"

class FOtherSpeechRecognizer : public FNuiSpeechRecognizerBase
{
public:
	virtual void Initialize() override;
	virtual void Destroy() override;
	virtual void RequestPermissionAudio() override;
	virtual void SetRecognizerVadMode(bool bVad) override;
	virtual void StartDialog() override;
	virtual void StopDialog() override;
};
