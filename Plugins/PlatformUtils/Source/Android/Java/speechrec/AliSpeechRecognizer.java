package com.epicgames.unreal.speechrec;

import com.epicgames.unreal.Logger;

import android.Manifest;
import android.app.Activity;
import android.content.pm.PackageManager;
import android.media.AudioFormat;
import android.media.AudioRecord;
import android.media.MediaPlayer;
import android.media.MediaRecorder;
import android.os.Build;
import android.os.Bundle;
import android.os.Handler;
import android.os.HandlerThread;
import android.util.Log;

import androidx.core.app.ActivityCompat;
import androidx.core.content.ContextCompat;

import com.alibaba.fastjson.JSONException;
import com.alibaba.fastjson.JSONObject;
import com.alibaba.idst.nui.AsrResult;
import com.alibaba.idst.nui.CommonUtils;
import com.alibaba.idst.nui.Constants;
import com.alibaba.idst.nui.INativeNuiCallback;
import com.alibaba.idst.nui.KwsResult;
import com.alibaba.idst.nui.NativeNui;
import com.epicgames.unreal.GameActivity;
import com.epicgames.unreal.Logger;

import java.util.concurrent.atomic.AtomicBoolean;

// 本样例展示在线一句话语音识别使用方法
// Android SDK 详细说明：https://help.aliyun.com/document_detail/173115.html
public class AliSpeechRecognizer implements INativeNuiCallback {
    public static Logger Log = new Logger("UE", "AliSpeechRecognizer");

    public native void nativeSetGlobalRecognizer();
    public native void nativeRecognizerErrorCallback(int event, String errorMessage);
    public native void nativeRecognizerEventCallback(int event, final int resultCode, int arg2, KwsResult kwsResult, AsrResult asrResult);
    public native int nativeRecognizerNeedAudioData(byte[] buffer, int len, int javaRet);
    public native void nativeRecognizerAudioStateChanged(int state);
    public native void nativeRecognizerAudioRMSChanged(float var1);
    public native void nativeRecognizerVprEventCallback(int event);

    NativeNui nui_instance = new NativeNui();
    final static int WAVE_FRAM_SIZE = 20 * 2 * 1 * 16000 / 1000; //20ms audio for 16k/16bit/mono
    public final static int SAMPLE_RATE = 16000;
    private AudioRecord mAudioRecorder;
    private AtomicBoolean vadMode = new AtomicBoolean(false);
    private HandlerThread mHanderThread;
    private boolean mInit = false;
    private Handler mHandler;

    public AliSpeechRecognizer()
    {
        nativeSetGlobalRecognizer();
    }

    public void initialize() {
        if (CommonUtils.copyAssetsData(GameActivity.Get())) {
            Log.debug("copy assets data done");
        } else {
            nativeRecognizerErrorCallback(SpeechError.ERROR_ASSETS_DATA.getCode(), "copy assets failed!");
            Log.error("copy assets failed");
            return;
        }

        mHanderThread = new HandlerThread("process_thread");
        mHanderThread.start();
        mHandler = new Handler(mHanderThread.getLooper());

        //获取工作路径, 这里获得当前nuisdk.aar中assets路径
        String asset_path = CommonUtils.getModelPath(GameActivity.Get());
        Log.debug("use workspace " + asset_path);

        String debug_path = GameActivity.Get().getExternalCacheDir().getAbsolutePath() + "/debug_" + System.currentTimeMillis();
        Utils.createDir(debug_path);

        //录音初始化，录音参数中格式只支持16bit/单通道，采样率支持8K/16K
        //使用者请根据实际情况选择Android设备的MediaRecorder.AudioSource
        //录音麦克风如何选择,可查看https://developer.android.google.cn/reference/android/media/MediaRecorder.AudioSource
        if (ActivityCompat.checkSelfPermission(GameActivity.Get(), Manifest.permission.RECORD_AUDIO) != PackageManager.PERMISSION_GRANTED) {
            nativeRecognizerErrorCallback(SpeechError.ERROR_PERMISSION.getCode(), "你没有录音权限!");
            return;
        }
        mAudioRecorder = new AudioRecord(MediaRecorder.AudioSource.DEFAULT, SAMPLE_RATE,
                AudioFormat.CHANNEL_IN_MONO, AudioFormat.ENCODING_PCM_16BIT, WAVE_FRAM_SIZE * 4);

        //初始化SDK，注意用户需要在Auth.getAliYunTicket中填入相关ID信息才可以使用。
        int ret = nui_instance.initialize(this, genInitParams(asset_path,debug_path), Constants.LogLevel.LOG_LEVEL_VERBOSE, true);
        Log.debug("result = " + ret);
        if (ret == Constants.NuiResultCode.SUCCESS) {
            mInit = true;
        } else {
            nativeRecognizerErrorCallback(SpeechError.ERROR_INIT.getCode(), "AliSpeechRecognizer初始化失败,ErrorCode:" + ret);
        }

        //设置相关识别参数，具体参考API文档
        nui_instance.setParams(genParams());
    }

