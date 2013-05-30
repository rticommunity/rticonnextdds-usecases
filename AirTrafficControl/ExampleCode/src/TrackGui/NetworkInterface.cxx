#include "NetworkInterface.h"
#include "../CommonInfrastructure/OSAPI.h"



using namespace DDS;
using namespace com::rti::atc::generated;

// ----------------------------------------------------------------------------
// This creates the NetworkInterface object.  

// The NetworkInterface is comprised of:
// 1) One DDSCommunicator object - which is responsible for creating all 
//    objects that may be shared by multiple DataWriters and DataReaders - 
//    essentially all the objects that are (usually) created only once, 
//    regardless of how many data streams the application is sending or 
//    receiving.
//    The objects that are (usually) created once generally include:
//      1) DomainParticipant objects.  Typically an application has only one,
//         unless it must communicate in multiple domains.
//      2) Publisher and/or Subscriber.  Typically an application has at most 
//	       one of each.
//      3) Topics.  A topic with a particular name may be created only once per
//         DomainParticipant, and can be shared between multiple DataWriters
//         and DataReaders.
//      4) Types.  These must be registered and unregistered exactly once with
//         the DomainParticipant.
// 2) Any DataWriters and DataReaders that comprise the network interface
//    of the application.
NetworkInterface::NetworkInterface( 					 
	std::vector<std::string>qosFileNames)	
{

	// Class with code for creating the basic objects for DDS communication.
	_communicator = new DDSCommunicator();

	// Calling the parent class's CreateParticipant method.
	// This creates the DomainParticpant, the first step in creating a DDS
	// application.  This starts the discovery process.  For more information
	// on what the DomainParticipant is responsible for, and how to configure
	// it, see the base class.
	if (NULL == _communicator->CreateParticipant(0, qosFileNames, 
									"RTIExampleQosLibrary", 
									"HighThroughputRadar")) {
		std::stringstream errss;
		errss << "Failed to create DomainParticipant object";
		throw errss.str();
	}

	Subscriber *sub = GetCommunicator()->CreateSubscriber();

	// Create the DataReader that receives flight plan data.  The profiles
	// that are passed in define how the application will receive data,
	// and how much data will be kept by the middleware.  Look at the 
	// associated XML files for details.
	_flightPlanReader = new FlightPlanReader(this, sub, 
								"RTIExampleQosLibrary",
								"FlightPlanStateData");

	// Create the DataReader that receives track data.  The profiles
	// that are passed in define how the application will receive data,
	// and how much data will be kept by the middleware.  Look at the 
	// associated XML files for details.
	_trackReader = new TrackReader(this, sub, 
								"RTIExampleQosLibrary", 
								"HighThroughputRadar");
}

// ----------------------------------------------------------------------------
// Destructor for the network interface. This deletes the readers, and the 
// communicator.  Notice that the DDS-specific cleanup code is in the 
// destructors of the individual reader and communicator objects.
NetworkInterface::~NetworkInterface()
{
	// Wake the reader up in case it is waiting for data
	_trackReader->NotifyWakeup();
	_flightPlanReader->NotifyWakeup();

	delete _flightPlanReader;
	delete _trackReader;
	delete _communicator;

}


