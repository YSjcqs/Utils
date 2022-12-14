package com.epicgames.unreal.speechrec;

import android.Manifest;
import android.media.AudioFormat;
import android.media.AudioRecord;
import android.media.MediaRecorder;
import android.os.Handler;
import android.os.HandlerThread;

import com.alibaba.fastjson.JSONException;
import com.alibaba.fastjson.JSONObject;
import com.alibaba.idst.nui.AsrResult;
import com.alibaba.idst.nui.Constants;
import com.alibaba.idst.nui.INativeNuiCallback;
import com.alibaba.idst.nui.KwsResult;
import com.alibaba.idst.nui.NativeNui;
import com.epicgames.unreal.Logger;

public class NuiSpeechTranscriber implements INativeNuiCallback {
    public static Logger Log = new Logger("UE", "NuiSpeechTranscriber");
    
    NativeNui nui_instance = new NativeNui();
    final static int WAVE_FRAM_SIZE = 20 * 2 * 1 * 16000 / 1000; //20ms audio for 16k/16bit/mono
    public final static int SAMPLE_RATE = 16000;
    private AudioRecord mAudioRecorder;
    private HandlerThread mHanderThread;
    private boolean mInit = false;
    private Handler mHandler;
    private String[] permissions = {Manifest.permission.RECORD_AUDIO};

    private String SpeechTextCache;

    public int initialize(String initParams) {
        //录音初始化，录音参数中格式只支持16bit/单通道，采样率支持8K/16K
        //使用者请根据实际情况选择Android设备的MediaRecorder.AudioSource
        //录音麦克风如何选择, 可查看https://developer.android.google.cn/reference/android/media/MediaRecorder.AudioSource
        mHanderThread = new HandlerThread("process_thread");
        mHanderThread.start();
        mHandler = new Handler(mHanderThread.getLooper());
        mAudioRecorder = new AudioRecord(MediaRecorder.AudioSource.DEFAULT, SAMPLE_RATE,
                AudioFormat.CHANNEL_IN_MONO, AudioFormat.ENCODING_PCM_16BIT, WAVE_FRAM_SIZE * 4);

        //初始化SDK，注意用户需要在Auth.getAliYunTicket中填入相关ID信息才可以使用。
        int ret = nui_instance.initialize(this,initParams, Constants.LogLevel.LOG_LEVEL_VERBOSE, true);
        Log.debug("result = " + ret);
        if (ret == Constants.NuiResultCode.SUCCESS) {
            mInit = true;
        } else {
            Log.error(Utils.getMsgWithErrorCode(ret, "init"));
        }

        //设置相关识别参数，具体参考API文档
        nui_instance.setParams(genParams());
        return ret;
    }

    public void releaseDialog() {
        nui_instance.release();
    }

    private String genParams() {
        String params = "";
        try {
            JSONObject nls_config = new JSONObject();
            nls_config.put("enable_intermediate_result", true);
//            参数可根据实际业务进行配置
//            接口说明可见https://help.aliyun.com/document_detail/173528.html
//            nls_config.put("enable_punctuation_prediction", true);
//            nls_config.put("enable_inverse_text_normalization", true);
//            nls_config.put("max_sentence_silence", 800);
//            nls_config.put("enable_words", false);
//            nls_config.put("sample_rate", 16000);
//            nls_config.put("sr_format", "opus");
            JSONObject tmp = new JSONObject();
            tmp.put("nls_config", nls_config);
            tmp.put("service_type", Constants.kServiceTypeSpeechTranscriber);
//            如果有HttpDns则可进行设置
//            tmp.put("direct_ip", Utils.getDirectIp());
            params = tmp.toString();
        } catch (JSONException e) {
            e.printStackTrace();
        }
        return params;
    }

    public void startDialog() {
        mHandler.post(new Runnable() {
            @Override
            public void run() {
                int ret = nui_instance.startDialog(Constants.VadMode.TYPE_P2T,
                        genDialogParams());
                Log.debug("start done with " + ret);
            }
        });
    }

    public void stopDialog()
    {
        mHandler.post(new Runnable() {
            @Override
            public void run() {
                long ret = nui_instance.stopDialog();
                Log.debug("cancel dialog " + ret + " end");
            }
        });
    }


    private String genDialogParams() {
        String params = "";
        try {
            JSONObject dialog_param = new JSONObject();
            params = dialog_param.toString();
        } catch (JSONException e) {
            e.printStackTrace();
            Log.error(e.getMessage());
        }

        Log.debug("dialog params: " + params);
        return params;
    }

    public boolean checkNotInitToast() {
        if (!mInit) {
            Log.warn("nui dialog not init!");
            return false;
        } else {
            return true;
        }
    }

    //当回调事件发生时调用
    @Override
    public void onNuiEventCallback(Constants.NuiEvent event, final int resultCode, final int arg2, KwsResult kwsResult,
                                   AsrResult asrResult) {
        Log.debug("event=" + event);
        if (event == Constants.NuiEvent.EVENT_TRANSCRIBER_COMPLETE) {
        } else if (event == Constants.NuiEvent.EVENT_ASR_PARTIAL_RESULT || event == Constants.NuiEvent.EVENT_SENTENCE_END) {
            SpeechTextCache = asrResult.asrResult;
            Log.debug("SpeechTextCache:"+SpeechTextCache);
        } else if (event == Constants.NuiEvent.EVENT_ASR_ERROR){
            Log.error("ERROR with " + resultCode);
            SpeechTextCache = "";
        }
        try {
            NuiSpeechManager.DialogEventCallback(event.ordinal(), resultCode, SpeechTextCache);
        }catch (Exception ex) {
            ex.printStackTrace();
            Log.error(ex.getMessage());
        }
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
        return ret;
    }

    //当录音状态发送变化的时候调用
    @Override
    public void onNuiAudioStateChanged(Constants.AudioState state) {
        Log.debug("onNuiAudioStateChanged");
        if (state == Constants.AudioState.STATE_OPEN) {
            Log.debug("audio recorder start");
            mAudioRecorder.startRecording();
            Log.debug("audio recorder start done");
        } else if (state == Constants.AudioState.STATE_CLOSE) {
            Log.debug("audio recorder close");
            mAudioRecorder.release();
        } else if (state == Constants.AudioState.STATE_PAUSE) {
            Log.debug("audio recorder pause");
            mAudioRecorder.stop();
        }
        try {
            NuiSpeechManager.DialogAudioStateChanged(state.ordinal());
        }catch (Exception ex) {
            ex.printStackTrace();
            Log.error(ex.getMessage());
        }
    }

    @Override
    public void onNuiAudioRMSChanged(float val) {
        Log.debug("onNuiAudioRMSChanged vol " + val);
        try {
            NuiSpeechManager.DialogAudioRMSChanged(val);
        }catch (Exception ex) {
            ex.printStackTrace();
            Log.error(ex.getMessage());
        }
    }

    @Override
    public void onNuiVprEventCallback(Constants.NuiVprEvent event) {
        Log.debug("onNuiVprEventCallback event " + event);
        try {
            NuiSpeechManager.DialogVprEventCallback(event.ordinal());
        }catch (Exception ex) {
            ex.printStackTrace();
            Log.error(ex.getMessage());
        }
    }
}



