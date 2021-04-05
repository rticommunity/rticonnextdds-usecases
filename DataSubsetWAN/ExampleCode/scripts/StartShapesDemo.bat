@echo off
setlocal

IF []==[%NDDSHOME%] GOTO NeedNDDSHome

IF "%1"=="" GOTO NeedArgs

set dir=%~dp0
set executable_name=rtishapesdemo

cd %dir%\..\apps\ShapesDemo

call "%NDDSHOME%\bin\%executable_name%" -domainId %1
EXIT /B 0

:NeedNDDSHome
@echo NDDSHOME must be set to the RTI Connext install dir to run this example
EXIT /B 1

:NeedArgs
@echo Needs an arg for DDS Domain (5 or 6 for this example)
EXIT /B 1