    public void destroy() {
        mInit = false;
        nui_instance.release();
    }

    public void requestPermissionAudio() {
        GameActivity.Get().runOnUiThread(new Runnable() {
            @Override
            public void run() {
                if (ContextCompat.checkSelfPermission(GameActivity.Get(), Manifest.permission.RECORD_AUDIO)
                        != PackageManager.PERMISSION_GRANTED) {
                    // 最后的请求码是对应回调方法的请求码
                    ActivityCompat.requestPermissions(GameActivity.Get(),
                            new String[]{Manifest.permission.RECORD_AUDIO}, 321);
                } else {
                    Log.debug("已经拥有录音权限了，可以直接录音！");
                }
            }
        });
    }

    public void setRecognizerVadMode(boolean bVad) {
        vadMode.set(bVad);
    }

    private String genParams() {
        String params = "";
        try {
            JSONObject nls_config = new JSONObject();
            nls_config.put("enable_intermediate_result", true);
            //参数可根据实际业务进行配置
            //接口说明可见: https://help.aliyun.com/document_detail/173298.html
            //nls_config.put("enable_punctuation_prediction", true);
            //nls_config.put("enable_inverse_text_normalization", true);
            //nls_config.put("enable_voice_detection", true);
            //nls_config.put("customization_id", "test_id");
            //nls_config.put("vocabulary_id", "test_id");
            //nls_config.put("max_start_silence", 10000);
            //nls_config.put("max_end_silence", 800);
            //nls_config.put("sample_rate", 16000);
            //nls_config.put("sr_format", "opus");
            JSONObject parameters = new JSONObject();

            parameters.put("nls_config", nls_config);
            parameters.put("service_type", Constants.kServiceTypeASR);

            //如果有HttpDns则可进行设置
            //parameters.put("direct_ip", Utils.getDirectIp());

            params = parameters.toString();
        } catch (JSONException e) {
            e.printStackTrace();
        }
        return params;
    }

    public void startDialog() {
        if (!checkNotInitToast()) {
            nativeRecognizerErrorCallback(SpeechError.ERROR_INIT.getCode(), "AliSpeechRecognizer未初始化.");
            return;
        }
        mHandler.post(new Runnable() {
            @Override
            public void run() {
                Constants.VadMode vad_mode = Constants.VadMode.TYPE_P2T;
                if (vadMode.get()) {
                    vad_mode = Constants.VadMode.TYPE_VAD;
                } else {
                    vad_mode = Constants.VadMode.TYPE_P2T;
                }
                int ret = nui_instance.startDialog(vad_mode,
                        genDialogParams());
                Log.debug("start done with " + ret);
                if (ret != 0) {
                    nativeRecognizerErrorCallback(SpeechError.ERROR_START_DIALOG.getCode(), "Failed Start Dialog!ErrorCode:" + ret);
                }
            }
        });
    }

    public void stopDialog() {
        if (!checkNotInitToast()) {
            nativeRecognizerErrorCallback(SpeechError.ERROR_INIT.getCode(), "AliSpeechRecognizer未初始化.");
            return;
        }
        mHandler.post(new Runnable() {
            @Override
            public void run() {
                long ret = nui_instance.stopDialog();
                if (ret != 0) {
                    nativeRecognizerErrorCallback(SpeechError.ERROR_STOP_DIALOG.getCode(), "Failed stop Dialog!ErrorCode:" + ret);
                }
            }
        });
    }

