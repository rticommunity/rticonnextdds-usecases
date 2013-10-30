@echo off
setlocal

set dir=%~dp0
set executable_name=StationController

set Path=%NDDSHOME%\lib\i86Win32VS2010;%PATH%

cd %dir%\..\win32\Release\i86Win32VS2010\

start %executable_name% --controller-type 1 %*
start %executable_name% --controller-type 2 %*
start %executable_name% --controller-type 3 %*
start %executable_name% --controller-type 4 %*
start %executable_name% --controller-type 5 %*
