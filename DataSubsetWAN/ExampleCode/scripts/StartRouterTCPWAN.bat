@echo off
setlocal

IF []==[%NDDSHOME%] GOTO NeedNDDSHome

IF "%1"=="" GOTO NeedArgs
IF "%2"=="" GOTO NeedArgs
IF "%3"=="" GOTO NeedArgs

set dir=%~dp0
set executable_name=rtiroutingservice

cd %dir%\..\routing

call "%NDDSHOME%\bin\%executable_name%" -cfgFile Routing-TCP-WAN.xml -cfgName %1 -DREMOTE_IPADDR=%2 -DLOCAL_IPADDR=%3
EXIT /B 0

:NeedNDDSHome
@echo NDDSHOME must be set to the RTI Connext install dir to run this example
EXIT /B 1

:NeedArgs
@echo Needs args for RS config (SOCI or COSI) for 'SquareOutCircleIn' or 'CircleOutSquareIn',
@echo  and for IP addresses of remote machine (xx.xx.xx.xx) and local machine (yy.yy.yy.yy)
EXIT /B 1
