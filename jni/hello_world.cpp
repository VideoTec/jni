#include "jni_util.h"

extern "C" {

void helloworld(JNIEnv *env, jobject clazz, jstring jni_str) {
  const char *str_utf8 = env->GetStringUTFChars(jni_str, nullptr);
  //LOGI(str_utf8);
  env->ReleaseStringUTFChars(jni_str, str_utf8);
}

}

JNINativeMethod g_helloworld_methods[] = {
    {"say_hello", "(Ljava/lang/String;)V", (void *)helloworld}
};
extern "C" const int g_helloworld_methods_num = sizeof(g_helloworld_methods) / sizeof(g_helloworld_methods[0]);
