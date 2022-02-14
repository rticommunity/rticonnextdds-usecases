@echo off
setlocal

cd %~dp0..

rem check with the FFMPEG manual for your version and platform for a correct camera-input command line.  These are examples:
rem start ffmpeg -y -f dshow -i video="Integrated Webcam":audio="Microphone (Realtek Audio)" -pix_fmt yuv420p -vcodec libx264 -preset ultrafast -tune zerolatency -f mpegts udp://127.0.0.1:2277
start ffmpeg -y -f vfwcap -r 25 -i 0 -g 15 -pix_fmt yuv420p -vcodec libx264 -preset ultrafast -tune zerolatency -f mpegts udp://127.0.0.1:2277
start ffplay -fflags nobuffer -probesize 32 -i udp://127.0.0.1:2277
