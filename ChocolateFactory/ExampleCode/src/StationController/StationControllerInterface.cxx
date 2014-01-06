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
#include <iostream>
#include "../Generated/ChocolateFactory.h"
#include "../Generated/ChocolateFactorySupport.h"
#include "StationControllerInterface.h"

using namespace DDS;
using namespace com::rti::chocolatefactory::generated;


// ------------------------------------------------------------------------- //
// The StationControllerInterface is the network interface to the whole 
// Station Controller application.  This creates DataReaders and DataWriters
// in order to receive and send data.  
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
// Reading ChocolateLotState data:
// ------------------------------
// The station controller listens to chocolate lot state data that indicates that
// a chocolate lot is on the way to this station controller.
//
// It uses a DDS DataReader, with a content filter to receive only updates
// that indicate that it is the next station controller to process the lot.
// 
// Writing ChocolateLotState data:
// ----------------------------
// This application sends chocolate lot state data, announcing that the current
// lot of chocolates is either:
//   1. Waiting to be processed by this station controller
//   2. Being processed by this station controller
//   3. Done being processed by this station controller/ready to be processed
//      by the next station controller.
// 
// For information on the ChocolateRecipe or ChocolateLotState types, please see the
// ChocolateFactory.idl file.  
//
// For information on the quality of service for state data, please see the
// recipe_profiles_multicast.xml file.
//
// Reading Recipe data:
// --------------------
// This application reads recipe data to know which state controller to send
// the chocolate lot to when it is done.
//
// Quality of Service:
// -------------------
// All of the data in this example is modeled as "state data," which means that:
//   1. It is sent reliably (RELIABLE_RELIABILITY_QOS)
//   2. It is made available to late-joining applications as soon as they start
//      (TRANSIENT_LOCAL_DURABILITY_QOS)
//   3. A predetermined amount of state is sent to any late-joiners.  In this 
//      case, applications are only interested in the current state of each
//      chocolate lot (or the current chocolate recipe), which translates to a
//      history with depth = 1, kind = KEEP_LAST_HISTORY_QOS
//

// ------------------------------------------------------------------------- //


StationControllerInterface::StationControllerInterface(
		StationControllerKind stationControllerID, 
		std::vector<std::string>qosFileNames) 
{ 

	_stationControllerID = stationControllerID;

	// Creating the communicator object
	_communicator = new DDSCommunicator();

	// All data in this example is "state data."  The string constants with the
	// QoS library name and the QoS profile name are configured as constants in
	// the .idl file.  The profiles themselves are configured in the .xml file.
	// Look in the XML for more details on the definition of state data.


	// Calling the DDSCommunicator class's CreateParticipant method.
	// This creates the DomainParticpant, the first step in creating a DDS
	// application.  This starts the discovery process.  For more information
	// on what the DomainParticipant is responsible for, and how to configure
	// it, see DDSCommunicator class
	if (NULL == GetCommunicator()->CreateParticipant(
					0, 
					qosFileNames, 
					QOS_LIBRARY, 
					QOS_PROFILE_STATE_DATA)) 
	{
		std::stringstream errss;
		errss << "Failed to create DomainParticipant object";
		throw errss.str();
	}


	// Calling the DDSCommunicator class's CreatePublisher method.  
	// You do _not_ need to create one publisher per DataWriter.
	Publisher *publisher = GetCommunicator()->CreatePublisher();

	if (publisher == NULL) 
	{
		std::stringstream errss;
		errss << "Failed to create Publisher object";
		throw errss.str();
	}

	// Creating the application's ChocolateLotStateWriter object.  
	// This could use the RTI Connext DDS writer directly as a way to write.
	// This DataWriter is configured with QoS for state data.
	_chocolateLotStateWriter = new ChocolateLotStateWriter(
		GetCommunicator(), 
		publisher,
		QOS_LIBRARY, QOS_PROFILE_STATE_DATA);
	if (_chocolateLotStateWriter == NULL) 
	{
		std::stringstream errss;
		errss << "Failed to create ChocolateLotState DataWriter object";
		throw errss.str();
	}


	// Creating a DDS subscriber.  
	// You do _not_ need to create one subscriber per DataReader.
	Subscriber *subscriber = GetCommunicator()->CreateSubscriber();
	if (subscriber == NULL) 
	{
		std::stringstream errss;
		errss << "Failed to create Subscriber object";
		throw errss.str();
	}

	// Creating the application's ChocolateLotStateReader object.
	// We could give the application access to the DataReader directly, but 
	// this simplifies the application's access - this creates the objects that
	// allow the application to block a thread until a ChocolateLotState update
	// is received that notifies this Station Controller that it needs to 
	// process a chocolate lot.
	// This DataReader is configured with QoS for state data.
	_chocolateLotStateReader = new ChocolateLotStateReader(
		GetCommunicator(),
		subscriber, 
		"RTIExampleQosLibrary",
		"FactoryStateData",
		_stationControllerID);

	if (_chocolateLotStateReader == NULL) 
	{
		std::stringstream errss;
		errss << "Failed to create ChocolateLotState DataReader object";
		throw errss.str();
	}

	// Creating the application's ChocolateRecipe DataReader object.
	// We could give the application access to the DataReader directly, but 
	// this simplifies the application's access - this receives and stores
	// all recipes in the middleware's queue, and contains the logic to look up
	// a single recipe by name. This DataReader is configured with QoS for 
	// state data
	_recipeReader = new ChocolateRecipeReader(this, subscriber, 
		"RTIExampleQosLibrary",
		"FactoryStateData");

	if (_recipeReader == NULL) 
	{
		std::stringstream errss;
		errss << "Failed to create Recipe DataReader object";
		throw errss.str();
	}

}

