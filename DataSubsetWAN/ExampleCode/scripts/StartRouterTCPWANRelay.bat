@echo off
setlocal

IF []==[%NDDSHOME%] GOTO NeedNDDSHome

IF "%1"=="" GOTO NeedArgs
IF "%2"=="" GOTO NeedArgs

set dir=%~dp0
set executable_name=rtiroutingservice

cd %dir%\..\routing

rem this configuration takes 2 arguments: config name (Local5 or Local6) and IP addr of relay machine.
call "%NDDSHOME%\bin\%executable_name%" -cfgFile Routing-TCP-WAN-RELAY.xml -cfgName %1 -DRELAY_IPADDR=%2 
EXIT /B 0

:NeedNDDSHome
@echo NDDSHOME must be set to the RTI Connext install dir to run this example 
EXIT /B 1

:NeedArgs
@echo Need args for config (Local5 or Local6) and relay machine IP address (xx.xx.xx.xx) 
EXIT /B 1
