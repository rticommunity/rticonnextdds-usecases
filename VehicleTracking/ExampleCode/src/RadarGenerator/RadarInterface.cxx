/*********************************************************************************************
(c) 2005-2013 Copyright, Real-Time Innovations, Inc.  All rights reserved.    	                             
RTI grants Licensee a license to use, modify, compile, and create derivative works 
of the Software.  Licensee has the right to distribute object form only for use with RTI 
products.  The Software is provided “as is”, with no warranty of any type, including 
any warranty for fitness for any purpose. RTI is under no obligation to maintain or 
support the Software.  RTI shall not be liable for any incidental or consequential 
damages arising out of the use or inability to use the software.
**********************************************************************************************/

#include <vector>
#include <sstream>
#include "../Generated/AirTrafficControl.h"
#include "../Generated/AirTrafficControlSupport.h"
#include "RadarInterface.h"
#include "GeneratorAdapter.h"

using namespace DDS;
using namespace com::rti::atc::generated;


// ------------------------------------------------------------------------- //
// The RadarInterface is the network interface to the whole application.  This 
// creates DataReaders and DataWriters in order to receive and send data.  
//
// This interface is built from:
// 1. Network data types and topic names defined in the IDL file
// 2. XML configuration files that describe the QoS profiles that should be 
//    used by individual DataWriters and DataReaders.  These describe the 
//    movement and persistence characteristics of the data (how reliable should
//    this be?), as well as other QoS such as resource limits.
// 3. The code itself creates DataReaders and DataWriters, and selects which 
//    profile to use when creating the DataReaders and DataWriters.
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
// ------------------------------------------------------------------------- //


RadarInterface::RadarInterface(long radarId, int maxFlights, 
							enum RadarProfile profile, 
							std::vector<std::string>qosFileNames)
{ 

	_radarId = radarId;
	_maxFlightsToHandle = maxFlights;


	std::string libName;
	std::string profileName;

	// Depending on what is passed in, choose one of two XML profiles to 
	// use - either for best latency or higher throughput.  Note that the
	// profile string is a constant defined in the .idl file.
	libName = QOS_LIBRARY;
	if (profile == LOW_LATENCY) 
	{
		profileName = QOS_PROFILE_RADAR_LOW_LATENCY;
	} else if (profile == HIGH_THROUGHPUT) 
	{
		profileName = QOS_PROFILE_RADAR_HIGH_THROUGHPUT;
	}

	_communicator = new DDSCommunicator();

	// Calling the DDSCommunicator class's CreateParticipant method.
	// This creates the DomainParticpant, the first step in creating a DDS
	// application.  This starts the discovery process.  For more information
	// on what the DomainParticipant is responsible for, and how to configure
	// it, see the DDSCommunicator class.
	if (NULL == _communicator->CreateParticipant(0, 
					qosFileNames, libName.c_str(), 
					profileName.c_str())) 
	{
		std::stringstream errss;
		errss << "Failed to create DomainParticipant object";
		throw errss.str();
	}


	// Calling the DDSCommunicator class's CreatePublisher method.  
	// You do _not_ need to create one publisher per DataWriter.
	Publisher *publisher = _communicator->CreatePublisher();

	if (publisher == NULL) 
	{
		std::stringstream errss;
		errss << "Failed to create Publisher object";
		throw errss.str();
	}

	// Creating the application's RadarWriter object.  
	// This could use the RTI Connext DDS writer directly as a way to write, 
	// but this example assumes that you are converting between an internal 
	// data structure and the network data structure.  If you are not doing 
	// this, you can simplifythe logic a bit by giving the applications direct
	// access to the DDS DataWriter class.
	// Note that this might be created with one of two separate XML QoS 
	// profiles depending on the requirement for lowest latency or higher 
	// throughput at the cost of latency. To see the individual QoS tuning,
	// refer to the XML file.  
	_radarWriter = new RadarWriter(this, publisher,
		libName, profileName);
	if (_radarWriter == NULL) 
	{
		std::stringstream errss;
		errss << "Failed to create RadarWriter object";
		throw errss.str();
	}


	// Creating a DDS subscriber.  
	// You do _not_ need to create one subscriber per DataReader.
	Subscriber *subscriber = _communicator->CreateSubscriber();
	if (subscriber == NULL) 
	{
		std::stringstream errss;
		errss << "Failed to create Subscriber object";
		throw errss.str();
	}

	// Creating the FlightPlanReader object.
	// We could give the application access to the DataReader directly, but 
	// this simplifies the application's access - in this case, we can choose 
	// to let the application store the data in the DataReader's queue, and 
	// query it directly from the DataReader but we create an object to hide
	// that decision from the user.
	// Initialize the receiver with the QoS profile defined in the 
	// flight_plan_profiles_multicast.xml file
	_flightPlanReader = new FlightPlanReader(this, subscriber, 
		QOS_LIBRARY,
		QOS_PROFILE_FLIGHT_PLAN);

	if (_flightPlanReader == NULL) 
	{
		std::stringstream errss;
		errss << "Failed to create FlightPlanReader object";
		throw errss.str();
	}

}

