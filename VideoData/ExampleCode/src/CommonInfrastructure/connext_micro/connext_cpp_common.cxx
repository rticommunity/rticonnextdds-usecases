/* Interface */
#include "connext_cpp_common.h"

/* Implementation */
#include <iostream>
#include "netio/netio_udp.h"
#include "connext_micro_log_trace_handlers.h"

namespace Connext {

static bool G_do_multicast = true;
#define VIDEOSTREAM_HISTORY_DEPTH (50)

/* Convenience function for setting profiles files in the ParticipantFactory */

DDS::ReturnCode_t
set_url_profile(
   std::vector<std::string> fileNames)
{
   /* Quick workaround: do nothing, assume multicast for now */
   return DDS::RETCODE_OK;
}

DDS::ReturnCode_t
initialize_infrastructure(const std::string &interface_name)
{
    DDS::ReturnCode_t result = DDS::RETCODE_ERROR;
    DDS::DomainParticipantFactory *factory = NULL;
    RT::Registry *registry = NULL;
    bool bresult;
    DPDE::DiscoveryPluginProperty dpde_properties;
    UDP::InterfaceFactoryProperty *udp_property = NULL;
    const char *udp_intf = NULL; /* TODO: remove this, should have its own parameter */   

   /* Profile name not important here, ignored */
   factory = DDS::DomainParticipantFactory::get_instance();
   if (NULL == factory) {
      std::cout << "Failed to get instance of DomainParticipantFactory" << std::endl;
      goto done;       
   }

   /* Can not install trace handlers before DPF::get_instance() is invoked */
   bresult = LogTraceHandlers_Initialize("VideoDataParticipant");
   if (!bresult) {
      std::cout << "Failed to install log or trace handler" << std::endl;
      goto done;
   }

   registry = factory->get_registry();
   if (NULL == registry) {
      std::cout << "Failed to get component registry" << std::endl;
      goto done;       
   }

   bresult = registry->register_component("wh",
                            WHSM::HistoryFactory::get_interface(),
                            NULL, NULL);
  if (!bresult) {
      std::cout << "Failed to register WH component" << std::endl;
      goto done;
   }

   bresult = registry->register_component("rh",
                            RHSM::HistoryFactory::get_interface(),
                            NULL, NULL);
   if (!bresult) {
      printf("Failed to register RH component");
      goto done;
   }

    /* Configure UDP transport's allowed interfaces */
    bresult = registry->unregister(NETIO::DEFAULT_UDP_NAME, NULL, NULL);
    if (!bresult) {
        printf("Failed to unregister default UDP component");
        goto done;
    }

    udp_property = new UDP::InterfaceFactoryProperty();
    udp_property->allow_interface.maximum(2);
    udp_property->allow_interface.length(2);

    /* loopback interface */
#if defined(__APPLE__)
   *udp_property->allow_interface.get_reference(0) = DDS_String_dup("lo0");
#elif defined (__linux__)
   *udp_property->allow_interface.get_reference(0) = DDS_String_dup("lo");
#elif defined(_WIN32)
   *udp_property->allow_interface.get_reference(0) = DDS_String_dup("Loopback Pseudo-Interface 1");
#else
   #error Unknown operating system, currently only supports OSX/macOS, Linux and Windows
#endif

   if (!interface_name.empty()) { /* use interface supplied as parameter */
      *udp_property->allow_interface.get_reference(1) =
         DDS::String_dup(interface_name.c_str());
   } else {                /* use hardcoded interface */
#if defined(__APPLE__)
      *udp_property->allow_interface.get_reference(1) =
         DDS::String_dup("en1");
#elif defined (__linux__)
      *udp_property->allow_interface.get_reference(1) =
         DDS::String_dup("eth0");
#elif defined(_WIN32)
      *udp_property->allow_interface.get_reference(1) =
         DDS::String_dup("Local Area Connection");
#else
   #error Unknown operating system, currently only supports OSX/macOS, Linux and Windows
#endif
   }

   udp_property->max_receive_buffer_size = 2097152;
   udp_property->max_message_size = 65507;

   bresult = registry->register_component(NETIO::DEFAULT_UDP_NAME,
                             UDP::InterfaceFactory::get_interface(),
                             &udp_property->_parent._parent,
                             NULL);
   if (!bresult) {
      std::cout << "Failed to register UDP component" << std::endl;
      goto done;
   }

   bresult = registry->register_component(
                             "dpde",
                             DPDE::DiscoveryFactory::get_interface(),
                             &dpde_properties._parent,
                             NULL);
   if (!bresult) {
      std::cout << "Failed to register DPDE component" << std::endl;
      goto done;
   }

   result = DDS::RETCODE_OK;

done:
   return result;
}

/* Functions that are equivalent to the member functions on ParticipantFactory */

DDS::ReturnCode_t
get_participant_qos_from_profile(
    DDS::DomainParticipantQos &qos,
    const std::string &library_name, const std::string &profile_name)
{
   DDS::ReturnCode_t result = DDS::RETCODE_ERROR;
   bool bresult;

   bresult = qos.discovery.discovery.name.set_name("dpde");
   if (!bresult) {
      std::cout << "Failed to set discovery plugin name" << std::endl;
      goto done;
   }

   qos.discovery.initial_peers.maximum(1);
   qos.discovery.initial_peers.length(1);
   *qos.discovery.initial_peers.get_reference(0) = DDS_String_dup("127.0.0.1");

   /* if there are more remote or local endpoints, you need to increase these limits */
   qos.resource_limits.max_destination_ports = 32;
   qos.resource_limits.max_receive_ports = 32;
   qos.resource_limits.local_topic_allocation = 1;
   qos.resource_limits.local_type_allocation = 1;
   qos.resource_limits.local_reader_allocation = 1;
   qos.resource_limits.local_writer_allocation = 1;
   qos.resource_limits.remote_participant_allocation = 8;
   qos.resource_limits.remote_reader_allocation = 8;
   qos.resource_limits.remote_writer_allocation = 8;

   result = DDS::RETCODE_OK;
done:
   return result;
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
   /* We assume a single writer of VideoData */
   qos.resource_limits.max_samples = VIDEOSTREAM_HISTORY_DEPTH;
   qos.resource_limits.max_instances = 1;
   qos.resource_limits.max_samples_per_instance = VIDEOSTREAM_HISTORY_DEPTH;
   qos.reader_resource_limits.max_remote_writers = 1;
   qos.reader_resource_limits.max_remote_writers_per_instance = 1;
   qos.history.depth = VIDEOSTREAM_HISTORY_DEPTH;

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
   qos.resource_limits.max_samples = VIDEOSTREAM_HISTORY_DEPTH;
   qos.resource_limits.max_samples_per_instance = VIDEOSTREAM_HISTORY_DEPTH;
   qos.resource_limits.max_instances = 1;
   qos.history.depth = VIDEOSTREAM_HISTORY_DEPTH;

   return DDS::RETCODE_OK;
}


}