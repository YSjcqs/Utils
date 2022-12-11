package com.epicgames.unreal;

import android.Manifest;
import android.app.Activity;
import android.content.pm.PackageManager;
import android.media.AudioFormat;
import android.media.AudioRecord;
import android.media.MediaRecorder;
import android.os.Build;
import android.os.Handler;
import android.os.HandlerThread;
import android.util.Log;
import android.widget.Toast;
import java.io.File;
import androidx.core.content.ContextCompat;

import com.alibaba.fastjson.JSONException;
import com.alibaba.fastjson.JSONObject;
import com.alibaba.idst.nui.AsrResult;
import com.alibaba.idst.nui.CommonUtils;
import com.alibaba.idst.nui.Constants;
import com.alibaba.idst.nui.INativeNuiCallback;
import com.alibaba.idst.nui.KwsResult;
import com.alibaba.idst.nui.NativeNui;

public class NuiSpeechManager implements INativeNuiCallback {

    public static native void UEDebug(String DebugMessage);

    NativeNui nui_dialog_instance = new NativeNui(Constants.ModeType.MODE_DIALOG);
    NativeNui nui_tts_instance = new NativeNui(Constants.ModeType.MODE_TTS);
    private Handler nui_handler;
    private AudioRecord nui_audio_record;
    private boolean nui_save_log = true;
    private Constants.VadMode nui_vad_mode;
    private Constants.LogLevel nui_log_level;
    private HandlerThread nui_handler_thread;
    private int current_dialog_state = -1;

    final static int WAVE_FRAM_SIZE = 20 * 2 * 1 *16000/1000; //20ms audio for 16k/16bit/mono
    public final static int SAMPLE_RATE = 16000;
    private boolean nui_initialized = false;
    private Activity game_activity;
    private String[] permissions = {
        Manifest.permission.RECORD_AUDIO
    };

