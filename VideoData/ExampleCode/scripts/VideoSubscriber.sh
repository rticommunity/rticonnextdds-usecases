#!/bin/sh

filename=$0
script_dir=`dirname $filename`
executable_name="VideoSubscriber"

#Find NDDS architecture currently in use
oIFS="${IFS}"
IFS=:
for p in ${LD_LIBRARY_PATH}; do
    if [ -e ${p}/libnddsc.so ]; then
        ARCH=$(basename ${p})
    fi
done
IFS="${oIFS}"

bin_dir=${script_dir}/../objs/${ARCH}/VideoSubscriber

if [ -f $bin_dir/$executable_name ]
then
    cd $bin_dir
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
