#!/bin/sh

filename=$0
script_dir=`dirname $filename`
executable_name="rtiddsprototyper"

if [ -f $NDDSHOME/scripts/$executable_name ]
then
    cd $script_dir/../apps
    $NDDSHOME/scripts/$executable_name \
	-cfgFile PrototyperConfig.xml \
	-cfgName ParticipantLibrary::Sender \
	-luaFile scripts/alarm.lua
else
    echo "**************************************************************************"
    echo "NDDSHOME must be set to prototyper install dir to run this example"
    echo "**************************************************************************"
fi
