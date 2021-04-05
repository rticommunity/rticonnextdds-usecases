@echo off
setlocal

IF []==[%NDDSHOME%] GOTO NeedNDDSHome

IF "%1"=="" GOTO NeedArgs
IF "%2"=="" GOTO NeedArgs

set dir=%~dp0
set executable_name=rtiroutingservice

cd %dir%\..\routing

call "%NDDSHOME%\bin\%executable_name%" -cfgFile Routing-UDP-WAN.xml -cfgName %1 -DCDS_IPADDR=%2
EXIT /B 0

:NeedNDDSHome
@echo environment variable NDDSHOME must be set to the RTI Connext install dir to run this example
EXIT /B 1

:NeedArgs
@echo Needs args for RS config (SOCI or COSI) for 'SquareOutCircleIn' or 'CircleOutSquareIn',
@echo  and for IP address of RTI Cloud Discovery Service instance (xx.xx.xx.xx)
EXIT /B 1
