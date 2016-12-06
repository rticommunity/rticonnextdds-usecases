@echo off
setlocal

set executableName=VideoPublisher.exe
set appName=VideoPublisher

set scriptDir=%~dp0
set args=%*
set releaseBinDir=%scriptDir%..\win32\Release\i86Win32VS2010
set debugBinDir=%scriptDir%..\win32\Debug\i86Win32VS2010

set Path=%NDDSHOME%\lib\i86Win32VS2010;%Path%

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