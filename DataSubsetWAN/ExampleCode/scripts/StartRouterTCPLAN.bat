@echo off
setlocal

IF []==[%NDDSHOME%] GOTO NeedNDDSHome

IF "%1"=="" GOTO NeedArgs

set dir=%~dp0
set executable_name=rtiroutingservice

cd %dir%\..\routing

call "%NDDSHOME%\bin\%executable_name%" -cfgFile Routing-TCP-LAN.xml -cfgName %1 -DREMOTE_IPADDR=%2 
EXIT /B 0

:NeedNDDSHome
@echo NDDSHOME must be set to the RTI Connext install dir to run this example
EXIT /B 1

:NeedArgs
@echo Needs args for RS config (SOCI or COSI) for 'SquareOutCircleIn' or 'CircleOutSquareIn',
@echo  and the IP address of the remote machine (xx.xx.xx.xx)
EXIT /B 1
