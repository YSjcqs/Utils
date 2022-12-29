#if PLATFORM_IOS
#include "IOSSpeechTts.h"

#if PLATFORM_IOS
#import <AliSpeechTts.h>
#endif

FIOSSpeechTts::FIOSSpeechTts() {}
FIOSSpeechTts::~FIOSSpeechTts() {}
void FIOSSpeechTts::Initialize() {}
void FIOSSpeechTts::Destroy() {}
int FIOSSpeechTts::StartTts(FString TtsText)
{
	return -1;
}
int FIOSSpeechTts::QuitTts()
{
	return -1;
}
int FIOSSpeechTts::CancelTts()
{
	return -1;
}
int FIOSSpeechTts::PauseTts()
{
	return -1;
}
int FIOSSpeechTts::ResumeTts()
{
	return -1;
}
int FIOSSpeechTts::SetParamTts(FString Key, FString Value)
{
	return -1;
}
#endif