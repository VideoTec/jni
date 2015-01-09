#include "JNIInterface.h"

#define HELLOWORLD_JNI_CLS "com/example/jnihelloworld/JNIInterface"

extern const int g_methods_num;
extern JNINativeMethod g_helloworl_jnicls_methods[];

extern "C" jint JNI_OnLoad(JavaVM *jvm, void *reserved) {
    JNIEnv *env = 0;
    jclass helloworld_jni_cls;
    LOGI("JNI Hello World: v1.0.0");
    LOGI("JNI_OnLoad jvm: %X", (unsigned int)jvm);

    if(jvm->GetEnv((void **)&env, JNI_VERSION_1_4) < 0) {
        LOGI("jvm->GetEnv failed");
        return JNI_FALSE;
    }

    LOGI("get env: %X", (unsigned int)env);
    
    helloworld_jni_cls = env->FindClass(HELLOWORLD_JNI_CLS);

    if(helloworld_jni_cls) {
        LOGI("RegisterNatives begin");
        env->RegisterNatives(helloworld_jni_cls, g_helloworl_jnicls_methods, g_methods_num);
        LOGI("RegisterNatives end");

    } else {
        LOGI("cannt find java class: helloworld_jni_cls");
    }

    return JNI_VERSION_1_4;
}

extern "C" void JNI_OnUnload(JavaVM *jvm, void *reserved) {
}
