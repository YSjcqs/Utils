#pragma once
#include "NuiSpeechBase.h"

class FOtherSpeechTranscriber : public FNuiSpeechTranscriberBase
{
public:
	virtual void Initialize() override;
	virtual void Destroy() override;
	virtual void RequestPermissionAudio() override;
	virtual void SetTranscriberVadMode(bool bVad) override;
	virtual void StartDialog() override;
	virtual void StopDialog() override;
};
