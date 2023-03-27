###############################################################################
##                                                                           ##
##         Permission to modify and use for internal purposes granted.       ##
## This software is provided "as is", without warranty, express or implied.  ##
##                                                                           ##
###############################################################################

#! /bin/sh

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

### Launch FFMPEG to FFPLAY using UDP on this machine
case ${TERM} in
  lxterminal)
    ${TERM} ${GEOMETRY} -t ffmpeg -e "ffmpeg -re -i resource/RTI-vehicles-captioned-480.mp4 -g 15 -pix_fmt yuv420p -vcodec libx264 -preset ultrafast -tune zerolatency -f mpegts udp://127.0.0.1:2277" &
    ${TERM} ${GEOMETRY} -t ffplay -e "ffplay -fflags nobuffer -i udp://127.0.0.1:2277" &
    ;;
  xterm)
    ${TERM} ${GEOMETRY} -e "ffmpeg -re -i resource/RTI-vehicles-captioned-480.mp4 -g 15 -pix_fmt yuv420p -vcodec libx264 -preset ultrafast -tune zerolatency -f mpegts udp://127.0.0.1:2277" &
    ${TERM} ${GEOMETRY} -e "ffplay -fflags nobuffer -i udp://127.0.0.1:2277" &
    ;;
  gnome-terminal) 
    ${TERM} ${GEOMETRY} -- ffmpeg -re -i resource/RTI-vehicles-captioned-480.mp4 -g 15 -pix_fmt yuv420p -vcodec libx264 -preset ultrafast -tune zerolatency -f mpegts udp://127.0.0.1:2277 &
    ${TERM} ${GEOMETRY} -- ffplay -fflags nobuffer -i udp://127.0.0.1:2277 &
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
