cd %~dp0
:BUILD
call ndk-build V=1 NDK_DEBUG=0
pause
cls
goto BUILD