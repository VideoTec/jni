package com.xueyie.jni;

/**
 * jni 封装类
 * Created by wangxiangfx on 2016/6/14.
 */
public class JNITemplate {
    static {
        System.loadLibrary("jniTemplate");
    }

    public native int say(String str);
}