// ----------------------------------------------------------------------------
// Creating the FlightPlanReader object.
// This creates the DDS DataReader object that receives flight plan data over 
// one or more transports, and makes it available to the application.  When the
// DataReader object is first created, it starts the discovery process.  The
// DataReader will start to receive data from DataWriters that are:
//  1) In the same domain
//  2) Have the same topic
//  3) Have compatible types
//  4) Have compatible QoS
// as soon as the discovery process has completed.
FlightPlanReader::FlightPlanReader(NetworkInterface *app, 
							Subscriber *sub,			
							char *qosLibrary, 
							char *qosProfile) {


	_mutex = new OSMutex();

	if (app == NULL) {
		std::stringstream errss;
		errss << "FlightPlanReader(): bad parameter \"app\"";
		throw errss.str();
	}

	_app = app;


	// Creating a Topic
	// The topic object is the description of the data that you will be 
	// sending. It associates a particular data type with a name that 
	// describes the meaning of the data.  Along with the data types, and
	// whether your application is reading or writing particular data, this
	// is the data interface of your application.

	// This topic has the name AIRCRAFT_FLIGHT_PLAN_TOPIC - a constant string that
	// is defined in the .idl file.  (It is not required that you define your 
	// topic name in IDL, but it is a best practice for ensuring the data
	// interface of an application is all defined in one place.
	// Generally you can register all topics and types up-front if
	// necessary.
	Topic *topic = _app->GetCommunicator()->CreateTopic<FlightPlan>( 
		AIRCRAFT_FLIGHT_PLAN_TOPIC);

	// Creating a DataReader
	// This DataReader will receive the flight plan, and will store thatflight
	// plan data in the middleware's queue to be queried by the 
	 DataReader *reader = sub->create_datareader_with_profile(topic, qosLibrary,
		qosProfile, NULL, DDS_STATUS_MASK_NONE);
	 // Down casting to the type-specific reader
	 _fpReader = FlightPlanDataReader::narrow(reader);
	_waitSet = new WaitSet();
	if (_waitSet == NULL) {
		std::stringstream errss;
		errss << "FlightPlanReader(): failure to create WaitSet.";
		throw errss.str();
	}

	// Create a query condition that will be used later to access a specific 
	// flight plan in the DataReader's queue
	DDS_StringSeq queryParameters;
	queryParameters.ensure_length(1,1);
	queryParameters[0] = DDS_String_dup("''");
	_queryForFlights = _fpReader->create_querycondition(DDS_ANY_SAMPLE_STATE, 
		DDS_ANY_VIEW_STATE, DDS_ALIVE_INSTANCE_STATE,
		"flightId MATCH %0", queryParameters);
	if (_queryForFlights == NULL)
	{
		std::stringstream errss;
		errss << "FlightPlanReader(): failure to initialize query condition.";
		throw errss.str();
	}
	// Use this guard condition to wake up this reader if it is waiting later
	_shutDownNotifyCondition = new GuardCondition;
	_waitSet->attach_condition(_shutDownNotifyCondition);

	_condition = _fpReader->get_statuscondition();
	_condition->set_enabled_statuses(DDS_SAMPLE_LOST_STATUS | 
		DDS_SAMPLE_REJECTED_STATUS | DDS_DATA_AVAILABLE_STATUS);
	if (_condition == NULL) {
		std::stringstream errss;
		errss << "FlightPlanReader(): failure to initialize condition.";
		throw errss.str();
	}

	_waitSet->attach_condition(_condition);



}

// ----------------------------------------------------------------------------
// Destroying the FlightPlanReader and the objects that are being used to 
// access it, such as the WaitSet and conditions.  Notice that we call 
// the DDS API delete_contained_entities() to ensure that all conditions
// associated with the DataReader are destroyed.  Topics are not destroyed by
// this call, because they may be shared across multiple DataReaders and
// DataWriters.
FlightPlanReader::~FlightPlanReader()
{
	_mutex->Lock();

	_waitSet->detach_condition(_condition);
	_waitSet->detach_condition(	_shutDownNotifyCondition);
	delete _shutDownNotifyCondition;
	delete _waitSet;

	// Deleted when calling delete_contained_entities
	// delete _queryForFlights;
	// delete _condition

	_fpReader->delete_contained_entities();

	Subscriber *sub = _fpReader->get_subscriber();
	sub->delete_datareader(_fpReader);
	_fpReader = NULL;


	_mutex->Unlock();

	delete _mutex;

}


// ----------------------------------------------------------------------------
// This call:
//   1) Queries the queue for flight plan data for flights with the ID equal to
//      flightId
//   2) Copies the value of a single flight plan into the the object that is 
//      passed in.  Due to the QoS settings, we know this has a history depth 
//      of one, so only the latest flight plan information will be in the 
//      DataReader's queue.
void FlightPlanReader::GetFlightPlan(char *flightId, FlightPlan *plan)
{
	DDS_StringSeq queryParameters;
	queryParameters.ensure_length(1,1);

	// Note that a QueryCondition requires that the single quotes around
	// a string are inside the query condition parameter, so this creates
	// a string with single-quotes around the flight ID
	sprintf(_flightIdQueried, "'%s'", flightId);
	queryParameters[0] = DDS_String_dup(_flightIdQueried);
	_queryForFlights->set_query_parameters(queryParameters);

	if (0 == strcmp(flightId, "")) 
	{
		return;
	}

	FlightPlanSeq flightSeq;
	SampleInfoSeq infoSeq;
	_fpReader->read_w_condition(flightSeq, infoSeq, DDS_LENGTH_UNLIMITED,
		_queryForFlights);


	if (flightSeq.length() > 0)
	{

		if (infoSeq[0].valid_data)
		{
			FlightPlanTypeSupport::copy_data(plan, &flightSeq[0]);
		}
	}
	_fpReader->return_loan(flightSeq, infoSeq);

}

// ----------------------------------------------------------------------------
// This wakes up the WaitSet for the FlightPlan DataReader, in case it is being
// used to wait until data is available.  This is used when shutting down to
// ensure that a thread that is querying data from the middleware will be woken
// up to shut down nicely.
void FlightPlanReader::NotifyWakeup() 
{
	_shutDownNotifyCondition->set_trigger_value(true);
}

