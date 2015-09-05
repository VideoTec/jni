#ifndef _JNI_UTIL_H_
#define _JNI_UTIL_H_

#include <jni.h>
#include <android/log.h>

#define  LOG_TAG    "JNILog"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

#ifdef __cplusplus
extern "C" {
#endif

int jniThrowException(JNIEnv* c_env, const char* className, const char* msg);
int jniThrowExceptionFmt(JNIEnv* env, const char* className, const char* fmt, va_list args);
int jniThrowNullPointerException(JNIEnv* env, const char* msg);
int jniThrowRuntimeException(JNIEnv* env, const char* msg);
int jniThrowIOException(JNIEnv* env, int errnum);

#ifdef __cplusplus
}
#endif

#endif /* _JNI_UTIL_H_ */