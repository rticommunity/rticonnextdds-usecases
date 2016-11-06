@echo off
setlocal

IF []==[%NDDSHOME%] (
  @echo The NDDSHOME environment variable must be set to rti_connext_dds-5.x.x to run this example
)

set dir=%~dp0
set executable_name=rtiroutingservice


cd %dir%\..\routing

call %NDDSHOME%\bin\%executable_name% -cfgFile Routing-UDP-LAN.xml -cfgName %1