// ------------------------------------------------------------------------- //
// Deleting the Radar Writer, the Flight Plan Reader, and the communicator
// infrastructure.  See the individual destructors to see how these are 
// deleted.
RadarInterface::~RadarInterface()
{

	delete _radarWriter;
	delete _flightPlanReader;
	delete _communicator;
}

// ------------------------------------------------------------------------- //
// Create the Radar DataWriter.  This uses the RadarInterface's 
// DomainParticipant object to create a DataWriter and Topic.
RadarWriter::RadarWriter(RadarInterface *netInterface, 
						Publisher *pub, 
						const std::string &qosLibrary,
						const std::string &qosProfile) 
{
	ReturnCode_t retcode;

	if (netInterface == NULL) 
	{
		std::stringstream errss;
		errss << "RadarWriter(): Bad parameter \"netInterface\"";
		throw errss.str();
	}

	_trackWriter = NULL;

	_communicator = netInterface;
	DomainParticipant *participant = 
		netInterface->GetCommunicator()->GetParticipant();
		
	if (participant == NULL) 
	{
		std::stringstream errss;
		errss << "RadarWriter(): participant has not been created";
		throw errss.str();
	}

	// The topic object is the description of the data that you will be 
	// sending. It associates a particular data type with a name that 
	// describes the meaning of the data.  Along with the data types, and
	// whether your application is reading or writing particular data, this
	// is the data interface of your application.

	// This topic has the name AIR_TRACK_TOPIC - a constant string that is
	// defined in the .idl file.  (It is not required that you define your 
	// topic name in IDL, but it is a best practice for ensuring the data
	// interface of an application is all defined in one place.
	// Generally you can register all topics and types up-front if
	// necessary.

	// This can be done at any time before creating the DataWriters and
	// DataReaders.  In some systems, this is done in a separate initialization
	// all at once - especially in applications that read and write the same 
	// topic
	Topic *topic = _communicator->GetCommunicator()->CreateTopic<Track>(
		AIR_TRACK_TOPIC);


	// Create a DataWriter
	// The topic object is the description of the data that you will be 
	// sending. It associates a particular data type with a name that 
	// describes the meaning of the data.  Along with the data types, and
	// whether your application is reading or writing particular data, this
	// is the data interface of your application.

	// This topic has the name AIR_TRACK_TOPIC - a constant string that was 
	// defined in the .idl file.  (It is not required that you define your 
	// topic name in IDL, but it is a best practice for ensuring the data
	// interface of an application is all defined in one place.
	// Generally you can register all topics and types up-front if
	// necessary.

	// Start with QoS gathered from the XML file, then update the value of 
	// the max_samples and max_instances before creating the DataWriter
	DDS_DataWriterQos writerQos;
	retcode = TheParticipantFactory->get_datawriter_qos_from_profile(
											writerQos,
											qosLibrary.c_str(), 
											qosProfile.c_str());

	if (retcode != DDS_RETCODE_OK) 
	{
		std::stringstream errss;
		errss << "RadarWriter(): failure to get writer Qos. Bad names?";
		throw errss.str();
	}
	writerQos.resource_limits.max_instances = 
		_communicator->GetMaxFlightsToHandle();
	writerQos.resource_limits.max_samples = 
		_communicator->GetMaxFlightsToHandle();
	writerQos.resource_limits.initial_samples = 
		_communicator->GetMaxFlightsToHandle();
	writerQos.resource_limits.initial_instances = 
		_communicator->GetMaxFlightsToHandle();
	if (_communicator->GetMaxFlightsToHandle() < 
		writerQos.protocol.rtps_reliable_writer.heartbeats_per_max_samples)
	{
		writerQos.protocol.rtps_reliable_writer.heartbeats_per_max_samples
				= _communicator->GetMaxFlightsToHandle();
	}

	// Create the DDS DataWriter object that sends data over the network (or
	// shared memory)
	DataWriter *ddsWriter = 
		pub->create_datawriter(topic, writerQos, 
				NULL, DDS_STATUS_MASK_NONE);


	// You cannot use a generic DataWriter to write data, you must cast it to
	// your type-specific DataWriter - in this case, a TrackDataWriter.
	_trackWriter = TrackDataWriter::narrow(ddsWriter);
	if (_trackWriter == NULL) 
	{
		std::stringstream errss;
		errss << "RadarWriter(): failure to create writer. Inconsistent Qos?";
		throw errss.str();
	}

}

