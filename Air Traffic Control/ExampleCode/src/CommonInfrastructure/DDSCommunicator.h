#ifndef DDS_COMMUNICATOR_H
#define DDS_COMMUNICATOR_H

#include <sstream>
#include <vector>
#include <map>
#include "ndds/ndds_cpp.h"
#include "ndds/ndds_namespace_cpp.h"


// ------------------------------------------------------------------------- //
// Function that is used to unregister types from the DomainParticipant.
// types are automatically registered when you create the topic, and 
// unregistered at shutdown.

typedef DDS_ReturnCode_t (*unregister_fn)(DDSDomainParticipant *, const char *);

struct UnregisterInfo {
  std::string typeName;
  unregister_fn unregisterFunction;
};
// ------------------------------------------------------------------------- //
//
// DDSCommunicator:
// This class is used by all RTI Connext DDS interfaces to create the core
// communication objects, such as a DomainParticipant, Publisher and/or 
// Subscriber.
//
// ------------------------------------------------------------------------- //
class DDSCommunicator {

public:
	DDSCommunicator() : _participant(NULL), _pub(NULL), _sub(NULL)
	{}

	~DDSCommunicator();

	// --- Creating a DomainParticipant --- 

	// A DomainParticipant starts the DDS discovery process.  It creates
	// several threads, sends and receives discovery information over one or 
	// more transports, and maintains an in-memory discovery database of 
	// remote DomainParticipants, remote DataWriters, and remote DataReaders

	// Quality of Service can be applied on the level of the DomainParticipant.  
	// This QoS controls the characteristics of:
	// 1. Transport properties such as which type of network (UDPv4, UDPv6, 
	//    shared memory) or which network interfaces it is allowed to use
	// 2. Which applications this discovers.  By default, apps will discover
	//    other DDS applications over multicast, loopback, and shared memory.
	// 3. Resource limits for the DomainParticipant
	//
	// For more information on participant QoS, see the USER_QOS_PROFILES.xml
	// file

	// Creates a DomainParticipant with default QoS in domain 0
	DDS::DomainParticipant* CreateParticipant();

	// Creates a DomainParticipant with default QoS in the specified domain
	DDS::DomainParticipant* CreateParticipant(long domain);

	// Creates a DomainParticipant with specified QoS in the specified domain
	DDS::DomainParticipant* CreateParticipant(long domain, 
		char *participantQosLibrary, char *participantQosProfile);

	// Loads a set of XML files to load QoS profile information
	// Creates a DomainParticipant with specified QoS in the specified domain
	DDS::DomainParticipant* CreateParticipant(long domain, 
		std::vector<std::string>fileNames, char *participantQosLibrary, 
		char *participantQosProfile) ;

	// --- Getting the DomainParticipant --- 

	// Returns the DomainParticipant created by the Communicator.
	DDS::DomainParticipant* GetParticipant() {
		return _participant;
	}

	// --- Creating a Publisher --- 

	// The Publisher object is a factory for creating type-specific DataWriters
	// Note that the same publisher can be used for multiple DataWriters - 
	// typically you will create zero or one Publisher per application.

	// Create a Publisher with default QoS
	DDS::Publisher* CreatePublisher();

	// Create a Publisher with specified QoS
	DDS::Publisher* CreatePublisher(char *qosLibrary, char *qosProfile);

	// --- Getting the Publisher --- 

	// Returns the Publisher created by the Communicator.
	DDS::Publisher* GetPublisher() {
		return _pub;
	}

	// --- Creating a Subscriber --- 

	// The Subscriber object is a factory for creating type-specific 
	// DataReaders.
	// Note that the same subscriber can be used for multiple DataReaders - 
	// typically you will create zero or one Subscriber per application.

	// Create a Subscriber with default QoS
	DDS::Subscriber* CreateSubscriber();

	// Create a Subscriber with specified QoS
	DDS::Subscriber* CreateSubscriber(char *qosLibrary, char *qosProfile);
	
	// --- Getting the Subscriber --- 

	// Returns the Publisher created by the Communicator.
	DDS::Subscriber* GetSubscriber() {
		return _sub;
	}

	// --- Create a Topic --- 
	template <typename T>
	DDS::Topic *CreateTopic(std::string topicName)
	{
		// Register the data type with the DomainParticipant - this
		// allows the DomainParticipant to 
		const char *typeName = T::TypeSupport::get_type_name();
		
		DDS_ReturnCode_t retcode = T::TypeSupport::register_type(
				GetParticipant(), typeName);
		if (retcode != DDS_RETCODE_OK) {
			std::stringstream errss;
			errss << "Failure to register type. Regisetered twice?";
			throw errss.str();
		}

		DDS::Topic *topic = GetParticipant()->create_topic(
			topicName.c_str(),
			typeName, DDS_TOPIC_QOS_DEFAULT, NULL /* listener */,
			DDS_STATUS_MASK_NONE);
		if (topic == NULL) {
			std::stringstream errss;
			errss << "FlightPlanReader(): failure to create Topic. Created twice?";
			throw errss.str();
		}

		UnregisterInfo unregisterInfo;
		unregisterInfo.typeName = typeName;
		unregisterInfo.unregisterFunction = 
			T::TypeSupport::unregister_type;
		_typeCleanupFunctions[typeName] = unregisterInfo;

		return topic;
	}

private:

	DDS::DomainParticipant* _participant;
	DDS::Publisher* _pub;
	DDS::Subscriber* _sub;
	std::map<std::string, UnregisterInfo> _typeCleanupFunctions;


};

#endif