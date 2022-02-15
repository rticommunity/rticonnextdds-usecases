![Image](https://www.rti.com/hubfs/RTI_Oct2016/Images/rti-logounit.png)  
RTI Connext DDS Use Case:  
Vehicle Tracking
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
Detailed documentation and how-to videos for this example are available online at:
  https://www.rti.com/resources/usecases/vehicle-tracking

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
To run this example on all platforms, an environment variable called `NDDSHOME`
must be set to point to the RTI Connext DDS installation directory, such as
rti_connext_dds-6.0.x.
For more information on how to set an environment variable, please see the RTI
Core Libraries and Utilities Getting Started Guide.

We will refer to the location where you unzipped the example in this document
as EXAMPLE_HOME.  

All source and build files are located in EXAMPLE_HOME/ExampleCode/.  Before
building or running, change directories into EXAMPLE_HOME/ExampleCode. A 
CMakeLists.txtis provided and has been tested with Visual Studio 2017 64-bit 
and Ubuntu 18.04 


Windows Systems
---------------
Under EXAMPLE_HOME/ExampleCode/ create a build directory 
`mkdir build`

Change to the build directory
`cd build`

Run CMake to generate the build files
`cmake -G "Visual Studio 15 2017" -Ax64 ..`
 
Build the example
`cmake --build .`


Linux Systems
-------------
Under EXAMPLE_HOME/ExampleCode/ create a build directory 
`mkdir build`

Change to the build directory
`cd build`

Run CMake to generate the build files
`cmake ..`
 
Build the example
`cmake --build .`


Run the Example
---------------
On Windows systems, navigate to the `EXAMPLE_HOME\ExampleCode\scripts` directory.  
In this directory are three separate batch files to start the applications:

    - FlightPlanGenerator.bat
    - RadarGenerator.bat
    - TrackGui.bat


On Linux systems, navigate to the `EXAMPLE_HOME/ExampleCode/scripts` directory.  
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
```
--high-throughput        Use the high throughput XML configuration
```
Additional Command-Line Options for the Radar Generator
```
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
```
