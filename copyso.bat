@echo off
cd %~dp0
:BUILD
call ndk-build V=1 NDK_DEBUG=0
echo �������
:WAIT
set /p KEY=
cls
if "%KEY%"=="C" (
  call ndk-build clean
  echo �������
  set KEY=0
  goto WAIT

) else (
  goto BUILD
)