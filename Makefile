CXX = E:\android\ndk\toolchains\arm-linux-androideabi-4.8\prebuilt\windows-x86_64\bin\arm-linux-androideabi-g++.exe
CXXFLAGS = --sysroot=E:/android/ndk/platforms/android-9/arch-arm \
           -std=c++11 -MMD -MF $(@:.o=.d) -MT $@

CC = E:\android\ndk\toolchains\arm-linux-androideabi-4.8\prebuilt\windows-x86_64\bin\arm-linux-androideabi-gcc.exe
CFLAGS = --sysroot=E:/android/ndk/platforms/android-9/arch-arm -std=c11 -MMD -MF $(@:.o=.d) -MT $@

LD = E:/android/ndk/toolchains/arm-linux-androideabi-4.8/prebuilt/windows-x86_64/bin/arm-linux-androideabi-gcc
LDFLAGS = --sysroot=E:/android/ndk/platforms/android-9/arch-arm \
          -L..\..\..\..\feinno-video\libav-10.1\output\lib \
          -shared

include jni/Makefile

OBJS := $(OBJS:%=jni/%)

LIB_NAME = libs/armeabi/lib$(NAME).so

all:$(LIB_NAME)

$(LIB_NAME): $(OBJS)
	$(LD) $(LDFLAGS) -llog -o $@ $^

clean:
	rm -f $(OBJS) $(LIB_NAME) $(OBJS:.o=.d)

-include $(wildcard $(OBJS:.o=.d))
