package com.example.jni;

import android.app.Service;
import android.content.Intent;
import android.os.Handler;
import android.os.IBinder;
import android.util.Log;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.lang.Process;
import java.io.IOException;

public class CrashService extends Service {
    private Handler mHandler;
    public CrashService() {
    }

    @Override
    public void onCreate() {
        mHandler = new Handler(getMainLooper());
        super.onCreate();
    }

    @Override
    public IBinder onBind(Intent intent) {
        // TODO: Return the communication channel to the service.
        throw new UnsupportedOperationException("Not yet implemented");
    }

    @Override
    public int onStartCommand(Intent intent, int flags, int startId) {
        Log.e("tag", "crash service start 3");

        mHandler.postDelayed(new Runnable() {
            @Override
            public void run() {
                try {
                    Process process = Runtime.getRuntime().exec(new String[]{"logcat","-d","-t","500","-v","threadtime"});
                    BufferedReader br = new BufferedReader(new InputStreamReader(process.getInputStream()), 8096);
                    String line;
                    while((line = br.readLine()) != null) {
                        Log.d("crash", line);
                    }
                } catch (IOException e) {
                    Log.e("tag", e.toString());
                }

            }
        }, 5 * 1000);
        return super.onStartCommand(intent, flags, startId);
    }
}
