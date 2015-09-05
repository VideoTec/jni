LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_CPP_EXTENSION := .cxx .cpp .cc
LOCAL_MODULE := jniTemplate
LOCAL_SRC_FILES := jni_entry.c hello_world.cpp
LOCAL_CFLAGS := -D__STDC_CONSTANT_MACROS -Wl,--no-undefined
LOCAL_CPPFLAGS := -std=c++11
LOCAL_CONLYFLAGS := -std=c99
LOCAL_LDLIBS := -llog -ljnigraphics -landroid -lz -lGLESv2 -lEGL

include $(BUILD_SHARED_LIBRARY)

