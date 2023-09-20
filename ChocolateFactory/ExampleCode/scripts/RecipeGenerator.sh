#!/bin/sh

filename=$0
script_dir=`dirname $filename`
executable_name="RecipeGenerator"
bin_dir=${script_dir}/../build

if [ -f $bin_dir/$executable_name ]
then
    cd $bin_dir
    export LD_LIBRARY_PATH=$LD_LIBRARY_PATH
    ./$executable_name $*
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
