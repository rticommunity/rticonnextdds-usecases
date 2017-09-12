@echo off
setlocal

set dir=%~dp0
set executable_name=FlightPlanGenerator

set Path=%NDDSHOME%\lib\i86Win32VS2015;%dir%\..\thirdparty\wxWidgets-3.0.3\lib\vc_dll;%dir%\..\thirdparty\proj-4.9.3\lib\i86Win32VS2015;%dir%\..\thirdparty\shapelib-1.4.0\lib\i86Win32VS2015\;%PATH%

cd %dir%\..\win32\Release\i86Win32VS2015\

call %executable_name% %*