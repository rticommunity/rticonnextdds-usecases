/*********************************************************************************************
(c) 2005-2013 Copyright, Real-Time Innovations, Inc.  All rights reserved.    	                             
RTI grants Licensee a license to use, modify, compile, and create derivative works 
of the Software.  Licensee has the right to distribute object form only for use with RTI 
products.  The Software is provided “as is”, with no warranty of any type, including 
any warranty for fitness for any purpose. RTI is under no obligation to maintain or 
support the Software.  RTI shall not be liable for any incidental or consequential 
damages arising out of the use or inability to use the software.
**********************************************************************************************/

#include "MESInterface.h"

using namespace DDS;
using namespace com::rti::chocolatefactory::generated;


// ------------------------------------------------------------------------- //
// The MESInterface is the network interface to the whole Manufacturing
// Execution System application.  This creates DataReaders and DataWriters
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
// The Manufacturing Execution System listens to chocolate lot state data that 
// indicates the current location of the chocolate lot state according to each
// Station Controller.  
//
// !!!
// NOTE: This may receive updates about a chocolate lot state out of order,
// because the chocolate lot state is being updated by multiple applications
// that could reside on multiple machines.  Getting in-order data from multiple
// sources can be difficult, and may require finely-synchronized clocks on each
// machine.
// 
// Writing ChocolateLotState data:
// ----------------------------
// This application sends chocolate lot state data, using the announcement to 
// assign the chocolate lot to a particular controller.  This sets the 
// chocolate lot state to:
//    - Assigned to the next station controller.
// 
// For information on the ChocolateRecipe or ChocolateLotState types, please see the
// ChocolateFactory.idl file.  
//
// For information on the quality of service for state data, please see the 
// recipe_profiles_multicast.xml file.
//
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

MESInterface::MESInterface(
		std::vector<std::string>qosFileNames) 
{ 

	// Creating the communicator object
	_communicator = new DDSCommunicator();

	// Calling the DDSCommunicator class's CreateParticipant method.
	// This creates the DomainParticpant, the first step in creating a DDS
	// application.  This starts the discovery process.  For more information
	// on what the DomainParticipant is responsible for, and how to configure
	// it, see DDSCommunicator class

	// Note: all data in this example is "state data."  The string constants with the
	// QoS library name and the QoS profile name are configured as constants in
	// the .idl file.  The profiles themselves are configured in the .xml file.
	// Look in the XML for more details on the definition of state data.
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
		QOS_LIBRARY, 
		QOS_PROFILE_STATE_DATA);
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
	// is received that notifies this MES that a chocolate lot state has been
	// updated.
	// This DataReader is configured with QoS for state data.
	_chocolateLotStateReader = new ChocolateLotStateReader(
		GetCommunicator(), 
		subscriber, 
		QOS_LIBRARY,
		QOS_PROFILE_STATE_DATA,
		INVALID_CONTROLLER);

	if (_chocolateLotStateReader == NULL) 
	{
		std::stringstream errss;
		errss << "Failed to create ChocolateLotState DataReader object";
		throw errss.str();
	}

}

// ------------------------------------------------------------------------- //
// Deleting the ChocolateLotState DataWriter, and the ChocolateLotState 
// DataReader and the communicator infrastructure.  See the 
// individual destructors to see how these are deleted.
MESInterface::~MESInterface()
{
	delete _chocolateLotStateWriter;
	delete _chocolateLotStateReader;
}
