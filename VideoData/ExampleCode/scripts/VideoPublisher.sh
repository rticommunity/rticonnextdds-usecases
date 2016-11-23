#!/bin/sh

video_executable_name=VideoPublisher

#Search platform using standard RTI scripts
executable_name=rtiddsspy
script_dir="$(dirname "$(which ${executable_name})")"
source ${NDDSHOME}/resource/scripts/rticommon.sh

video_bin_dir=objs/${platform_name}/VideoPublisher

if [ -f $video_bin_dir/$video_executable_name ]
then
    (cd $video_bin_dir; ./$video_executable_name $*)
else
    echo "***************************************************************"
    echo $executable_name executable does not exist in:
    echo $bin_dir
    echo ""
    echo Please, try to recompile the application using the command:
    echo " $ make -f make/Makefile.${ARCH}"
    echo "***************************************************************"
fi
