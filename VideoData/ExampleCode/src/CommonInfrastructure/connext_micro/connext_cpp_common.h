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

namespace Connext {

/* Convenience function for setting profiles files in the ParticipantFactory */

DDS::ReturnCode_t
set_url_profile(
   std::vector<std::string> fileNames);

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
