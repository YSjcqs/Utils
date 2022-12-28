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
import android.widget.Toast;

import com.alibaba.fastjson.JSONException;
import com.alibaba.fastjson.JSONObject;
import com.alibaba.idst.nui.CommonUtils;
import com.alibaba.idst.nui.Constants;
import com.alibaba.idst.nui.INativeTtsCallback;
import com.alibaba.idst.nui.NativeNui;
import com.epicgames.unreal.GameActivity;
import com.epicgames.unreal.Logger;

import java.io.FileOutputStream;
import java.io.IOException;
import java.io.OutputStream;

// 在线语音合成使用方法
// Android SDK 详细说明：https://help.aliyun.com/document_detail/174481.html
public class AliSpeechTts implements INativeTtsCallback {
    public static Logger Log = new Logger("UE", "AliSpeechTts");

    public native void nativeTtsErrorCallback(int event, String errorMessage);
    public native void nativeTtsEventCallback(int event, String task_id, int ret_code, String errorMsg);
//    public native void nativeTtsDataCallback(String info, int info_len, byte[] data);
//    public native void nativeTtsVolCallback(int vol);

    NativeNui nui_tts_instance = new NativeNui(Constants.ModeType.MODE_TTS);
    String asset_path;
    Toast mToast;
    private long UEObject = 0;
    private OutputStream output_file = null;
    private boolean b_savewav = false;
    boolean initialized =  false;
    private String ttsText = new String();
    //  AudioPlayer默认采样率是16000
    private AudioPlayer mAudioTrack =  new AudioPlayer(new AudioPlayerCallback() {
        @Override
        public void playStart() {
            Log.debug( "start play");
        }
        @Override
        public void playOver() {
            Log.debug( "play over");
        }
    });

    public void setSaveWav(boolean bSave) {
        b_savewav = bSave;
    }

    public void initialize() {
        String assets_path = CommonUtils.getModelPath(GameActivity.Get());
        int ret = nui_tts_instance.tts_initialize(this, genTicket(assets_path), Constants.LogLevel.LOG_LEVEL_VERBOSE, true);

        if (Constants.NuiResultCode.SUCCESS != ret) {
            Log.debug( "create failed");
            nativeTtsErrorCallback(SpeechError.ERROR_INIT.getCode(), "TTS初始化失败!ErrorCode:" + ret);
            return;
        }

        initialized = true;
        // 在线语音合成发音人可以参考阿里云官网
        // https://help.aliyun.com/document_detail/84435.html
        nui_tts_instance.setparamTts("font_name", "zhiyan_emo");

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
    }

    public void destroy() {
        mAudioTrack.stop();
        initialized = false;
        nui_tts_instance.release();
    }

    public int startTts(String ttsText)
    {
        if (!checkNotInitToast()) {
            nativeTtsErrorCallback(SpeechError.ERROR_INIT.getCode(), "Tts未初始化.");
            return -1;
        }
        if (TextUtils.isEmpty(ttsText)) {
            Log.error("tts empty");
            return -1;
        }

        Log.debug("start play tts");
        // 支持一次性合成300字符以内的文字，其中1个汉字、1个英文字母或1个标点均算作1个字符，
        // 超过300个字符的内容将会截断。所以请确保传入的text小于300字符(不包含ssml格式)。
        int charNum = nui_tts_instance.getUtf8CharsNum(ttsText);
        Log.debug("chars:" + charNum + " of text:" + ttsText);
        if (charNum > 300) {
            Log.warn("text exceed 300 chars.");
        }
        return  nui_tts_instance.startTts("1", "", ttsText);
    }
    public int quitTts()
    {
        if (!checkNotInitToast()) {
            nativeTtsErrorCallback(SpeechError.ERROR_INIT.getCode(), "Tts未初始化.");
            return -1;
        }
        Log.debug("tts release");
        mAudioTrack.stop();
        initialized = false;
        return nui_tts_instance.tts_release();
    }
    public int cancelTts()
    {
        if (!checkNotInitToast()) {
            nativeTtsErrorCallback(SpeechError.ERROR_INIT.getCode(), "Tts未初始化.");
            return -1;
        }
        Log.debug("cancel tts");
        mAudioTrack.stop();
        return nui_tts_instance.cancelTts("");
    }
    public int pauseTts()
    {
        if (!checkNotInitToast()) {
            nativeTtsErrorCallback(SpeechError.ERROR_INIT.getCode(), "Tts未初始化.");
            return -1;
        }
        Log.debug("pause tts");
        mAudioTrack.pause();
        return nui_tts_instance.pauseTts();
    }
    public int resumeTts()
    {
        if (!checkNotInitToast()) {
            nativeTtsErrorCallback(SpeechError.ERROR_INIT.getCode(), "Tts未初始化.");
            return -1;
        }
        Log.debug("resume tts");
        mAudioTrack.play();
        return nui_tts_instance.resumeTts();
    }

    public int setparamTts(String name, String value)
    {
        if (!checkNotInitToast()) {
            nativeTtsErrorCallback(SpeechError.ERROR_INIT.getCode(), "Tts未初始化.");
            return -1;
        }
        return nui_tts_instance.setparamTts(name, value);
    }

    private boolean checkNotInitToast() {
        if (!initialized) {
            return false;
        } else {
            return true;
        }
    }

    private String genTicket(String workpath) {
        String str = "";
        try {
            JSONObject object = Auth.getAliYunTicket();
            object.put("workspace", workpath);

            // 设置为在线合成
            //  Local = 0,
            //  Mix = 1,  // init local and cloud
            //  Cloud = 2,
            object.put("mode_type", "2");
            str = object.toString();
        } catch (JSONException e) {
            e.printStackTrace();
        }
        Log.debug( "UserContext:" + str);
        return str;
    }

    @Override
    public void onTtsEventCallback(TtsEvent event, String task_id, int ret_code) {
        String errorMsg = "";
        Log.debug( "tts event:" + event + " task id " + task_id + " ret " + ret_code);
        if (event == TtsEvent.TTS_EVENT_START) {
            mAudioTrack.play();
            Log.debug( "start play");
        } else if (event == TtsEvent.TTS_EVENT_END) {
            /*
             * 提示: TTS_EVENT_END事件表示TTS已经合成完并通过回调传回了所有音频数据, 而不是表示播放器已经播放完了所有音频数据。
             */
            Log.debug( "play end");

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
            Log.debug( "play pause");
        } else if (event == TtsEvent.TTS_EVENT_RESUME) {
            mAudioTrack.play();
        } else if (event == TtsEvent.TTS_EVENT_ERROR) {
            // 表示推送完数据, 当播放器播放结束则会有playOver回调
            mAudioTrack.isFinishSend(true);

            errorMsg =  nui_tts_instance.getparamTts("error_msg");
        }
        nativeTtsEventCallback(event.getCode(), task_id, ret_code, errorMsg);
    }
    @Override
    public void onTtsDataCallback(String info, int info_len, byte[] data) {
        if (info.length() > 0) {
            Log.debug( "info: " + info);
        }
        if (data.length > 0) {
            mAudioTrack.setAudioData(data);
            Log.debug( "write:" + data.length);
            if (b_savewav) {
                try {
                    output_file.write(data);
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        }
//        nativeTtsDataCallback(info, info_len, data);
    }
    @Override
    public void onTtsVolCallback(int vol) {
        Log.debug( "tts vol " + vol);
//        nativeTtsVolCallback(vol);
    }
}
