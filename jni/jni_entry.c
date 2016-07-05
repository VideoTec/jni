#include "jni_util.h"

#include <stdio.h>
#include <string.h>
#include <signal.h>

static struct sigaction old_sa[NSIG];
JavaVM *g_jvm = 0;

void android_sigaction(int signal, siginfo_t *info, void *reserved)
{
    if (g_jvm != 0) {
      JNIEnv* env = 0;
      (*g_jvm)->AttachCurrentThread(g_jvm, &env, 0);
      jclass java_clazz = (*env)->FindClass(env, "com/xueyie/jni/JNITemplate");
      jmethodID methodID = (*env)->GetStaticMethodID(env, java_clazz, "onNativeCrashed", "()V");
      (*env)->CallStaticVoidMethod(env, java_clazz, methodID);
    }
    old_sa[signal].sa_handler(signal);
}

int jniRegisterNativeMethods(JNIEnv* env, const char* className,
    const JNINativeMethod* methods, int numMethods)
{
    LOGI("Registering %s's %d native methods...", className, numMethods);
    jclass java_clazz = (*env)->FindClass(env, className);

    //g_env = env;
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
    g_jvm = jvm;
    LOGI("JNI Template: v2.0.1 56");
    
    // Try to catch crashes...
    struct sigaction handler;
    memset(&handler, 0, sizeof(sigaction));
    handler.sa_sigaction = android_sigaction;
    handler.sa_flags = SA_RESETHAND;
#define CATCHSIG(X) sigaction(X, &handler, &old_sa[X])
    CATCHSIG(SIGILL);
    CATCHSIG(SIGABRT);
    CATCHSIG(SIGBUS);
    CATCHSIG(SIGFPE);
    CATCHSIG(SIGSEGV);
    CATCHSIG(SIGSTKFLT);
    CATCHSIG(SIGPIPE);

    if((*jvm)->GetEnv(jvm, (void **)&env, JNI_VERSION_1_4) < 0) {
        LOGI("jvm->GetEnv failed");
        return JNI_FALSE;
    }

    REG_JNI(HelloWorld, "com/xueyie/jni/JNITemplate");

    return JNI_VERSION_1_4;
}

void JNI_OnUnload(JavaVM *jvm, void *reserved) {
}
