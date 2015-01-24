#include "jni_util.h"

#define REG_JNI(name, class_name) \
  extern JNINativeMethod g_##name##_methods[]; \
  extern const int g_##name##_methods_num; \
  jclass java_##name##_clazz = (*env)->FindClass(env, class_name); \
  if(java_##name##_clazz) { \
    if((*env)->RegisterNatives(env, java_##name##_clazz, g_##name##_methods, g_##name##_methods_num)) { \
      LOGE("register natives failed for class: %s", class_name); \
    } else { \
      LOGI("register natives success for class: %s", class_name); \
    } \
  } else { \
    LOGE("cannt find java class: &s", class_name); \
  }

jint JNI_OnLoad(JavaVM *jvm, void *reserved) {
    JNIEnv *env = 0;
    LOGI("JNI Hello World: v2.0.0");

    if((*jvm)->GetEnv(jvm, (void **)&env, JNI_VERSION_1_4) < 0) {
        LOGI("jvm->GetEnv failed");
        return JNI_FALSE;
    }

    REG_JNI(helloworld, "com/example/jni/HelloWorld");

    return JNI_VERSION_1_4;
}

void JNI_OnUnload(JavaVM *jvm, void *reserved) {
}