    public int initNuiSpeech(Activity activity, int vad_mode, int log_level, boolean save_log)
    {
        if (CommonUtils.copyAssetsData(activity)) {
            UEDebug("copy assets data done");
        } else {
            UEDebug("copy assets failed");
            return -1;
        }
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.M) {
            // 检查该权限是否已经获取
            int i = ContextCompat.checkSelfPermission(activity, permissions[0]);
            // 权限是否已经 授权 GRANTED---授权  DINIED---拒绝
            if (i != PackageManager.PERMISSION_GRANTED) {
                // 如果没有授予该权限，就去提示用户请求
                activity.requestPermissions(permissions, 321);
            }
            while (true) {
                i = ContextCompat.checkSelfPermission(activity, permissions[0]);
                // 权限是否已经 授权 GRANTED---授权  DINIED---拒绝
                if (i == PackageManager.PERMISSION_GRANTED)
                    break;
            }
        }
        game_activity = activity;
        nui_save_log = save_log;
        nui_vad_mode = Constants.VadMode.values()[vad_mode];
        nui_log_level = Constants.LogLevel.values()[log_level];
        nui_handler_thread = new HandlerThread("nui_process_thread");
        nui_handler_thread.start();
        nui_handler = new Handler(nui_handler_thread.getLooper());
        return 0;
    }

    public int nuiStart(String app_key, String app_token, String nui_url)
    {
        nui_audio_record = new AudioRecord(MediaRecorder.AudioSource.DEFAULT, SAMPLE_RATE,
                AudioFormat.CHANNEL_IN_MONO, AudioFormat.ENCODING_PCM_16BIT, WAVE_FRAM_SIZE * 4);
        int ret = nui_dialog_instance.initialize(this, genInitParams(app_key, app_token, nui_url), nui_log_level, nui_save_log);
        if (ret == Constants.NuiResultCode.SUCCESS) {
            nui_initialized = true;
            nui_dialog_instance.setParams(genParams());
        } else {
            UEDebug("Nui initialized failed! Code:" + ret);
        }
        return ret;
    }

    public int nuiStop()
    {
        return nui_dialog_instance.release();
    }

    public int startDialog() {
        if (!nui_initialized) {
            UEDebug("nui 未初始化!");
            return -1;
        }
        nui_handler.post(new Runnable() {
            @Override
            public void run() {
                current_dialog_state = nui_dialog_instance.startDialog(nui_vad_mode, genDialogParams());
            }
        });
        return current_dialog_state;
    }

    public int stopDialog() {
        if (!nui_initialized) {
            UEDebug("nui 未初始化!");
            return -1;
        }
        nui_handler.post(new Runnable() {
            @Override
            public void run() {
                current_dialog_state = nui_dialog_instance.stopDialog();
            }
        });
        return current_dialog_state;
    }

    public boolean checkNuiInitState() {
        if (!nui_initialized) {
            UEDebug("Nui SDK 未初始化!");
            return false;
        } else {
            return true;
        }
    }

    private String genParams() {
        String params = "";
        try {
            JSONObject nls_config = new JSONObject();
            nls_config.put("enable_intermediate_result", true);
            // 参数可根据实际业务进行配置
            // 接口说明可见https://help.aliyun.com/document_detail/173528.html
            // nls_config.put("enable_punctuation_prediction", true);
            // nls_config.put("enable_inverse_text_normalization", true);
            // nls_config.put("max_sentence_silence", 800);
            // nls_config.put("enable_words", false);
            // nls_config.put("sample_rate", 16000);
            // nls_config.put("sr_format", "opus");
            JSONObject tmp = new JSONObject();
            tmp.put("nls_config", nls_config);
            tmp.put("service_type", Constants.kServiceTypeSpeechTranscriber);
            // 如果有HttpDns则可进行设置
            // tmp.put("direct_ip", Utils.getDirectIp());
            params = tmp.toString();
        } catch (JSONException e) {
            e.printStackTrace();
        }
        return params;
    }

    private String genInitParams(String app_key, String app_token, String nui_url) {
        String str = "";
        String assets_path = CommonUtils.getModelPath(game_activity);
        String debug_path = game_activity.getExternalCacheDir().getAbsolutePath() + "/debug_android_" + System.currentTimeMillis();
        createDir(debug_path);
        try{
            JSONObject object = new JSONObject();

            object.put("url", nui_url);
            object.put("app_key", app_key);
            object.put("token", app_token);
            object.put("workspace", assets_path);
            object.put("debug_path", debug_path);
            object.put("device_id", android.os.Build.SERIAL);

            // FullMix = 0   // 选用此模式开启本地功能并需要进行鉴权注册
            // FullCloud = 1
            // FullLocal = 2 // 选用此模式开启本地功能并需要进行鉴权注册
            // AsrMix = 3    // 选用此模式开启本地功能并需要进行鉴权注册
            // AsrCloud = 4
            // AsrLocal = 5  // 选用此模式开启本地功能并需要进行鉴权注册
            // 这里只能选择FullMix和FullCloud
            object.put("service_mode", Constants.ModeFullCloud);

            str = object.toString();
        } catch (JSONException e) {
            e.printStackTrace();
        }

        // 注意! str中包含ak_id ak_secret token app_key等敏感信息, 实际产品中请勿在Log中输出这类信息！
        UEDebug("InsideUserContext:" + str);
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

        return params;
    }
    
    private static int createDir (String dirPath) {
        File dir = new File(dirPath);
        //文件夹是否已经存在
        if (dir.exists()) {
            return 1;
        }

        if (!dirPath.endsWith(File.separator)) {//不是以 路径分隔符 "/" 结束，则添加路径分隔符 "/"
            dirPath = dirPath + File.separator;
        }

        //创建文件夹
        if (dir.mkdirs()) {
            return 0;
        }

        return -1;
    }

    public static native void NuiEventCallback(int NuiEvent, int resultCode, int arg2,
                                               int WuwType, String Kws,
                                               boolean finish, int asrCode, String asrString);
    public static native void NuiAudioStateChanged(int var1);
    public static native void NuiAudioRMSChanged(float var1);
    public static native void NuiVprEventCallback(int var1);

    //当回调事件发生时调用
    @Override
    public void onNuiEventCallback(Constants.NuiEvent event, final int resultCode, final int arg2, KwsResult kwsResult,
                                   AsrResult asrResult) {
        UEDebug("event=" + event);
        NuiEventCallback(event.ordinal(), resultCode, arg2, kwsResult.type.ordinal(),
                kwsResult.kws, asrResult.finish, asrResult.resultCode, asrResult.asrResult);
    }

    //当调用NativeNui的start后，会一定时间反复回调该接口，底层会提供buffer并告知这次需要数据的长度
    //返回值告知底层读了多少数据，应该尽量保证return的长度等于需要的长度，如果返回<=0，则表示出错
    @Override
    public int onNuiNeedAudioData(byte[] buffer, int len) {
        int ret = 0;
        if (nui_audio_record.getState() != AudioRecord.STATE_INITIALIZED) {
            UEDebug("audio recorder not init");
            return -1;
        }
        ret = nui_audio_record.read(buffer, 0, len);
        return ret;
    }

    //当录音状态发送变化的时候调用
    @Override
    public void onNuiAudioStateChanged(Constants.AudioState state) {
        UEDebug("onNuiAudioStateChanged");
        if (state == Constants.AudioState.STATE_OPEN) {
            UEDebug("audio recorder start");
            nui_audio_record.startRecording();
            UEDebug("audio recorder start done");
        } else if (state == Constants.AudioState.STATE_CLOSE) {
            UEDebug("audio recorder close");
            nui_audio_record.release();
        } else if (state == Constants.AudioState.STATE_PAUSE) {
            UEDebug( "audio recorder pause");
            nui_audio_record.stop();
        }
        NuiAudioStateChanged(state.ordinal());
    }

    @Override
    public void onNuiAudioRMSChanged(float val) {
//        UEDebug( "onNuiAudioRMSChanged vol " + val);
        NuiAudioRMSChanged(val);
    }

    @Override
    public void onNuiVprEventCallback(Constants.NuiVprEvent event) {
        UEDebug("onNuiVprEventCallback event " + event);
        NuiVprEventCallback(event.ordinal());
    }
}
