#include "jni_util.h"

#include <stdio.h>
#include <string.h>

int jniRegisterNativeMethods(JNIEnv* env, const char* className,
    const JNINativeMethod* methods, int numMethods)
{
    LOGI("Registering %s's %d native methods...", className, numMethods);
    jclass java_clazz = (*env)->FindClass(env, className);

    if (java_clazz == NULL) {
        char* msg;
        asprintf(&msg, "Native registration unable to find class '%s'; aborting...", className);
        (*env)->FatalError(env, msg);
    }

    if ((*env)->RegisterNatives(env, java_clazz, methods, numMethods) < 0) {
        char* msg;
        asprintf(&msg, "RegisterNatives failed for '%s'; aborting...", className);
        (*env)->FatalError(env, msg);
    }

    return 0;
}

#define REG_JNI(moduleName, className) \
  extern JNINativeMethod g##moduleName##Methods[]; \
  extern const int g##moduleName##NumMethods; \
  jniRegisterNativeMethods(env, className, \
                           g##moduleName##Methods, \
                           g##moduleName##NumMethods);

jint JNI_OnLoad(JavaVM *jvm, void *reserved) {
    JNIEnv *env = 0;
    LOGI("JNI Template: v2.0.1");

    if((*jvm)->GetEnv(jvm, (void **)&env, JNI_VERSION_1_4) < 0) {
        LOGI("jvm->GetEnv failed");
        return JNI_FALSE;
    }

    REG_JNI(HelloWorld, "com/xueyie/jni/JNITemplate");

    return JNI_VERSION_1_4;
}

void JNI_OnUnload(JavaVM *jvm, void *reserved) {
}
