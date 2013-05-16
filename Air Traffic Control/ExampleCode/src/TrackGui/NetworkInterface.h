#ifndef NETWORK_INTERFACE_H
#define NETWORK_INTERFACE_H

#include <vector>
#include "../CommonInfrastructure/DDSCommunicator.h"
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
// ------------------------------------------------------------------------- //
class NetworkInterface  {
public:

	// The constructor creates all the necessary DDS objects (in this case, 
	// a DomainParticipant, a Subscriber, and objects wrapping two DDS 
	// DataReaders.)  This also configures the XML QoS configuration files that
	// should be used by the application.
	NetworkInterface( 
		std::vector<std::string>qosFileNames);

	// Destructor
	~NetworkInterface();

	// Accessor for the communicator (the class that sets up the basic
	// DDS infrastructure like the DomainParticipant).
	DDSCommunicator *GetCommunicator() 
	{ 
		return _communicator; 
	}

	// Accessor for the flight plan reader
	FlightPlanReader *GetFlightPlanReader() 
	{ 
		return _flightPlanReader; 
	}

	// Accessor for the track reader
	TrackReader *GetTrackReader() 
	{ 
		return _trackReader; 
	}

private:
		DDSCommunicator *_communicator;
		FlightPlanReader *_flightPlanReader;
		TrackReader *_trackReader;

};

// ------------------------------------------------------------------------- //
// A query string has two single quotes around the string to be queried.
// In this case, our query is for a particular flight ID, so we have the 
// length pre-defined in IDL.
#define FLIGHT_ID_QUERY_LENGTH com::rti::atc::generated::FLIGHT_ID_LENGTH + 2

// ------------------------------------------------------------------------- //
//
// FlightPlanReader:
// A wrapper for a DDS DataReader, that receives flight plan data, leaves it
// in the middleware queue, and queries the flight plan when a track updates.
//
// ------------------------------------------------------------------------- //
class FlightPlanReader {

public:

	// Subscribes to flight plan information
	FlightPlanReader(NetworkInterface *app, DDS::Subscriber *sub, 
		char *qosLibrary, char *qosProfile);


	// Destructor
	~FlightPlanReader();

	void NotifyWakeup(); 

	// This example is not being notified when new flight plans arrive, and
	// instead queries the middleware for a particular flight plan update
	// when it is interested in it.  It queries the middleware queue by
	// flight ID.
	void GetFlightPlan(char *flightId, 
		com::rti::atc::generated::FlightPlan *plan);

private:
	NetworkInterface *_app;
	com::rti::atc::generated::FlightPlanDataReader *_fpReader;
	DDS::WaitSet *_waitSet;
	DDS::StatusCondition *_condition;
	DDS::GuardCondition *_shutDownNotifyCondition;
	DDS::QueryCondition *_queryForFlights;
	char _flightIdQueried[FLIGHT_ID_QUERY_LENGTH];
	OSMutex *_mutex;

};

// ------------------------------------------------------------------------- //
//
// TrackReader:
// A wrapper for a DDS DataReader, that blocks an application thread, waiting
// to receive notifications of track data.
//
// ------------------------------------------------------------------------- //
class TrackReader {

public:

	// Subscribes to flight plan information
	TrackReader(NetworkInterface *app, DDS::Subscriber *sub, 
		char *qosLibrary, char *qosProfile);

	// Destructor
	~TrackReader();

	// This example is looking up all flight plans, and leaving them 
	// in the middleware's queue.  it does this because it does not need
	// to do any transformation on the flight plan data. 
	// This method allows the application to be notified when tracks
	// are available
	void WaitForTracks(
		std::vector<com::rti::atc::generated::Track *> *tracks);

	// This example is looking up all flight plans, and leaving them 
	// in the middleware's queue.  it does this because it does not need
	// to do any transformation on the flight plan data.  This example does
	// not care about when the tracks arrive, it simply queries which 
	// tracks are in the queue (polling for data)
	// See the other example application for alternatives - being notified
	// that data is available.
	void GetCurrentTracks(
		std::vector<com::rti::atc::generated::Track *> *tracks);

	void NotifyWakeup();

private:
	NetworkInterface *_app;
	com::rti::atc::generated::TrackDataReader *_reader;
	DDS::WaitSet *_waitSet;
	DDS::StatusCondition *_condition;
	DDS::GuardCondition *_shutDownNotifyCondition;
	OSMutex *_mutex;
};

#endif