    private String genInitParams(String workpath, String debugpath) {
        String str = "";
        try{
            JSONObject object = Auth.getAliYunTicket();
            object.put("workspace", workpath);
            object.put("debug_path", debugpath);
            object.put("sample_rate", "16000");
            object.put("format", "opus");
//            object.put("save_wav", "true");

            // FullMix = 0   // 选用此模式开启本地功能并需要进行鉴权注册
            // FullCloud = 1
            // FullLocal = 2 // 选用此模式开启本地功能并需要进行鉴权注册
            // AsrMix = 3    // 选用此模式开启本地功能并需要进行鉴权注册
            // AsrCloud = 4
            // AsrLocal = 5  // 选用此模式开启本地功能并需要进行鉴权注册
            object.put("service_mode", Constants.ModeAsrCloud);
            str = object.toString();
        } catch (JSONException e) {
            e.printStackTrace();
        }

        Log.debug( "InsideUserContext:" + str);
        return str;
    }

    private String genDialogParams() {
        String params = "";
        try {
            JSONObject dialog_param = new JSONObject();
            params = dialog_param.toString();
        } catch (JSONException e) {
            e.printStackTrace();
        }

        Log.debug( "dialog params: " + params);
        return params;
    }

    private boolean checkNotInitToast() {
        if (!mInit) {
            return false;
        } else {
            return true;
        }
    }


    //当回调事件发生时调用
    @Override
    public void onNuiEventCallback(Constants.NuiEvent event, final int resultCode, final int arg2, KwsResult kwsResult,
                                   AsrResult asrResult) {
        Log.debug( "event=" + event);
        if (event == Constants.NuiEvent.EVENT_ASR_RESULT) {

        } else if (event == Constants.NuiEvent.EVENT_ASR_PARTIAL_RESULT) {

        } else if (event == Constants.NuiEvent.EVENT_ASR_ERROR) {

        }

        nativeRecognizerEventCallback(event.ordinal(), resultCode, arg2, kwsResult, asrResult);
    }

    //当调用NativeNui的start后，会一定时间反复回调该接口，底层会提供buffer并告知这次需要数据的长度
    //返回值告知底层读了多少数据，应该尽量保证return的长度等于需要的长度，如果返回<=0，则表示出错
    @Override
    public int onNuiNeedAudioData(byte[] buffer, int len) {
        int ret = 0;
        if (mAudioRecorder.getState() != AudioRecord.STATE_INITIALIZED) {
            Log.error("audio recorder not init");
            return -1;
        }
        ret = mAudioRecorder.read(buffer, 0, len);
        return nativeRecognizerNeedAudioData(buffer, len, ret);
    }

    //当录音状态发送变化的时候调用
    @Override
    public void onNuiAudioStateChanged(Constants.AudioState state) {
        Log.debug( "onNuiAudioStateChanged");
        if (state == Constants.AudioState.STATE_OPEN) {
            Log.debug( "audio recorder start");
            mAudioRecorder.startRecording();
            Log.debug( "audio recorder start done");
        } else if (state == Constants.AudioState.STATE_CLOSE) {
            Log.debug( "audio recorder close");
            mAudioRecorder.release();
        } else if (state == Constants.AudioState.STATE_PAUSE) {
            Log.debug( "audio recorder pause");
            mAudioRecorder.stop();
        }
        nativeRecognizerAudioStateChanged(state.ordinal());
    }

    @Override
    public void onNuiAudioRMSChanged(float val) {
        Log.debug( "onNuiAudioRMSChanged vol " + val);
        nativeRecognizerAudioRMSChanged(val);
    }

    @Override
    public void onNuiVprEventCallback(Constants.NuiVprEvent event) {
        Log.debug( "onNuiVprEventCallback event " + event);
        nativeRecognizerVprEventCallback(event.ordinal());
    }
}


