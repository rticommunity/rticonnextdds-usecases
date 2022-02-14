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

### Launch FFMPEG(camera) to FFPLAY using UDP on this machine
### Note: these are examples only; check with the FFMPEG manual for your version and platform for a correct camera-input command line.
case ${TERM} in
  lxterminal)
    ${TERM} ${GEOMETRY} -t ffmpeg -e "ffmpeg -y -f v4l2 -framerate 25 -video_size 640x480 -i /dev/video0 -pix_fmt yuv420p -vcodec libx264 -preset ultrafast -tune zerolatency -f mpegts udp://127.0.0.1:2277" &
    ${TERM} ${GEOMETRY} -t ffplay -e "ffplay -fflags nobuffer -i udp://127.0.0.1:2277" &
    ;;
  xterm)
    ${TERM} ${GEOMETRY} -e "ffmpeg -y -f v4l2 -framerate 25 -video_size 640x480 -i /dev/video0 -pix_fmt yuv420p -vcodec libx264 -preset ultrafast -tune zerolatency -f mpegts udp://127.0.0.1:2277" &
    ${TERM} ${GEOMETRY} -e "ffplay -fflags nobuffer -i udp://127.0.0.1:2277" &
    ;;
  gnome-terminal) 
    ${TERM} ${GEOMETRY} -- ffmpeg -y -f v4l2 -framerate 25 -video_size 640x480 -i /dev/video0 -pix_fmt yuv420p -vcodec libx264 -preset ultrafast -tune zerolatency -f mpegts udp://127.0.0.1:2277 &
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