// ----------------------------------------------------------------------------
// Creating the TrackReader object.
// This creates the DDS DataReader object that receives track data over one or 
// more transports, and makes it available to the application.  When the 
// DataReader object is first created, it starts the discovery process.  The
// DataReader will start to receive data from DataWriters that are:
//  1) In the same domain
//  2) Have the same topic
//  3) Have compatible types
//  4) Have compatible QoS
// as soon as the discovery process has completed.
TrackReader::TrackReader(NetworkInterface *app, 
						Subscriber *sub, 
						char *qosLibrary, 
						char *qosProfile) {

	_mutex = new OSMutex();
	ReturnCode_t retcode;

	if (app == NULL) {
		std::stringstream errss;
		errss << "FlightPlanReader(): bad parameter \"app\"";
		throw errss.str();
	}

	_app = app;

	const char *typeName = TrackTypeSupport::get_type_name();
	retcode = TrackTypeSupport::register_type(
			_app->GetCommunicator()->GetParticipant(), typeName);
	if (retcode != RETCODE_OK) {
		std::stringstream errss;
		errss << "TrackReader(): failure to register type. Registered twice?";
		throw errss.str();
	}

	// Creating a Topic
	// The topic object is the description of the data that you will be 
	// sending. It associates a particular data type with a name that 
	// describes the meaning of the data.  Along with the data types, and
	// whether your application is reading or writing particular data, this
	// is the data interface of your application.

	// This topic has the name AIRCRAFT_FLIGHT_PLAN_TOPIC - a constant string that
	// is defined in the .idl file.  (It is not required that you define your 
	// topic name in IDL, but it is a best practice for ensuring the data
	// interface of an application is all defined in one place.
	// Generally you can register all topics and types up-front if
	// necessary.
	Topic *topic = _app->GetCommunicator()->CreateTopic<Track>( 
		AIR_TRACK_TOPIC);

	// Creating a DataReader
	// This DataReader will receive the flight plan, and will store thatflight
	// plan data in the middleware's queue to be queried by the 
	 DataReader *reader = sub->create_datareader_with_profile(topic, qosLibrary,
		qosProfile, NULL, DDS_STATUS_MASK_NONE);
	 // Down casting to the type-specific reader
	 _reader = TrackDataReader::narrow(reader);
	_waitSet = new WaitSet();
	if (_waitSet == NULL) {
		std::stringstream errss;
		errss << "FlightPlanReader(): failure to create WaitSet.";
		throw errss.str();
	}

	_condition = _reader->get_statuscondition();
	_condition->set_enabled_statuses(DDS_SAMPLE_LOST_STATUS | 
		DDS_SAMPLE_REJECTED_STATUS | DDS_DATA_AVAILABLE_STATUS);
	if (_condition == NULL) {
		std::stringstream errss;
		errss << "FlightPlanReader(): failure to initialize condition.";
		throw errss.str();
	}


	_waitSet->attach_condition(_condition);	

	_shutDownNotifyCondition = new GuardCondition;
	_waitSet->attach_condition(_shutDownNotifyCondition);

}

// ----------------------------------------------------------------------------
// Destroying the TrackReader and the objects that are being used to 
// access it, such as the WaitSet and conditions.  Notice that we call 
// the DDS API delete_contained_entities() to ensure that all conditions
// associated with the DataReader are destroyed.  Topics are not destroyed by
// this call, because they may be shared across multiple DataReaders and
// DataWriters.
TrackReader::~TrackReader()
{

	_mutex->Lock();

	_waitSet->detach_condition(_condition);
	_waitSet->detach_condition(	_shutDownNotifyCondition);
	delete _shutDownNotifyCondition;

	delete _waitSet;

	_reader->delete_contained_entities();
	Subscriber *sub = _reader->get_subscriber();
	sub->delete_datareader(_reader);


	_mutex->Unlock();

	delete _mutex;
}

// ----------------------------------------------------------------------------
// This example is using an application thread to be notified when tracks
// arrive.  
// 
// In this example, we leave the data from the middleware's queue by calling
// read().  We do this to illustrate a case where an object that represents
// the flight information (flight plan + track) can be created from data
// that remains in the middleware's queue.  The middleware is configured 
// with QoS that allow old updates of track data to be overwritten, so the
// queue does not grow forever.
//
// There are three options for getting data from RTI Connext DDS:
// 1. Being notified in the application's thread of data arriving (as here).
//    This mechanism has slightly higher latency than option #2, but low
//    latency is not important for this use case.  In addition, this is safer
//    than using option #2, because you do not have to worry about the effect
//    on the middleware's thread.  
//    This uses WaitSet objects to be notified of data arriving.
//    A simple of example of this can be found at: 
//    http://community.rti.com/examples/waitset-status-condition
// 2. Being notified in a listener callback of data arriving.
//    This has lower latency than using a WaitSet, but is more dangerous
//    because you have to worry about not blocking the middleware's thread.
// 3. Polling for data.
//    You can call read() or take() at any time to view or remove the data that
//    is currently in the queue. 
//    A simple example of this can be found at:
//    http://community.rti.com/examples/polling-read

