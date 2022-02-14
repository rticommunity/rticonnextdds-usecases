@echo off
setlocal

cd %~dp0..

start ffmpeg -re -i resource/RTI-vehicles-captioned-480.mp4 -g 15 -pix_fmt yuv420p -vcodec libx264 -preset ultrafast -tune zerolatency -f mpegts udp://127.0.0.1:2277
start ffplay -fflags nobuffer -i udp://127.0.0.1:2277
