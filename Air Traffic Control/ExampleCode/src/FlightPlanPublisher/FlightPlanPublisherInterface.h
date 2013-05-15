#ifndef FLIGHT_PLAN_PUBLISHER_INTERFACE_H
#define FLIGHT_PLAN_PUBLISHER_INTERFACE_H

#include <sstream>
#include "../CommonInfrastructure/DDSCommunicator.h"
#include "../Generated/AirTrafficControl.h"
#include "../Generated/AirTrafficControlSupport.h"

using namespace com::rti::atc::generated;

class FlightPlanPublisherInterface : public DDSCommunicator
{

public:

	// Initializes the flight plan interface, including creating a DomainParticipant, 
	// creating all publishers and subscribers, topics writers and readers.
	// Takes as input a vector of xml QoS files that should be loaded to find 
	// QoS profiles and libraries.
	FlightPlanPublisherInterface(std::vector<std::string> xmlFiles) 
	{

		if (NULL == CreateParticipant(0, xmlFiles, "RTIExampleQosLibrary", "FlightPlanStateData")) {
			std::stringstream errss;
			errss << "Failed to create DomainParticipant object";
			throw errss.str();
		}

		// This application only writes data, so we only need to create a
		// publisher.  The RadarData application has a more complex pattern
		// so we explicitly separate the writing interface from the overall
		// network interface - meaning that the publisher is created in the
		// network interface, and the DataWriter is created in a separate class
		// Note that one Publisher can be used to create multiple DataWriters
		DDS::Publisher *pub = GetParticipant()->create_publisher(
			DDS_PUBLISHER_QOS_DEFAULT, 
			NULL, DDS_STATUS_MASK_NONE);

		if (pub == NULL) 
		{
			std::stringstream errss;
			errss << "Failed to create Publisher object";
			throw errss.str();
		}

		const char *type_name = FlightPlanTypeSupport::get_type_name();
		DDS_ReturnCode_t retcode = FlightPlanTypeSupport::register_type(
				GetParticipant(), type_name);
		if (retcode != DDS_RETCODE_OK) {
			std::stringstream errss;
			errss << "RadarWriter(): failure to register type. Regisetered twice?";
			throw errss.str();
		}

		// 4. Look here at creating a Topic
		// The topic object is the description of the data that you will be 
		// sending. It associates a particular data type with a name that 
		// describes the meaning of the data.  Along with the data types, and
		// whether your application is reading or writing particular data, this
		// is the data interface of your application.

		// This topic has the name AIRCRAFT_FLIGHT_PLAN_TOPIC - a constant  
		// string that is defined in the .idl file.  (It is not required that
		// you define your topic name in IDL, but it is a best practice for
		// ensuring the data interface of an application is all defined in one 
		// place. You can register all topics and types up-front, if you nee
		DDS::Topic *topic = GetParticipant()->create_topic(
			AIRCRAFT_FLIGHT_PLAN_TOPIC,
			type_name, DDS_TOPIC_QOS_DEFAULT, NULL /* listener */,
			DDS_STATUS_MASK_NONE);
		if (topic == NULL) {
			std::stringstream errss;
			errss << "RadarWriter(): failure to create Topic. Created twice?";
			throw errss.str();
		}


		// 5.  Look here at creating a DataWriter.  This creates a DataWriter
		// that writes flight plan data, with QoS that is used for State Data.
		DDS::DataWriter *writer = pub->create_datawriter_with_profile(topic, 
			"RTIExampleQosLibrary", "FlightPlanStateData",
			NULL, DDS_STATUS_MASK_NONE);

		// Downcast the generic datawriter to a flight plan DataWriter 
		_writer = FlightPlanDataWriter::narrow(writer);

		if (_writer == NULL) 
		{
			std::stringstream errss;
			errss << "RadarWriter(): failure to create writer. Inconsistent Qos?";
			throw errss.str();
		}

	}

	~FlightPlanPublisherInterface()
	{
		DDS::Publisher *pub = _writer->get_publisher();
		pub->delete_datawriter(_writer);
		_writer = NULL;
	}

	// Sends the flight plan
	bool Write(FlightPlan *data) 
	{
		DDS_ReturnCode_t retcode = DDS_RETCODE_OK;
		DDS_InstanceHandle_t handle = DDS_HANDLE_NIL;

		// This actually sends the flight plan data over the network.  

		// The handle that the write() call takes is a handle to the individual
		// flight plan instance - a unique flight plan described by a 
		// unique 8-character flight ID.  

		// The flight plan data does not need the high-throughput that the 
		// radar data requires, so we are not bothering to pre-register
		// the instance handle.  If we did pre-register the instance handle,
		// this could potentially speed up the writing.
		retcode = _writer->write(*data, handle);

		if (retcode != DDS_RETCODE_OK) {
			return false;
		}

		return true;

	}

	// "Deletes" the flight plan from the system - removing the DDS instance 
	// from all applications.
	bool Delete(FlightPlan *data)
	{
		DDS_ReturnCode_t retcode = DDS_RETCODE_OK;
		DDS_InstanceHandle_t handle = DDS_HANDLE_NIL;

		// Note that the deletion maps to an "unregister" in the RTI Connext
		// DDS world.  This allows the instance to be cleaned up entirely, 
		// so the space can be reused for another instance.  If you call
		// "dispose" it will not clean up the space for a new instance - 
		// instead it marks the current instance disposed and expects that you
		// might reuse the same instance again later.
		retcode = _writer->unregister_instance(*data, handle);

		if (retcode != DDS_RETCODE_OK)
		{
			return false;
		}

		return true;
	}

private:
	FlightPlanDataWriter *_writer;
};

#endif