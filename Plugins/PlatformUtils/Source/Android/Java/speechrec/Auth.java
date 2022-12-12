package com.epicgames.unreal.speechrec;

import com.alibaba.fastjson.JSON;
import com.alibaba.fastjson.JSONObject;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.Reader;

import com.epicgames.unreal.speechrec.token.AccessToken;


public class Auth {
    // 将鉴权信息打包成json格式
    public static JSONObject getTicket(String app_key, String accessKeyId, String accessKeySecret) {
        JSONObject object = new JSONObject();

        // ak_id ak_secret app_key如何获得, 请查看https://help.aliyun.com/document_detail/72138.html
        // 涉及账户安全, 以下账号信息请妥善保存, 不推荐明文存储。
        // 可将以下账号信息加密后存在服务器, 待需要传入SDK时在解密; 或在本地加密后存储(不推荐, 仍然有风险)。
        object.put("ak_id", app_key);
        object.put("ak_secret", accessKeyId);
        object.put("app_key", accessKeySecret);

        // 特别说明: 鉴权所用的id是由以下device_id，与手机内部的一些唯一码进行组合加密生成的。
        //   更换手机或者更换device_id都会导致重新鉴权计费。
        //   此外, 以下device_id请设置有意义且具有唯一性的id, 比如用户账号(手机号、IMEI等),
        //   传入相同或随机变换的device_id会导致鉴权失败或重复收费。
        object.put("device_id", Utils.getDeviceId());
        // 离线语音合成sdk_code取值：精品版为software_nls_tts_offline， 标准版为software_nls_tts_offline_standard
        // 唤醒sdk_code取值：nls_asrttssdk_public_cn
        object.put("sdk_code", "software_nls_tts_offline_standard");
        return object;
    }

    // 也可以将鉴权信息以json格式保存至文件，然后从文件里加载（必须包含成员：ak_id/ak_secret/app_key/device_id/sdk_code）
    // 该方式切换账号切换账号比较方便
    public static JSONObject getTicketFromJsonFile(String fileName) {
        try {
            String jsonStr = "";
            File jsonFile = new File(fileName);
            FileReader fileReader = new FileReader(jsonFile);
            Reader reader = new InputStreamReader(new FileInputStream(jsonFile),"utf-8");
            int ch = 0;
            StringBuffer sb = new StringBuffer();
            while ((ch = reader.read()) != -1) {
                sb.append((char) ch);
            }
            fileReader.close();
            reader.close();
            jsonStr = sb.toString();
            return JSON.parseObject(jsonStr);
        } catch (IOException e) {
            e.printStackTrace();
            return null;
        }
    }

    public static JSONObject getAliYunTicket(String app_key, String accessKeyId, String accessKeySecret) {
        JSONObject object = new JSONObject();
        final AccessToken token;
        //From Aliyun(https://help.aliyun.com/document_detail/72138.html) 请根据相关文档获取并填入
        //涉及账户安全, 以下账号信息请妥善保存
//        String app_key = "";
//        String accessKeyId = "";
//        String accessKeySecret = "";

        token = new AccessToken(accessKeyId, accessKeySecret);
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

        object.put("app_key", app_key);
        object.put("token", token_txt);
        object.put("device_id", Utils.getDeviceId());
        object.put("url", "wss://nls-gateway.cn-shanghai.aliyuncs.com:443/ws/v1");
        return object;
    }
}
