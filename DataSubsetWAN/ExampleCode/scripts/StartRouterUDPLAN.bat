@echo off
setlocal

IF []==[%NDDSHOME%] GOTO NeedNDDSHome

IF "%1"=="" GOTO NeedArgs

set dir=%~dp0
set executable_name=rtiroutingservice

cd %dir%\..\routing

call "%NDDSHOME%\bin\%executable_name%" -cfgFile Routing-UDP-LAN.xml -cfgName %1
EXIT /B 0

:NeedNDDSHome
@echo NDDSHOME must be set to the RTI Connext install dir to run this example
EXIT /B 1

:NeedArgs
@echo Needs an arg for RS config (SOCI or COSI) for 'SquareOutCircleIn' or 'CircleOutSquareIn'
EXIT /B 1
