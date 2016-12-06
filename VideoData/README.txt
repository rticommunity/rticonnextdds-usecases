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

All source and build files are located in EXAMPLE_HOME/ExampleCode/.  Before
building or running, change directories into EXAMPLE_HOME/ExampleCode.

Windows Systems
---------------

On a Windows system, start by opening the file 
win32\StreamingVideoExample-<compilerver>.sln.

This code is made up of a combination of libraries, source, and IDL files that 
represent the interface to the application. The Visual Studio solution files 
are set up to automatically generate the necessary code and link against the 
required libraries.

Linux Systems
-------------

To build the applications on a Linux system, change directories to the 
ExampleCode directory and use the command:

gmake -f make/Makefile.<platform>
The platform you choose will be the combination of your processor, OS, and 
compiler version.  Right now this example only supports i86Linux2.6gcc4.5.5

Run the Example
---------------

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
