/*****************************

{"initMediaSource", "(Ljava/lang/String;)I", (void *)media_source_init}
{"getFrameFromeMediaSource", "(ILandroid/graphics/Bitmap;[BLjava/lang/Integer;)I", (void *)media_source_get_frame},

CMediaSource *media_source_init(JNIEnv *env, jobject clazz, jstring fname) {
  const char *utf8 = env->GetStringUTFChars(fname, NULL);
  if(!utf8) LOGE("JNI: media_source_init: GetStringUTFChars failed");
  
  LOGI("JNI: media_source_init: alloc a new media source object: %s", utf8);
  CMediaSource *obj = new CMediaSource(utf8);
  LOGI("JNI: media_source_init: alloc a new media source object: %X", (unsigned int)obj);
  
  env->ReleaseStringUTFChars(fname, utf8);
  env->DeleteLocalRef(fname);
  return obj;
}

*****************************/

#include "JNIInterface.h"

extern "C" {

void helloworld(JNIEnv *env, jobject clazz, jstring jni_str) {
  const char *str_utf8 = env->GetStringUTFChars(jni_str, nullptr);
  LOGI(str_utf8);
  env->ReleaseStringUTFChars(jni_str, str_utf8);
}

}

JNINativeMethod g_helloworl_jnicls_methods[] = {
    {"jni_helloworld", "(Ljava/lang/String;)V", (void *)helloworld}
};
