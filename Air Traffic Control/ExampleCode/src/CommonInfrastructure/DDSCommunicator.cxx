#include "DDSCommunicator.h"

using namespace DDS;

DDSCommunicator::~DDSCommunicator() 
{
	if (_participant != NULL) {
		_participant->delete_contained_entities();
		TheParticipantFactory->delete_participant(_participant);

		// In theory, can finalize the participant factory here, but this
		// will not work if you have multiple communicators - for example
		// in different DDS domains.  Leaving this commented out because
		// this should only be called before the end of the application
		TheParticipantFactory->finalize_instance();
	}
}


DomainParticipant* DDSCommunicator::CreateParticipant(long domain) 
{
	DomainParticipant* participant = 
		TheParticipantFactory->create_participant(domain, 
		PARTICIPANT_QOS_DEFAULT, NULL, STATUS_MASK_NONE);

	if (participant == NULL) {
		std::stringstream errss;
		errss << "Failed to create DomainParticipant object";
		throw errss.str();
	} 

	return participant;
}


DomainParticipant* DDSCommunicator::CreateParticipant() 
{
	_participant = 
		TheParticipantFactory->create_participant(
									0, 
									PARTICIPANT_QOS_DEFAULT, 
									NULL, STATUS_MASK_NONE);

	if (_participant == NULL) {
		std::stringstream errss;
		errss << "Failed to create DomainParticipant object";
		throw errss.str();
	} 

	return _participant;
}


DomainParticipant* DDSCommunicator::CreateParticipant(
	long domain, 
	char *participantQosLibrary, 
	char *participantQosProfile) 
{
	_participant = 
		TheParticipantFactory->create_participant_with_profile(
									domain, 
									participantQosLibrary, 
									participantQosProfile, 
									NULL, 
									STATUS_MASK_NONE);

	if (_participant == NULL) {
		std::stringstream errss;
		errss << "Failed to create DomainParticipant object";
		throw errss.str();
	} 

	return _participant;

}


DomainParticipant* DDSCommunicator::CreateParticipant(long domain, 
	std::vector<std::string>fileNames, char *participantQosLibrary, 
	char *participantQosProfile) 
{

	DDS_ReturnCode_t retcode;
	// Adding a list of explicit file names to the DomainParticipantFactory
	// This gives the middleware a set of places to search for the files
	// 
	DomainParticipantFactoryQos factoryQos;
	TheParticipantFactory->get_qos(factoryQos);
	factoryQos.profile.url_profile.ensure_length(fileNames.size(),
												fileNames.size());

	for (unsigned int i = 0; i < fileNames.size(); i++) 
	{
		// Note that we copy the file names here, so they cannot go out of 
		// scope
		factoryQos.profile.url_profile[i] = DDS_String_dup(
			fileNames[i].c_str());
	}

	retcode = TheParticipantFactory->set_qos(factoryQos);
		
	if (retcode != DDS_RETCODE_OK) {
		std::stringstream errss;
		errss << "Failed to create DomainParticipant object";
		throw errss.str();
	}

	_participant = 
		TheParticipantFactory->create_participant_with_profile(
									domain, 
									participantQosLibrary, 
									participantQosProfile, 
									NULL, 
									STATUS_MASK_NONE);

	if (_participant == NULL) {
		std::stringstream errss;
		errss << "Failed to create DomainParticipant object";
		throw errss.str();
	} 

	return _participant;

}


Publisher* DDSCommunicator::CreatePublisher()
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
	// can actually send data.  The Publisher object is being created in 
	// the RadarInterface class because one Publisher can be used to create
	// multiple DDS DataWriters.  This could be moved to the base class, 
	// 
	_pub = GetParticipant()->create_publisher(
									DDS_PUBLISHER_QOS_DEFAULT, 
									NULL, DDS_STATUS_MASK_NONE);	

	if (_pub == NULL) 
	{
		std::stringstream errss;
		errss << "Failed to create Publisher";
		throw errss.str();
	}

	return _pub;
}

Publisher* DDSCommunicator::CreatePublisher(char *qosLibrary, char *qosProfile)
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
	// can actually send data.  The Publisher object is being created in the
	// RadarInterface class because one Publisher can be used to create
	// multiple DDS DataWriters.  This could be moved to the base class, 
	// 
	_pub = GetParticipant()->create_publisher_with_profile(
								qosLibrary, 
								qosProfile,
								NULL, DDS_STATUS_MASK_NONE);	

	if (_pub == NULL) 
	{
		std::stringstream errss;
		errss << "Failed to create Publisher";
		throw errss.str();
	}

	return _pub;
}


Subscriber* DDSCommunicator::CreateSubscriber()
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
	_sub = GetParticipant()->create_subscriber(
								DDS_SUBSCRIBER_QOS_DEFAULT, 
								NULL, DDS_STATUS_MASK_NONE);	

	if (_sub == NULL) 
	{
		std::stringstream errss;
		errss << "Failed to create Subscriber";
		throw errss.str();
	}

	return _sub;
}

Subscriber* DDSCommunicator::CreateSubscriber(char *qosLibrary,
	char *qosProfile)
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
	_sub = GetParticipant()->create_subscriber_with_profile(
								qosLibrary, 
								qosProfile, 
								NULL, DDS_STATUS_MASK_NONE);	
	if (_sub == NULL) 
	{
		std::stringstream errss;
		errss << "Failed to create Subscriber";
		throw errss.str();
	}

	return _sub;

}