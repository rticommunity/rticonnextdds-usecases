@echo off
setlocal

set dir=%~dp0
set executable_name=RecipeGenerator

set Path=%NDDSHOME%\lib\i86Win32VS2012;%PATH%

cd %dir%\..\win32\Release\i86Win32VS2012\

call %executable_name% %*