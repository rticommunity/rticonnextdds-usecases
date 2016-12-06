/*********************************************************************************************
(c) 2005-2013 Copyright, Real-Time Innovations, Inc.  All rights reserved.    	                             
RTI grants Licensee a license to use, modify, compile, and create derivative works 
of the Software.  Licensee has the right to distribute object form only for use with RTI 
products.  The Software is provided �as is�, with no warranty of any type, including 
any warranty for fitness for any purpose. RTI is under no obligation to maintain or 
support the Software.  RTI shall not be liable for any incidental or consequential 
damages arising out of the use or inability to use the software.
**********************************************************************************************/
#include "DDSCommunicator.h"

// ------------------------------------------------------------------------- //
// Destruction of a DDS communication interface.  This first deletes all the
// entities created by the DomainParticipant object.  Then, it cleans up the 
// types that have been registered with the DomainParticipant.  (This is not
// strictly necessary, but will cause a very small memory leak at shutdown if
// all types are not unregistered.  Thirdly, this deletes the 
// DomainParticipant.  Lastly, this finalizes the DomainParticipantFactory.
DDSCommunicator::~DDSCommunicator() 
{
	if (_participant != NULL) 
	{

		// Delete DataWriters, DataReaders, Topics, Subscribers, and Publishers
		// created by this DomainParticipant.
		_participant->delete_contained_entities();

		// Unregister all the data types registered with this DomainParticipant
		for (std::map<std::string, 
			UnregisterInfo>::iterator it =
			_typeCleanupFunctions.begin();
				it != _typeCleanupFunctions.end();  it++)
		{
			(*it).second.unregisterFunction(_participant, (
				*it).first.c_str());
		}

		// Delete the DomainParticipant
		TheParticipantFactory->delete_participant(_participant);

		// You finalize the participant factory here, but this
		// will not work if you have multiple communicators - for example
		// in different DDS domains.  In that case, you must be more careful
		// to only finalize the participant factory after all 
		// DomainParticipants have been deleted.
		TheParticipantFactory->finalize_instance();
	}
}

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

// ------------------------------------------------------------------------- //
// Creating a DomainParticipant with a specified domain ID  
DDS::DomainParticipant* DDSCommunicator::CreateParticipant(long domain, 
		DDS::DataReaderListener *discoveryListener,
		DiscoveryListenerKind listenerKind) 
{
   return CreateParticipant(domain, "", "", discoveryListener, listenerKind);
}

// ------------------------------------------------------------------------- //
// Creating a DomainParticipant with a domain ID of zero
DDS::DomainParticipant* DDSCommunicator::CreateParticipant() 
{
	return CreateParticipant(0, "", "", NULL, NO_DISCOVERY_KIND);
}


// ------------------------------------------------------------------------- //
// Creating a DomainParticipant with a specified domain ID and specified QoS 
DDS::DomainParticipant* DDSCommunicator::CreateParticipant(
	long domain, 
	const std::string &participantQosLibrary, 
	const std::string &participantQosProfile,		
	DDS::DataReaderListener *discoveryListener,
	DiscoveryListenerKind listenerKind) 
{
   DDS::ReturnCode_t retcode;
   
	// If we have a discovery listener installed, create the DomainParticipant
	// disabled, so that we can install the listener before the discovery
	// process starts.
	if (discoveryListener != NULL)
	{
		PrepareFactoryForDiscoveryListener();
	}

   DDS::DomainParticipantQos participant_qos;
   /* Only invoke profile action if not both strings are empty */
   if (!(participantQosLibrary.empty() && participantQosProfile.empty())) {
      retcode = Connext::get_participant_qos_from_profile(participant_qos,
         participantQosLibrary.c_str(), participantQosProfile.c_str());
      if (retcode != DDS::RETCODE_OK) 
      {
         std::stringstream errss;
         errss << "Failed to get ParticipantQos from profile";
         throw errss.str();
      }
   } else {
      participant_qos = DDS::PARTICIPANT_QOS_DEFAULT;
   }

   /* Initialize infrastructure before creating Participant */
   retcode = Connext::initialize_infrastructure("");
   if (retcode != DDS::RETCODE_OK) 
   {
      std::stringstream errss;
      errss << "Failed to initialize infrastructure";
      throw errss.str();
   }
   
	_participant = 
		TheParticipantFactory->create_participant(
									domain,
                           participant_qos,
									NULL,
									DDS::STATUS_MASK_NONE);
   if (_participant == NULL) 
	{
		std::stringstream errss;
		errss << "Failed to create DomainParticipant object";
		throw errss.str();
	} 

	if (discoveryListener != NULL)
	{
		// Install the discovery listener and enable the DomainParticipant
		InstallDiscoveryListener(discoveryListener, listenerKind);
	}

	return _participant;
}


