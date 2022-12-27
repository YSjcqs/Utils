#pragma once
#include "NuiSpeechBase.h"

class FOtherSpeechTts : public FNuiSpeechTtsBase
{
public:
	virtual void Initialize() override;
	virtual void Destroy() override;
	virtual int StartTts(FString TtsText) override;
	virtual int QuitTts() override;
	virtual int CancelTts() override;
	virtual int PauseTts() override;
	virtual int ResumeTts() override;
	virtual int SetParamTts(FString Key, FString Value) override;
};
