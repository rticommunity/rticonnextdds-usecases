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
            -cfgFile Routing-UDP-WAN.xml \
            -cfgName $1 -DCDS_IPADDR=$2
    else
        echo "*************************************************************"
        echo " $0: Wrong parameters"
        echo "" 
        echo " Usage:"
        echo " $0 [SOCI|COSI] [xx.xx.xx.xx]"
        echo " Where:"
        echo "    SOCI = SquareOutCircleIn, COSI = CircleOutSquareIn"
        echo "    xx.xx.xx.xx = IP address of an RTI Cloud Discover Server"
        echo "*************************************************************"
    fi
else
    echo "*****************************************************************"
    echo "The NDDSHOME environment variable must be set to"
    echo "your Connext installation directory to run this example"
    echo "*****************************************************************"
fi
