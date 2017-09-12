@echo off
setlocal

IF []==[%NDDSHOME%] GOTO NeedNDDSHome

set dir=%~dp0
set executable_name=rtiroutingservice


cd %dir%\..\routing

call "%NDDSHOME%\bin\%executable_name%" -cfgFile Routing-UDP-LAN.xml -cfgName %1
EXIT /B 0

:NeedNDDSHome
@echo NDDSHOME must be set to the RTI Connext install dir to run this example
EXIT /B 1
