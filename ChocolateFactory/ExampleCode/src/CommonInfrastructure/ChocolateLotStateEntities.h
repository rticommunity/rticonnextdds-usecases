/*********************************************************************************************
(c) 2005-2013 Copyright, Real-Time Innovations, Inc.  All rights reserved.    	                             
RTI grants Licensee a license to use, modify, compile, and create derivative works 
of the Software.  Licensee has the right to distribute object form only for use with RTI 
products.  The Software is provided “as is”, with no warranty of any type, including 
any warranty for fitness for any purpose. RTI is under no obligation to maintain or 
support the Software.  RTI shall not be liable for any incidental or consequential 
damages arising out of the use or inability to use the software.
**********************************************************************************************/

#ifndef CHOCOLATE_LOT_STATE_ENTITIES_H
#define CHOCOLATE_LOT_STATE_ENTITIES_H

#include "ndds/ndds_cpp.h"
#include "ndds/ndds_namespace_cpp.h"
#include "DDSCommunicator.h"
#include "DDSTypeWrapper.h"
#include "../Generated/ChocolateFactory.h"
#include "../Generated/ChocolateFactorySupport.h"

// ------------------------------------------------------------------------- //
//
// ChocolateLotStateReader:
// Used for receiving the chocolate lot state.  This encapsulates the concepts
// of a DDS type-specific DataReader (for type ChocolateLotState), along with 
// the mechanisms for accessing data - in this case, this allows the 
// application to block one of its threads to wait for data from the 
// ChocolateLotStateReader.
//
// ------------------------------------------------------------------------- //
class ChocolateLotStateReader 
{

public:

	// --- Constructor --- 
	// This creates a DDS DataReader that subscribes to chocolate lot information.  
	// This uses the app object to access the DomainParticipant, and it uses 
	// the QoS profiles specified when creating the DataReader.  The XML QoS 
	// files were previously configured when the StationControllerInterface's 
	// DDSCommunicator was created.
	ChocolateLotStateReader(
		DDSCommunicator *comm, 
		DDS::Subscriber *sub, 
		const std::string &qosLibrary, 
		const std::string &qosProfile,
		com::rti::chocolatefactory::generated::StationControllerKind 
			stationControllerKind);


	// --- Destructor --- 
	~ChocolateLotStateReader();

	// --- Receive chocolate lot updates --- 
	// This example receives updates about chocolate lots that are destined for 
	// it, including: lot updates that suggest this should process them, or lot
	// updates saying that the lot is entirely done (so this can remove the
	// state)
	void WaitForChocolateLotUpdates(
		std::vector< 
		DdsAutoType<com::rti::chocolatefactory::generated::ChocolateLotState> >
			*lotState);


private:
	// --- Private methods --- 

	// --- Process chocolate lot state updates in queue ---	
	bool ProcessChocolateLot(
		std::vector< 
		DdsAutoType<com::rti::chocolatefactory::generated::ChocolateLotState> >
			*lotState);

	// --- Private members ---

	// Contains all the components needed to create the DataReader
	DDSCommunicator *_communicator;

	// Application-specific DDS DataReader for receiving chocolate lot state data
	com::rti::chocolatefactory::generated::ChocolateLotStateDataReader *_reader;

	// Objects to block a thread until chocolate lot state update arrives
	DDS::WaitSet *_waitSet;
	DDS::StatusCondition *_condition;

	// Parameters for the content-filtered topic.  These can theoretically change,
	// but in this case we are always filtering for data for ourself.
	DDS_StringSeq _parameters;

};

// ------------------------------------------------------------------------- //
//
// ChocolateLotStateWriter:
// This class is used to create a write chocolate lot data over the network.
//
class ChocolateLotStateWriter 
{

public:

	// --- Constructor --- 
	// This creates a DDS DataWriter that publishes the chocolate lot state
	ChocolateLotStateWriter(DDSCommunicator *comm, 
		DDS::Publisher *pub, 
		const std::string &qosLibrary, 
		const std::string &qosProfile);

	// --- Destructor --- 
	~ChocolateLotStateWriter();
	
	// --- Sends the Chocolate Lot State --- 
	// Uses DDS interface to send a chocolate lot state update over the network
	// or shared memory to interested applications subscribing to chocolate
	// lot state information.
	void PublishChocolateLotState(
		DdsAutoType<com::rti::chocolatefactory::generated::ChocolateLotState> 
			&lotState);

	// --- Unregisters the lot state --- 
	// When this application sees that the chocolate lot is finished, it 
	// unregisters the lot state
	void UnregisterChocolateLotState(
		DdsAutoType<com::rti::chocolatefactory::generated::ChocolateLotState> 
			&lotState);

private:
	// --- Private members ---

	// Contains all the components needed to create the DataWriter
	DDSCommunicator *_communicator;

	// The application-specific DDS DataWriter that sends chocolate lot state
	// updates over the network or shared memory
	com::rti::chocolatefactory::generated::ChocolateLotStateDataWriter 
		*_chocolateLotStateWriter;


};



#endif