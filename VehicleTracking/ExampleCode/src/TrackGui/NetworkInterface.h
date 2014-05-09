/*********************************************************************************************
(c) 2005-2014 Copyright, Real-Time Innovations, Inc.  All rights reserved.    	                             
RTI grants Licensee a license to use, modify, compile, and create derivative works 
of the Software.  Licensee has the right to distribute object form only for use with RTI 
products.  The Software is provided “as is”, with no warranty of any type, including 
any warranty for fitness for any purpose. RTI is under no obligation to maintain or 
support the Software.  RTI shall not be liable for any incidental or consequential 
damages arising out of the use or inability to use the software.
**********************************************************************************************/
#ifndef NETWORK_INTERFACE_H
#define NETWORK_INTERFACE_H

#include <vector>
#include "../CommonInfrastructure/DDSCommunicator.h"
#include "../CommonInfrastructure/DDSTypeWrapper.h"
#include "../Generated/AirTrafficControl.h"
#include "../Generated/AirTrafficControlSupport.h"

class FlightPlanReader;
class TrackReader;
class OSMutex;


// ------------------------------------------------------------------------- //
//
// NetworkInterface:
// A class that sets up the DDS interface (the network interface) of this 
// GUI application, including creating appropriate DDS DataWriters, DDS
// DataReaders, and all other DDS objects.
//
// In this example, the GUI is only subscribing to data, so this class creates
// two DDS DataReaders and no DDS DataWriters.
//
// ------------------------------------------------------------------------- //
class NetworkInterface  
{
public:

	// --- Constructor --- 
	// The constructor creates all the necessary DDS objects (in this case, 
	// a DomainParticipant, a Subscriber, and objects wrapping two DDS 
	// DataReaders.)  This also configures the XML QoS configuration files that
	// should be used by the application.
	NetworkInterface( 
		std::vector<std::string>qosFileNames);

	// --- Destructor --- 
	~NetworkInterface();

	// --- Getter for Communicator --- 
	// Accessor for the communicator (the class that sets up the basic
	// DDS infrastructure like the DomainParticipant).
	// This allows access to the DDS DomainParticipant/Publisher/Subscriber
	// classes
	DDSCommunicator *GetCommunicator() 
	{ 
		return _communicator; 
	}

	// --- Getter for the flight plan reader --- 
	// Accessor for the object that receives flight plans from the network
	FlightPlanReader *GetFlightPlanReader() 
	{ 
		return _flightPlanReader; 
	}

	// --- Getter for the track reader --- 
	// Accessor for the object that receives track updates from the network
	TrackReader *GetTrackReader() 
	{ 
		return _trackReader; 
	}

private:
	// --- Private members ---

	// Used to create basic DDS entities that all applications need
	DDSCommunicator *_communicator;

	// Flight plan receiver specific to this application
	FlightPlanReader *_flightPlanReader;

	// Track receiver specific to this application
	TrackReader *_trackReader;

};


// ------------------------------------------------------------------------- //
//
// FlightPlanReader:
// A wrapper for a DDS DataReader, that receives flight plan data, leaves it
// in the middleware queue, and queries the flight plan when a track updates.
//
// ------------------------------------------------------------------------- //
class FlightPlanReader 
{

public:

	// --- Constructor --- 
	// Subscribes to flight plan information
	FlightPlanReader(NetworkInterface *app, DDS::Subscriber *sub, 
		const std::string &qosLibrary, const std::string &qosProfile);

	// --- Destructor --- 
	~FlightPlanReader();

	// --- Wake up the reader thread if it is waiting on data ---
	void NotifyWakeup(); 

	// --- Retrieve flight plan --- 
	// This example is not being notified when new flight plans arrive, and
	// instead queries the middleware for a particular flight plan update
	// when it is interested in it.  It queries the middleware queue by
	// flight ID.
	void GetFlightPlan(char *flightId, 
		DdsAutoType<com::rti::atc::generated::FlightPlan> *plan);

private:
	// --- Private members ---

	// Contains all the components needed to create the DataReader
	NetworkInterface *_app;

	// The DDS DataReader of flight plans 
	com::rti::atc::generated::FlightPlanDataReader *_fpReader;

	// The mechanisms that cause a thread to wait until flight plan data
	// becomes available, and to be woken up when the data arrives
	DDS::WaitSet *_waitSet;
	DDS::StatusCondition *_condition;
	DDS::GuardCondition *_shutDownNotifyCondition;

	// Mutex for threading
	OSMutex *_mutex;

};

// ------------------------------------------------------------------------- //
//
// TrackReader:
// A wrapper for a DDS DataReader, that blocks an application thread, waiting
// to receive notifications of track data.
//
// ------------------------------------------------------------------------- //
class TrackReader 
{

public:

	// --- Constructor --- 
	// Subscribes to flight plan information
	TrackReader(NetworkInterface *app, DDS::Subscriber *sub, 
		const std::string &qosLibrary, const std::string &qosProfile);

	// --- Destructor --- 
	~TrackReader();

	// --- Waiting for tracks --- 
	// This waits for new tracks to become available, and notifies the 
	// application that there are new tracks or deleted tracks.
	void WaitForTracks(
		std::vector< DdsAutoType<com::rti::atc::generated::Track> > 
										*tracksUpdated,
		std::vector< DdsAutoType<com::rti::atc::generated::Track> > 
										*tracksDeleted);

	// --- Retreiving current track updates --- 
	// This retrieves track updates from the middleware queue.  This is used
	// to poll for all the current track updates from the middleware.  This
	// keeps a second vector that includes all tracks that have been deleted.
	void GetCurrentTracks(
		std::vector< DdsAutoType<com::rti::atc::generated::Track> > 
										*tracksUpdated,
		std::vector< DdsAutoType<com::rti::atc::generated::Track> > 
										*tracksDeleted);

	// --- Wake up the reader thread if it is waiting on data ---
	void NotifyWakeup();

private:
	// --- Private members ---

	// Contains all the components needed to create the DataReader
	NetworkInterface *_app;

	// The DDS DataReader of tracks 
	com::rti::atc::generated::TrackDataReader *_reader;

	// The mechanisms that cause a thread to wait until flight plan data
	// becomes available, and to be woken up when the data arrives
	DDS::WaitSet *_waitSet;
	DDS::StatusCondition *_condition;
	DDS::GuardCondition *_shutDownNotifyCondition;

	// Mutex for threading
	OSMutex *_mutex;
};

#endif