// ------------------------------------------------------------------------- //
// Delete the RadarWriter, and the DDS entities using DDS mechanisms - use
// the factory that created the DataWriter to delete the DataWriter
RadarWriter::~RadarWriter()
{
	Publisher *pub = _trackWriter->get_publisher();
	pub->delete_datawriter(_trackWriter);
}

// ------------------------------------------------------------------------- //
// Write the data into the DDS "cloud" - in other words, write the data,
// within the numbered domain that the DomainParticipant was created with, 
// to whichever DataReaders of the same topic were discovered over the
// available transports.
void RadarWriter::PublishTrack(DdsAutoType<Track> &track)
{

	InstanceHandle_t handle = DDS_HANDLE_NIL;
	bool handleSet = false;

	// You can register the instance handle to get better 
	// throughput - however, this mostly makes sense if you are keeping
	// an object in your application where you can attach the instance
	// handle, or if you key fields are complex (more than 16 bytes long)

/*		 handle = _trackWriter->register_instance(track);
*/

	// Write the track data onto the network (or over shared memory)
	DDS_ReturnCode_t retcode = _trackWriter->write(track, handle);

	if (retcode != RETCODE_OK) 
	{
		std::stringstream errss;
		errss << "Write failure - resource limits hit?";
		throw errss.str();
	}


}


// ------------------------------------------------------------------------- //
// Deletes the track from the DDS system - this is used to indicate that it
// has landed, and the system does not need to keep track of it any more.
void RadarWriter::DeleteTrack(DdsAutoType<Track> &track)
{
	InstanceHandle_t handle = DDS_HANDLE_NIL;
	
	// Retrieve the handle of the instance we were disposing
	handle = _trackWriter->lookup_instance(track);

	// Note that DDS has two ways to indicate that an instance has gone away
	// it can unregister the instance or dispose it.  Also, by default when
	// the DataWriter unregisters an instance, it also disposes it.  If you
	// dispose and instance, the memory for the instance is not cleaned up,
	// with the expectation that it will be reused.  In this case, the 
	// instance IDs will always be recycled, so it is okay to dispose the 
	// instance instead of unregistering it.
	DDS_ReturnCode_t retcode = 
		_trackWriter->dispose(track, handle);

	if (retcode != RETCODE_OK) 
	{
		std::stringstream errss;
		errss << "Write failure - resource limits hit?";
		throw errss.str();
	}

}

// ------------------------------------------------------------------------- //
// This creates the DDS DataReader that receives updates about flight plans.
FlightPlanReader::FlightPlanReader(RadarInterface *comm, Subscriber *sub, 
			const std::string &qosLibrary, 
			const std::string &qosProfile) 
{

	if (comm == NULL) 
	{
		std::stringstream errss;
		errss << "FlightPlanReader(): bad parameter \"comm\"";
		throw errss.str();
	}

	_communicator = comm;

	// Creating a Topic
	// The topic object is the description of the data that you will be 
	// sending. It associates a particular data type with a name that 
	// describes the meaning of the data.  Along with the data types, and
	// whether your application is reading or writing particular data, this
	// is the data interface of your application.

	// This topic has the name AIRCRAFT_FLIGHT_PLAN_TOPIC - a constant string 
	// that is defined in the .idl file.  (It is not required that you define  
	// your topic name in IDL, but it is a best practice for ensuring the data
	// interface of an application is all defined in one place.
	// Generally you can register all topics and types up-front if
	// necessary.
	Topic *topic = _communicator->GetCommunicator()->CreateTopic<FlightPlan>(
										AIRCRAFT_FLIGHT_PLAN_TOPIC);

	// Creating a DataReader
	// This DataReader will receive the flight plan. The application will 
	// remove the flight plan data from the middleware's queue as it attaches 
	// the flight ID to a particular radar track.
	DataReader *reader = sub->create_datareader_with_profile(
		topic,
		qosLibrary.c_str(),
		qosProfile.c_str(), NULL, DDS_STATUS_MASK_NONE);
	if (reader == NULL)
	{
		std::stringstream errss;
		errss << "FlightPlanReader(): failure to create DataReader.";
		throw errss.str();
	}

	 // Down casting to the type-specific reader
	 _reader = FlightPlanDataReader::narrow(reader);

	// This WaitSet object will be used to block a thread until one or more 
	// conditions become true.  In this case, there is a single condition that
	// will wake up the WaitSet when the reader receives data
	 _waitSet = new WaitSet();
	if (_waitSet == NULL) 
	{
		std::stringstream errss;
		errss << "FlightPlanReader(): failure to create WaitSet.";
		throw errss.str();
	}

	// Use this status condition to wake up the thread when data becomes 
	// available
	_condition = _reader->get_statuscondition();

	// Wake up the thread when data is available
	_condition->set_enabled_statuses(DDS_DATA_AVAILABLE_STATUS);
	if (_condition == NULL) 
	{
		std::stringstream errss;
		errss << "FlightPlanReader(): failure to initialize condition.";
		throw errss.str();
	}

	// Attaching the condition to the WaitSet
	_waitSet->attach_condition(_condition);

}

