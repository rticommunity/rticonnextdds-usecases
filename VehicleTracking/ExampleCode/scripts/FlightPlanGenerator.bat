@echo off
setlocal

rem (c) 2021 Copyright, Real-Time Innovations, Inc. (RTI)
rem All rights reserved.
rem
rem RTI grants Licensee a license to use, modify, compile, and create derivative
rem works of the Software solely in combination with RTI Connext DDS. Licensee
rem may redistribute copies of the Software provided that all such copies are
rem subject to this License. The Software is provided "as is", with no warranty
rem of any type, including any warranty for fitness for any purpose. RTI is
rem under no obligation to maintain or support the Software. RTI shall not be
rem liable for any incidental or consequential damages arising out of the use or
rem inability to use the Software. For purposes of clarity, nothing in this
rem License prevents Licensee from using alternate versions of DDS, provided
rem that Licensee may not combine or link such alternate versions of DDS with
rem the Software.


set dir=%~dp0..\build
set executable_name=FlightPlanGenerator.exe
set Path=%NDDSHOME%\lib\%arch%;"%PATH%"


set exeDir=%dir%\Release\
if not exist  %exeDir%\%executable_name% (
    set exeDir=%dir%\Debug\
)
if not exist  %exeDir%\%executable_name% (
   echo %dir%\Release\%executable_name% or %dir%\Debug\%executable_name% does not exists
    echo Please compile the application using the Visual Studio project
    exit /b
)

call %exeDir%\%executable_name%  %*
