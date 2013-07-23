/*********************************************************************************************
(c) 2005-2013 Copyright, Real-Time Innovations, Inc.  All rights reserved.    	                             
RTI grants Licensee a license to use, modify, compile, and create derivative works 
of the Software.  Licensee has the right to distribute object form only for use with RTI 
products.  The Software is provided “as is”, with no warranty of any type, including 
any warranty for fitness for any purpose. RTI is under no obligation to maintain or 
support the Software.  RTI shall not be liable for any incidental or consequential 
damages arising out of the use or inability to use the software.
**********************************************************************************************/

#ifndef FLIGHT_PLAN_PUBLISHER_INTERFACE_H
#define FLIGHT_PLAN_PUBLISHER_INTERFACE_H

#include <sstream>
#include "../CommonInfrastructure/DDSCommunicator.h"
#include "../CommonInfrastructure/DDSTypeWrapper.h"
#include "../Generated/AirTrafficControl.h"
#include "../Generated/AirTrafficControlSupport.h"

using namespace com::rti::atc::generated;

// ----------------------------------------------------------------------------
//
// The flight plan interface provides flight plan data over the network (or
// shared memory) to other applications that are interested in flight plans.
//
// Writing flight plan data:
// -------------------------
// This application sends flight plan data, configured to behave as state data
// (or last-value cache).  This will reliably deliver each flight plan to both
// existing and late-joining applications that subscribe to flight plan data.
//
// For information on the flight plan data type, please see the 
// AirTrafficControl.idl file.  
//
// For information on the quality of service for flight plan state data, please
// see the flight_plan_profiles.xml file.
//
// ----------------------------------------------------------------------------
class FlightPlanPublisherInterface
{

public:

	// --- Constructor --- 
	// Initializes the flight plan interface, including creating a 
	// DomainParticipant, creating all publishers and subscribers, topics 
	// writers and readers.  Takes as input a vector of xml QoS files that
	// should be loaded to find QoS profiles and libraries.
	FlightPlanPublisherInterface(std::vector<std::string> xmlFiles);

	// --- Destructor --- 
	~FlightPlanPublisherInterface();

	// --- Getter for Communicator --- 
	// Accessor for the communicator (the class that sets up the basic
	// DDS infrastructure like the DomainParticipant).
	// This allows access to the DDS DomainParticipant/Publisher/Subscriber
	// classes
	DDSCommunicator *GetCommunicator() 
	{ 
		return _communicator; 
	}

	// --- Sends the flight plan ---
	// Uses DDS interface to send a flight plan efficiently over the network
	// or shared memory to interested applications subscribing to flight plan
	// information.
	bool Write(DdsAutoType<FlightPlan> data);

	// --- Deletes the flight plan ---
	// "Deletes" the flight plan from the system - removing the DDS instance 
	// from all applications.
	bool Delete(DdsAutoType<FlightPlan> data);

private:
	// --- Private members ---

	// Used to create basic DDS entities that all applications need
	DDSCommunicator *_communicator;

	// Flight plan publisher specific to this application
	FlightPlanDataWriter *_writer;
};

#endif