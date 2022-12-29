#pragma once
#if PLATFORM_IOS

#include "NuiSpeechBase.h"

class FIOSSpeechTts : public FNuiSpeechTtsBase
{
public:
	FIOSSpeechTts();
	virtual ~FIOSSpeechTts() override;
	virtual void Initialize() override;
	virtual void Destroy() override;
	virtual int StartTts(FString TtsText) override;
	virtual int QuitTts() override;
	virtual int CancelTts() override;
	virtual int PauseTts() override;
	virtual int ResumeTts() override;
	virtual int SetParamTts(FString Key, FString Value) override;
};
#endif