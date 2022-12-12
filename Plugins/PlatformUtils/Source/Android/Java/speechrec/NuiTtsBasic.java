/*
 * Copyright (C) 2010 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


package com.epicgames.unreal.speechrec;

import android.text.TextUtils;

import com.alibaba.idst.nui.Constants;
import com.alibaba.idst.nui.INativeTtsCallback;
import com.alibaba.idst.nui.NativeNui;
import com.epicgames.unreal.Logger;

import java.io.FileOutputStream;
import java.io.IOException;
import java.io.OutputStream;

public class NuiTtsBasic implements INativeTtsCallback {
    public static Logger Log = new Logger("UE", "NuiTtsBasic");

    NativeNui nui_tts_instance = new NativeNui(Constants.ModeType.MODE_TTS);
    private OutputStream output_file = null;
    private boolean b_savewav = false;
    //  AudioPlayer默认采样率是16000
    private AudioPlayer mAudioTrack =  new AudioPlayer(new AudioPlayerCallback() {
        @Override
        public void playStart() { Log.debug("start play"); }
        @Override
        public void playOver() { Log.debug("play over"); }
    });
    boolean initialized =  false;

    public int releaseTts() {
        Log.warn("tts release");
        mAudioTrack.stop();
        initialized = false;
        return nui_tts_instance.tts_release();
    }

    public void startTts(String ttsText)
    {
        if (!initialized) {
            return;
        }
        if (TextUtils.isEmpty(ttsText)) {
            Log.error("tts empty");
            return;
        }

        Log.debug("start play tts");
        // 支持一次性合成300字符以内的文字，其中1个汉字、1个英文字母或1个标点均算作1个字符，
        // 超过300个字符的内容将会截断。所以请确保传入的text小于300字符(不包含ssml格式)。
        int charNum = nui_tts_instance.getUtf8CharsNum(ttsText);
        Log.debug("chars:" + charNum + " of text:" + ttsText);
        if (charNum > 300) {
            Log.warn("text exceed 300 chars.");
        }
        nui_tts_instance.startTts("1", "", ttsText);
    }
    public void quitTts()
    {
        Log.debug("tts release");
        mAudioTrack.stop();
        nui_tts_instance.tts_release();
        initialized = false;
    }
    public void cancelTts()
    {
        Log.debug("cancel tts");
        nui_tts_instance.cancelTts("");
        mAudioTrack.stop();
    }
    public void pauseTts()
    {
        Log.debug("pause tts");
        nui_tts_instance.pauseTts();
        mAudioTrack.pause();
    }
    public void resumeTts()
    {
        Log.debug("resume tts");
        nui_tts_instance.resumeTts();
        mAudioTrack.play();
    }

    public int initialize(String ticket) {
        int ret = nui_tts_instance.tts_initialize(this, ticket, Constants.LogLevel.LOG_LEVEL_VERBOSE, true);

        if (Constants.NuiResultCode.SUCCESS != ret) {
            Log.error("create failed");
        }

        // 在线语音合成发音人可以参考阿里云官网
        // https://help.aliyun.com/document_detail/84435.html
        nui_tts_instance.setparamTts("font_name", "siqi");

        // 详细参数可见: https://help.aliyun.com/document_detail/173642.html
        nui_tts_instance.setparamTts("sample_rate", "16000");
        // 模型采样率设置16K，则播放器也得设置成相同采样率16K.
        mAudioTrack.setSampleRate(16000);

        nui_tts_instance.setparamTts("enable_subtitle", "1");
//        nui_tts_instance.setparamTts("speed_level", "1");
//        nui_tts_instance.setparamTts("pitch_level", "0");
//        nui_tts_instance.setparamTts("volume", "1.0");

        if (b_savewav) {
            try {
                output_file = new FileOutputStream("/sdcard/mit/tmp/test.pcm");
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
        return ret;
    }

    public boolean checkNotInitToast() {
        if (!initialized) {
            Log.warn("nui dialog not init!");
            return false;
        } else {
            return true;
        }
    }

    @Override
    public void onTtsEventCallback(TtsEvent event, String task_id, int ret_code) {
        Log.warn("tts event:" + event + " task id " + task_id + " ret " + ret_code);
        if (event == TtsEvent.TTS_EVENT_START) {
            mAudioTrack.play();
            Log.debug("start play");
        } else if (event == TtsEvent.TTS_EVENT_END) {
            /*
             * 提示: TTS_EVENT_END事件表示TTS已经合成完并通过回调传回了所有音频数据, 而不是表示播放器已经播放完了所有音频数据。
             */
            Log.warn("play end");

            // 表示推送完数据, 当播放器播放结束则会有playOver回调
            mAudioTrack.isFinishSend(true);

            // 调试使用, 若希望存下音频文件, 如下
            if (b_savewav) {
                try {
                    output_file.close();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        } else if (event == TtsEvent.TTS_EVENT_PAUSE) {
            mAudioTrack.pause();
            Log.warn("play pause");
        } else if (event == TtsEvent.TTS_EVENT_RESUME) {
            mAudioTrack.play();
        } else if (event == TtsEvent.TTS_EVENT_ERROR) {
            // 表示推送完数据, 当播放器播放结束则会有playOver回调
            mAudioTrack.isFinishSend(true);

            String error_msg =  nui_tts_instance.getparamTts("error_msg");
            Log.error("TTS_EVENT_ERROR error_code:" + ret_code + " errmsg:" + error_msg);
        }

        try {
            NuiSpeechManager.TtsEventCallback(event.ordinal(), task_id, ret_code);
        }catch (Exception ex) {
            ex.printStackTrace();
            Log.error(ex.getMessage());
        }
    }
    @Override
    public void onTtsDataCallback(String info, int info_len, byte[] data) {
        if (info.length() > 0) {
            Log.debug("info: " + info);
        }
        if (data.length > 0) {
            mAudioTrack.setAudioData(data);
            Log.debug("write:" + data.length);
            if (b_savewav) {
                try {
                    output_file.write(data);
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        }
    }
    @Override
    public void onTtsVolCallback(int vol) {
        Log.debug("tts vol " + vol);
        try {
            NuiSpeechManager.TtsVolCallback(vol);
        }catch (Exception ex) {
            ex.printStackTrace();
            Log.error(ex.getMessage());
        }
    }
}
