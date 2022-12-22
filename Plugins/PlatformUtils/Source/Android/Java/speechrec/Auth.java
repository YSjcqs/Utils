package com.epicgames.unreal.speechrec;

import com.alibaba.fastjson.JSONObject;
import java.io.IOException;
import com.epicgames.unreal.speechrec.token.AccessToken;

public class Auth {
    private static String mAapKey = "";
    private static String mAccessKeyId = "";
    private static String mAccessKeySecret = "";

    public static JSONObject getAliYunTicket() {
        JSONObject object = new JSONObject();
        final AccessToken token;
        token = new AccessToken(mAccessKeyId, mAccessKeySecret);
        Thread th = new Thread(){
            @Override
            public void run() {
                try {
                    token.apply();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }

        };
        th.start();
        try {
            th.join(5000);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        String token_txt = token.getToken();
        // token生命周期超过expired_time, 则需要重新token = new AccessToken()
        long expired_time = token.getExpireTime();

        object.put("app_key", mAapKey);
        object.put("token", token_txt);
        object.put("device_id", Utils.getDeviceId());
        object.put("url", "wss://nls-gateway.cn-shanghai.aliyuncs.com:443/ws/v1");
        return object;
    }
}
