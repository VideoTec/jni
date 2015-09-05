@echo off
cd %~dp0
:BUILD
call ndk-build V=0 NDK_DEBUG=0
echo f | xcopy libs\armeabi-v7a\libjniTemplate.so D:\workspace\Project\app\src\main\jniLibs\armeabi-v7a\libjniTemplate.so /Y
echo 编译结束
:WAIT
set /p KEY=
cls
if "%KEY%"=="C" (
  call ndk-build clean
  echo 清理结束
  set KEY=0
  goto WAIT

) else (
  goto BUILD
)