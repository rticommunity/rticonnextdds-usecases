#!/bin/sh
#
# (c) 2021 Copyright, Real-Time Innovations, Inc. (RTI)
# All rights reserved.
#
# RTI grants Licensee a license to use, modify, compile, and create derivative
# works of the Software solely in combination with RTI Connext DDS. Licensee
# may redistribute copies of the Software provided that all such copies are
# subject to this License. The Software is provided "as is", with no warranty
# of any type, including any warranty for fitness for any purpose. RTI is
# under no obligation to maintain or support the Software. RTI shall not be
# liable for any incidental or consequential damages arising out of the use or
# inability to use the Software. For purposes of clarity, nothing in this
# License prevents Licensee from using alternate versions of DDS, provided
# that Licensee may not combine or link such alternate versions of DDS with
# the Software.
#

filename=$0
script_dir=`dirname $filename`
executable_name="TrackGui"
bin_dir=${script_dir}/../build

if [ -f $bin_dir/$executable_name ]
then
    cd $bin_dir
    export LD_LIBRARY_PATH=$PWD/../../../thirdparty/proj-5.2/Linux/lib/${arch}:$PWD/../../../thirdparty/wxWidgets-3.1.2/Linux/lib/${arch}:../../../thirdparty/shapelib-1.5.0/Linux/lib:$LD_LIBRARY_PATH
    ./$executable_name $*
else
    echo "***************************************************************"
    echo $executable_name executable does not exist in:
    echo $bin_dir
    echo ""
    echo Please, try to recompile the application using the command:
    echo " $ cd ../build"
    echo " $ cmake .. "
    echo " $ cmake --build ."
    echo "***************************************************************"
fi
