
//
//  AliSpeech.h
//  Nui
//
//  Created by ysjcqs on 2022/12/29.
//

#ifndef AliSpeech_h
#define AliSpeech_h

@interface AliSpeechTts : NSObject

- (void)initialize;
- (void)destroy;
- (int)startTts:(NSString *)content;
- (int)cancelTts;
- (int)pauseTts;
- (int)resumeTts;
- (int)setParamTts:(NSString *)keyStr value:(NSString *)valueStr;

@end

#endif /* AliSpeech_h */
