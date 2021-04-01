#!/bin/bash

filename=$0
script_dir=`dirname $filename`
executable_name="rtiroutingservice"

if [ -f $NDDSHOME/bin/$executable_name ]
then
    if [[ ( "$1" = "Local5"  ||  "$1" = "Local6" ) ]] && [ -n "$2" ] && [ n "$3" ]
    then 
	    cd $script_dir/../routing
	    $NDDSHOME/bin/$executable_name \
    	    -cfgFile Routing-TCP-WAN.xml \
	        -cfgName $1 $2 $3
    else
        echo "*************************************************************"
        echo " $0: Wrong parameters"
        echo "" 
        echo " Usage:"
        echo " $0 [Local5|Local6] [-DRELAY_IPADDR=xx.xx.xx.xx]"
        echo " Where:"
        echo "    Local5 = My local UDP is on DDS domain 5, Local6 = Local domain 6"
        echo "    -DRELAY_IPADDR = IP address of the DDS TCP relay machine"
        echo "*************************************************************"
    fi
else
    echo "******************************************************************"
    echo "The NDDSHOME environment variable must be set to"
    echo "the Connext installation directory to run this example"
    echo "******************************************************************"
fi
