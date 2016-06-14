package com.example.jni;

public class HelloWorld {
	static {
		System.loadLibrary("jniTemplate");
	}
	
	public native void say_hello(String str);
}
