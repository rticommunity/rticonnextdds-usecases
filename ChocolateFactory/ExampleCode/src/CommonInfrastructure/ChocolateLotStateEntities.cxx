/*********************************************************************************************
(c) 2005-2013 Copyright, Real-Time Innovations, Inc.  All rights reserved.    	                             
RTI grants Licensee a license to use, modify, compile, and create derivative works 
of the Software.  Licensee has the right to distribute object form only for use with RTI 
products.  The Software is provided “as is”, with no warranty of any type, including 
any warranty for fitness for any purpose. RTI is under no obligation to maintain or 
support the Software.  RTI shall not be liable for any incidental or consequential 
damages arising out of the use or inability to use the software.
**********************************************************************************************/
#include "ChocolateLotStateEntities.h"
#include "EnumPrintHelpers.h"

using namespace DDS;
using namespace com::rti::chocolatefactory::generated;

// ------------------------------------------------------------------------- //
// Create the ChocolateLotState DataWriter.  This uses the 
// DDSCommunicator's DomainParticipant object to create a 
// DataWriter and Topic.
ChocolateLotStateWriter::ChocolateLotStateWriter(
						DDSCommunicator *communicator,
						Publisher *pub, 
						const std::string &qosLibrary,
						const std::string &qosProfile) 
{

	if (communicator == NULL) 
	{
		std::stringstream errss;
		errss << "ChocolateLotStateWriter(): Bad parameter communicator";
		throw errss.str();
	}

	_chocolateLotStateWriter = NULL;

	_communicator = communicator;
	DomainParticipant *participant = 
		_communicator->GetParticipant();
		
	if (participant == NULL) 
	{
		std::stringstream errss;
		errss << "ChocolateLotStateWriter(): participant has not been created";
		throw errss.str();
	}

	// The topic object is the description of the data that you will be 
	// sending. It associates a particular data type with a name that 
	// describes the meaning of the data.  Along with the data types, and
	// whether your application is reading or writing particular data, this
	// is the data interface of your application.

	// This topic has the name CHOCOLATE_LOT_TOPIC - a constant string that is
	// defined in the .idl file.  (It is not required that you define your 
	// topic name in IDL, but it is a best practice for ensuring the data
	// interface of an application is all defined in one place.)
	// Generally you can register all topics and types up-front if
	// necessary.

	// This can be done at any time before creating the DataWriters and
	// DataReaders.  In some systems, this is done in a separate initialization
	// all at once - especially in applications that read and write the same 
	// topic
	Topic *topic = (DDS::Topic *)
		_communicator->
				GetParticipant()->lookup_topicdescription(CHOCOLATE_LOT_TOPIC);

	if (topic == NULL)
	{

		topic = _communicator->CreateTopic<ChocolateLotState>(
													CHOCOLATE_LOT_TOPIC);
	}


	// Create a DataWriter
	// The topic object is the description of the data that you will be 
	// sending. It associates a particular data type with a name that 
	// describes the meaning of the data.  Along with the data types, and
	// whether your application is reading or writing particular data, this
	// is the data interface of your application.

	// This topic has the name CHOCOLATE_LOT_TOPIC - a constant string that was
	// defined in the .idl file.  (It is not required that you define your 
	// topic name in IDL, but it is a best practice for ensuring the data
	// interface of an application is all defined in one place.
	// Generally you can register all topics and types up-front if
	// necessary.

	// Use QoS loaded from the XML file

	// Create the DDS DataWriter object that sends data over the network (or
	// shared memory)
	DataWriter *ddsWriter = 
		pub->create_datawriter_with_profile(
							topic,
							qosLibrary.c_str(), 
							qosProfile.c_str(),
							NULL, 
							DDS_STATUS_MASK_NONE);


	// You cannot use a generic DataWriter to write data, you must cast it to
	// your type-specific DataWriter - in this case, a 
	// ChocolateLotStateDataWriter.
	_chocolateLotStateWriter = ChocolateLotStateDataWriter::narrow(ddsWriter);
	if (_chocolateLotStateWriter == NULL) 
	{
		std::stringstream errss;
		errss << "ChocolateLotStateWriter(): failure to create writer. " <<
			"Inconsistent Qos?";
		throw errss.str();
	}

}