void TrackReader::WaitForTracks(std::vector<Track *> *tracks) {

	ConditionSeq activeConditions;
	DDS_Duration_t timeout = {0,300000000};

	_mutex->Lock();

	// Block this thread until track data becomes available.
	DDS_ReturnCode_t retcode = _waitSet->wait(activeConditions, timeout);

	// May be normal to time out
	if (retcode == DDS_RETCODE_TIMEOUT) {
		_mutex->Unlock();
		return;
	}
	if (retcode != DDS_RETCODE_OK) {
		std::stringstream errss;
		errss << "WaitForTracks(): error when receiving flight plans.";
		_mutex->Unlock();
		throw errss.str();
	}

	// Note: These two sequences are being created with a length = 0.
	// this means that the middleware is loaning memory to them, which
	// the application must return to the middleware.  This avoids 
	// having two separate copies of the data.
	TrackSeq trackSeq;
	SampleInfoSeq sampleInfos;

	// This leaves the data in the DataReader's queue.  Alternately, can call
	// take() which will remove it from the queue.  Leaving data in the 
	// makes sense in this application for two reasons:  
	// 1) the QoS allows the overwriting of data in the queue
	// 2) the application wants to always see the latest update of each 
	//    instance
	retcode = _reader->read(trackSeq, sampleInfos);

	if (retcode != DDS_RETCODE_NO_DATA &&
		retcode != DDS_RETCODE_OK) {
		std::stringstream errss;
		errss << "WaitForTracks(): error when retrieving flight plans.";
		_mutex->Unlock();
		throw errss.str();
	}

	// Note, based on the QoS profile (history = keep last, depth = 1) and the 
	// fact that we modeled flights as separate instances, we can assume there
	// is only one entry per flight.  So if a flight plan for a particular 
	// flight has been changed 10 times, we will  only be maintaining the most 
	// recent update to that flight plan in the middleware queue.
	for (int i = 0; i < trackSeq.length(); i++) {
		if (sampleInfos[i].valid_data) {
			SampleInfo info = sampleInfos[i];

			// Making copies of this type for clean API because we do not need 
			//lowest latency for flight plan data
			Track *trackReturned = TrackTypeSupport::create_data();
			TrackTypeSupport::copy_data(trackReturned, &trackSeq[i]);
			tracks->push_back(trackReturned);
		}

	}

	// The original track sequence was loaned from the middleware to the
	// application.  We have copied the data out of it, so we can now return
	// the loan to the middleware.
	_reader->return_loan(trackSeq, sampleInfos);
	_mutex->Unlock();

}

// ----------------------------------------------------------------------------
// This example is using an application thread to poll for all the existing 
// track data inside the middleware's queue.
void TrackReader::GetCurrentTracks(std::vector<Track *> *tracks)
{
	_mutex->Lock();

	TrackSeq trackSeq;
	SampleInfoSeq sampleInfos;

	// This reads the data from the queue, and loans it to the application
	// in the trackSeq sequence.  See below that you have to return the loan.
	DDS_ReturnCode_t retcode = _reader->read(trackSeq, sampleInfos);

	if (retcode != DDS_RETCODE_NO_DATA &&
		retcode != DDS_RETCODE_OK) {
		std::stringstream errss;
		errss << "WaitForTracks(): error when retrieving flight plans.";
		_mutex->Unlock();
		throw errss.str();
	}

	// Note, based on the QoS profile (history = keep last, depth = 1) and the 
	// fact that we modeled flights as separate instances, we can assume there
	// is only one entry per flight.  So if a flight plan for a particular 
	// flight has been changed 10 times, we will  only be maintaining the most 
	// recent update to that flight plan in the middleware queue.
	for (int i = 0; i < trackSeq.length(); i++) {
		if (sampleInfos[i].valid_data) {
			SampleInfo info = sampleInfos[i];
			// Currently we are allocating and copying the data, though in the 
			// future, we may change to pre-allocating.
			Track *trackReturned = TrackTypeSupport::create_data();
			TrackTypeSupport::copy_data(trackReturned, &trackSeq[i]);
			tracks->push_back(trackReturned);
		}

	}

	// The original track sequence was loaned from the middleware to the
	// application.  We have copied the data out of it, so we can now return
	// the loan to the middleware.
	_reader->return_loan(trackSeq, sampleInfos);
	_mutex->Unlock();

}

// ----------------------------------------------------------------------------
// This wakes up the WaitSet for the Track DataReader, in case it is being
// used to wait until data is available.  This is used when shutting down to
// ensure that a thread that is querying data from the middleware will be woken
// up to shut down nicely.
void TrackReader::NotifyWakeup() 
{
	_shutDownNotifyCondition->set_trigger_value(true);
}

