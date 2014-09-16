
/*
  WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

  This file was generated from VideoData.idl using "rtiddsgen".
  The rtiddsgen tool is part of the RTI Connext distribution.
  For more information, type 'rtiddsgen -help' at a command shell
  or consult the RTI Connext manual.
*/

#ifndef VideoDataPlugin_1974959798_h
#define VideoDataPlugin_1974959798_h

#include "VideoData.h"



struct RTICdrStream;

#ifndef pres_typePlugin_h
#include "pres/pres_typePlugin.h"
#endif


#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif


namespace com{

namespace rti{

namespace media{

namespace generated{

/* The type used to store keys for instances of type struct
 * VideoStream.
 *
 * By default, this type is struct VideoStream
 * itself. However, if for some reason this choice is not practical for your
 * system (e.g. if sizeof(struct VideoStream)
 * is very large), you may redefine this typedef in terms of another type of
 * your choosing. HOWEVER, if you define the KeyHolder type to be something
 * other than struct VideoStream, the
 * following restriction applies: the key of struct
 * VideoStream must consist of a
 * single field of your redefined KeyHolder type and that field must be the
 * first field in struct VideoStream.
*/
typedef  class VideoStream VideoStreamKeyHolder;


#define VideoStreamPlugin_get_sample PRESTypePluginDefaultEndpointData_getSample  
#define VideoStreamPlugin_get_buffer PRESTypePluginDefaultEndpointData_getBuffer 
#define VideoStreamPlugin_return_buffer PRESTypePluginDefaultEndpointData_returnBuffer 

#define VideoStreamPlugin_get_key PRESTypePluginDefaultEndpointData_getKey 
#define VideoStreamPlugin_return_key PRESTypePluginDefaultEndpointData_returnKey
 

#define VideoStreamPlugin_create_sample PRESTypePluginDefaultEndpointData_createSample 
#define VideoStreamPlugin_destroy_sample PRESTypePluginDefaultEndpointData_deleteSample 

/* --------------------------------------------------------------------------------------
    Support functions:
 * -------------------------------------------------------------------------------------- */

NDDSUSERDllExport extern VideoStream*
VideoStreamPluginSupport_create_data_w_params(
    const struct DDS_TypeAllocationParams_t * alloc_params);

NDDSUSERDllExport extern VideoStream*
VideoStreamPluginSupport_create_data_ex(RTIBool allocate_pointers);

NDDSUSERDllExport extern VideoStream*
VideoStreamPluginSupport_create_data(void);

NDDSUSERDllExport extern RTIBool 
VideoStreamPluginSupport_copy_data(
    VideoStream *out,
    const VideoStream *in);

NDDSUSERDllExport extern void 
VideoStreamPluginSupport_destroy_data_w_params(
    VideoStream *sample,
    const struct DDS_TypeDeallocationParams_t * dealloc_params);

NDDSUSERDllExport extern void 
VideoStreamPluginSupport_destroy_data_ex(
    VideoStream *sample,RTIBool deallocate_pointers);

NDDSUSERDllExport extern void 
VideoStreamPluginSupport_destroy_data(
    VideoStream *sample);

NDDSUSERDllExport extern void 
VideoStreamPluginSupport_print_data(
    const VideoStream *sample,
    const char *desc,
    unsigned int indent);


NDDSUSERDllExport extern VideoStream*
VideoStreamPluginSupport_create_key_ex(RTIBool allocate_pointers);

NDDSUSERDllExport extern VideoStream*
VideoStreamPluginSupport_create_key(void);

NDDSUSERDllExport extern void 
VideoStreamPluginSupport_destroy_key_ex(
    VideoStreamKeyHolder *key,RTIBool deallocate_pointers);

NDDSUSERDllExport extern void 
VideoStreamPluginSupport_destroy_key(
    VideoStreamKeyHolder *key);

/* ----------------------------------------------------------------------------
    Callback functions:
 * ---------------------------------------------------------------------------- */

NDDSUSERDllExport extern PRESTypePluginParticipantData 
VideoStreamPlugin_on_participant_attached(
    void *registration_data, 
    const struct PRESTypePluginParticipantInfo *participant_info,
    RTIBool top_level_registration, 
    void *container_plugin_context,
    RTICdrTypeCode *typeCode);

NDDSUSERDllExport extern void 
VideoStreamPlugin_on_participant_detached(
    PRESTypePluginParticipantData participant_data);
    
NDDSUSERDllExport extern PRESTypePluginEndpointData 
VideoStreamPlugin_on_endpoint_attached(
    PRESTypePluginParticipantData participant_data,
    const struct PRESTypePluginEndpointInfo *endpoint_info,
    RTIBool top_level_registration, 
    void *container_plugin_context);

NDDSUSERDllExport extern void 
VideoStreamPlugin_on_endpoint_detached(
    PRESTypePluginEndpointData endpoint_data);
    
NDDSUSERDllExport extern void    
VideoStreamPlugin_return_sample(
    PRESTypePluginEndpointData endpoint_data,
    VideoStream *sample,
    void *handle);    
 

NDDSUSERDllExport extern RTIBool 
VideoStreamPlugin_copy_sample(
    PRESTypePluginEndpointData endpoint_data,
    VideoStream *out,
    const VideoStream *in);

/* --------------------------------------------------------------------------------------
    (De)Serialize functions:
 * -------------------------------------------------------------------------------------- */

NDDSUSERDllExport extern RTIBool 
VideoStreamPlugin_serialize(
    PRESTypePluginEndpointData endpoint_data,
    const VideoStream *sample,
    struct RTICdrStream *stream, 
    RTIBool serialize_encapsulation,
    RTIEncapsulationId encapsulation_id,
    RTIBool serialize_sample, 
    void *endpoint_plugin_qos);

NDDSUSERDllExport extern RTIBool 
VideoStreamPlugin_deserialize_sample(
    PRESTypePluginEndpointData endpoint_data,
    VideoStream *sample, 
    struct RTICdrStream *stream,
    RTIBool deserialize_encapsulation,
    RTIBool deserialize_sample, 
    void *endpoint_plugin_qos);

 
NDDSUSERDllExport extern RTIBool 
VideoStreamPlugin_deserialize(
    PRESTypePluginEndpointData endpoint_data,
    VideoStream **sample, 
    RTIBool * drop_sample,
    struct RTICdrStream *stream,
    RTIBool deserialize_encapsulation,
    RTIBool deserialize_sample, 
    void *endpoint_plugin_qos);




NDDSUSERDllExport extern RTIBool
VideoStreamPlugin_skip(
    PRESTypePluginEndpointData endpoint_data,
    struct RTICdrStream *stream, 
    RTIBool skip_encapsulation,  
    RTIBool skip_sample, 
    void *endpoint_plugin_qos);

NDDSUSERDllExport extern unsigned int 
VideoStreamPlugin_get_serialized_sample_max_size(
    PRESTypePluginEndpointData endpoint_data,
    RTIBool include_encapsulation,
    RTIEncapsulationId encapsulation_id,
    unsigned int current_alignment);

NDDSUSERDllExport extern unsigned int 
VideoStreamPlugin_get_serialized_sample_min_size(
    PRESTypePluginEndpointData endpoint_data,
    RTIBool include_encapsulation,
    RTIEncapsulationId encapsulation_id,
    unsigned int current_alignment);

NDDSUSERDllExport extern unsigned int
VideoStreamPlugin_get_serialized_sample_size(
    PRESTypePluginEndpointData endpoint_data,
    RTIBool include_encapsulation,
    RTIEncapsulationId encapsulation_id,
    unsigned int current_alignment,
    const VideoStream * sample);



/* --------------------------------------------------------------------------------------
    Key Management functions:
 * -------------------------------------------------------------------------------------- */

NDDSUSERDllExport extern PRESTypePluginKeyKind 
VideoStreamPlugin_get_key_kind(void);

NDDSUSERDllExport extern unsigned int 
VideoStreamPlugin_get_serialized_key_max_size(
    PRESTypePluginEndpointData endpoint_data,
    RTIBool include_encapsulation,
    RTIEncapsulationId encapsulation_id,
    unsigned int current_alignment);

NDDSUSERDllExport extern RTIBool 
VideoStreamPlugin_serialize_key(
    PRESTypePluginEndpointData endpoint_data,
    const VideoStream *sample,
    struct RTICdrStream *stream,
    RTIBool serialize_encapsulation,
    RTIEncapsulationId encapsulation_id,
    RTIBool serialize_key,
    void *endpoint_plugin_qos);

NDDSUSERDllExport extern RTIBool 
VideoStreamPlugin_deserialize_key_sample(
    PRESTypePluginEndpointData endpoint_data,
    VideoStream * sample,
    struct RTICdrStream *stream,
    RTIBool deserialize_encapsulation,
    RTIBool deserialize_key,
    void *endpoint_plugin_qos);

 
NDDSUSERDllExport extern RTIBool 
VideoStreamPlugin_deserialize_key(
    PRESTypePluginEndpointData endpoint_data,
    VideoStream ** sample,
    RTIBool * drop_sample,
    struct RTICdrStream *stream,
    RTIBool deserialize_encapsulation,
    RTIBool deserialize_key,
    void *endpoint_plugin_qos);


NDDSUSERDllExport extern RTIBool
VideoStreamPlugin_serialized_sample_to_key(
    PRESTypePluginEndpointData endpoint_data,
    VideoStream *sample,
    struct RTICdrStream *stream, 
    RTIBool deserialize_encapsulation,  
    RTIBool deserialize_key, 
    void *endpoint_plugin_qos);

 
NDDSUSERDllExport extern RTIBool 
VideoStreamPlugin_instance_to_key(
    PRESTypePluginEndpointData endpoint_data,
    VideoStreamKeyHolder *key, 
    const VideoStream *instance);

NDDSUSERDllExport extern RTIBool 
VideoStreamPlugin_key_to_instance(
    PRESTypePluginEndpointData endpoint_data,
    VideoStream *instance, 
    const VideoStreamKeyHolder *key);

NDDSUSERDllExport extern RTIBool 
VideoStreamPlugin_instance_to_keyhash(
    PRESTypePluginEndpointData endpoint_data,
    DDS_KeyHash_t *keyhash,
    const VideoStream *instance);

NDDSUSERDllExport extern RTIBool 
VideoStreamPlugin_serialized_sample_to_keyhash(
    PRESTypePluginEndpointData endpoint_data,
    struct RTICdrStream *stream, 
    DDS_KeyHash_t *keyhash,
    RTIBool deserialize_encapsulation,
    void *endpoint_plugin_qos); 
     
/* Plugin Functions */
NDDSUSERDllExport extern struct PRESTypePlugin*
VideoStreamPlugin_new(void);

NDDSUSERDllExport extern void
VideoStreamPlugin_delete(struct PRESTypePlugin *);

} /* namespace generated */

} /* namespace media */

} /* namespace rti */

} /* namespace com */

        
#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif        

#endif /* VideoDataPlugin_1974959798_h */
