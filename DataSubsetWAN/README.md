![Image](https://www.rti.com/hubfs/RTI_Oct2016/Images/rti-logounit.png)  
RTI Connext DDS Use Case:  
Connecting High-Speed LAN Data over a WAN
====================================================================

Concept
-------
This use case example shows two (or more) applications sharing real-time data across 
different kinds of logical network separations: different DDS domains in the same local network,
and separated local networks sharing data using TCP WAN or the RTI UDPv4-WAN transport.

This example set uses the RTI Shapes Demo as the test application(s), which uses the "ShapeType" 
data type.   This was selected for ease-of-use and to make it easier to understand and port to
your own applications.

It also uses RTI Routing Service to act as a gateway between domains and transports, with the
exception of the final example case which uses the RTI UDPv4-WAN transport natively with RTI
Shapes Demo, to provide a global connection using UDP.  Discovery assistance is (optionally)
provided by RTI Cloud Discovery Service, residing on a www-accessible server.


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


How to Run the Example use cases
-----------------------
To run this example on all platforms, an environment variable called `NDDSHOME`
must be set to point to the RTI Connext DDS installation directory, such as
rti_connext_dds-6.1.x.  Helper scripts to set the environment are included in the 
Connext installation directory, typically found at `"C:\Program Files\rti_connext_dds-6.1.0\resource\script\rtisetenv*"`
for Windows, or `source ~/rti_connext_dds-6.1.0/resource/scripts/rtisetenv*` for Linux.  
For more information on how to set an environment variable, please see the RTI
Core Libraries and Utilities Getting Started Guide.

We will refer to the location where you unzipped the example in this document
as `EXAMPLE_HOME`.  

All configuration and script files for this example are located in `EXAMPLE_HOME/ExampleCode/`.  
Before running, change directories into `EXAMPLE_HOME/ExampleCode`.

There are 6 use-cases in this example, all are using RTI Shapes Demo as test applications:
| Use Case               | Using               | Description                               |
|------------------------|---------------------|-------------------------------------------|
| 1. `UDP LAN`           | RTI Routing Service | Bridge DDS domain 5 and 6 on UDP LAN      |
| 2. `TCP LAN`           | RTI Routing Service | as above, on TCP LAN                      |
| 3. `TCP WAN`           | RTI Routing Service | as above, on TCP WAN                      |
| 4. `TCP WAN via Relay` | RTI Routing Service | as above, through cloud-based relay       |
| 5. `UDP WAN`           | RTI Routing Service | as above, using UDP-WAN transport and CDS |
| 6. `UDP WAN`           | UDPv4-WAN transport | Direct connection, discovery aided w/CDS  |

Where:  
 - `UDP-WAN` is the new RTI UDPv4-WAN transport, which enables direct WAN connections between Connext applications on separate LANs.
 - `CDS` is the RTI Cloud Discovery Service, which facilitates discovery between applications that are otherwise blocked from automated discovery (such as: no multicast, or residing on unconnected LANs).


To Launch the Test Applications
-------------------
These use cases are typically used to connect applications on separate computer instances, 
but because DDS provides a logical separation of DDS domains, most can be run on a single test machine.
This explanation will refer to the machine and terminal instances as `A` and `B`.  
Open a command terminal for each (A and B).


**RTI Shapes Demo**  
Two instances of RTI Shapes Demo are needed for this example, on DDS domains 5 and 6.  
For convenience, a shell script / batch file has been provided:

 - **Terminal A1:** `scripts/StartShapesDemo 5'
 - **Terminal B1:** `scripts/StartShapesDemo 6'
 
**NOTE**: scripts have been provided for Linux and Windows; use the appropriate suffix (.bat or .sh) for your environment.

This should result in 2 instances of Shapes Demo: one on domain 5, one on domain 6.  
Using the **Publish** and **Subscribe** menus in each Shapes Demo, set up the following:

**Shapes Demo 5**
 - Publish: Circle, any color or size, default settings for everything else.
 - Subscribe: Square, default settings.

**Shapes Demo 5**
 - Publish: Square, any color or size, default settings for everything else.
 - Subscribe: Circle, default settings.

*These applications cannot 'see' each other* because they are on different DDS domains (5 and 6), 
so the subscribed-to topics will receive no data samples.   
The following use-cases solve this in different ways.

###1. UDP LAN Bridge

This case uses a pair of Routing Service instances to bridge domains 5 and 6 via an intermediate UDP domain 0.
Note that the domains could also have been bridged directly (5 <--> 6) using a single Routing Service
instance, without using this intermediate domain.  

Open 2 terminals (A2 and B2) in `EXAMPLE_HOME/ExampleCode` and run the following scripts:
 - **Terminal A2:** `scripts/StartRouterUDPLAN COSI`
 - **Terminal B2:** `scripts/StartRouterUDPLAN SOCI`

These scripts will launch 2 instances of Routing Service, with topic routing configurations for
`COSI` (CircleOutSquareIn) and `SOCI` (SquareOutCircleIn), which results in the routing of:

 - Circle topics from domain 5 to domain 6.
 - Square topics from domain 6 to domain 5, with a content filter to block any Squares in the top half of Shapes Demo.

You should see results similar to:

  [image file showing 2 Shapes Demo instances, with circles and squares]

Note that because this uses an intermediate domain, other Connext DDS applications can also join this domain
as participants with read/write access.   Launching a 3rd Shapes Demo on domain 0 should have full access to
all ShapeType data topics (Square, Circle, Triangle).


###2. TCP LAN Bridge

This case also uses a pair of Routing Service instances to bridge domains 5 and 6 via an intermediate TCP domain.
This is useful for bridging topics between isolated network segments that allow TCP data to pass, but not UDP.

Open or re-use 2 terminals (A2 and B2) in `EXAMPLE_HOME/ExampleCode` and run the following scripts:
 - **Terminal A2:** `scripts/StartRouterTCPLAN COSI <ip address of the B machine>`
 - **Terminal B2:** `scripts/StartRouterTCPLAN SOCI <ip address of the A machine>`

These scripts will launch 2 instances of Routing Service, with topic routing configurations for
`COSI` (CircleOutSquareIn) and `SOCI` (SquareOutCircleIn), which results in the routing of:

 - Circle topics from domain 5 to domain 6.
 - Square topics from domain 6 to domain 5.

This 'bridge' is a point-to-point connection between the 2 Routing Service instances; no other
instances of Routing Service can join this intermediate connection.

You should see results similar to:

  [image file showing 2 Shapes Demo instances, with circles and squares]


###3. TCP WAN Bridge

This case is similar to case 2, but will use the TCPv4-WAN transport option to enable traversing
a WAN such as the internet.  This case requires publicly-accessible IP addresses and open ports on
the endpoint machines, and some editing of the Routing Service configuration file to match the opened
port number in the endpoint machines.

Open or re-use 2 terminals (A2 and B2) in `EXAMPLE_HOME/ExampleCode` and run the following scripts:
 - **Terminal A2:** `scripts/StartRouterTCPWAN COSI <ip address of the B machine> <ip address of this machine>`
 - **Terminal B2:** `scripts/StartRouterTCPWAN SOCI <ip address of the A machine> <ip address of this machine>`

These scripts will launch 2 instances of Routing Service, with topic routing configurations for
`COSI` (CircleOutSquareIn) and `SOCI` (SquareOutCircleIn), which results in a point-to-point connection
between these two Routing Service instances, bridging their respective domains on the selected topics.


###4. TCP WAN Bridge with Relay

This case uses a www-accessible "TCP Relay" machine to bridge and route topic data between separate networks.

  [block diagram image]

The TCP relay is a Routing Service instance, configured to automatically pass discovered topics between
TCP domains 1 and 2.   When used with Routing Service instances at each end (to pass topic data between
UDP domain 5 and TCP domain 1, and between UDP domain 6 and TCP domain 2) it creates a bridge that only
requires the IP address of the relay machine -- not of the endpoint machines.

Open or re-use 2 terminals (A2 and B2) in `EXAMPLE_HOME/ExampleCode` and run the following scripts:
 - **Terminal A2:** `scripts/StartRouterTCPWANRelay Local5 <ip address of the relay machine>`
 - **Terminal B2:** `scripts/StartRouterTCPWANRelay Local6 <ip address of the relay machine>`

These scripts will launch 2 instances of Routing Service, both configured for auto-topic routing between
domains 5 and 6 (over the TCP relay machine), which automatically creates a route for discovered topics. 
In this case, any shapes published by a Shapes Demo on one domain would be available for subscription on 
the other.

  [image of lots of shapes]
  
Note: in this case, DDS traffic is routed any-to-any on either side of the bridge, so any additional Shapes Demo
instances or Routing Service instances launched at other locations will also see the shapes demo samples 
at their location.

###5. UDP WAN Bridge with Cloud Discovery Service

This case uses RTI Routing Service with the RTI UDPv4_WAN transport option.  
The UDPv4_WAN transport is an optional component that enables direct connectivity between applications on 
separate UDP LANs, provided the LANs have connectivity to an external WAN such as the internet, typically
through a NAT router.  This case uses the assistance of RTI Cloud Discovery Service (CDS) on a web-accessible 
server to help determine the external address of the DDS participant, which enables discovery by other 
remote participants on similarly NAT-isolated LANs -- on a global scale.

Open or re-use 2 terminals (A2 and B2) in `EXAMPLE_HOME/ExampleCode` and run the following scripts:
 - **Terminal A2:** `scripts/StartRouterUDPWAN COSI <ip address of the CDS machine>`
 - **Terminal B2:** `scripts/StartRouterUDPWAN SOCI <ip address of the CDS machine>`

These scripts will launch Routing Service instances configured for UDPv4_WAN transport option, and with
a similar routing configuration as the above use cases:

 - Circle topics from domain 5 to domain 6.
 - Square topics from domain 6 to domain 5.

Note that complete discovery may take several seconds due to network delays in traversing the internet,
but once the connection is established it should have relatively short latency (to be determined by the 
specifics of your internet connection performance).


###6. UDP-WAN Transport with Cloud Discovery Service

This case has the user application (Shapes Demo) directly using the UDPv4_WAN transport option to 
connect with a remote application -- **no Routing Service needed**.  It also relies on Cloud Discovery
Service (CDS) to facilitate the automated discovery of participants on a global scale.

To launch this use case:  
Launch 2 copies of RTI Shapes Demo on the same domain, using the provided launch script:

 - **Terminal A1:** `scripts/StartShapesDemo 5'
 - **Terminal B1:** `scripts/StartShapesDemo 5'

In each instance of Shapes Demo:
 - Use the `Controls / Configuration` menu to select **Stop**
 - In the 'Choose the profile' drop-box, select `UDPv4_WAN_Profile` option and then press **Start**
 
This configuration is described in the file at `apps/ShapesDemo/USER_QOS_PROFILES.xml`, and points 
to an example CDS instace; you may need to change this address to a known-good CDS instance.

You should be able to publish shapes from either Shapes Demo, and to subscribe to them at the other.
Note that discovery may take several seconds depending on internet conditions.


Please visit the online version of the documentation for this example at:
https://www.rti.com/resources/usecases/real-time-lan-over-wan
