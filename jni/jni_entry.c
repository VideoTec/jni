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


int jniThrowException(JNIEnv* env, const char* className, const char* msg) {
    jclass exceptionClass = (*env)->FindClass(env, className);

    if (exceptionClass == NULL) {
        LOGE("Unable to find exception class %s", className);
        /* ClassNotFoundException now pending */
        return -1;
    }

    if ((*env)->ThrowNew(env, exceptionClass, msg) != JNI_OK) {
        LOGE("Failed throwing '%s' '%s'", className, msg);
        /* an exception, most likely OOM, will now be pending */
        return -1;
    }

    (*env)->DeleteLocalRef(env, exceptionClass);
    return 0;
}

int jniThrowExceptionFmt(JNIEnv* env, const char* className, const char* fmt, va_list args) {
    char msgBuf[512];
    vsnprintf(msgBuf, sizeof(msgBuf), fmt, args);
    return jniThrowException(env, className, msgBuf);
}

int jniThrowNullPointerException(JNIEnv* env, const char* msg) {
    return jniThrowException(env, "java/lang/NullPointerException", msg);
}

int jniThrowRuntimeException(JNIEnv* env, const char* msg) {
    return jniThrowException(env, "java/lang/RuntimeException", msg);
}

const char* jniStrError(int errnum, char* buf, size_t buflen);
int jniThrowIOException(JNIEnv* env, int errnum) {
    char buffer[80];
    const char* message = jniStrError(errnum, buffer, sizeof(buffer));
    return jniThrowException(env, "java/io/IOException", message);
}

const char* jniStrError(int errnum, char* buf, size_t buflen) {
#if __GLIBC__
    // Note: glibc has a nonstandard strerror_r that returns char* rather than POSIX's int.
    // char *strerror_r(int errnum, char *buf, size_t n);
    return strerror_r(errnum, buf, buflen);
#else
    int rc = strerror_r(errnum, buf, buflen);
    if (rc != 0) {
        // (POSIX only guarantees a value other than 0. The safest
        // way to implement this function is to use C++ and overload on the
        // type of strerror_r to accurately distinguish GNU from POSIX.)
        snprintf(buf, buflen, "errno %d", errnum);
    }
    return buf;
#endif
}
