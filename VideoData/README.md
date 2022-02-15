![Image](https://www.rti.com/hubfs/RTI_Oct2016/Images/rti-logounit.png)  
 RTI Connext DDS Use Case:  
 Streaming Video
==========================================

Concept
-------
This use case example will stream compressed video over a local or wide area network
such as the Internet.  RTI Connext provides the communications framework with adjustments
for Quality of Service and sample size, while external applications are used to 
encode ([FFMPEG](https://www.ffmpeg.org/)) and decode/display ([FFPLAY](https://www.ffmpeg.org/)) 
video and audio, in this case from a pre-recorded file or from a camera connected to the host system.  


FFMPEG and FFPLAY are available as buildable source code or as pre-built binary executables for 
most desktop host platforms, and are used here to encode video and audio using h.264 compression 
into an [MPEG-TS](https://en.wikipedia.org/wiki/MPEG_transport_stream) stream of 188-byte 'packets', 
which are then grouped and sent over a Connext DDS topic to one or more subscribers for presentation.
Note that this example could be made to work with other streaming video codecs.  


Additional Documentation
------------------------
Detailed documentation and how-to videos for this example are available online at:
  https://www.rti.com/developers/case-code/video-data-streaming

More Case + Code examples are available at:
  https://www.rti.com/resources/usecases



Download RTI Connext DDS
------------------------
If you do not already have RTI Connext DDS installed, download and install it
now. You can use a 30-day trial license to try out the product. Your download
will include the libraries that are required to run the example, and tools you
can use to visualize and debug your distributed system.

You can download RTI Connext here: https://www.rti.com/downloads/


How to Build this Code
----------------------
To build this example, an environment variable called `NDDSHOME`
must be set to point to the RTI Connext DDS installation directory, such as
`~/rti_connext_dds-6.1.0`.   This variable can be set manually, or by running
the `rtisetenv_xxx` configuration script located in the `resources/scripts` 
directory of the Connext installation, or by opening a "Connext DDS Professional 
Terminal" from the Utilities tab of the RTI Launcher. 
For more information on how to set an environment variable, please see the RTI
Core Libraries and Utilities Getting Started Guide.


We will refer to the location where you unzipped the example in this document
as EXAMPLE_HOME.  

All source and build files are located in `EXAMPLE_HOME/VideoData/ExampleCode/`.  
Before building or running the example, change directories into EXAMPLE_HOME/ExampleCode.

**Building on Windows**  
To build the application on a Windows host PC, open a terminal at `EXAMPLE_HOME/VideoData/ExampleCode/` and:
````
    (setup RTI build environment per above)
    (ensure Windows build tools are configured; 'vcvarsall.bat' is an example config script)
    mkdir build
    cd build
    cmake ..
    msbuild cc_streamvid.sln
````


**Building on Linux**  
To build the application on a Linux host PC, open a terminal at `EXAMPLE_HOME/VideoData/ExampleCode/` and:
````
    (setup RTI build environment per above)
    (ensure Linux build tools are configured)
    mkdir build
    cd build
    cmake ..
    make
````

The build process will create an executable application: `streamvid`, which is used as both 
publisher and subscriber of the streaming data.  


Running the Example
---------------
Open a terminal in the `EXAMPLE_HOME/VideoData/ExampleCode/` directory.   This terminal
must have the `FFMPEG` and `FFPLAY` utilities available in the system PATH variable.  

**Scripted Demonstrators**  
For convenience, a set of scripts are included to launch all of the needed components on 
a common host system;  this will 'stream' the video only within that machine, but serves as 
a baseline test that things are working correctly.  

The scripts are:
````
    run_demo         == File --> FFMPEG --> Connext pub --> Connext sub --> FFPLAY
    run_demo_ff_only == File --> FFMPEG --> FFPLAY (no Connext)
                        Fils is at: resource/RTI-vehicles-captions-480.mp4
    run_cam_demo     == Camera --> FFMPEG --> Connext pub --> Connext sub --> FFPLAY
    run_cam_ff_only  == Camera --> FFMPEG --> FFPLAY
                        This script may need editing to match your system/camera
````

Be sure to run the appropriate script for your system (*.bat scripts for Windows, *.sh scripts for Linux)  

**Command-Line Operation**  
`streamvid` can be run with several command-line arguments.  These can be viewed using the `-h` option, also printed below:

| argument | description |
| ---------- | ----------- |
| -d, --domain [int] | DDS Domain ID for this application (0) |
| -p, --pub [string] | Publish (video stream) as this ID |
| -s, --sub [string] | Subscribe (video stream) from this ID |
| -b, --buffer [int] | Size of the published DDS samples in bytes (1316) |
| -c, --configfile [string] | Configuration filename to load (config.properties)  |
| -w, --writeback | Write-back to the config file, updated args ||
| -q, --qos [a,b,c] | QoS profile to use: a:rel, b:besteffort, c:userdef (USER_QOS_PROFILES.xml) |
| -v, --verbosity [int] | How much debugging output to show (1:EXCEPTION)|
| -h, --help | Print this list and exit|

To launch as individual applications (on one or more host machines): Open 4 terminals:  

To launch as separate applications: Two pairs of terminals will be needed: 2 for publish, 2 for subscribe

Publisher terminal 1:

    build/streamvid.exe -p PubMachine

Publisher terminal 2:

    ffmpeg -re -i resource/RTI-vehicles-captioned-480.mp4 -g 15 -pix_fmt yuv420p -vcodec libx264 -preset ultrafast -tune zerolatency -f mpegts udp://127.0.0.1:2277

Subscriber terminal 1:

    build/streamvid.exe -s PubMachine

Subscriber terminal 2:

    ffplay -fflags nobuffer -i udp://127.0.0.1:2278


See the detailed description at: https://www.rti.com/developers/case-code/video-data-streaming
