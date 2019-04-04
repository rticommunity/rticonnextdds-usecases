@echo off
setlocal

set dir=%~dp0
set executable_name=StationController.exe
set arch=%1
set Path=%NDDSHOME%\lib\%arch%;%PATH%

if "%arch%" == "" (
    echo "Architecture not set. Please specify arcitecture e.g. i86Win32VS2015, x64Win64VS2017
    exit /b
)

if not exist  %dir%\..\win\Release\%arch%\%executable_name% ( 
   echo %dir%\..\win\Release\%arch%\%executable_name% does not exists
   echo Please try to compile the application using the Visual Studio project
   exit /b
)

cd %dir%\..\win\Release\%arch%\

for /f "tokens=1,* delims= " %%a in ("%*") do set ALL_BUT_FIRST=%%b

start %executable_name% --controller-type 1 %ALL_BUT_FIRST%
start %executable_name% --controller-type 2 %ALL_BUT_FIRST%
start %executable_name% --controller-type 3 %ALL_BUT_FIRST%
start %executable_name% --controller-type 4 %ALL_BUT_FIRST%
start %executable_name% --controller-type 5 %ALL_BUT_FIRST%
