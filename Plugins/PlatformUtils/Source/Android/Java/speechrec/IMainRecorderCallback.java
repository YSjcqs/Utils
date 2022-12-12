package com.epicgames.unreal.speechrec;

public interface IMainRecorderCallback {
    int onRecorderData(byte[] data, int len, boolean first_pack);
}
