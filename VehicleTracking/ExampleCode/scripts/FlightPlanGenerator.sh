#!/bin/sh

filename=$0
arch=$1
script_dir=`dirname $filename`
executable_name="FlightPlanGenerator"
bin_dir=${script_dir}/../objs/${arch}/FlightPlan

if [ -z "$arch" ]
then
    echo "Architecture not set. Please specify arcitecture e.g. x64Linux3gcc5.4.0, x64Linux4gcc7.3.0"
    exit
fi

if [ -f $bin_dir/$executable_name ]
then
    cd $bin_dir
    export LD_LIBRARY_PATH=../thirdparty/proj-5.2/Linux/lib:../thirdparty/wxWidgets-3.1.2/Linux/lib/${arch}:$LD_LIBRARY_PATH
    shift
    ./$executable_name $*
else
    echo "***************************************************************"
    echo $executable_name executable does not exist in:
    echo $bin_dir
    echo ""
    echo Please, try to recompile the application using the command:
    echo " $ make -f make/Makefile.x64Linux3gcc5.4.0"
    echo "***************************************************************"
fi
