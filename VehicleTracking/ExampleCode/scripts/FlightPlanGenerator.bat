@echo off
setlocal

set dir=%~dp0
set executable_name=FlightPlanGenerator

set Path=%NDDSHOME%\lib\i86Win32VS2010;%dir%\..\thirdparty\wxWidgets-2.9.4\lib\vc_dll;%dir%\..\thirdparty\proj-4.8.0\lib\i86Win32VS2010;%dir%\..\thirdparty\shapelib-1.3.0\lib\i86Win32VS2010\;%PATH%

cd %dir%\..\win32\Release\i86Win32VS2010\

call %executable_name% %*