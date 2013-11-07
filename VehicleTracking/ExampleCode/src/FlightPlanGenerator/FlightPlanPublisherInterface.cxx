/*********************************************************************************************
(c) 2005-2013 Copyright, Real-Time Innovations, Inc.  All rights reserved.    	                             
RTI grants Licensee a license to use, modify, compile, and create derivative works 
of the Software.  Licensee has the right to distribute object form only for use with RTI 
products.  The Software is provided “as is”, with no warranty of any type, including 
any warranty for fitness for any purpose. RTI is under no obligation to maintain or 
support the Software.  RTI shall not be liable for any incidental or consequential 
damages arising out of the use or inability to use the software.
**********************************************************************************************/
#include "FlightPlanPublisherInterface.h"


// ----------------------------------------------------------------------------
// The FlightPlanPublisherInterface is the network interface to the whole 
// application.  This creates a DataWriter in order to send flight plan data
// over the network (or shared memory) to other applications that are 
// interested in flight plans.
//
// This interface is built from:
// 1. Network data types and topic names defined in the IDL file
// 2. XML configuration files that describe the QoS profiles that should be 
//    used by individual DataWriters and DataReaders.  These describe the 
//    movement and persistence characteristics of the data (how reliable should
//    this be?), as well as other QoS such as resource limits.
// 3. The code itself creates DataWriters, and selects which QoS profile to use
//    when creating the DataWriters.
// 
// Writing flight plan data:
// -------------------------
// This application sends flight plan data, configured to act as state data
// (or last-value cache).  This will reliably deliver the flight plan to both
// existing and late-joining applications that subscribe to flight plan data.
//
// For information on the flight plan data type, please see the 
// AirTrafficControl.idl file.  
//
// For information on the quality of service for flight plan state data, please
// see the flight_plan_profiles.xml file.
// ------------------------------------------------------------------------- //

FlightPlanPublisherInterface::FlightPlanPublisherInterface(std::vector<std::string> xmlFiles) 
{

	_communicator = new DDSCommunicator();

	// Create a DomainParticipant
	// Start by creating a DomainParticipant.  Generally you will have only
	// one DomainParticipant per application.  A DomainParticipant is
	// responsible for starting the discovery process, allocating resources,
	// and being the factory class used to create Publishers, Subscribers, 
	// Topics, etc.  Note:  The string constants with the QoS library name and 
	// the QoS profile name are configured as constants in the .idl file.  The
	// profiles themselves are configured in the .xml file.
	if (NULL == _communicator->CreateParticipant(0, xmlFiles, 
				QOS_LIBRARY, QOS_PROFILE_FLIGHT_PLAN)) 
	{
		std::stringstream errss;
		errss << "Failed to create DomainParticipant object";
		throw errss.str();
	}

	// Create a Publisher
	// This application only writes data, so we only need to create a
	// publisher.  The RadarData application has a more complex pattern
	// so we explicitly separate the writing interface from the overall
	// network interface - meaning that the publisher is created in the
	// network interface, and the DataWriter is created in a separate class
	// Note that one Publisher can be used to create multiple DataWriters
	DDS::Publisher *pub = _communicator->CreatePublisher();

	if (pub == NULL) 
	{
		std::stringstream errss;
		errss << "Failed to create Publisher object";
		throw errss.str();
	}


	// Creating a Topic
	// The Topic object is the description of the data that you will be 
	// sending. It associates a particular data type with a name that 
	// describes the meaning of the data.  Along with the data types, and
	// whether your application is reading or writing particular data, this
	// is the data interface of your application.

	// This topic has the name AIRCRAFT_FLIGHT_PLAN_TOPIC - a constant  
	// string that is defined in the .idl file.  (It is not required that
	// you define your topic name in IDL, but it is a best practice for
	// ensuring the data interface of an application is all defined in one 
	// place. You can register all topics and types up-front, if you nee
	DDS::Topic *topic = _communicator->CreateTopic<FlightPlan>( 
		AIRCRAFT_FLIGHT_PLAN_TOPIC);


	// Create a DataWriter.  
	// This creates a single DataWriter that writes flight plan data, with QoS
	// that is used for State Data.	Note: The string constants with the QoS 
	// library name and the QoS profile name are configured as constants in the
	// .idl file.  The profiles themselves are configured in the .xml file.
	DDS::DataWriter *writer = pub->create_datawriter_with_profile(topic, 
		QOS_LIBRARY, QOS_PROFILE_FLIGHT_PLAN,
		NULL, DDS_STATUS_MASK_NONE);

	// Downcast the generic datawriter to a flight plan DataWriter 
	_writer = FlightPlanDataWriter::narrow(writer);

	if (_writer == NULL) 
	{
		std::stringstream errss;
		errss << 
			"Failure to create FlightPlan writer. Inconsistent Qos?";
		throw errss.str();
	}

}

// ----------------------------------------------------------------------------
// Destructor.
// Deletes the DataWriter, and the Communicator object
FlightPlanPublisherInterface::~FlightPlanPublisherInterface()
{
	DDS::Publisher *pub = _writer->get_publisher();
	pub->delete_datawriter(_writer);
	_writer = NULL;

	delete _communicator;
}


// ----------------------------------------------------------------------------
// Sends the flight plan over a transport (such as shared memory or UDPv4)
// This writes the FlightPlan data using RTI Connext DDS to any DataReader
// that shares the same Topic
bool FlightPlanPublisherInterface::Write(DdsAutoType<FlightPlan> data)
{
	DDS_ReturnCode_t retcode = DDS_RETCODE_OK;
	DDS_InstanceHandle_t handle = DDS_HANDLE_NIL;

	// This actually sends the flight plan data over the network.  

	// The handle that the write() call takes is a handle to the individual
	// flight plan instance - a unique flight plan described by a 
	// unique 8-character flight ID.  

	// The flight plan data has a very simple ID, and does not need high-
	// throughput, so we are not bothering to pre-register the instance 
	// handle.  If we did pre-register the instance handle, this could 
	// potentially speed up the writing.
	retcode = _writer->write(data, handle);

	if (retcode != DDS_RETCODE_OK) 
	{
		return false;
	}

	return true;

}

// ----------------------------------------------------------------------------
// Sends a deletion message for the flight plan data over a transport (such as 
// shared memory or UDPv4) This uses the unregiste_instance call to notify
// other applications that this flight plan has gone away and should be deleted
bool FlightPlanPublisherInterface::Delete(DdsAutoType<FlightPlan> data)
{
	DDS_ReturnCode_t retcode = DDS_RETCODE_OK;
	DDS_InstanceHandle_t handle = DDS_HANDLE_NIL;

	// Note that the deletion maps to an "unregister" in the RTI Connext
	// DDS world.  This allows the instance to be cleaned up entirely, 
	// so the space can be reused for another instance.  If you call
	// "dispose" it will not clean up the space for a new instance - 
	// instead it marks the current instance disposed and expects that you
	// might reuse the same instance again later.
	retcode = _writer->unregister_instance(data, handle);

	if (retcode != DDS_RETCODE_OK)
	{
		return false;
	}

	return true;
}
