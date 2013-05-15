#ifndef DDS_COMMUNICATOR_H
#define DDS_COMMUNICATOR_H

#include <sstream>
#include <vector>
#include "ndds/ndds_cpp.h"
#include "ndds/ndds_namespace_cpp.h"


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

private:

	DDS::DomainParticipant* _participant;
	DDS::Publisher* _pub;
	DDS::Subscriber* _sub;


};

#endif