// ------------------------------------------------------------------------- //
// Delete the ChocolateLotStateWriter, and the DDS entities using DDS 
// mechanisms - use the factory that created the DataWriter to delete the 
// DataWriter
ChocolateLotStateWriter::~ChocolateLotStateWriter()
{
	Publisher *pub = _chocolateLotStateWriter->get_publisher();
	pub->delete_datawriter(_chocolateLotStateWriter);
}

// ------------------------------------------------------------------------- //
// Write the data into the DDS "cloud" - in other words, write the data,
// within the numbered domain that the DomainParticipant was created with, 
// to whichever DataReaders of the same topic were discovered over the
// available transports.
void ChocolateLotStateWriter::PublishChocolateLotState(
	DdsAutoType<ChocolateLotState> &lotState)
{

	InstanceHandle_t handle = DDS_HANDLE_NIL;
	bool handleSet = false;

	// You can register the instance handle to get better 
	// throughput - however, this mostly makes sense if you are keeping
	// an object in your application where you can attach the instance
	// handle, or if you key fields are complex (more than 16 bytes long)

/*		 handle = _chocolateLotStateWriter->register_instance(lotState);
*/

	// Write the chocolate lot data onto the network (or over shared memory)
	DDS_ReturnCode_t retcode = _chocolateLotStateWriter->write(lotState, handle);

	if (retcode != RETCODE_OK) 
	{
		std::stringstream errss;
		errss << "Write failure - resource limits hit?";
		throw errss.str();
	}


}


// ------------------------------------------------------------------------- //
// Unregisters the lot state published by this station controller.  This says
// that this station controller no longer wants to provide an update to the
// state of a particular lot. 
// (The application calls this when a lot has completed all stages of 
// processing so there is no need for a station controller to continue to 
// provide its processing state for that lot).
void ChocolateLotStateWriter::UnregisterChocolateLotState(
	DdsAutoType<ChocolateLotState> &lotState)
{
	InstanceHandle_t handle = DDS_HANDLE_NIL;
	
	// Retrieve the handle of the instance we were disposing
	handle = _chocolateLotStateWriter->lookup_instance(lotState);

	// Note that DDS has two ways to indicate that an instance has gone away
	// it can unregister the instance or dispose it.  Also, by default when
	// the DataWriter unregisters an instance, it also disposes it.  If you
	// dispose and instance, the memory for the instance is not cleaned up,
	// with the expectation that it will be reused.
	// In this case, the next station controller in the factory will start 
	// writing the lot state for this lot instance.  We don't want to dispose
	// that lot, but only unregister it.
	DDS_ReturnCode_t retcode = 
		_chocolateLotStateWriter->unregister_instance(lotState, handle);

	if (retcode != RETCODE_OK) 
	{
		std::stringstream errss;
		errss << "Write failure - resource limits hit?";
		throw errss.str();
	}

}


