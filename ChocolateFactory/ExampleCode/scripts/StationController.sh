#!/bin/sh

filename=$0
arch=$1
script_dir=`dirname $filename`
executable_name="StationController"
bin_dir=${script_dir}/../objs/${arch}/StationController

if [ -f $bin_dir/$executable_name ]
then
    cd $bin_dir
    export LD_LIBRARY_PATH=$LD_LIBRARY_PATH
    echo $LD_LIBRARY_PATH
    shift
    ./$executable_name $*
else
    echo "***************************************************************"
    echo $executable_name executable does not exist in:
    echo $bin_dir
    echo ""
    echo Please, try to recompile the application using the command:
    echo " $ make -f make/Makefile.${arch}"
    echo "***************************************************************"
fi