// ------------------------------------------------------------------------- //
// Creating a DomainParticipant with a specified domain ID, specified QoS file
// names, and specified QoS 
DDS::DomainParticipant* DDSCommunicator::CreateParticipant(long domain, 
	std::vector<std::string> fileNames, 
	const std::string &participantQosLibrary, 
	const std::string &participantQosProfile, 
	DDS::DataReaderListener *discoveryListener, 
	DiscoveryListenerKind listenerKind) 
{

	// Adding a list of explicit file names to the DomainParticipantFactory
	// This gives the middleware a set of places to search for the files
   DDS::ReturnCode_t retcode = Connext::set_url_profile(fileNames);
	if (retcode != DDS::RETCODE_OK) 
	{
		std::stringstream errss;
		errss << "Failed to set url profiles";
		throw errss.str();
	}
   return CreateParticipant(domain, participantQosLibrary,
      participantQosProfile, discoveryListener, listenerKind);
}


// ------------------------------------------------------------------------- //
// Creating a Publisher object.  This is used to create type-specific 
// DataWriter objects in the application
DDS::Publisher* DDSCommunicator::CreatePublisher()
{
   return CreatePublisher("", "");
}

// ------------------------------------------------------------------------- //
// Creating a Publisher object with specified QoS.  This is used to create 
// type-specific DataWriter objects in the application
DDS::Publisher* DDSCommunicator::CreatePublisher(
	const std::string &qosLibrary, 
	const std::string &qosProfile)
{
	if (GetParticipant() == NULL) 
	{
		std::stringstream errss;
		errss << 
			"DomainParticipant NULL - communicator not properly " << 
				"initialized";
		throw errss.str();
	}

	// Creating a Publisher.  
	// This object is used to create type-specific DataWriter objects that 
	// can actually send data.  
	// 
   DDS::PublisherQos publisher_qos;
   /* Only invoke profile action if not both strings are empty */
   if (!(qosLibrary.empty() && qosProfile.empty())) {
      DDS::ReturnCode_t retcode = Connext::get_publisher_qos_from_profile(publisher_qos,
         qosLibrary.c_str(), qosProfile.c_str());
      if (retcode != DDS::RETCODE_OK) 
      {
         std::stringstream errss;
         errss << "Failed to get PublisherQoS from profile " <<
            qosLibrary << "::" << qosProfile;
         throw errss.str();
      }
   } else {
      publisher_qos = DDS::PUBLISHER_QOS_DEFAULT;
   }

   _pub = GetParticipant()->create_publisher(
      publisher_qos,	NULL, DDS::STATUS_MASK_NONE);
	if (_pub == NULL) 
	{
		std::stringstream errss;
		errss << "Failed to create Publisher";
		throw errss.str();
	}

	return _pub;
}


// ------------------------------------------------------------------------- //
// Creating a Subscriber object.  This is used to create type-specific 
// DataReader objects in the application
DDS::Subscriber* DDSCommunicator::CreateSubscriber()
{
   return CreateSubscriber("", "");
}

