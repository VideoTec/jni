LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_CPP_EXTENSION := .cxx .cpp .cc
LOCAL_MODULE := helloworld
LOCAL_SRC_FILES := jni_entry.c hello_world.cpp
LOCAL_STATIC_LIBRARIES := avfilter avformat swresample swscale avcodec avutil opencore-amrnb x264
LOCAL_C_INCLUDES := $(LOCAL_PATH)/include/
LOCAL_CFLAGS := -std=c99 -D__STDC_CONSTANT_MACROS -Wl,--no-undefined
LOCAL_CPPFLAGS := -std=c++11
LOCAL_CPP_FEATURES := rtti exceptions
LOCAL_LDLIBS := -llog -ljnigraphics -landroid -lz -lGLESv2 -lEGL -lOpenSLES

include $(BUILD_SHARED_LIBRARY)

