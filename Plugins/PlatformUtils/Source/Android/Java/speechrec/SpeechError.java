package com.epicgames.unreal.speechrec;

import com.alibaba.idst.nui.Constants;

public enum SpeechError {
    ERROR_UNKNOWN(-1),
    ERROR_ASSETS_DATA(0),
    ERROR_INIT(1),
    ERROR_PERMISSION(2),
    ERROR_START_DIALOG(3),
    ERROR_STOP_DIALOG(4);

    private int code;

    public int getCode() {
        return this.code;
    }

    private SpeechError(int k) {
        this.code = k;
    }

    public static SpeechError fromInt(int k) {
        switch(k) {
            case -1:
                return ERROR_UNKNOWN;
            case 0:
                return ERROR_ASSETS_DATA;
            case 1:
                return ERROR_INIT;
            case 2:
                return ERROR_PERMISSION;
            case 3:
                return ERROR_START_DIALOG;
            case 4:
                return ERROR_STOP_DIALOG;
            default:
                return ERROR_UNKNOWN;
        }
    }
}