/*********************************************************************************************
(c) 2005-2013 Copyright, Real-Time Innovations, Inc.  All rights reserved.    	                             
RTI grants Licensee a license to use, modify, compile, and create derivative works 
of the Software.  Licensee has the right to distribute object form only for use with RTI 
products.  The Software is provided “as is”, with no warranty of any type, including 
any warranty for fitness for any purpose. RTI is under no obligation to maintain or 
support the Software.  RTI shall not be liable for any incidental or consequential 
damages arising out of the use or inability to use the software.
**********************************************************************************************/
#ifndef RADAR_INTERFACE_H
#define RADAR_INTERFACE_H


#include "ndds/ndds_cpp.h"
#include "ndds/ndds_namespace_cpp.h"
#include "../CommonInfrastructure/DDSCommunicator.h"
#include "../Generated/AirTrafficControl.h"
#include "../Generated/AirTrafficControlSupport.h"
#include "TrackGenerator.h"
#include "GeneratorAdapter.h"

#include <map>


class FlightPlanReader;
class RadarWriter;
class RadarInterface;

// ----------------------------------------------------------------------------
// The radar interface is composed of two parts:  
//
// Writing radar data:
// -------------------
// This application sends radar data, either with the lowest possible latency
// or with higher throughput at a slight cost in latency.
// 
// For information on the radar data type, please see the AirTrafficControl.idl
// file.  
//
// For information on the quality of service for throughput vs. latency, please
// see the radar_profiles_multicast.xml file.
//
// Reading flight plan data:
// -------------------------
// This application receives flight plan data.  This data is sent less
// frequently, and if it was sent before the radar application was started, it
// must be automatically delivered to the radar at startup.  Becasue of these
// requirements, it has different QoS than the radar data.  This QoS is
// generally described as the QoS for "state data"
// 
// For information on the flight plan data type, please see the 
// AirTrafficControl.idl file.  
//
// For information on the quality of service for flight plan state data, please
// see the flight_plan_profiles.xml file.


// This enumeration is passed in when creating the interface, to choose whether
// to send with lowest latency, or with best throughput.
// These map in the source to two different QoS profiles that are described in 
// the USER_QOS_PROFILES.xml file.  The XML contains different tunings for how 
// to send or receive data.
enum RadarProfile 
{
	LOW_LATENCY,
	HIGH_THROUGHPUT
};




// ------------------------------------------------------------------------- //
//
// RadarInterface:
// A class that sets up the DDS interface (the network interface) of this 
// radar application, including creating appropriate DDS DataWriters, DDS
// DataReaders, and all other DDS objects.
//
// ------------------------------------------------------------------------- //
class RadarInterface  
{

public:

	// This takes in the ID of the radar which becomes part of the data when 
	// sending information over the network.  This allows a real-world
	// application to differentiate between different sources of track data, 
	// which is commonly necessary.
	// This also takes in a parameter for the maximum flights that the 
	// radar application can generate.  This gets used both for generating the 
	// radar tracks, and for setting up resource limits in the middleware, 
	// which the middleware uses as the maximum amount of queue size to 
	// allocate


	// --- Constructor --- 
	// Note that the radar may have two separate profiles depending in whether
	// the requirement is for lowest latency or highest throughput.  Flight
	// plan data has only one profile, so it is not part of the interface
	RadarInterface(long radarId, int maxFlights, RadarProfile profile, 
		std::vector<std::string>qosFileNames);

	// --- Destructor --- 
	~RadarInterface();

	// --- Getter for the RadarWriter --- 
	// This returns a RadarWriter object, which is the part of the network
	// interface that sends the radar data over the network.  Look at the
	// RadarWriter class to see how to write data in RTI Connext DDS.  This
	// RadarWriter class has some logic for writing efficiently for low latency
	RadarWriter *GetRadarWriter() 
	{
		return _radarWriter;
	}

	// This returns the FlightPlan receiver - a small wrapper around the 
	// FlightPlanDataReader that initializes the reader and uses the 
	// DDS "WaitSet" object to wait for flight plans
	FlightPlanReader *GetFlightPlanReader() 
	{
		return _flightPlanReader;
	}

	// --- How many flights should the middleware handle at once? --- 
	// This is the maximum number of flights the middleware is expected to 
	// handle at one time.  This could be set up as unlimited, but in a real
	// system that must preallocate memory, this is one way to tell the 
	// middleware the maximum amount of memory to allocate
	int GetMaxFlightsToHandle() 
	{
		return _maxFlightsToHandle;
	}

	// --- Getter for Communicator --- 
	// Accessor for the communicator (the class that sets up the basic
	// DDS infrastructure like the DomainParticipant).
	// This allows access to the DDS DomainParticipant/Publisher/Subscriber
	// classes
	DDSCommunicator *GetCommunicator() 
	{
		return _communicator; 
	}

private:
	// --- Private members ---

