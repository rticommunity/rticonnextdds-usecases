#!/bin/sh

filename=$0
script_dir=`dirname $filename`
executable_name="StationController"
bin_dir=${script_dir}/../build

if [ -f $bin_dir/$executable_name ]
then
    cd $bin_dir
    export LD_LIBRARY_PATH=$LD_LIBRARY_PATH
    gnome-terminal --tab -- bash -c "./$executable_name --controller-type 1 $*"
    gnome-terminal --tab -- bash -c "./$executable_name --controller-type 2 $*"
    gnome-terminal --tab -- bash -c "./$executable_name --controller-type 3 $*"
    gnome-terminal --tab -- bash -c "./$executable_name --controller-type 4 $*"
    gnome-terminal --tab -- bash -c "./$executable_name --controller-type 5 $*"
else
    echo "***************************************************************"
    echo $executable_name executable does not exist in:
    echo $bin_dir
    echo ""
    echo Please, try to recompile the application using the command:
    echo " $ cmake --build ."
    echo while in the build directory.
    echo "***************************************************************"
fi
