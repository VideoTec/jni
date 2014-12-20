/*************
    this head file must be used in cpp file .
**/

#ifndef _H_JNI_INTERFACE_H_
#define _H_JNI_INTERFACE_H_

#include <string.h>
#include <jni.h>

#include <android/log.h>
#define  LOG_TAG    "JNILog"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

#endif //_H_JNI_INTERFACE_H_