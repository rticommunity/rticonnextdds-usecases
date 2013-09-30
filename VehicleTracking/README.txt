===========================================
 RTI Connext DDS Use Case: Vehicle Tracking
===========================================

Concept
-------

This use case example includes three applications that send and receive data
related to an air traffic control system.

The three applications are:

1. Flight-plan Generator (FlightPlanGenerator)
        - Provides flight plans for aircraft
2. Radar Generator (RadarGenerator)
        - Provides high-speed radar track data
        - Receives flight plans from the Flight-plan Generator
        - Associates a flight ID from the flight plan with a radar track if 
          the flight plan is available
3. Air Traffic Control GUI (TrackGUI)
        - Receives radar tracks and flight plans
        - Displays the radar tracks
        - If a radar track has an associated flight ID, looks up the flight 
          plan and displays the flight plan data in a table with the track.

Additional Documentation
------------------------

Additional documentation is available in the Docs directory and online at: 
www.rti.com/usecases/vehicle-tracking.html

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
win32\AirTrafficExample-<compilerver>.sln.

This code is made up of a combination of libraries, source, and IDL files that 
represent the interface to the application. The Visual Studio solution files 
are set up to automatically generate the necessary code and link against the 
required libraries.

Linux Systems
-------------

To build the applications on a Linux system, change directories to the 
ExampleCode directory and use the command:

gmake –f make/Makefile.<platform>
The platform you choose will be the combination of your processor, OS, and 
compiler version.  Right now this example only supports i86Linux2.6gcc4.5.5

Run the Example
---------------

On Windows systems, navigate to the EXAMPLE_HOME\ExampleCode\scripts directory.  
In this directory are three separate batch files to start the applications:

        - FlightPlanGenerator.bat
        - RadarGenerator.bat
        - TrackGui.bat

On Linux systems, navigate to the EXAMPLE_HOME/ExampleCode/scripts directory.  
In this directory are three separate batch files to start the applications:

        - FlightPlanGenerator.sh
        - RadarGenerator.sh
        - TrackGui.sh

You can run these script or batch files on the same machine, or you can copy 
this example and run on multiple machines. If you run them on the same machine, 
they will communicate over the shared memory transport. If you run them on 
multiple machines, they will communicate over UDP.


RadarGenerator Parameters:
--------------------------

By default, the radar generator application runs with the lowest possible 
latency. To run it with increased throughput at the expense of latency, use the 
following parameter:

--high-throughput        Use the high throughput XML configuration

Additional Command-Line Options for the Radar Generator
--low-latency (default)  Use the low latency XML configuration 
--radar-id [number]      ID of the radar used to differentiate if there
                         are multiple radar generator applications
--start-tracks [number]  Number of tracks the generator should generate 
                         at startup
--max-tracks [number]    Maximum of tracks the generator sends at once
--run-rate [number]      Run in real time, faster, or slower.  For
                         example, 2 will run twice as fast.  .5 will 
                         run half as fast.
--creation-rate [number] How fast to create new tracks.
--no-multicast           Do not use multicast (note you must edit XML
                         config to include IP addresses)You can also 

