@echo off
setlocal

set executableName=VideoPublisher.exe
set appName=VideoPublisher
set arch=%1

if "%arch%" == "" (
    echo "Architecture not set. Please specify arcitecture e.g. i86Win32VS2015, i86Win86VS2017
    exit /b
)

set scriptDir=%~dp0
for /f "tokens=1,* delims= " %%a in ("%*") do set args=%%b

set releaseBinDir=%scriptDir%..\win32\Release\%arch%
set debugBinDir=%scriptDir%..\win32\Debug\%arch%

set Path=%NDDSHOME%\lib\%arch%;%scriptDir%..\thirdparty\gstreamer-sdk\win32\0.10\x86\bin;%Path%

if exist "%releaseBinDir%\%executableName%" (
    cd %releaseBinDir%
    call "%executableName%" %args%
) else if exist "%debugBinDir%\%executableName%" (
    cd %debugBinDir%
	call "%executableName%" %args%
) else (
    echo.
	echo Error: Could not find %executableName% under %releaseBinDir%
    echo or %debugBinDir%.
	echo.
	echo First, please compile %appName% using
	echo the Visual Studio solution you will find under
	echo %scriptDir%..\win32
	echo.
	exit /b 1
)
