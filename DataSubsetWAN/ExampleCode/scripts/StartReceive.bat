@echo off
setlocal

IF []==[%NDDSHOME%] (
  @echo NDDSHOME must be set to the RTI Connext install dir to run this example
)

set dir=%~dp0
set executable_name=rtiddsprototyper


cd %dir%\..\apps

call %NDDSHOME%\bin\%executable_name% -cfgFile PrototyperConfig.xml -cfgName ParticipantLibrary::Receiver