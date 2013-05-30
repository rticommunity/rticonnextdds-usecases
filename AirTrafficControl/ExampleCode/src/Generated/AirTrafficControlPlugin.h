
/*
  WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

  This file was generated from AirTrafficControl.idl using "rtiddsgen".
  The rtiddsgen tool is part of the RTI Connext distribution.
  For more information, type 'rtiddsgen -help' at a command shell
  or consult the RTI Connext manual.
*/

#ifndef AirTrafficControlPlugin_1144379923_h
#define AirTrafficControlPlugin_1144379923_h

#include "AirTrafficControl.h"




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

namespace atc{

namespace generated{


#define com_rti_atc_generated_FlightId_LAST_MEMBER_ID string_LAST_MEMBER_ID

#define FlightIdPlugin_get_sample PRESTypePluginDefaultEndpointData_getSample 
#define FlightIdPlugin_return_sample PRESTypePluginDefaultEndpointData_returnSample 
#define FlightIdPlugin_get_buffer PRESTypePluginDefaultEndpointData_getBuffer 
#define FlightIdPlugin_return_buffer PRESTypePluginDefaultEndpointData_returnBuffer 
 

#define FlightIdPlugin_create_sample PRESTypePluginDefaultEndpointData_createSample 
#define FlightIdPlugin_destroy_sample PRESTypePluginDefaultEndpointData_deleteSample 

/* --------------------------------------------------------------------------------------
    Support functions:
 * -------------------------------------------------------------------------------------- */

NDDSUSERDllExport extern FlightId*
FlightIdPluginSupport_create_data_ex(RTIBool allocate_pointers);

NDDSUSERDllExport extern FlightId*
FlightIdPluginSupport_create_data(void);

NDDSUSERDllExport extern RTIBool 
FlightIdPluginSupport_copy_data(
    FlightId *out,
    const FlightId *in);

NDDSUSERDllExport extern void 
FlightIdPluginSupport_destroy_data_ex(
    FlightId *sample,RTIBool deallocate_pointers);

NDDSUSERDllExport extern void 
FlightIdPluginSupport_destroy_data(
    FlightId *sample);

NDDSUSERDllExport extern void 
FlightIdPluginSupport_print_data(
    const FlightId *sample,
    const char *desc,
    unsigned int indent);



NDDSUSERDllExport extern RTIBool 
FlightIdPlugin_copy_sample(
    PRESTypePluginEndpointData endpoint_data,
    FlightId *out,
    const FlightId *in);

/* --------------------------------------------------------------------------------------
    (De)Serialize functions:
 * -------------------------------------------------------------------------------------- */

NDDSUSERDllExport extern RTIBool 
FlightIdPlugin_serialize(
    PRESTypePluginEndpointData endpoint_data,
    const FlightId *sample,
    struct RTICdrStream *stream, 
    RTIBool serialize_encapsulation,
    RTIEncapsulationId encapsulation_id,
    RTIBool serialize_sample, 
    void *endpoint_plugin_qos);

NDDSUSERDllExport extern RTIBool 
FlightIdPlugin_deserialize_sample(
    PRESTypePluginEndpointData endpoint_data,
    FlightId *sample, 
    struct RTICdrStream *stream,
    RTIBool deserialize_encapsulation,
    RTIBool deserialize_sample, 
    void *endpoint_plugin_qos);




NDDSUSERDllExport extern RTIBool
FlightIdPlugin_skip(
    PRESTypePluginEndpointData endpoint_data,
    struct RTICdrStream *stream, 
    RTIBool skip_encapsulation,  
    RTIBool skip_sample, 
    void *endpoint_plugin_qos);

NDDSUSERDllExport extern unsigned int 
FlightIdPlugin_get_serialized_sample_max_size(
    PRESTypePluginEndpointData endpoint_data,
    RTIBool include_encapsulation,
    RTIEncapsulationId encapsulation_id,
    unsigned int current_alignment);

NDDSUSERDllExport extern unsigned int 
FlightIdPlugin_get_serialized_sample_min_size(
    PRESTypePluginEndpointData endpoint_data,
    RTIBool include_encapsulation,
    RTIEncapsulationId encapsulation_id,
    unsigned int current_alignment);

NDDSUSERDllExport extern unsigned int
FlightIdPlugin_get_serialized_sample_size(
    PRESTypePluginEndpointData endpoint_data,
    RTIBool include_encapsulation,
    RTIEncapsulationId encapsulation_id,
    unsigned int current_alignment,
    const FlightId * sample);



/* --------------------------------------------------------------------------------------
    Key Management functions:
 * -------------------------------------------------------------------------------------- */

NDDSUSERDllExport extern PRESTypePluginKeyKind 
FlightIdPlugin_get_key_kind(void);

NDDSUSERDllExport extern unsigned int 
FlightIdPlugin_get_serialized_key_max_size(
    PRESTypePluginEndpointData endpoint_data,
    RTIBool include_encapsulation,
    RTIEncapsulationId encapsulation_id,
    unsigned int current_alignment);

NDDSUSERDllExport extern RTIBool 
FlightIdPlugin_serialize_key(
    PRESTypePluginEndpointData endpoint_data,
    const FlightId *sample,
    struct RTICdrStream *stream,
    RTIBool serialize_encapsulation,
    RTIEncapsulationId encapsulation_id,
    RTIBool serialize_key,
    void *endpoint_plugin_qos);

NDDSUSERDllExport extern RTIBool 
FlightIdPlugin_deserialize_key_sample(
    PRESTypePluginEndpointData endpoint_data,
    FlightId * sample,
    struct RTICdrStream *stream,
    RTIBool deserialize_encapsulation,
    RTIBool deserialize_key,
    void *endpoint_plugin_qos);



NDDSUSERDllExport extern RTIBool
FlightIdPlugin_serialized_sample_to_key(
    PRESTypePluginEndpointData endpoint_data,
    FlightId *sample,
    struct RTICdrStream *stream, 
    RTIBool deserialize_encapsulation,  
    RTIBool deserialize_key, 
    void *endpoint_plugin_qos);


#define com_rti_atc_generated_Track_LAST_MEMBER_ID 0
/* The type used to store keys for instances of type struct
 * Track.
 *
 * By default, this type is struct Track
 * itself. However, if for some reason this choice is not practical for your
 * system (e.g. if sizeof(struct Track)
 * is very large), you may redefine this typedef in terms of another type of
 * your choosing. HOWEVER, if you define the KeyHolder type to be something
 * other than struct Track, the
 * following restriction applies: the key of struct
 * Track must consist of a
 * single field of your redefined KeyHolder type and that field must be the
 * first field in struct Track.
*/
typedef  class Track TrackKeyHolder;


#define TrackPlugin_get_sample PRESTypePluginDefaultEndpointData_getSample 
#define TrackPlugin_return_sample PRESTypePluginDefaultEndpointData_returnSample 
#define TrackPlugin_get_buffer PRESTypePluginDefaultEndpointData_getBuffer 
#define TrackPlugin_return_buffer PRESTypePluginDefaultEndpointData_returnBuffer 

#define TrackPlugin_get_key PRESTypePluginDefaultEndpointData_getKey 
#define TrackPlugin_return_key PRESTypePluginDefaultEndpointData_returnKey
 

#define TrackPlugin_create_sample PRESTypePluginDefaultEndpointData_createSample 
#define TrackPlugin_destroy_sample PRESTypePluginDefaultEndpointData_deleteSample 

/* --------------------------------------------------------------------------------------
    Support functions:
 * -------------------------------------------------------------------------------------- */

NDDSUSERDllExport extern Track*
TrackPluginSupport_create_data_ex(RTIBool allocate_pointers);

NDDSUSERDllExport extern Track*
TrackPluginSupport_create_data(void);

NDDSUSERDllExport extern RTIBool 
TrackPluginSupport_copy_data(
    Track *out,
    const Track *in);

NDDSUSERDllExport extern void 
TrackPluginSupport_destroy_data_ex(
    Track *sample,RTIBool deallocate_pointers);

NDDSUSERDllExport extern void 
TrackPluginSupport_destroy_data(
    Track *sample);

NDDSUSERDllExport extern void 
TrackPluginSupport_print_data(
    const Track *sample,
    const char *desc,
    unsigned int indent);


NDDSUSERDllExport extern Track*
TrackPluginSupport_create_key_ex(RTIBool allocate_pointers);

NDDSUSERDllExport extern Track*
TrackPluginSupport_create_key(void);

NDDSUSERDllExport extern void 
TrackPluginSupport_destroy_key_ex(
    TrackKeyHolder *key,RTIBool deallocate_pointers);

NDDSUSERDllExport extern void 
TrackPluginSupport_destroy_key(
    TrackKeyHolder *key);

/* ----------------------------------------------------------------------------
    Callback functions:
 * ---------------------------------------------------------------------------- */

NDDSUSERDllExport extern PRESTypePluginParticipantData 
TrackPlugin_on_participant_attached(
    void *registration_data, 
    const struct PRESTypePluginParticipantInfo *participant_info,
    RTIBool top_level_registration, 
    void *container_plugin_context,
    RTICdrTypeCode *typeCode);

NDDSUSERDllExport extern void 
TrackPlugin_on_participant_detached(
    PRESTypePluginParticipantData participant_data);
    
NDDSUSERDllExport extern PRESTypePluginEndpointData 
TrackPlugin_on_endpoint_attached(
    PRESTypePluginParticipantData participant_data,
    const struct PRESTypePluginEndpointInfo *endpoint_info,
    RTIBool top_level_registration, 
    void *container_plugin_context);

NDDSUSERDllExport extern void 
TrackPlugin_on_endpoint_detached(
    PRESTypePluginEndpointData endpoint_data);


NDDSUSERDllExport extern RTIBool 
TrackPlugin_copy_sample(
    PRESTypePluginEndpointData endpoint_data,
    Track *out,
    const Track *in);

/* --------------------------------------------------------------------------------------
    (De)Serialize functions:
 * -------------------------------------------------------------------------------------- */

NDDSUSERDllExport extern RTIBool 
TrackPlugin_serialize(
    PRESTypePluginEndpointData endpoint_data,
    const Track *sample,
    struct RTICdrStream *stream, 
    RTIBool serialize_encapsulation,
    RTIEncapsulationId encapsulation_id,
    RTIBool serialize_sample, 
    void *endpoint_plugin_qos);

NDDSUSERDllExport extern RTIBool 
TrackPlugin_deserialize_sample(
    PRESTypePluginEndpointData endpoint_data,
    Track *sample, 
    struct RTICdrStream *stream,
    RTIBool deserialize_encapsulation,
    RTIBool deserialize_sample, 
    void *endpoint_plugin_qos);

 
NDDSUSERDllExport extern RTIBool 
TrackPlugin_deserialize(
    PRESTypePluginEndpointData endpoint_data,
    Track **sample, 
    RTIBool * drop_sample,
    struct RTICdrStream *stream,
    RTIBool deserialize_encapsulation,
    RTIBool deserialize_sample, 
    void *endpoint_plugin_qos);




NDDSUSERDllExport extern RTIBool
TrackPlugin_skip(
    PRESTypePluginEndpointData endpoint_data,
    struct RTICdrStream *stream, 
    RTIBool skip_encapsulation,  
    RTIBool skip_sample, 
    void *endpoint_plugin_qos);

NDDSUSERDllExport extern unsigned int 
TrackPlugin_get_serialized_sample_max_size(
    PRESTypePluginEndpointData endpoint_data,
    RTIBool include_encapsulation,
    RTIEncapsulationId encapsulation_id,
    unsigned int current_alignment);

NDDSUSERDllExport extern unsigned int 
TrackPlugin_get_serialized_sample_min_size(
    PRESTypePluginEndpointData endpoint_data,
    RTIBool include_encapsulation,
    RTIEncapsulationId encapsulation_id,
    unsigned int current_alignment);

NDDSUSERDllExport extern unsigned int
TrackPlugin_get_serialized_sample_size(
    PRESTypePluginEndpointData endpoint_data,
    RTIBool include_encapsulation,
    RTIEncapsulationId encapsulation_id,
    unsigned int current_alignment,
    const Track * sample);



/* --------------------------------------------------------------------------------------
    Key Management functions:
 * -------------------------------------------------------------------------------------- */

NDDSUSERDllExport extern PRESTypePluginKeyKind 
TrackPlugin_get_key_kind(void);

NDDSUSERDllExport extern unsigned int 
TrackPlugin_get_serialized_key_max_size(
    PRESTypePluginEndpointData endpoint_data,
    RTIBool include_encapsulation,
    RTIEncapsulationId encapsulation_id,
    unsigned int current_alignment);

NDDSUSERDllExport extern RTIBool 
TrackPlugin_serialize_key(
    PRESTypePluginEndpointData endpoint_data,
    const Track *sample,
    struct RTICdrStream *stream,
    RTIBool serialize_encapsulation,
    RTIEncapsulationId encapsulation_id,
    RTIBool serialize_key,
    void *endpoint_plugin_qos);

NDDSUSERDllExport extern RTIBool 
TrackPlugin_deserialize_key_sample(
    PRESTypePluginEndpointData endpoint_data,
    Track * sample,
    struct RTICdrStream *stream,
    RTIBool deserialize_encapsulation,
    RTIBool deserialize_key,
    void *endpoint_plugin_qos);

 
NDDSUSERDllExport extern RTIBool 
TrackPlugin_deserialize_key(
    PRESTypePluginEndpointData endpoint_data,
    Track ** sample,
    RTIBool * drop_sample,
    struct RTICdrStream *stream,
    RTIBool deserialize_encapsulation,
    RTIBool deserialize_key,
    void *endpoint_plugin_qos);


NDDSUSERDllExport extern RTIBool
TrackPlugin_serialized_sample_to_key(
    PRESTypePluginEndpointData endpoint_data,
    Track *sample,
    struct RTICdrStream *stream, 
    RTIBool deserialize_encapsulation,  
    RTIBool deserialize_key, 
    void *endpoint_plugin_qos);

 
NDDSUSERDllExport extern RTIBool 
TrackPlugin_instance_to_key(
    PRESTypePluginEndpointData endpoint_data,
    TrackKeyHolder *key, 
    const Track *instance);

NDDSUSERDllExport extern RTIBool 
TrackPlugin_key_to_instance(
    PRESTypePluginEndpointData endpoint_data,
    Track *instance, 
    const TrackKeyHolder *key);

NDDSUSERDllExport extern RTIBool 
TrackPlugin_instance_to_keyhash(
    PRESTypePluginEndpointData endpoint_data,
    DDS_KeyHash_t *keyhash,
    const Track *instance);

NDDSUSERDllExport extern RTIBool 
TrackPlugin_serialized_sample_to_keyhash(
    PRESTypePluginEndpointData endpoint_data,
    struct RTICdrStream *stream, 
    DDS_KeyHash_t *keyhash,
    RTIBool deserialize_encapsulation,
    void *endpoint_plugin_qos); 
     
/* Plugin Functions */
NDDSUSERDllExport extern struct PRESTypePlugin*
TrackPlugin_new(void);

NDDSUSERDllExport extern void
TrackPlugin_delete(struct PRESTypePlugin *);


/* ------------------------------------------------------------------------
 * (De)Serialization Methods
 * ------------------------------------------------------------------------ */

NDDSUSERDllExport extern RTIBool
FlightRulesKindPlugin_serialize(
    PRESTypePluginEndpointData endpoint_data,
    const FlightRulesKind *sample, struct RTICdrStream *stream,
    RTIBool serialize_encapsulation,
    RTIEncapsulationId encapsulation_id,
    RTIBool serialize_sample, 
    void *endpoint_plugin_qos);

NDDSUSERDllExport extern RTIBool
FlightRulesKindPlugin_deserialize_sample(
    PRESTypePluginEndpointData endpoint_data,
    FlightRulesKind *sample, 
    struct RTICdrStream *stream, 
    RTIBool deserialize_encapsulation,
    RTIBool deserialize_sample, 
    void *endpoint_plugin_qos);

NDDSUSERDllExport extern RTIBool
FlightRulesKindPlugin_skip(
    PRESTypePluginEndpointData endpoint_data,
    struct RTICdrStream *stream, 
    RTIBool skip_encapsulation,  
    RTIBool skip_sample, 
    void *endpoint_plugin_qos);

NDDSUSERDllExport extern unsigned int
FlightRulesKindPlugin_get_serialized_sample_max_size(
    PRESTypePluginEndpointData endpoint_data,
    RTIBool include_encapsulation,
    RTIEncapsulationId encapsulation_id,
    unsigned int current_alignment);

NDDSUSERDllExport extern unsigned int
FlightRulesKindPlugin_get_serialized_sample_min_size(
    PRESTypePluginEndpointData endpoint_data,
    RTIBool include_encapsulation,
    RTIEncapsulationId encapsulation_id,
    unsigned int current_alignment);

NDDSUSERDllExport extern unsigned int
FlightRulesKindPlugin_get_serialized_sample_size(
    PRESTypePluginEndpointData endpoint_data,
    RTIBool include_encapsulation,
    RTIEncapsulationId encapsulation_id,
    unsigned int current_alignment,
    const FlightRulesKind * sample);


/* ------------------------------------------------------------------------
    Key Management functions:
 * ------------------------------------------------------------------------ */

NDDSUSERDllExport extern RTIBool 
FlightRulesKindPlugin_serialize_key(
    PRESTypePluginEndpointData endpoint_data,
    const FlightRulesKind *sample,
    struct RTICdrStream *stream,
    RTIBool serialize_encapsulation,
    RTIEncapsulationId encapsulation_id,
    RTIBool serialize_key,
    void *endpoint_plugin_qos);

NDDSUSERDllExport extern RTIBool 
FlightRulesKindPlugin_deserialize_key_sample(
    PRESTypePluginEndpointData endpoint_data,
    FlightRulesKind *sample,
    struct RTICdrStream *stream,
    RTIBool deserialize_encapsulation,
    RTIBool deserialize_key,
    void *endpoint_plugin_qos);

NDDSUSERDllExport extern unsigned int 
FlightRulesKindPlugin_get_serialized_key_max_size(
    PRESTypePluginEndpointData endpoint_data,
    RTIBool include_encapsulation,
    RTIEncapsulationId encapsulation_id,
    unsigned int current_alignment);

NDDSUSERDllExport extern RTIBool
FlightRulesKindPlugin_serialized_sample_to_key(
    PRESTypePluginEndpointData endpoint_data,
    FlightRulesKind *sample,
    struct RTICdrStream *stream, 
    RTIBool deserialize_encapsulation,  
    RTIBool deserialize_key, 
    void *endpoint_plugin_qos);

 


/* ----------------------------------------------------------------------------
    Support functions:
 * ---------------------------------------------------------------------------- */

NDDSUSERDllExport extern void
FlightRulesKindPluginSupport_print_data(
    const FlightRulesKind *sample, const char *desc, int indent_level);



/* ------------------------------------------------------------------------
 * (De)Serialization Methods
 * ------------------------------------------------------------------------ */

NDDSUSERDllExport extern RTIBool
FlightTypeKindPlugin_serialize(
    PRESTypePluginEndpointData endpoint_data,
    const FlightTypeKind *sample, struct RTICdrStream *stream,
    RTIBool serialize_encapsulation,
    RTIEncapsulationId encapsulation_id,
    RTIBool serialize_sample, 
    void *endpoint_plugin_qos);

NDDSUSERDllExport extern RTIBool
FlightTypeKindPlugin_deserialize_sample(
    PRESTypePluginEndpointData endpoint_data,
    FlightTypeKind *sample, 
    struct RTICdrStream *stream, 
    RTIBool deserialize_encapsulation,
    RTIBool deserialize_sample, 
    void *endpoint_plugin_qos);

NDDSUSERDllExport extern RTIBool
FlightTypeKindPlugin_skip(
    PRESTypePluginEndpointData endpoint_data,
    struct RTICdrStream *stream, 
    RTIBool skip_encapsulation,  
    RTIBool skip_sample, 
    void *endpoint_plugin_qos);

NDDSUSERDllExport extern unsigned int
FlightTypeKindPlugin_get_serialized_sample_max_size(
    PRESTypePluginEndpointData endpoint_data,
    RTIBool include_encapsulation,
    RTIEncapsulationId encapsulation_id,
    unsigned int current_alignment);

NDDSUSERDllExport extern unsigned int
FlightTypeKindPlugin_get_serialized_sample_min_size(
    PRESTypePluginEndpointData endpoint_data,
    RTIBool include_encapsulation,
    RTIEncapsulationId encapsulation_id,
    unsigned int current_alignment);

NDDSUSERDllExport extern unsigned int
FlightTypeKindPlugin_get_serialized_sample_size(
    PRESTypePluginEndpointData endpoint_data,
    RTIBool include_encapsulation,
    RTIEncapsulationId encapsulation_id,
    unsigned int current_alignment,
    const FlightTypeKind * sample);


/* ------------------------------------------------------------------------
    Key Management functions:
 * ------------------------------------------------------------------------ */

NDDSUSERDllExport extern RTIBool 
FlightTypeKindPlugin_serialize_key(
    PRESTypePluginEndpointData endpoint_data,
    const FlightTypeKind *sample,
    struct RTICdrStream *stream,
    RTIBool serialize_encapsulation,
    RTIEncapsulationId encapsulation_id,
    RTIBool serialize_key,
    void *endpoint_plugin_qos);

NDDSUSERDllExport extern RTIBool 
FlightTypeKindPlugin_deserialize_key_sample(
    PRESTypePluginEndpointData endpoint_data,
    FlightTypeKind *sample,
    struct RTICdrStream *stream,
    RTIBool deserialize_encapsulation,
    RTIBool deserialize_key,
    void *endpoint_plugin_qos);

NDDSUSERDllExport extern unsigned int 
FlightTypeKindPlugin_get_serialized_key_max_size(
    PRESTypePluginEndpointData endpoint_data,
    RTIBool include_encapsulation,
    RTIEncapsulationId encapsulation_id,
    unsigned int current_alignment);

NDDSUSERDllExport extern RTIBool
FlightTypeKindPlugin_serialized_sample_to_key(
    PRESTypePluginEndpointData endpoint_data,
    FlightTypeKind *sample,
    struct RTICdrStream *stream, 
    RTIBool deserialize_encapsulation,  
    RTIBool deserialize_key, 
    void *endpoint_plugin_qos);

 


/* ----------------------------------------------------------------------------
    Support functions:
 * ---------------------------------------------------------------------------- */

NDDSUSERDllExport extern void
FlightTypeKindPluginSupport_print_data(
    const FlightTypeKind *sample, const char *desc, int indent_level);



/* ------------------------------------------------------------------------
 * (De)Serialization Methods
 * ------------------------------------------------------------------------ */

NDDSUSERDllExport extern RTIBool
EquipmentKindPlugin_serialize(
    PRESTypePluginEndpointData endpoint_data,
    const EquipmentKind *sample, struct RTICdrStream *stream,
    RTIBool serialize_encapsulation,
    RTIEncapsulationId encapsulation_id,
    RTIBool serialize_sample, 
    void *endpoint_plugin_qos);

NDDSUSERDllExport extern RTIBool
EquipmentKindPlugin_deserialize_sample(
    PRESTypePluginEndpointData endpoint_data,
    EquipmentKind *sample, 
    struct RTICdrStream *stream, 
    RTIBool deserialize_encapsulation,
    RTIBool deserialize_sample, 
    void *endpoint_plugin_qos);

NDDSUSERDllExport extern RTIBool
EquipmentKindPlugin_skip(
    PRESTypePluginEndpointData endpoint_data,
    struct RTICdrStream *stream, 
    RTIBool skip_encapsulation,  
    RTIBool skip_sample, 
    void *endpoint_plugin_qos);

NDDSUSERDllExport extern unsigned int
EquipmentKindPlugin_get_serialized_sample_max_size(
    PRESTypePluginEndpointData endpoint_data,
    RTIBool include_encapsulation,
    RTIEncapsulationId encapsulation_id,
    unsigned int current_alignment);

NDDSUSERDllExport extern unsigned int
EquipmentKindPlugin_get_serialized_sample_min_size(
    PRESTypePluginEndpointData endpoint_data,
    RTIBool include_encapsulation,
    RTIEncapsulationId encapsulation_id,
    unsigned int current_alignment);

NDDSUSERDllExport extern unsigned int
EquipmentKindPlugin_get_serialized_sample_size(
    PRESTypePluginEndpointData endpoint_data,
    RTIBool include_encapsulation,
    RTIEncapsulationId encapsulation_id,
    unsigned int current_alignment,
    const EquipmentKind * sample);


/* ------------------------------------------------------------------------
    Key Management functions:
 * ------------------------------------------------------------------------ */

NDDSUSERDllExport extern RTIBool 
EquipmentKindPlugin_serialize_key(
    PRESTypePluginEndpointData endpoint_data,
    const EquipmentKind *sample,
    struct RTICdrStream *stream,
    RTIBool serialize_encapsulation,
    RTIEncapsulationId encapsulation_id,
    RTIBool serialize_key,
    void *endpoint_plugin_qos);

NDDSUSERDllExport extern RTIBool 
EquipmentKindPlugin_deserialize_key_sample(
    PRESTypePluginEndpointData endpoint_data,
    EquipmentKind *sample,
    struct RTICdrStream *stream,
    RTIBool deserialize_encapsulation,
    RTIBool deserialize_key,
    void *endpoint_plugin_qos);

NDDSUSERDllExport extern unsigned int 
EquipmentKindPlugin_get_serialized_key_max_size(
    PRESTypePluginEndpointData endpoint_data,
    RTIBool include_encapsulation,
    RTIEncapsulationId encapsulation_id,
    unsigned int current_alignment);

NDDSUSERDllExport extern RTIBool
EquipmentKindPlugin_serialized_sample_to_key(
    PRESTypePluginEndpointData endpoint_data,
    EquipmentKind *sample,
    struct RTICdrStream *stream, 
    RTIBool deserialize_encapsulation,  
    RTIBool deserialize_key, 
    void *endpoint_plugin_qos);

 


/* ----------------------------------------------------------------------------
    Support functions:
 * ---------------------------------------------------------------------------- */

NDDSUSERDllExport extern void
EquipmentKindPluginSupport_print_data(
    const EquipmentKind *sample, const char *desc, int indent_level);


#define com_rti_atc_generated_FlightPlan_LAST_MEMBER_ID 0
/* The type used to store keys for instances of type struct
 * FlightPlan.
 *
 * By default, this type is struct FlightPlan
 * itself. However, if for some reason this choice is not practical for your
 * system (e.g. if sizeof(struct FlightPlan)
 * is very large), you may redefine this typedef in terms of another type of
 * your choosing. HOWEVER, if you define the KeyHolder type to be something
 * other than struct FlightPlan, the
 * following restriction applies: the key of struct
 * FlightPlan must consist of a
 * single field of your redefined KeyHolder type and that field must be the
 * first field in struct FlightPlan.
*/
typedef  class FlightPlan FlightPlanKeyHolder;


#define FlightPlanPlugin_get_sample PRESTypePluginDefaultEndpointData_getSample 
#define FlightPlanPlugin_return_sample PRESTypePluginDefaultEndpointData_returnSample 
#define FlightPlanPlugin_get_buffer PRESTypePluginDefaultEndpointData_getBuffer 
#define FlightPlanPlugin_return_buffer PRESTypePluginDefaultEndpointData_returnBuffer 

#define FlightPlanPlugin_get_key PRESTypePluginDefaultEndpointData_getKey 
#define FlightPlanPlugin_return_key PRESTypePluginDefaultEndpointData_returnKey
 

#define FlightPlanPlugin_create_sample PRESTypePluginDefaultEndpointData_createSample 
#define FlightPlanPlugin_destroy_sample PRESTypePluginDefaultEndpointData_deleteSample 

/* --------------------------------------------------------------------------------------
    Support functions:
 * -------------------------------------------------------------------------------------- */

NDDSUSERDllExport extern FlightPlan*
FlightPlanPluginSupport_create_data_ex(RTIBool allocate_pointers);

NDDSUSERDllExport extern FlightPlan*
FlightPlanPluginSupport_create_data(void);

NDDSUSERDllExport extern RTIBool 
FlightPlanPluginSupport_copy_data(
    FlightPlan *out,
    const FlightPlan *in);

NDDSUSERDllExport extern void 
FlightPlanPluginSupport_destroy_data_ex(
    FlightPlan *sample,RTIBool deallocate_pointers);

NDDSUSERDllExport extern void 
FlightPlanPluginSupport_destroy_data(
    FlightPlan *sample);

NDDSUSERDllExport extern void 
FlightPlanPluginSupport_print_data(
    const FlightPlan *sample,
    const char *desc,
    unsigned int indent);


NDDSUSERDllExport extern FlightPlan*
FlightPlanPluginSupport_create_key_ex(RTIBool allocate_pointers);

NDDSUSERDllExport extern FlightPlan*
FlightPlanPluginSupport_create_key(void);

NDDSUSERDllExport extern void 
FlightPlanPluginSupport_destroy_key_ex(
    FlightPlanKeyHolder *key,RTIBool deallocate_pointers);

NDDSUSERDllExport extern void 
FlightPlanPluginSupport_destroy_key(
    FlightPlanKeyHolder *key);

/* ----------------------------------------------------------------------------
    Callback functions:
 * ---------------------------------------------------------------------------- */

NDDSUSERDllExport extern PRESTypePluginParticipantData 
FlightPlanPlugin_on_participant_attached(
    void *registration_data, 
    const struct PRESTypePluginParticipantInfo *participant_info,
    RTIBool top_level_registration, 
    void *container_plugin_context,
    RTICdrTypeCode *typeCode);

NDDSUSERDllExport extern void 
FlightPlanPlugin_on_participant_detached(
    PRESTypePluginParticipantData participant_data);
    
NDDSUSERDllExport extern PRESTypePluginEndpointData 
FlightPlanPlugin_on_endpoint_attached(
    PRESTypePluginParticipantData participant_data,
    const struct PRESTypePluginEndpointInfo *endpoint_info,
    RTIBool top_level_registration, 
    void *container_plugin_context);

NDDSUSERDllExport extern void 
FlightPlanPlugin_on_endpoint_detached(
    PRESTypePluginEndpointData endpoint_data);


NDDSUSERDllExport extern RTIBool 
FlightPlanPlugin_copy_sample(
    PRESTypePluginEndpointData endpoint_data,
    FlightPlan *out,
    const FlightPlan *in);

/* --------------------------------------------------------------------------------------
    (De)Serialize functions:
 * -------------------------------------------------------------------------------------- */

NDDSUSERDllExport extern RTIBool 
FlightPlanPlugin_serialize(
    PRESTypePluginEndpointData endpoint_data,
    const FlightPlan *sample,
    struct RTICdrStream *stream, 
    RTIBool serialize_encapsulation,
    RTIEncapsulationId encapsulation_id,
    RTIBool serialize_sample, 
    void *endpoint_plugin_qos);

NDDSUSERDllExport extern RTIBool 
FlightPlanPlugin_deserialize_sample(
    PRESTypePluginEndpointData endpoint_data,
    FlightPlan *sample, 
    struct RTICdrStream *stream,
    RTIBool deserialize_encapsulation,
    RTIBool deserialize_sample, 
    void *endpoint_plugin_qos);

 
NDDSUSERDllExport extern RTIBool 
FlightPlanPlugin_deserialize(
    PRESTypePluginEndpointData endpoint_data,
    FlightPlan **sample, 
    RTIBool * drop_sample,
    struct RTICdrStream *stream,
    RTIBool deserialize_encapsulation,
    RTIBool deserialize_sample, 
    void *endpoint_plugin_qos);




NDDSUSERDllExport extern RTIBool
FlightPlanPlugin_skip(
    PRESTypePluginEndpointData endpoint_data,
    struct RTICdrStream *stream, 
    RTIBool skip_encapsulation,  
    RTIBool skip_sample, 
    void *endpoint_plugin_qos);

NDDSUSERDllExport extern unsigned int 
FlightPlanPlugin_get_serialized_sample_max_size(
    PRESTypePluginEndpointData endpoint_data,
    RTIBool include_encapsulation,
    RTIEncapsulationId encapsulation_id,
    unsigned int current_alignment);

NDDSUSERDllExport extern unsigned int 
FlightPlanPlugin_get_serialized_sample_min_size(
    PRESTypePluginEndpointData endpoint_data,
    RTIBool include_encapsulation,
    RTIEncapsulationId encapsulation_id,
    unsigned int current_alignment);

NDDSUSERDllExport extern unsigned int
FlightPlanPlugin_get_serialized_sample_size(
    PRESTypePluginEndpointData endpoint_data,
    RTIBool include_encapsulation,
    RTIEncapsulationId encapsulation_id,
    unsigned int current_alignment,
    const FlightPlan * sample);



/* --------------------------------------------------------------------------------------
    Key Management functions:
 * -------------------------------------------------------------------------------------- */

NDDSUSERDllExport extern PRESTypePluginKeyKind 
FlightPlanPlugin_get_key_kind(void);

NDDSUSERDllExport extern unsigned int 
FlightPlanPlugin_get_serialized_key_max_size(
    PRESTypePluginEndpointData endpoint_data,
    RTIBool include_encapsulation,
    RTIEncapsulationId encapsulation_id,
    unsigned int current_alignment);

NDDSUSERDllExport extern RTIBool 
FlightPlanPlugin_serialize_key(
    PRESTypePluginEndpointData endpoint_data,
    const FlightPlan *sample,
    struct RTICdrStream *stream,
    RTIBool serialize_encapsulation,
    RTIEncapsulationId encapsulation_id,
    RTIBool serialize_key,
    void *endpoint_plugin_qos);

NDDSUSERDllExport extern RTIBool 
FlightPlanPlugin_deserialize_key_sample(
    PRESTypePluginEndpointData endpoint_data,
    FlightPlan * sample,
    struct RTICdrStream *stream,
    RTIBool deserialize_encapsulation,
    RTIBool deserialize_key,
    void *endpoint_plugin_qos);

 
NDDSUSERDllExport extern RTIBool 
FlightPlanPlugin_deserialize_key(
    PRESTypePluginEndpointData endpoint_data,
    FlightPlan ** sample,
    RTIBool * drop_sample,
    struct RTICdrStream *stream,
    RTIBool deserialize_encapsulation,
    RTIBool deserialize_key,
    void *endpoint_plugin_qos);


NDDSUSERDllExport extern RTIBool
FlightPlanPlugin_serialized_sample_to_key(
    PRESTypePluginEndpointData endpoint_data,
    FlightPlan *sample,
    struct RTICdrStream *stream, 
    RTIBool deserialize_encapsulation,  
    RTIBool deserialize_key, 
    void *endpoint_plugin_qos);

 
NDDSUSERDllExport extern RTIBool 
FlightPlanPlugin_instance_to_key(
    PRESTypePluginEndpointData endpoint_data,
    FlightPlanKeyHolder *key, 
    const FlightPlan *instance);

NDDSUSERDllExport extern RTIBool 
FlightPlanPlugin_key_to_instance(
    PRESTypePluginEndpointData endpoint_data,
    FlightPlan *instance, 
    const FlightPlanKeyHolder *key);

NDDSUSERDllExport extern RTIBool 
FlightPlanPlugin_instance_to_keyhash(
    PRESTypePluginEndpointData endpoint_data,
    DDS_KeyHash_t *keyhash,
    const FlightPlan *instance);

NDDSUSERDllExport extern RTIBool 
FlightPlanPlugin_serialized_sample_to_keyhash(
    PRESTypePluginEndpointData endpoint_data,
    struct RTICdrStream *stream, 
    DDS_KeyHash_t *keyhash,
    RTIBool deserialize_encapsulation,
    void *endpoint_plugin_qos); 
     
/* Plugin Functions */
NDDSUSERDllExport extern struct PRESTypePlugin*
FlightPlanPlugin_new(void);

NDDSUSERDllExport extern void
FlightPlanPlugin_delete(struct PRESTypePlugin *);

} /* namespace generated */

} /* namespace atc */

} /* namespace rti */

} /* namespace com */

        
#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif        

#endif /* AirTrafficControlPlugin_1144379923_h */