// ------------------------------------------------------------------------- //
// Destory the flight plan DataReader and WaitSet.  Note that this uses
// the DDS factories that created various objects to later delete them.
FlightPlanReader::~FlightPlanReader()
{
	_waitSet->detach_condition(_condition);
	delete _waitSet;

	_reader->delete_contained_entities();
	Subscriber *sub = _reader->get_subscriber();
	sub->delete_datareader(_reader);

}

// This example is using an application thread to be notified when flight plans
// arrive.  
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

void FlightPlanReader::WaitForFlightPlans(
std::vector< DdsAutoType<FlightPlan> > *plans) 
{

	ConditionSeq activeConditions;
	// How long to block for data at a time
	DDS_Duration_t timeout = {1,0};

	// Process flight plans if they exist, and do not wait for another
	// notification of new data
	if (true == ProcessFlightPlans(plans))
	{
		return;
	}

	// Block thread for flight plan data to arrive
	DDS_ReturnCode_t retcode = _waitSet->wait(activeConditions, timeout);

	// Normal to time out 
	if (retcode == DDS_RETCODE_TIMEOUT) 
	{
		return;
	}
	if (retcode != DDS_RETCODE_OK) 
	{
		std::stringstream errss;
		errss << "WaitForFlightPlans(): error " << retcode << 
			" when receiving flight plans.";
		throw errss.str();
	}

	// If we have been woken up and notified that there was an event, we can
	// try to process flight plans.  Errors in processing flight plans will 
	// throw an exception
	ProcessFlightPlans(plans);


}

// This method is taking data from the middleware's queue.
//
// In this example, we remove the data from the middleware's queue by calling
// take().  We do this to illustrate the common case where the data must be
// changed from one format (the network format) to another (the format that the
// radar library expects to receive its flight plan data).
// If the application is able to use the data directly without converting it to
// a different format, you can call read().  This leaves the data in the queue,
// and lets the application access it without having to copy it.

bool FlightPlanReader::ProcessFlightPlans(
std::vector< DdsAutoType<FlightPlan> > *plans) 
{
	// Note: These two sequences are being created with a length = 0.
	// this means that the middleware is loaning memory to them, which
	// the application must return to the middleware.  This avoids 
	// having two separate copies of the data.
	FlightPlanSeq flightPlans;
	SampleInfoSeq sampleInfos;

	bool havePlans = false;

	DDS_ReturnCode_t retcode = DDS_RETCODE_OK;

	while (retcode != DDS_RETCODE_NO_DATA)
	{
		// This call removes the data from the middleware's queue
		retcode = _reader->take(flightPlans, sampleInfos, 
			_communicator->GetMaxFlightsToHandle());

		// If an error has occurred, throw an exception.  No data being
		// available is not an error condition
		if ((retcode != DDS_RETCODE_OK) && 
					(retcode != DDS_RETCODE_NO_DATA)) 
		{
			std::stringstream errss;
			errss << "ProcessFlightPlans(): error " << retcode << 
				" when retrieving flight plans.";
			throw errss.str();
		}

		// Note, based on the QoS profile (history = keep last, depth = 1) and the 
		// fact that we modeled flights as separate instances, we can assume there
		// is only one entry per flight.  So if a flight plan for a particular 
		// flight has been changed 10 times, we will  only be maintaining the most 
		// recent update to that flight plan in the middleware queue.
		for (int i = 0; i < flightPlans.length(); i++) 
		{
			// Data may not be valid if this is a notification that an instance
			// has changed state.  In other words, this could be a notification 
			// that a writer called "dispose" to notify the other applications 
			// that the flight plan has moved to a dispose state.
			if (sampleInfos[i].valid_data) 
			{
				// Return a value of true that flight plans have been received
				havePlans = true;

				// Making copies of this type for clean API because we do not need 
				// lowest latency for flight plan data
				DdsAutoType<FlightPlan> plan = flightPlans[i];
				plans->push_back(plan);
			}

		}

		// This returns the loaned memory to the middleware.
		_reader->return_loan(flightPlans, sampleInfos);

	}

	return havePlans;
}
