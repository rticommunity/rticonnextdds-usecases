@echo off
setlocal

IF []==[%PROTOTYPER_HOME%] (
  @echo PROTOTYPER_HOME must be set to the prototyper install dir to run this example
)

set dir=%~dp0
set executable_name=rtiddsprototyper


cd %dir%\..\apps

call %PROTOTYPER_HOME%\scripts\%executable_name% -cfgFile PrototyperConfig.xml -cfgName ParticipantLibrary::Receiver