// ------------------------------------------------------------------------- //
// This creates the DDS DataReader that receives updates about chocolate lots.
ChocolateLotStateReader::ChocolateLotStateReader(
	DDSCommunicator *comm, 
	Subscriber *sub, 
	const std::string &qosLibrary, 
	const std::string &qosProfile,
	StationControllerKind stationControllerKind) 
{

	if (comm == NULL) 
	{
		std::stringstream errss;
		errss << "ChocolateLotStateReader(): bad parameter \"comm\"";
		throw errss.str();
	}

	_communicator = comm;

	// Creating a Topic
	// The topic object is the description of the data that you will be 
	// sending. It associates a particular data type with a name that 
	// describes the meaning of the data.  Along with the data types, and
	// whether your application is reading or writing particular data, this
	// is the data interface of your application.

	// This topic has the name CHOCOLATE_LOT_TOPIC - a constant string 
	// that is defined in the .idl file.  (It is not required that you define  
	// your topic name in IDL, but it is a best practice for ensuring the data
	// interface of an application is all defined in one place.
	// Generally you can register all topics and types up-front if
	// necessary.
	Topic *topic = (DDS::Topic *)
		_communicator->
				GetParticipant()->lookup_topicdescription(CHOCOLATE_LOT_TOPIC);

	if (topic == NULL)
	{

		topic = _communicator->
			CreateTopic<ChocolateLotState>(CHOCOLATE_LOT_TOPIC);
	}

	// If this ChocolateLotStateReader is receiving data for a real station 
	// controller, it filters data so it receives data only for that controller
	// If it is being used by another object such as the MES, it does not 
	// filter, so all ChocolateLotState updates are received by the DataReader.
	TopicDescription *topicDescription = NULL;

	if (stationControllerKind != INVALID_CONTROLLER)
	{
		_parameters.ensure_length(1,1);

		// Static helper method that converts an enumeration into the string 
		// that represents that enumeration
		std::string enumName;
		StationControllerType::GetControllerEnumName(
			stationControllerKind, 
			enumName);

		// Filter to receive updates if: 1) This is assigned to me or 2) this  
		// lot is in state LOT_COMPLETED (at which point I unregister the 
		// instance) Note: The _parameters StringSeq will delete this 
		// char * when the ChocolateLotStateReader class is deleted, so must
		// duplicate the string using DDS::String_dup.
		_parameters[0] = 
			DDS::String_dup(const_cast<char *>(enumName.c_str()));
		ContentFilteredTopic *cft = 
			_communicator->
				GetParticipant()->create_contentfilteredtopic(
				"ContentFilter",
				topic, 
				"lotStatus = 'LOT_COMPLETED' OR nextController = %0",
				_parameters);
		if (cft == NULL)
		{
			std::stringstream errss;
			errss << "ChocolateLotStateReader(): failure to create " <<
				"Content-Filtered Topic.";
			throw errss.str();
		}

		topicDescription = cft;
	}
	else 
	{
		topicDescription = topic;
	}

	// Creating a DataReader
	// This DataReader will receive the chocolate lot, and will store that
	// data in the middleware's queue to be queried by the application
	// Note that if this DataReader belongs to a particular StationController
	// type, it will filter to only receive updates for that station controller.
	// If it belongs to a non-station controller it does not filter.
	DataReader *reader = sub->create_datareader_with_profile(
		topicDescription, 
		qosLibrary.c_str(),
		qosProfile.c_str(), 
		NULL, 
		DDS_STATUS_MASK_NONE);
	if (reader == NULL)
	{
		std::stringstream errss;
		errss << "ChocolateLotStateReader(): failure to create DataReader.";
		throw errss.str();
	}

	 // Down casting to the type-specific reader
	 _reader = ChocolateLotStateDataReader::narrow(reader);

	// This WaitSet object will be used to block a thread until one or more 
	// conditions become true.  In this case, there is a single condition that
	// will wake up the WaitSet when the reader receives data
	_waitSet = new WaitSet();
	if (_waitSet == NULL) 
	{
		std::stringstream errss;
		errss << "ChocolateLotStateReader(): failure to create WaitSet.";
		throw errss.str();
	}

	// Creating the infrastructure that allows an application thread to block
	// until some condition becomes true, such as data availability.
	_condition = _reader->get_statuscondition();

	// Wake up the thread when data is available
	_condition->set_enabled_statuses(DDS_DATA_AVAILABLE_STATUS);
	if (_condition == NULL) 
	{
		std::stringstream errss;
		errss << "ChocolateLotStateReader(): failure to initialize condition.";
		throw errss.str();
	}

	// Attaching the condition to the WaitSet
	_waitSet->attach_condition(_condition);

}

