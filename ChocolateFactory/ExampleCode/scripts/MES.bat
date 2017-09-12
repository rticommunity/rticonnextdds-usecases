@echo off
setlocal

set dir=%~dp0
set executable_name=ManufacturingExecutionSystem

set Path=%NDDSHOME%\lib\i86Win32VS2015;%PATH%

cd %dir%\..\win32\Release\i86Win32VS2015\

call %executable_name% %*