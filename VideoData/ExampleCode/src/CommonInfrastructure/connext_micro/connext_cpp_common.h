#ifndef CONNEXT_CPP_COMMON_H
#define CONNEXT_CPP_COMMON_H

/* Micro versions of Connext-specific includes */

#include "rti_me_cpp.hxx"
#include "dds_cpp/dds_cpp_namespace.hxx"

/* DDS generated code headers */
#include "VideoData.h"
#include "VideoDataSupport.h"

#define CONNEXT_HAS_BUILTINTOPICS      (-1)
#define CONNEXT_HAS_USERDATA           (-1)
#define VIDEODATA_MATCH_EMPTY_USERDATA (-1)

/* Since Connext Micro does not support XML QoS profiles, we need to provide
   functions that abstract the functionality */

#include <vector>
#include <string>

namespace Connext {

/* Return type to hide the different return types */

const RTI_BOOL TYPESUPPORT_OK = RTI_TRUE;

/* Encapsulating the sleep utility */
/* Encapsulating the sleep utility */
inline void sleep(long seconds, unsigned long nano_seconds) {
   OSAPI_Thread_sleep(seconds*1000 + nano_seconds/1000);
}
/* Convenience function for setting profiles files in the ParticipantFactory */

DDS::ReturnCode_t
set_url_profile(
   std::vector<std::string> fileNames);

/* Function encapsulating initialization of libraries, different for Pro and Micro */

DDS::ReturnCode_t
initialize_infrastructure(const std::string &interface_name);

/* Functions that are equivalent to the member functions on ParticipantFactory */

DDS::ReturnCode_t
get_participant_qos_from_profile(
    DDS::DomainParticipantQos &qos,
    const std::string &library_name, const std::string &profile_name);

DDS::ReturnCode_t
get_subscriber_qos_from_profile(
    DDS::SubscriberQos &qos,
    const std::string &library_name, const std::string &profile_name);

DDS::ReturnCode_t
get_datareader_qos_from_profile(
    DDS::DataReaderQos &qos,
    const std::string &library_name, const std::string &profile_name);

DDS::ReturnCode_t
get_publisher_qos_from_profile(
    DDS::PublisherQos &qos,
    const std::string &library_name, const std::string &profile_name);

DDS::ReturnCode_t
get_datawriter_qos_from_profile(
    DDS::DataWriterQos &qos,
    const std::string &library_name, const std::string &profile_name);

}

#endif /* CONNEXT_CPP_COMMON_H */
