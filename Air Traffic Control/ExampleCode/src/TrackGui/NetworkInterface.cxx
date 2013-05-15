#include "NetworkInterface.h"
#include "../CommonInfrastructure/OSAPI.h"


using namespace DDS;
using namespace com::rti::atc::generated;

NetworkInterface::NetworkInterface( 					 
	std::vector<std::string>qosFileNames)	
{

	_communicator = new DDSCommunicator();

	// 2. Calling the parent class's CreateParticipant method.
	// This creates the DomainParticpant, the first step in creating a DDS
	// application.  This starts the discovery process.  For more information
	// on what the DomainParticipant is responsible for, and how to configure
	// it, see the base class.
	if (NULL == _communicator->CreateParticipant(0, qosFileNames, "RTIExampleQosLibrary", 
					"HighThroughputRadar")) {
		std::stringstream errss;
		errss << "Failed to create DomainParticipant object";
		throw errss.str();
	}

	Subscriber *sub = GetCommunicator()->CreateSubscriber();
	_flightPlanReader = new FlightPlanReader(this, sub, "RTIExampleQosLibrary", 
					"FlightPlanStateData");

	_trackReader = new TrackReader(this, sub, "RTIExampleQosLibrary", 
					"HighThroughputRadar");
}

NetworkInterface::~NetworkInterface()
{
	// Wake the reader up in case it is waiting for data
	_trackReader->NotifyWakeup();
	_flightPlanReader->NotifyWakeup();

	delete _flightPlanReader;
	delete _trackReader;
	delete _communicator;

}


FlightPlanReader::FlightPlanReader(NetworkInterface *app, 
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

	const char *typeName = FlightPlanTypeSupport::get_type_name();
	retcode = FlightPlanTypeSupport::register_type(
			_app->GetCommunicator()->GetParticipant(), typeName);
	if (retcode != RETCODE_OK) {
		std::stringstream errss;
		errss << "FlightPlanReader(): failure to register type. Regisetered twice?";
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
	Topic *topic = _app->GetCommunicator()->GetParticipant()->create_topic(
		AIRCRAFT_FLIGHT_PLAN_TOPIC,
		typeName, TOPIC_QOS_DEFAULT, NULL /* listener */,
		STATUS_MASK_NONE);
	if (topic == NULL) {
		std::stringstream errss;
		errss << "FlightPlanReader(): failure to create Topic. Created twice?";
		throw errss.str();
	}

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

	const char *typeName = FlightPlanTypeSupport::get_type_name();
	FlightPlanTypeSupport::unregister_type(
			_app->GetCommunicator()->GetParticipant(), typeName);


	_mutex->Unlock();

	delete _mutex;

}



// Note, due to the data model, we know only one FlightPlan will be returned.
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

void FlightPlanReader::NotifyWakeup() 
{
	_shutDownNotifyCondition->set_trigger_value(true);
}


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
	Topic *topic = _app->GetCommunicator()->GetParticipant()->create_topic(
		AIR_TRACK_TOPIC,
		typeName, TOPIC_QOS_DEFAULT, NULL /* listener */,
		STATUS_MASK_NONE);
	if (topic == NULL) {
		std::stringstream errss;
		errss << "FlightPlanReader(): failure to create Topic. Created twice?";
		throw errss.str();
	}

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

	const char *typeName = TrackTypeSupport::get_type_name();
	TrackTypeSupport::unregister_type(
			_app->GetCommunicator()->GetParticipant(), typeName);

	_mutex->Unlock();

	delete _mutex;
}

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

	DDS_ReturnCode_t retcode = _waitSet->wait(activeConditions, timeout);

	// May be normal
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
//Double check that we have a proper copy constructor -> Note this is doing the wrong thing, have to call FlightPlanTypeSupport::copy() on this 
//TODO	// Making copies of this type for clean API because we do not need lowest latency for flight plan data
			Track *trackReturned = TrackTypeSupport::create_data();
			TrackTypeSupport::copy_data(trackReturned, &trackSeq[i]);
			tracks->push_back(trackReturned);
		}

	}

	// 
	_reader->return_loan(trackSeq, sampleInfos);
	_mutex->Unlock();

}

// TODO:  Comment me
void TrackReader::GetCurrentTracks(std::vector<Track *> *tracks)
{
	_mutex->Lock();

	TrackSeq trackSeq;
	SampleInfoSeq sampleInfos;


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
//Double check that we have a proper copy constructor -> Note this is doing the wrong thing, have to call FlightPlanTypeSupport::copy() on this 
//TODO	// Making copies of this type for clean API because we do not need lowest latency for flight plan data
			Track *trackReturned = TrackTypeSupport::create_data();
			TrackTypeSupport::copy_data(trackReturned, &trackSeq[i]);
			tracks->push_back(trackReturned);
		}

	}

	// 
	_reader->return_loan(trackSeq, sampleInfos);
	_mutex->Unlock();

}

// TODO:  Comment me
void TrackReader::NotifyWakeup() 
{
	_shutDownNotifyCondition->set_trigger_value(true);
}

