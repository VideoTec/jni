package com.xueyie.jni;

import android.content.Context;
import android.content.Intent;
import android.util.Log;

import com.example.jni.CrashService;
import com.example.jni.MainActivity;

/**
 * jni 封装类
 * Created by wangxiangfx on 2016/6/14.
 */
public class JNITemplate {
    static {
        System.loadLibrary("jniTemplate");
    }

    public native int say(String str);
    public native void sigOccur();
    private static void onNativeCrashed() {
        new RuntimeException("native crash here").printStackTrace(); //这时候 throw 是没有意义的，可能接收不到
        //Log.v("tag", "native crashed");
        MainActivity.sCtx.startService(new Intent(MainActivity.sCtx, CrashService.class));
    }
}
