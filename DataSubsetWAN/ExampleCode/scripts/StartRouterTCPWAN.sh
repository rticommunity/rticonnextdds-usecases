#!/bin/bash

filename=$0
script_dir=`dirname $filename`
executable_name="rtiroutingservice"

if [ -f $NDDSHOME/bin/$executable_name ]
then
    if [[ ( "$1" = "SOCI"  ||  "$1" = "COSI" ) ]] && [ -n "$2" ] && [ n "$3" ]
    then 
	    cd $script_dir/../routing
	    $NDDSHOME/bin/$executable_name \
    	    -cfgFile Routing-TCP-WAN.xml \
	        -cfgName $1 -DREMOTE_IPADDR=$2 -DLOCAL_IPADDR=$3
    else
        echo "*************************************************************"
        echo " $0: Wrong parameters"
        echo "" 
        echo " Usage:"
        echo " $0 [SOCI|COSI] [xx.xx.xx.xx] [yy.yy.yy.yy]"
        echo " Where:"
        echo "    SOCI = SquareOutCircleIn, COSI = CircleOutSquareIn"
        echo "    xx.xx.xx.xx = IP address of the remote machine"
        echo "    yy.yy.yy.yy = IP address of the local machine"
        echo "*************************************************************"
    fi
else
    echo "******************************************************************"
    echo "The NDDSHOME environment variable must be set to"
    echo "the Connext installation directory to run this example"
    echo "******************************************************************"
fi
