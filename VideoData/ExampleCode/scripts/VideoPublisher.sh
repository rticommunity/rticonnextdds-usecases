#!/bin/sh

filename=$0
arch=$1
script_dir=`dirname $filename`
executable_name="VideoPublisher"

if [ -z "$arch" ]
then
    echo "Architecture not set. Please specify arcitecture e.g. x64Linux3gcc5.4.0, x64Linux4gcc7.3.0"
    exit
fi


bin_dir=${script_dir}/../objs/${arch}/VideoPublisher

if [ -f $bin_dir/$executable_name ]
then
    cd $bin_dir
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
