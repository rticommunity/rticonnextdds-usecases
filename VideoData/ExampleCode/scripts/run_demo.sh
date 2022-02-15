###############################################################################
##                                                                           ##
##         Permission to modify and use for internal purposes granted.       ##
## This software is provided "as is", without warranty, express or implied.  ##
##                                                                           ##
###############################################################################

#! /bin/sh

# determine script location
script_path=$( cd "$(dirname "${BASH_SOURCE[0]}")" ; pwd -P )
cd "$script_path"/..

# Determine which terminal program to use.
TERM=notset
for terminal in xterm gnome-terminal lxterminal
do
  type ${terminal} >/dev/null 2>&1
  if test $? -eq 0 ; then
    TERM=${terminal}
    break 
  fi
done

# Did we find one we know how to use? If not, error.
case ${TERM} in
  xterm) ;;
  gnome-terminal) ;;
  lxterminal) ;;
  *)
    echo "Terminal; ${TERM} is unknown! Program error!"
    exit 1
esac

### Make sure all component programs are available
PROGRAMS="./build/streamvid"

for exe in ${PROGRAMS}
do
  if [ ! -r ${exe} ] ; then
    echo "${exe} is not present. Did you build the application?"
    exit 1
  fi

  if [ -d ${exe} ] ; then
    echo "${exe} is a directory. You cannot execute that"
    exit 1
  fi
done

### Launch all component programs
case ${TERM} in
  lxterminal)
    ${TERM} ${GEOMETRY} -t streamvid-pub -e "./build/streamvid -p PubMachine" &
    ${TERM} ${GEOMETRY} -t streamvid-sub -e "./build/streamvid -s PubMachine" &
    ${TERM} ${GEOMETRY} -t ffmpeg -e "ffmpeg -re -i resource/RTI-vehicles-captioned-480.mp4 -g 15 -pix_fmt yuv420p -vcodec libx264 -preset ultrafast -tune zerolatency -f mpegts udp://127.0.0.1:2277" &
    ${TERM} ${GEOMETRY} -t ffplay -e "ffplay -fflags nobuffer -i udp://127.0.0.1:2278" &
    ;;
  xterm)
    ${TERM} ${GEOMETRY} -e "./build/streamvid -p PubMachine" &
    ${TERM} ${GEOMETRY} -e "./build/streamvid -s PubMachine" &
    ${TERM} ${GEOMETRY} -e "ffmpeg -re -i resource/RTI-vehicles-captioned-480.mp4 -g 15 -pix_fmt yuv420p -vcodec libx264 -preset ultrafast -tune zerolatency -f mpegts udp://127.0.0.1:2277" &
    ${TERM} ${GEOMETRY} -e "ffplay -fflags nobuffer -i udp://127.0.0.1:2278" &
    ;;
  gnome-terminal) 
    ${TERM} ${GEOMETRY} -- ./build/streamvid -p PubMachine &
    ${TERM} ${GEOMETRY} -- ./build/streamvid -s PubMachine &
    ${TERM} ${GEOMETRY} -- ffmpeg -re -i resource/RTI-vehicles-captioned-480.mp4 -g 15 -pix_fmt yuv420p -vcodec libx264 -preset ultrafast -tune zerolatency -f mpegts udp://127.0.0.1:2277 &
    ${TERM} ${GEOMETRY} -- ffplay -fflags nobuffer -i udp://127.0.0.1:2278 &
    ;;
  *) exit 1
esac

### When the user is done, let them kill the programs
echo -n "Press return to kill programs> "
read ignored

pid=$(pgrep ffmpeg)
kill -- -$pid
pid=$(pgrep ffplay)
kill -- -$pid
pids=$(pgrep streamvid)
for psid in ${pids}
do
  kill -- -$psid
done
