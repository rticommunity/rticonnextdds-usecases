# RTI Connext GStreamer Plugin

This repository builds GStreamer plugins that allow to publish, subscribe and process video frames using RTI Connext Professional. GStreamer works by constructing a "pipeline" made out of "elements" that start with a source, end with a sink, and have filters in between. Please read more about GStreamer basics in the tutorials [here](https://gstreamer.freedesktop.org/documentation/tutorials/basic/concepts.html?gi-language=c). Currently this repo creates the following GStreamer plugins:

- `connextsink`: takes camera frames at the end of a pipeline and publishes them to Connext DDS.
- `connextsrc`: subscribes to camera frames from Connext DDS and acts as a GStreamer source at the start of the pipeline.

This repository also contains a set of QoS profiles optimized for video streaming in the `USER_QOS_PROFILES.xml` file.

## Cloning Repository

To clone the repository you will need to run git clone as follows to download both the repository and its submodule dependencies:

```sh
git clone --recurse-submodule https://github.com/rticommunity/rticonnextdds-usecases.git
```

If you forget to clone the repository with `--recurse-submodule`, simply run
the following command to pull all the dependencies:

```sh
git submodule update --init --recursive
```

## Prerequisites

- Linux-based OS or WSL.
- Follow the official [documentation](https://gstreamer.freedesktop.org/documentation/installing/on-linux.html?gi-language=c) to setup GStreamer on your machine.
- Necessary GStreamer plugins include:

```text
    libgstreamer1.0-0 \
    gstreamer1.0-plugins-base \
    gstreamer1.0-plugins-good \
    gstreamer1.0-plugins-bad \
    gstreamer1.0-plugins-ugly \
    libgstreamer1.0-dev \
    libgstreamer-plugins-base1.0-dev \
    libgstreamer-plugins-good1.0-dev \
    libgstreamer-plugins-bad1.0-dev
```

## Building the Plugin

### Configure

```sh
cd rticonnextdds-usecases/VideoData/
cmake -B build -DCMAKE_BUILD_TYPE=Release
```

### Build

```sh
cmake --build ./build --config Release
```

### Install

```sh
sudo cmake --install build/
```

This will install the plugins and add them to your GStreamer plugin directory so you can use them directly from the command line like other GStreamer plugins.

## Sample Pipelines

Here are some example pipelines you can use to test the plugin is correctly installed:

### Publishing live video

```sh
source qos_variables.sh
source buffer_script.sh
gst-launch-1.0  videotestsrc ! x264enc speed-preset=ultrafast tune=zerolatency byte-stream=true key-int-max=15  ! h264parse ! video/x-h264,stream-format=byte-stream,alignment=au ! connextsink domain=0 topic=Video key=cam1 dp-qos-profile="TransportLibrary::SHMEM" dw-qos-profile="DataFlowLibrary::Reliable"
```

This command takes frames from the GStreamer `videotestsrc`, and encodes it with H.264, and then publishes it using Connext. The `connextsink` accepts parameters for DDS Domain, Topic name, and the key as defined in `/idl/video.idl`. It also accepts parameters for DomainParticipant and DataWriter Quality-of-Service profiles. If you are using the provided USER_QOS_PROFILES.xml in this repository, you will need to `source qos_variables.sh`. You should also run `source buffer_script.sh` to update the sizes of the send / receive socket buffers. The example above publishes reliably over Shared Memory. The other profiles are optimized for other transports, including UDP and the RTI Real-Time WAN Transport.

### Subscribing to live video

```sh
source qos_variables.sh
source buffer_script.sh
gst-launch-1.0 connextsrc domain=0 topic=Video key=cam1 dp-qos-profile="TransportLibrary::SHMEM" dr-qos-profile="DataFlowLibrary::Reliable" ! h264parse ! avdec_h264 ! videoconvert ! fpsdisplaysink
```

Similarly, this command subscribes using the `connextsrc` plugin to the Connext databus with the provided domain, topic, key and QoS. The pipeline parses the H.264 encoding and displays it with the GStreamer `fpsdisplaysink`. There may be some latency depending on the capabilities of your hardware to perform video encoding. The plugin also supports `x-raw`

With GStreamer, you can customize every aspect of the pipeline you build, allowing for different forms of encoding, as well as adjustments to the resolution and framerate. This allows you to make further performance optimizations depending on your hardware, network environment and available bandwidth. Some of the ways you can do this are described below:

## Other Useful Tools

On **Linux**, the following commands may be helpful (you'll need to `sudo apt install v4l2-ctl`):

```sh
v4l2-ctl --list-devices
```

This will list the video devices available on your machine.

```sh
v4l2-ctl -d /dev/video0 --list-formats-ext
```

This command will list the available output formats of a specific video device (/dev/video0) in this case. This is useful to see what resolutions, framerates and formats your camera is able to support for your GStreamer pipeline.

The output can look like this, depending on the capabilities of the camera you are using:

```sh
ioctl: VIDIOC_ENUM_FMT
    Type: Video Capture

        [0]: 'MJPG' (Motion-JPEG, compressed)
            Size: Discrete 1280x720
                Interval: Discrete 0.033s (30.000 fps)
            Size: Discrete 960x540
                Interval: Discrete 0.033s (30.000 fps)
            Size: Discrete 848x480
                Interval: Discrete 0.033s (30.000 fps)
            Size: Discrete 640x360
                Interval: Discrete 0.033s (30.000 fps)
            Size: Discrete 640x480
                Interval: Discrete 0.033s (30.000 fps)
            
        [1]: 'YUYV' (YUYV 4:2:2)
            Size: Discrete 160x120
                Interval: Discrete 0.033s (30.000 fps)
            Size: Discrete 320x180
                Interval: Discrete 0.033s (30.000 fps)
            Size: Discrete 320x240
                Interval: Discrete 0.033s (30.000 fps)
            Size: Discrete 424x240
                Interval: Discrete 0.033s (30.000 fps)
            Size: Discrete 640x360
                Interval: Discrete 0.033s (30.000 fps)
            Size: Discrete 640x480
                Interval: Discrete 0.033s (30.000 fps)
```

This camera is able to output two different formats, MJPG and YUY2.
You can adjust your publisher pipeline like to use different formats like so:

```sh
gst-launch-1.0  v4l2src device=/dev/video0 ! 'video/x-raw, width=640, height=480, framerate=30/1, format=YUY2' ! autovideoconvert ! x264enc speed-preset=ultrafast tune=zerolatency byte-stream=true key-int-max=15  ! h264parse ! video/x-h264,stream-format=byte-stream,alignment=au ! connextsink domain=0 topic=Video key=cam1 dp-qos-profile="TransportLibrary::SHMEM" dw-qos-profile="DataFlowLibrary::Reliable"
```

The above pipeline captures the video from `/dev/video0` with 640x480p resolution at 30FPS, encodes it into H.264 format, and then publishes it over Connext. You can modify the second stage of the pipeline with different supported resolutions and framerates.
The corresponding subscriber pipeline is the same as the one above:

```sh
gst-launch-1.0 connextsrc domain=0 topic=Video key=cam1 dp-qos-profile="TransportLibrary::SHMEM" dr-qos-profile="DataFlowLibrary::Reliable" ! h264parse ! avdec_h264 ! videoconvert ! fpsdisplaysink
```

For more information on GStreamer and how to construct your pipeline, refer to the [GStreamer documentation](https://gstreamer.freedesktop.org/documentation/?gi-language=c). This plugin example currently supports H.264 encoded video.
To use other formats, you will need to modify the `CONNEXTSRC_VIDEO_CAPS` defined in each plugin.

## Special Thanks

RTI would like to acknowledge the European Space Agency (ESA) Human Robot Interaction Lab and the following contributors for their role in creating this plugin:

- Thomas Krueger <https://github.com/kruegerrobotics>
- Andrei Gherghescu <https://github.com/andrei-ng>
- Edmundo Ferreira <https://github.com/edmundoferreira>
- Lukas Hann <lukas.hann@protonmail.com>
- Peter Schmaus <peter.schmaus@dle.de>

This software was developed by RTI with help from contributors at the European Space Agency.  It is not affiliated with, nor authorized, sponsored, or approved by, the developers of GStreamer.  GStreamer is subject to separate license terms and conditions.  IT IS YOUR RESPONSIBILITY TO ENSURE THAT YOUR USE OF GSTREAMER, AND ANY OTHER THIRD-PARTY SOFTWARE, COMPLIES WITH THE CORRESPONDING THIRD-PARTY LICENSE TERMS AND CONDITIONS.
