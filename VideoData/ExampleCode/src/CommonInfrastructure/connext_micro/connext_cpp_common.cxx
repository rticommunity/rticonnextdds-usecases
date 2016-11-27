#include "connext_cpp_common.h"

namespace Connext {

/* Convenience function for setting profiles files in the ParticipantFactory */

DDS::ReturnCode_t
set_url_profile(
   std::vector<std::string> fileNames)
{
   return DDS::RETCODE_OK;
}

/* Functions that are equivalent to the member functions on ParticipantFactory */

DDS::ReturnCode_t
get_participant_qos_from_profile(
    DDS::DomainParticipantQos &qos,
    const std::string &library_name, const std::string &profile_name)
{
   return DDS::RETCODE_OK;
}

DDS::ReturnCode_t
get_subscriber_qos_from_profile(
    DDS::SubscriberQos &qos,
    const std::string &library_name, const std::string &profile_name)
{
   return DDS::RETCODE_OK;
}

DDS::ReturnCode_t
get_datareader_qos_from_profile(
    DDS::DataReaderQos &qos,
    const std::string &library_name, const std::string &profile_name)
{
   return DDS::RETCODE_OK;
}

DDS::ReturnCode_t
get_publisher_qos_from_profile(
    DDS::PublisherQos &qos,
    const std::string &library_name, const std::string &profile_name)
{
   return DDS::RETCODE_OK;
}

DDS::ReturnCode_t
get_datawriter_qos_from_profile(
    DDS::DataWriterQos &qos,
    const std::string &library_name, const std::string &profile_name)
{
   return DDS::RETCODE_OK;
}

}