	// This contains the calls that allow the interface to create a 
	// "DomainParticipant", the first object that must be created to 
	// communicate over a DDS middleware.
	DDSCommunicator *_communicator;

	// Used to identify which radar this is sending the flight plan information
	// This example is not focused on how to fuse radar tracks from multiple
	// radar, but in a real system this information is valuable for fusing
	// data from multiple radar.  Typically when you have duplicate sensors 
	// that are providing the same or similar information, the sensor ID will 
	// be a part of the data model.
	long _radarId;

	// Wrapper class around RTI Connext DDS for writing radar tracks.  This has
	// some logic to write with the lowest possible latency.
	RadarWriter *_radarWriter;

	// Used for receiving flight plan data, and being notified about the
	// arrival of flight plan data.
	FlightPlanReader *_flightPlanReader;

	// This maximum number is used in the middleware in several places
	int _maxFlightsToHandle;

};

// ------------------------------------------------------------------------- //
//
// FlightPlanReader:
// Used for receiving flight plans.  This encapsulates the concepts of a DDS
// type-specific DataReader (for type FlightPlan), along with the mechanisms
// for accessing data - in this case, this allows the application to block one
// of its threads to wait for data from the FlightPlanReader.
//
// ------------------------------------------------------------------------- //
class FlightPlanReader 
{

public:

	// --- Constructor --- 
	// This creates a DDS DataReader that subscribes to flight plan information.  
	// This uses the app object to access the DomainParticipant, and it uses the 
	// QoS profiles specified when creating the DataReader.  The XML QoS files
	// were previously configured when the RadarInterface's DDSCommunicator was
	// created.
	FlightPlanReader(RadarInterface *comm, DDS::Subscriber *sub, 
		const std::string &qosLibrary, const std::string &qosProfile);


	// --- Destructor --- 
	~FlightPlanReader();

	// --- Receive flight plans --- 
	// This example is looking up all flight plans, and leaving them 
	// in the middleware's queue.  it does this because it does not need
	// to do any transformation on the flight plan data.  This example does
	// not care about when the flight plans arrive, it simply queries which 
	// flight plans are in the queue (polling for data)
	// See the other example application for alternatives - being notified
	// that data is available.
	void WaitForFlightPlans(
		std::vector< DdsAutoType<com::rti::atc::generated::FlightPlan> > *plans);


private:
	// --- Private methods --- 

	// --- Process flight plans in queue ---
	bool ProcessFlightPlans(
		std::vector< DdsAutoType<com::rti::atc::generated::FlightPlan> > *plans);

	// --- Private members ---

	// Contains all the components needed to create the DataReader
	RadarInterface *_communicator;

	// Application-specific DDS DataReader for receiving flight plan data
	com::rti::atc::generated::FlightPlanDataReader *_reader;

	// Objects to block a thread until flight plan data arrives
	DDS::WaitSet *_waitSet;
	DDS::StatusCondition *_condition;
};




// ------------------------------------------------------------------------- //
//
// RadarWriter:
// This class is used to create a very efficient low-latency DataWriter.
//
// In particular, it sends data efficiently by pre-registering the DDS instance
// and storing the instance handle in a map.  (It is not necesary to pre-
// register an instance, but it makes the write() call more efficient.)
class RadarWriter 
{

public:

	// --- Constructor --- 
	// This creates a DDS DataWriter that publishes to track information.  
	// This uses the app object to access the DomainParticipant, and it uses the 
	// QoS profiles specified when creating the DataWriter.  The XML QoS files
	// were previously configured when the RadarInterface's DDSCommunicator was
	// created.
	RadarWriter(RadarInterface *comm, DDS::Publisher *pub, 
		const std::string &qosLibrary, const std::string &qosProfile);

	// --- Destructor --- 
	~RadarWriter();
	
	// --- Sends the Track Data --- 
	// Uses DDS interface to send a flight plan efficiently over the network
	// or shared memory to interested applications subscribing to flight plan
	// information.
	void PublishTrack(
		DdsAutoType<com::rti::atc::generated::Track> &track);

	// --- Deletes the Track Data --- 
	// "Deletes" the flight plan from the system - removing the DDS instance 
	// from all applications.
	void DeleteTrack(
		DdsAutoType<com::rti::atc::generated::Track> &track);

private:
	// --- Private members ---

	// Contains all the components needed to create the DataWriter
	RadarInterface *_communicator;

	// The application-specific DDS DataWriter that sends track data updates
	// over the network or shared memory
	com::rti::atc::generated::TrackDataWriter *_trackWriter;


};
	






#endif
