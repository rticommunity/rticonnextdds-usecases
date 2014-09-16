==========================================
 RTI Connext DDS Use Case: Streaming Video
==========================================

Concept
-------

This use case example includes two applications that send and receive 
streaming video data.

The two applications are:

1. Video Publisher (VideoPublisher)
        - Provides streaming video in VP8 format
2. Video Subscriber (VideoSubscriber)
	- Receives streaming video in VP8 format

Additional Documentation
------------------------

Additional documentation is available in the Docs directory and online at: 
www.rti.com/usecases/streaming-video.html

Download RTI Connext DDS
------------------------

If you do not already have RTI Connext DDS installed, download and install it 
now. You can use a 30-day trial license to try out the product. Your download 
will include the libraries that are required to run the example, and tools you 
can use to visualize and debug your distributed system.

How to Build this Code
----------------------

On all platforms, the first thing you must do is set an environment variable 
called NDDSHOME. This environment variable must point to the ndds.5.x.x 
directory inside your RTI Connext DDS installation. For more information on how 
to set an environment variable, please see the RTI Core Libraries and Utilities 
Getting Started Guide.

We will refer to the location where you unzipped the example in this document 
as EXAMPLE_HOME.  

IMPORTANT NOTE: the path EXAMPLE_HOME should not have blanks.

All source and build files are located in EXAMPLE_HOME/ExampleCode/.  Before
building or running, change directories into EXAMPLE_HOME/ExampleCode.

Build the example
-----------------
For building this example is needed to have installed CMake. You can download
from http://www.cmake.org/download/ . 

Then you have to run the CMake project in order to create your building files,
depending of the architecture you want to use. For this task you have to run in
a command prompt windows the Build.pl script is inside of scripts folder. 
Remember you have to run this scripts in the EXAMPLE_HOME\ExampleCode directory.
You can use the next command:
    perl ./scripts/Build.pl <architecture>
where you can choose your own architecture.

This script will create a 'projects' folder where your Visual Studio project, or 
your makefile will be stored. You can modify these files if you want.

Besides, the script will compile the example:
    - In Windows: run the msbuild compiler with the created solution.
    - In Linux: run the created makefile.

Also, Build.pl script will create two custom running scripts. The running 
scripts will be saved in the scripts directory following the template they have
in the same folder. 

The two custom script created are: one for the Publisher and the other one for
the subscriber. Both of them with the corresponding architecture you wrote 
calling the Build.pl script.

Run the Example
---------------
Remember that you have to run the scripts under EXAMPLE_HOME\ExampleCode 
directory!!!

On Windows systems, navigate to the EXAMPLE_HOME\ExampleCode\scripts directory.  
In this directory are two batch files to start the applications:

        - VideoPublisher.bat
        - VideoSubscriber.bat

On Linux systems, navigate to the EXAMPLE_HOME/ExampleCode/scripts directory. 
In this directory are two batch files to start the applications:

        - VideoPublisher.sh
        - VideoSubscriber.sh

You can run these script or batch files on the same machine, or you can copy 
this example and run on multiple machines. If you run them on the same machine, 
they will communicate over the shared memory transport. If you run them on 
multiple machines, they will communicate over UDP.


VideoPublisher Parameters:
--------------------------
The video publisher includes the option to disable multicast if your network 
does not support it.

Valid options are:
    --no-multicast       Do not use any multicast, including for discovery
                         (note you must edit XML config to include IP
                         addresses)

VideoSubscriber Parameters:
--------------------------
The video subscriber can choose to receive video streams over multicast. It
can also be configured to use no multicast at all, including for discovery.

Valid options are:
    --multicast          Use multicast for streaming video
    --no-multicast       Do not use any multicast, including for discovery
                         (note you must edit XML config to include IP
                         addresses)
