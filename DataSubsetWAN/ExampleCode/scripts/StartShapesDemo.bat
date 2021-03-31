@echo off
setlocal

IF []==[%NDDSHOME%] GOTO NeedNDDSHome

set dir=%~dp0
set executable_name=rtishapesdemo


cd %dir%\..\apps

call "%NDDSHOME%\bin\%executable_name%" -domainId %1
EXIT /B 0

:NeedNDDSHome
@echo NDDSHOME must be set to the RTI Connext install dir to run this example
EXIT /B 1

