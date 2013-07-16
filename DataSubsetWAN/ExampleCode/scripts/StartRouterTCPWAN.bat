@echo off
setlocal

IF []==[%ROUTER_HOME%] (
  @echo The ROUTER_HOME environment variable must be set to Connext_install_dir/RTI_Routing_Service_5.0.0 to run this example
)

set dir=%~dp0
set executable_name=rtiroutingservice


cd %dir%\..\routing

call %ROUTER_HOME%\scripts\%executable_name% -cfgFile Routing-TCP-WAN.xml -cfgName %1
