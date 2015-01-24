package com.example.jni;

public class HelloWorld {
	static {
		System.loadLibrary("helloworld");
	}
	
	public native void say_hello(String str);
}
