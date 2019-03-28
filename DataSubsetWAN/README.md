![Image](https://www.rti.com/hubfs/RTI_Oct2016/Images/rti-logounit.png)  
RTI Connext DDS Use Case:  
Connecting High-Speed LAN Data over a WAN
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
    - Filter temperature data between 32 and 100 so it never crosses the WAN
    - Decide which RTI Connext DDS data streams ("Topics" in DDS terms)
      are allowed to be sent across the WAN



Additional Documentation
------------------------
Detailed documentation and how-to videos for this example are available online at:
  https://www.rti.com/resources/usecases/real-time-lan-over-wan

More Case + Code examples are available at:
  https://www.rti.com/resources/usecases


Download RTI Connext DDS
------------------------
If you do not already have RTI Connext DDS installed, download and install it
now. You can use a 30-day trial license to try out the product. Your download
will include the libraries that are required to run the example, and tools you
can use to visualize and debug your distributed system.
You can download RTI Connext here: https://www.rti.com/downloads/


How to Run this Example
-----------------------
To run this example on all platforms, an environment variable called `NDDSHOME`
must be set to point to the RTI Connext DDS installation directory, such as
rti_connext_dds-6.0.x.
For more information on how to set an environment variable, please see the RTI
Core Libraries and Utilities Getting Started Guide.

We will refer to the location where you unzipped the example in this document
as EXAMPLE_HOME.  

All configuration and script files are located in EXAMPLE_HOME/ExampleCode/.  
Before running, change directories into EXAMPLE_HOME/ExampleCode.


To Start the Sender
-------------------
Run the (Windows) batch file: `scripts\StartSend.bat` or the (Linux) shell
script: `scripts/StartSend.sh`

This will send data in domain 6.


To Start the Receiver
---------------------
Run the (Windows) batch file: `scripts\StartReceive.bat` or the (Linux) shell
script: `scripts/StartReceive.sh`

This will receive data in domain 5.  
These two domains are logically isolated, so this application will not receive
any data until you run the RTI Routing Service.


To Start the Routing Services with UDP LAN Configuration
---------------------------------------------------------
To start the Routing Services in UDP LAN configuration,
enter the following commands:  
Windows:  
  `scripts\StartRouterUDPLAN.bat Router1`  
  `scripts\StartRouterUDPLAN.bat Router2`

Linux:  
  `scripts/StartRouterUDPLAN.sh Router1`  
  `scripts/StartRouterUDPLAN.sh Router2`

Example Output
--------------
The example output includes both Alarm and Temperature data.  Note that due to
temperature data between 32 and 100 degrees being filtered out, you may not see
data immediately.
```
  DataReader "AlarmReader" received sample 3 on Topic "Alarm" sent at 1373936124.699991 s
  appID: 234
  alarmType: TOO_COLD
  alarmLevel: WARNING

  DataReader "TemperatureReader" received sample 16 on Topic "Temperature" sent at 1373936125.699991 s
  appID: 234
  value: 30.000000

  DataReader "TemperatureReader" received sample 17 on Topic "Temperature" sent at 1373936126.699991 s
  appID: 234
  value: 29.000000

  DataReader "TemperatureReader" received sample 18 on Topic "Temperature" sent at 1373936127.699991 s
  appID: 234
  value: 28.000000
```

To Start the Routing Services with TCP WAN/LAN Configuration
---------------------------------------------------------
To start the Routing Services with TCP enabled, please visit the online
documentation for this example at:
https://www.rti.com/resources/usecases/real-time-lan-over-wan
