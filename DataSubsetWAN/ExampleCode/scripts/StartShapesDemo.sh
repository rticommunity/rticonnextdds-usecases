#!/bin/bash

executable_name="rtishapesdemo"
filename=$0
script_dir=`dirname $filename`

if [ -f $NDDSHOME/bin/$executable_name ]
then
    cd $script_dir/../apps
    $NDDSHOME/bin/$executable_name -domainId $1 &
else
    echo "**************************************************************************"
    echo "NDDSHOME must be set to RTI Connext install dir to run this example"
    echo "**************************************************************************"
fi
