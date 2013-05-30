#ifndef FLIGHT_PLAN_PUBLISHER_INTERFACE_H
#define FLIGHT_PLAN_PUBLISHER_INTERFACE_H

#include <sstream>
#include "../CommonInfrastructure/DDSCommunicator.h"
#include "../Generated/AirTrafficControl.h"
#include "../Generated/AirTrafficControlSupport.h"

using namespace com::rti::atc::generated;

class FlightPlanPublisherInterface
{

public:

	// Initializes the flight plan interface, including creating a 
	// DomainParticipant, creating all publishers and subscribers, topics 
	// writers and readers.  Takes as input a vector of xml QoS files that
	// should be loaded to find QoS profiles and libraries.
	FlightPlanPublisherInterface(std::vector<std::string> xmlFiles);


	DDSCommunicator *GetCommunicator() 
	{ 
		return _communicator; 
	}

	~FlightPlanPublisherInterface();

	// Sends the flight plan
	bool Write(FlightPlan *data);

	// "Deletes" the flight plan from the system - removing the DDS instance 
	// from all applications.
	bool Delete(FlightPlan *data);

private:
	DDSCommunicator *_communicator;
	FlightPlanDataWriter *_writer;
};

#endif