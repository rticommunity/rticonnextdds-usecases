#ifndef CONNEXT_CPP_COMMON_H
#define CONNEXT_CPP_COMMON_H

/* Pro versions of Connext-specific includes */

#if defined(_WIN32)
    #if !defined(RTI_WIN32)
        #define RTI_WIN32
    #endif
    #if !defined(NDDS_DLL_VARIABLE)
        #define NDDS_DLL_VARIABLE
    #endif
    #ifdef _DEBUG
        #pragma comment( lib, "nddscppd.lib")
        #pragma comment( lib, "nddscd.lib")
        #pragma comment( lib, "nddscored.lib")
    #else
        #pragma comment( lib, "nddscpp.lib")
        #pragma comment( lib, "nddsc.lib")
        #pragma comment( lib, "nddscore.lib")
    #endif /* #ifdef _DEBUG */
#endif /* defined(_WIN32) */

/* DDS C++ headers */
#include "ndds/ndds_cpp.h"
#include "ndds/ndds_namespace_cpp.h"

/* DDS generated code headers */
#include "VideoData.h"
#include "VideoDataSupport.h"

#define CONNEXT_HAS_BUILTINTOPICS      (1)
#define CONNEXT_HAS_USERDATA           (1)
#define VIDEODATA_MATCH_EMPTY_USERDATA (1)

/* Since Connext Micro does not support XML QoS profiles, we need to provide
   functions that abstract the functionality */

#include <string>
#include <vector>

namespace Connext {

/* Return type to hide the different return types */
const DDS::ReturnCode_t TYPESUPPORT_OK = DDS::RETCODE_OK;

/* Encapsulating the sleep utility */
inline void sleep(long seconds, unsigned long nano_seconds) {
/* macOS (Sierra) behaves differently, NDDSUtility::sleep does not work */
#ifdef __APPLE__
    struct timespec ts;
    ts.tv_sec = seconds;
    ts.tv_nsec = nano_seconds;
    nanosleep(&ts, NULL);
#else
    DDS_Duration_t duration;
    duration.sec = seconds;
    duration.nanosec = nano_seconds;
    NDDSUtility::sleep(duration);
#endif
}

/* Convenience function for setting profiles files in the ParticipantFactory */

inline DDS::ReturnCode_t
set_url_profile(
   std::vector<std::string> fileNames)
{
	DDS::DomainParticipantFactoryQos factoryQos;
	TheParticipantFactory->get_qos(factoryQos);
	factoryQos.profile.url_profile.ensure_length(fileNames.size(),
												fileNames.size());

	for (unsigned int i = 0; i < fileNames.size(); i++) {
		// Note that we copy the file names here, so they cannot go out of 
		// scope
		factoryQos.profile.url_profile[i] = DDS_String_dup(
			fileNames[i].c_str());
	}

	return TheParticipantFactory->set_qos(factoryQos);
}


/* Convenience function for setting profiles files in the ParticipantFactory */

inline DDS::ReturnCode_t
initialize_infrastructure(const std::string &interface_name)
{
   return DDS::RETCODE_OK;
}

/* Functions that are equivalent to the member functions on ParticipantFactory */

inline DDS::ReturnCode_t
get_participant_qos_from_profile(
    DDS::DomainParticipantQos &qos,
    const std::string &library_name, const std::string &profile_name)
{
   return TheParticipantFactory->get_participant_qos_from_profile(
      qos, library_name.c_str(), profile_name.c_str());
}

inline DDS::ReturnCode_t
get_subscriber_qos_from_profile(
    DDS::SubscriberQos &qos,
    const std::string &library_name, const std::string &profile_name)
{
   return TheParticipantFactory->get_subscriber_qos_from_profile(
      qos, library_name.c_str(), profile_name.c_str());
}

inline DDS::ReturnCode_t
get_datareader_qos_from_profile(
    DDS::DataReaderQos &qos,
    const std::string &library_name, const std::string &profile_name)
{
   return TheParticipantFactory->get_datareader_qos_from_profile(
      qos, library_name.c_str(), profile_name.c_str());
}

inline DDS::ReturnCode_t
get_publisher_qos_from_profile(
    DDS::PublisherQos &qos,
    const std::string &library_name, const std::string &profile_name)
{
   return TheParticipantFactory->get_publisher_qos_from_profile(
      qos, library_name.c_str(), profile_name.c_str());
}

inline DDS::ReturnCode_t
get_datawriter_qos_from_profile(
    DDS::DataWriterQos &qos,
    const std::string &library_name, const std::string &profile_name)
{
   return TheParticipantFactory->get_datawriter_qos_from_profile(
      qos, library_name.c_str(), profile_name.c_str());
}

}

#endif /* CONNEXT_CPP_COMMON_H */
