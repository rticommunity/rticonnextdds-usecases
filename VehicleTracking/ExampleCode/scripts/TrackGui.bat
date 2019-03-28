@echo off
setlocal

set dir=%~dp0
set executable_name=TrackGuiApp.exe
set arch=%1

if "%arch%" == "" (
    echo "Architecture not set. Please specify arcitecture e.g. i86Win32VS2015, x64Win64VS2017
    exit /b
)

echo.%arch% | find /I "Win64">nul && (
   set toolVersion=Win64
) || (
   set toolVersion=Win32
)


if not exist  %dir%\..\win\Release\%arch%\%executable_name% ( 
   echo %dir%\..\win\Release\%arch%\%executable_name% does not exists
   echo Please try to compile the application using the Visual Studio project
   exit /b
)

if %toolVersion% == Win32 (
    set Path=%NDDSHOME%\lib\%arch%;%dir%\..\thirdparty\wxWidgets-3.1.2\Win32\lib\vc_dll;%dir%\..\thirdparty\proj-5.2\Win32\bin;%dir%\..\thirdparty\shapelib-1.5.0\lib\Win32\;"%PATH%"
) else (
    set Path=%NDDSHOME%\lib\%arch%;%dir%\..\thirdparty\wxWidgets-3.1.2\Win64\lib\vc_x64_dll;%dir%\..\thirdparty\proj-5.2\Win64\bin;%dir%\..\thirdparty\shapelib-1.5.0\lib\Win64\;"%PATH%"
) 

cd %dir%\..\win\Release\%arch%\

for /f "tokens=1,* delims= " %%a in ("%*") do set ALL_BUT_FIRST=%%b

start %executable_name% %ALL_BUT_FIRST%
