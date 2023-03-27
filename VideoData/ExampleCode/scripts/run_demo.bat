@echo off
setlocal

cd %~dp0..

if exist "build\Debug\streamvid.exe" (
    set buildType=Debug
)
if exist "build\Release\streamvid.exe" (
    set buildType=Release
)

if [%buildType%] == [] (
   echo No application found. Check if the Visual Studio solution has been built
   ) else (
   start build\%buildType%\streamvid.exe -p PubMachine
   start build\%buildType%\streamvid.exe -s PubMachine
   start ffmpeg -re -i resource\RTI-vehicles-captioned-480.mp4 -g 15 -pix_fmt yuv420p -vcodec libx264 -preset ultrafast -tune zerolatency -f mpegts udp://127.0.0.1:2277
   start ffplay -fflags nobuffer -i udp://127.0.0.1:2278
)