// ------------------------------------------------------------------------- //
// Deleting the ChocolateLotState DataWriter, the ChocolateLotState DataReader, the
// ChocolateRecipeDataReader, and the communicator infrastructure.  See the 
// individual destructors to see how these are deleted.
StationControllerInterface::~StationControllerInterface()
{

	delete _chocolateLotStateWriter;
	delete _chocolateLotStateReader;
	delete _recipeReader;
}






// ------------------------------------------------------------------------- //
// This creates the DDS DataReader that receives updates about recipes.
ChocolateRecipeReader::ChocolateRecipeReader(
	StationControllerInterface *comm, 
	Subscriber *sub, 
	const std::string &qosLibrary, 
	const std::string &qosProfile) 
{

	if (comm == NULL) 
	{
		std::stringstream errss;
		errss << "ChocolateRecipeReader(): bad parameter \"comm\"";
		throw errss.str();
	}

	_communicator = comm;

	// Creating a Topic
	// The topic object is the description of the data that you will be 
	// sending. It associates a particular data type with a name that 
	// describes the meaning of the data.  Along with the data types, and
	// whether your application is reading or writing particular data, this
	// is the data interface of your application.

	// This topic has the name RECIPE_TOPIC - a constant string 
	// that is defined in the .idl file.  (It is not required that you define  
	// your topic name in IDL, but it is a best practice for ensuring the data
	// interface of an application is all defined in one place.
	// Generally you can register all topics and types up-front if
	// necessary.
	Topic *topic = (DDS::Topic *)
		_communicator->GetCommunicator()->
				GetParticipant()->lookup_topicdescription(RECIPE_TOPIC);

	if (topic == NULL)
	{

		topic = _communicator->GetCommunicator()->CreateTopic<ChocolateRecipe>(
													RECIPE_TOPIC);
	}

	// Creating a DataReader
	// This DataReader will receive the recipe, and will store it in the 
	// middleware's queue to be queried by the application
	DataReader *reader = sub->create_datareader_with_profile(topic, 
		qosLibrary.c_str(),
		qosProfile.c_str(), 
		NULL, 
		DDS_STATUS_MASK_NONE);

	 // Down casting to the type-specific reader
	 _reader = ChocolateRecipeDataReader::narrow(reader);


}

// ------------------------------------------------------------------------- //
// Destory the chocolate recipe DataReader.  Note that this uses
// the DDS factories that created various objects to later delete them.
ChocolateRecipeReader::~ChocolateRecipeReader()
{
	_reader->delete_contained_entities();
	Subscriber *sub = _reader->get_subscriber();
	sub->delete_datareader(_reader);

}

// This example uses instance information to query the middleware's queue for
// recipes that have previously been sent to this application.  This uses
// option #3 of the three options for getting data from RTI Connext DDS.
// 
// There are three options for getting data from RTI Connext DDS:
// 1. Being notified in the application's thread of data arriving.
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
// 3. Polling for data. (Used here)
//    You can call read() or take() at any time to view or remove the data that
//    is currently in the queue. 
//    A simple example of this can be found at:
//    http://community.rti.com/examples/polling-read

bool ChocolateRecipeReader::GetRecipe(
		std::string recipeName,
		DdsAutoType<ChocolateRecipe> *recipe)
{

	// Create a placeholder with only the key field filled in.  This will be
	// used to retrieve the recipe instance (if it exists).
	DdsAutoType<ChocolateRecipe> recipeHolder;
	strcpy(recipeHolder.recipeName, recipeName.c_str());

	// Look up the particular instance
	const DDS_InstanceHandle_t handle =
		_reader->lookup_instance(recipeHolder);

	// If we have received a lot that uses a recipe we do not have, this is an 
	// error!
	if (DDS_InstanceHandle_is_nil(&handle))
	{
		std::cout << "GetRecipe(): warning - " << 
			"Do not have the recipe needed to process this lot." << std::endl;
		return false;

	}

	ChocolateRecipeSeq recipeSeq;
	SampleInfoSeq infoSeq;

	// Reading just the data for the recipe we are interested in
	_reader->read_instance(recipeSeq, infoSeq, 
			DDS_LENGTH_UNLIMITED,
			handle);


	if (recipeSeq.length() > 0)
	{

		if (infoSeq[0].valid_data)
		{
			// DdsAutoType has a copy constructor that calls 
			// the appropriate TypeSupport::copy_data method
			*recipe = recipeSeq[0];
		}
	}
	_reader->return_loan(recipeSeq, infoSeq);

	return true;
}

