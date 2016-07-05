#include "jni_util.h"
#include <string.h>

/**
  Jni module: HelloWorld
*/

extern "C" {
JNIEXPORT int JNICALL jniSay(JNIEnv *env, jobject clazz, jstring jni_str);
JNIEXPORT void JNICALL jniSigOccur(JNIEnv *env, jobject clazz);
}

JNINativeMethod gHelloWorldMethods[] = {
    {"say", "(Ljava/lang/String;)I", (void *)jniSay},
    {"sigOccur", "()V", (void *)jniSigOccur}
};
extern "C" const int gHelloWorldNumMethods = 
    sizeof(gHelloWorldMethods) / sizeof(gHelloWorldMethods[0]);

int jniSay(JNIEnv *env, jobject clazz, jstring jni_str) {
  const char *str_utf8 = env->GetStringUTFChars(jni_str, nullptr);
  //jniThrowNullPointerException(env, "test exception");
  LOGI("%s", str_utf8);
  env->ReleaseStringUTFChars(jni_str, str_utf8);
  return 9;
}

void jniSigOccur(JNIEnv *env, jobject clazz) {
  char *str = 0;
  LOGI("SIGSEGV will occur");
  strcpy(str, "test");
  LOGI("string: %s", str);
}