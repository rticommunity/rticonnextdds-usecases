=======================================================================
 RTI Connext DDS Use Case: Industrial Automation in a Chocolate Factory
=======================================================================

Concept
-------

This use case example includes three applications that send and receive 
data related to a chocolate manufacturing plant.  These applications 
represent an example of an application with a distributed workflow. The
key concern with this design is that multiple applications are updating
the state of an object as it passes through a workflow.  In this case we are
showing a chocolate factory, but this could be any application that 

The three applications are:

1. Recipe Generator (RecipeGenerator)
        - Provides a set of recipes that describe the steps that a lot
          takes to become cookies. Makes these recipes available to the 
          station controller at startup.
2. Manufacturing Execution System (ManufacturingExecutionSystem)
	- Dispatches a lot by updating the lot state.  It provides:
		- The first Station Controller that must process the lot
		- The name of the recipe for this lot
	- Monitors the progress of the lots
3. Station Controller (StationController)
	- Receives one or more lots that it must process
	- Updates lot state to mark it as waiting
	- If it is not busy, updates the lot state to mark it as being 
	  processed
	- Simulates processing of a lot by sleeping for a period of time.
	- When it is done, updates the lot state to mark it as completed
	  at this station.
	- Checks the recipe for the lot. If there are more steps, updates
	  the lot state to be assigned to the next station in the recipe.
	  Otherwise, updates the lot to be completed.

Additional Documentation
------------------------

Additional documentation is available in the Docs directory and online at: 
http://www.rti.com/resources/usecases/index.html

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
win32\ChocolateFactory-<compilerver>.sln.

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
In this directory are four batch files to start the applications:

        - RecipeGenerator.bat
        - MES.bat
	- StationController.bat (to start a single station controller)
	- AllStationControllers.bat (to start all station controllers)

On Linux systems, navigate to the EXAMPLE_HOME/ExampleCode/scripts directory. 
In this directory are four batch files to start the applications:

        - RecipeGenerator.sh
        - MES.sh
	- StationController.sh (to start a single station controller)
	- AllStationControllers.sh (to start all station controllers)

You can run these script or batch files on the same machine, or you can copy 
this example and run on multiple machines. If you run them on the same machine, 
they will communicate over the shared memory transport. If you run them on 
multiple machines, they will communicate over UDP.


RecipeGenerator Parameters:
--------------------------
The recipe generator includes the option to disable multicast if your network 
does not support it.

Valid options are:
    --no-multicast       Do not use any multicast, including for discovery
                         (note you must edit XML config to include IP
                         addresses)

MES Parameters:
---------------
The manufacturing execution system can be configured with a number of lots to 
process.  It can also be configured to send those lots with a specified amount
of time between them.  It can also be configured to not use multicast.

Valid options are:
    --num-lots [num]              Number of lots to start before shutting down
    --time-between [time in ms]    Time between starting lot batches
    --no-multicast                 Do not use multicast (note you must edit XML
                                   config to include IP addresses)

StationController Parameters:
-----------------------------
The station controller can be configured with which type of controller it is, 
numbered between 1 and 5: 
1 = sugar controller
2 = cocoa butter controller
3 = cocoa liquor controller
4 = vanilla controller
5 = milk controller

It also includes the option to disable multicast if
your network does not support it.

Valid options are:
    --controller-type [number] Valid values 1-5. Type of controller this app
                               represents
    --no-multicast             Do not use multicast (note you must edit XML
                               config to include IP addresses)

AllStationController Parameters:
--------------------------------
The AllStationController script starts five station controllers.  This takes
the same parameters as the StationController script (other than the
--controller-type parameter).