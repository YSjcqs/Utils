package com.epicgames.unreal.speechrec;

import android.Manifest;
import android.app.Activity;
import android.content.pm.PackageManager;
import android.os.Build;

import androidx.core.content.ContextCompat;

import com.alibaba.fastjson.JSONException;
import com.alibaba.fastjson.JSONObject;
import com.alibaba.idst.nui.CommonUtils;
import com.alibaba.idst.nui.Constants;
import com.epicgames.unreal.Logger;

public class NuiSpeechManager {
    public static Logger Log = new Logger("UE", "NuiTtsBasic");

    private String tts_ticket;
    private String dialog_initParams;
    private String[] permissions = {Manifest.permission.RECORD_AUDIO};

    public NuiSpeechTranscriber speechTranscriber = new NuiSpeechTranscriber();
    public NuiTtsBasic ttsBasic = new NuiTtsBasic();

    public void initialize(Activity context, String app_key, String accessKeyId, String accessKeySecret)
    {
        if (CommonUtils.copyAssetsData(context)) {
            Log.debug("copy assets data done");
        } else {
            Log.debug("copy assets failed");
            return;
        }

        String assets_path = CommonUtils.getModelPath(context);
        Log.debug("use workspace " + assets_path);
        String debug_path = context.getExternalCacheDir().getAbsolutePath() + "/debug_" + System.currentTimeMillis();
        Utils.createDir(debug_path);

        tts_ticket = genTicket(assets_path, app_key, accessKeyId, accessKeySecret);
        dialog_initParams = genInitParams(assets_path, debug_path, app_key, accessKeyId, accessKeySecret);
        ttsBasic.initialize(tts_ticket);
        speechTranscriber.initialize(dialog_initParams);
    }

    public void audioPermissions(Activity context)
    {
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.M) {
            // 检查该权限是否已经获取
            int i = ContextCompat.checkSelfPermission(context, permissions[0]);
            // 权限是否已经 授权 GRANTED---授权  DINIED---拒绝
            if (i != PackageManager.PERMISSION_GRANTED) {
                // 如果没有授予该权限，就去提示用户请求
                context.requestPermissions(permissions, 321);
            }
        }
    }

    private String genTicket(String workpath, String app_key, String accessKeyId, String accessKeySecret) {
        String str = "";
        try {
            JSONObject object = Auth.getAliYunTicket(app_key, accessKeyId, accessKeySecret);
            object.put("workspace", workpath);
            // 设置为在线合成
            object.put("mode_type", "2");
            str = object.toString();
        } catch (JSONException e) {
            e.printStackTrace();
        }
        return str;
    }

    private String genInitParams(String workpath, String debugpath, String app_key, String accessKeyId, String accessKeySecret) {
        String str = "";
        try{
            JSONObject object = Auth.getAliYunTicket(app_key, accessKeyId, accessKeySecret);
            object.put("workspace", workpath);
            object.put("debug_path", debugpath);
            object.put("service_mode", Constants.ModeFullCloud);

            str = object.toString();
        } catch (JSONException e) {
            e.printStackTrace();
        }
        return str;
    }

    public static native void NuiEventCallback(int NuiEvent, int resultCode, String asrString);
    public static native void NuiAudioStateChanged(int var1);
    public static native void NuiAudioRMSChanged(float var1);
    public static native void NuiVprEventCallback(int var1);

    public static native void TtsEventCallback(int var1, String var2, int var3);
    public static native void TtsVolCallback(int var1);
}
