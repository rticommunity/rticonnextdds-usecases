#!/bin/sh

filename=$0
script_dir=`dirname $filename`
executable_name="rtiroutingservice"

if [ -f $NDDSHOME/bin/$executable_name ]
then
    if [ "$1" = "Router1" ] || [ "$1" = "Router2" ]
    then 
	cd $script_dir/../routing
	$NDDSHOME/bin/$executable_name \
	    -cfgFile Routing-TCP-LAN.xml \
	    -cfgName $1
    else
        echo "*************************************************************"
        echo " $0: Wrong parameters"
        echo "" 
        echo " Usage:"
        echo " $0 [Router1|Router2]"
        echo "*************************************************************"
    fi
else
    echo "*****************************************************************"
    echo "The NDDSHOME environment variable must be set to"
    echo "rti_connext_dds-5.x.x to run this example"
    echo "*****************************************************************"
fi
