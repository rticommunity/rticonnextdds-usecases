#!/bin/sh

filename=$0
script_dir=`dirname $filename`
executable_name="FlightPlanGenerator"
bin_dir=${script_dir}/../objs/i86Linux2.6gcc4.4.5/FlightPlan

if [ -f $bin_dir/$executable_name ]
then
    cd $bin_dir
    export LD_LIBRARY_PATH=../thirdparty/proj-4.8.0/lib/i86Linux2.6gcc4.4.5:../thirdparty/wxWidgets-2.9.4/lib/i86Linux2.6gcc4.4.5:$LD_LIBRARY_PATH
    ./$executable_name $*
else
    echo "***************************************************************"
    echo $executable_name executable does not exist in:
    echo $bin_dir
    echo ""
    echo Please, try to recompile the application using the command:
    echo " $ make -f make/Makefile.i86Linux2.6gcc4.4.5"
    echo "***************************************************************"
fi
