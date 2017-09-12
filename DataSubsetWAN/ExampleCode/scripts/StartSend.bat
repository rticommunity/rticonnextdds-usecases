@echo off
setlocal

IF []==[%NDDSHOME%] GOTO NeedNDDSHome

set dir=%~dp0
set executable_name=rtiddsprototyper


cd %dir%\..\apps

call "%NDDSHOME%\bin\%executable_name%" -cfgFile PrototyperConfig.xml -cfgName ParticipantLibrary::Sender -luaFile scripts\alarm.lua
EXIT /B 0

:NeedNDDSHome
@echo NDDSHOME must be set to the RTI Connext install dir to run this example
EXIT /B 1

