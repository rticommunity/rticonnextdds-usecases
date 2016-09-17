====================================================================
 RTI Connext DDS Use Case: Connecting High-Speed LAN Data over a WAN
====================================================================

Concept
-------

This use case example shows two (or more) logical applications sharing real-
time data within a LAN, and also sending a subset of that data over TCP 
across a WAN.

The applications are:

1. Temperature sensor and alarm provider
        - Writes temperature updates between 0 and 150 at a rate specified 
          by the user
        - Writes Alarm updates if the temperature has moved above 100
          degrees or below 32 degrees.
2. Temperature sensor and alarm receiver
        - Prints out temperature and alarm data
3. Routing Services
        - Act as a gateway between the LAN and WAN:  The WAN TCP addresses 
          are only specified in the Routing Service configuration, not in
          the local application
        - Filter temperature data between 32 and 100 so it never crosses the
          WAN
        - Decide which RTI Connext DDS data streams ("Topics" in DDS terms)
          are allowed to be sent across the WAN


Additional Documentation
------------------------

Additional documentation is available in the Docs directory and online at: 
www.rti.com/usecases/real-time-lan-over-wan.html


Download RTI Connext DDS
------------------------

If you do not already have RTI Connext DDS installed, download and install it 
now. You can use a 30-day trial license to try out the product. Your download 
will include the libraries that are required to run the example, and tools you 
can use to visualize and debug your distributed system. You can download RTI
Connext here: http://www.rti.com/downloads/

Download RTI Prototyper with Lua
--------------------------------

This example depends on the RTI Prototyper with Lua experimental product.
This is not required to send data across a WAN, but the example uses this to
generate interesting-looking data.  You can download this from here:
http://community.rti.com/downloads/experimental/rti-prototyper-with-lua


How to Run this Example
-----------------------

To run this example, on all platforms you must set two environment variables.

The first thing you must do is set an environment variable called NDDSHOME. 
This environment variable must point to the RTI Connext DDS installation, 
such as rti_connext_dds-5.2.x. For more information on how to set an 
environment variable, please see the RTI Core Libraries and Utilities Getting 
Started Guide.

We will refer to the location where you unzipped the example in this document 
as EXAMPLE_HOME.  

All configuration and script files are located in EXAMPLE_HOME/ExampleCode/.  
Before running, change directories into EXAMPLE_HOME/ExampleCode.



To Start the Sender
-------------------

Run the batch file: scripts\StartSend.bat or the shell script: 
scripts/StartSend.sh

This will send data in domain 6.


To Start the Receiver
---------------------
Run the batch file: scripts\StartReceive.bat or the shell script: 
scripts/StartReceive.sh

This will receive data in domain 5. These two domains are logically isolated, 
so this application will not receive any data until you run the Routing 
Service.


To Start the Routing Services with UDP LAN Configuration
---------------------------------------------------------

To start the Routing Services in UDP LAN configuration, enter the following 
commands: 
scripts\StartRouterLUDPAN.bat Router1
scripts\StartRouterUDPLAN.bat Router2

Example Output
--------------
The example output includes both Alarm and Temperature data.  Note that due to
temperature data between 32 and 100 degrees being filtered out, you may not see 
data immediately.

DataReader "AlarmReader" received sample 3 on Topic "Alarm" sent at 1373936124.6
99991 s
appID: 234
alarmType: TOO_COLD
alarmLevel: WARNING

DataReader "TemperatureReader" received sample 16 on Topic "Temperature" sent at
 1373936125.699991 s
appID: 234
value: 30.000000

DataReader "TemperatureReader" received sample 17 on Topic "Temperature" sent at
 1373936126.699991 s
appID: 234
value: 29.000000

DataReader "TemperatureReader" received sample 18 on Topic "Temperature" sent at
 1373936127.699991 s
appID: 234
value: 28.000000

To Start the Routing Services with TCP WAN/LAN Configuration
---------------------------------------------------------

To start the Routing Services with TCP enabled, please see the .pdf document
included with this example.
