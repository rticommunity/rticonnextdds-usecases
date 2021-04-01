#!/bin/bash

filename=$0
script_dir=`dirname $filename`
executable_name="rtiroutingservice"

if [ -f $NDDSHOME/bin/$executable_name ]
then
    if [[ ( "$1" = "SOCI"  ||  "$1" = "COSI" ) ]] && [ -n "$2" ]
    then
        cd $script_dir/../routing
        $NDDSHOME/bin/$executable_name \
   	        -cfgFile Routing-TCP-LAN.xml \
   	        -cfgName $1 $2
    else
        echo "*************************************************************"
        echo " $0: Wrong parameters"
        echo "" 
        echo " Usage:"
        echo " $0 [SOCI|COSI] [-DREMOTE_IPADDR=xx.xx.xx.xx]"
        echo " Where:"
        echo "    SOCI = SquareOutCircleIn, COSI = CircleOutSquareIn"
        echo "    -DREMOTE_IPADDR = IP address of the remote machine"
        echo "*************************************************************"
    fi
else
    echo "*****************************************************************"
    echo "The NDDSHOME environment variable must be set to"
    echo "the Connext installation directory to run this example"
    echo "*****************************************************************"
fi