// ------------------------------------------------------------------------- //
// Destory the chocolate lot DataReader and WaitSet.  Note that this uses
// the DDS factories that created various objects to later delete them.
ChocolateLotStateReader::~ChocolateLotStateReader()
{
	_waitSet->detach_condition(_condition);
	delete _waitSet;

	_reader->delete_contained_entities();
	Subscriber *sub = _reader->get_subscriber();
	sub->delete_datareader(_reader);

}

// This example is using an application thread to be notified when chocolate
// lot state updates arrive.
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

void ChocolateLotStateReader::WaitForChocolateLotUpdates(
std::vector< DdsAutoType<ChocolateLotState> > *lots) 
{

	ConditionSeq activeConditions;
	// How long to block for data at a time
	DDS_Duration_t timeout = {10,0};

	// Process chocolate lot updates if they exist, and do not wait for another
	// notification of new data
	if (true == ProcessChocolateLot(lots))
	{
		return;
	}

	// Block thread for chocolate lot state updates to arrive
	DDS_ReturnCode_t retcode = _waitSet->wait(activeConditions, timeout);

	// Normal to time out 
	if (retcode == DDS_RETCODE_TIMEOUT) 
	{
		return;
	}
	if (retcode != DDS_RETCODE_OK) 
	{
		std::stringstream errss;
		errss << "WaitForChocolateLotUpdates(): error " << retcode << 
			" when receiving updates to chocolate lots.";
		throw errss.str();
	}

	// If we have been woken up and notified that there was an event, we can
	// try to process chocolate lot state updates.  Errors in processing 
	// chocolate lot state updates will throw an exception
	ProcessChocolateLot(lots);


}

// This method is taking data from the middleware's queue.
//
// In this example, we remove the data from the middleware's queue by calling
// take().  We do this because we do not need to retrieve the same update to
// the chocolate lot state more than once.  This means there is no need for
// the chocolate lot state to be stored in the middleware's queue.

bool ChocolateLotStateReader::ProcessChocolateLot(
std::vector< DdsAutoType<ChocolateLotState> > *lots) 
{
	// Note: These two sequences are being created with a length = 0.
	// this means that the middleware is loaning memory to them, which
	// the application must return to the middleware.  This avoids 
	// having two separate copies of the data.
	ChocolateLotStateSeq lotStateUpdates;
	SampleInfoSeq sampleInfos;

	bool haveLotUpdates = false;

	DDS_ReturnCode_t retcode = DDS_RETCODE_OK;

	while (retcode != DDS_RETCODE_NO_DATA)
	{
		// This call removes the data from the middleware's queue
		retcode = _reader->take(lotStateUpdates, sampleInfos);

		// If an error has occurred, throw an exception.  No data being
		// available is not an error condition
		if ((retcode != DDS_RETCODE_OK) && 
					(retcode != DDS_RETCODE_NO_DATA)) 
		{
			std::stringstream errss;
			errss << "ProcessChocolateLot(): error " << retcode << 
				" when retrieving chocolate lot status updates.";
			throw errss.str();
		}

		// Note, based on the QoS profile (history = keep last, depth = 1) and 
		// the fact that we modeled chocolate lots so that an instance 
		// corresponds to the combination of a lot and a station controller 
		// means that we will get at most a single update per pair of 
		// <lot | station controller that has processed the lot>.
		for (int i = 0; i < lotStateUpdates.length(); i++) 
		{
			// Data may not be valid if this is a notification that an instance
			// has changed state.  In other words, this could be a notification 
			// that a writer called "dispose" to notify the other applications 
			// that the lot has moved to a disposed state.
			if (sampleInfos[i].valid_data) 
			{
				// Return a value of true that lot updates have been received
				haveLotUpdates = true;

				// Making copies of this type for clean API because we do not need 
				// lowest latency for lot updates
				DdsAutoType<ChocolateLotState> lot = lotStateUpdates[i];
				lots->push_back(lot);
			}

		}

		// This returns the loaned memory to the middleware.
		_reader->return_loan(lotStateUpdates, sampleInfos);

	}

	return haveLotUpdates;
}