// ------------------------------------------------------------------------- //
// Creating a Subscriber object with specified QoS.  This is used to create 
// type-specific DataReader objects in the application
DDS::Subscriber* DDSCommunicator::CreateSubscriber(
	const std::string &qosLibrary,
	const std::string &qosProfile)
{
	if (GetParticipant() == NULL) 
	{
		std::stringstream errss;
		errss << 
			"DomainParticipant NULL - communicator not properly " <<
				"initialized";
		throw errss.str();
	}

	// Creating a Subscriber.  
	// This object is used to create type-specific DataReader objects that 
	// can actually receive data.  The Subscriber object is being created
	//  in the DDSCommunicator class because one Subscriber can be used to
	//  create multiple DDS DataReaders. 
	// 
   DDS::SubscriberQos subscriber_qos;
   /* Only invoke profile action if not both strings are empty */
   if (!(qosLibrary.empty() && qosProfile.empty())) {
      DDS::ReturnCode_t retcode = Connext::get_subscriber_qos_from_profile(subscriber_qos,
         qosLibrary.c_str(), qosProfile.c_str());
      if (retcode != DDS::RETCODE_OK) 
      {
         std::stringstream errss;
         errss << "Failed to get SubscriberQoS from profile " <<
            qosLibrary << "::" << qosProfile;
         throw errss.str();
      }
   } else {
      subscriber_qos = DDS::SUBSCRIBER_QOS_DEFAULT;
   }

	_sub = GetParticipant()->create_subscriber(subscriber_qos,
      NULL, DDS::STATUS_MASK_NONE);
	if (_sub == NULL) 
	{
		std::stringstream errss;
		errss << "Failed to create Subscriber";
		throw errss.str();
	}

	return _sub;

}

// ------------------------------------------------------------------------- //
// This configures the DomainParticipant factory so that it will create the
// DomainParticipant, but will not automatically enable it.  This allows
// the application to add a listener for discovery.
void DDSCommunicator::PrepareFactoryForDiscoveryListener()
{
	DDS::DomainParticipantFactoryQos factoryQos;
	TheParticipantFactory->get_qos(factoryQos);
	factoryQos.entity_factory.autoenable_created_entities = false;
	TheParticipantFactory->set_qos(factoryQos);
}

// ------------------------------------------------------------------------- //
// This adds the discovery listener to the newly-created DomainParticipant, and
// enables the DomainParticipant when it is done.
void DDSCommunicator::InstallDiscoveryListener(
		DDS::DataReaderListener *discoveryListener,
		DiscoveryListenerKind listenerKind)
{
#if (CONNEXT_HAS_BUILTINTOPICS == 1)
	char *discoveryTopic = NULL;
	if (listenerKind == PARTICIPANT_DISCOVERY_KIND)
	{
		discoveryTopic = (char *)DDS::PARTICIPANT_TOPIC_NAME;
	}
	if (listenerKind == DATAWRITER_DISCOVERY_KIND)
	{
		discoveryTopic = (char *)DDS::PUBLICATION_TOPIC_NAME;
	}
	if (listenerKind == DATAREADER_DISCOVERY_KIND)
	{
		discoveryTopic = (char *)DDS::SUBSCRIPTION_TOPIC_NAME;
	}

	// Lookup the builtin DataReader to listen for either Participant discovery, 
	// DataWriter discovery, or DataReader discovery.
	DDS::DataReader *builtinReader = 
		(DDSSubscriptionBuiltinTopicDataDataReader *)
			_participant->get_builtin_subscriber()->
				lookup_datareader(discoveryTopic);

	if (builtinReader == NULL)
	{
		std::stringstream errss;
		errss << "Failed to access Builtin Discovery DataReader object";
		throw errss.str();
	}

	// Listen for discovery events
	builtinReader->set_listener(discoveryListener, 
		DDS::DATA_AVAILABLE_STATUS);
#elif (CONNEXT_HAS_BUILTINTOPICS == -1)
   /* Deliberately empty */
#else /* CONNEXT_HAS_BUILTINTOPICS */
#error Incorrect setup: CONNEXT_HAS_BUILTINTOPIC should be defined and have the value -1 or 1
#endif
	// Enable the DomainParticipant
	_participant->enable();

}
