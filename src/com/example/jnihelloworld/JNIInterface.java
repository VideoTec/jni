package com.example.jnihelloworld;

public class JNIInterface {
	static {
		System.loadLibrary("helloworld");
	}
	
	public native void jni_helloworld(String str);
}
