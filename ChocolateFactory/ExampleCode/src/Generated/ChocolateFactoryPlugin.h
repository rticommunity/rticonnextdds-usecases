
/*
  WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

  This file was generated from ChocolateFactory.idl using "rtiddsgen".
  The rtiddsgen tool is part of the RTI Connext distribution.
  For more information, type 'rtiddsgen -help' at a command shell
  or consult the RTI Connext manual.
*/

#ifndef ChocolateFactoryPlugin_1774920665_h
#define ChocolateFactoryPlugin_1774920665_h

#include "ChocolateFactory.h"



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

namespace chocolatefactory{

namespace generated{


/* ------------------------------------------------------------------------
 * (De)Serialization Methods
 * ------------------------------------------------------------------------ */

NDDSUSERDllExport extern RTIBool
StationControllerKindPlugin_serialize(
    PRESTypePluginEndpointData endpoint_data,
    const StationControllerKind *sample, struct RTICdrStream *stream,
    RTIBool serialize_encapsulation,
    RTIEncapsulationId encapsulation_id,
    RTIBool serialize_sample, 
    void *endpoint_plugin_qos);

NDDSUSERDllExport extern RTIBool
StationControllerKindPlugin_deserialize_sample(
    PRESTypePluginEndpointData endpoint_data,
    StationControllerKind *sample, 
    struct RTICdrStream *stream, 
    RTIBool deserialize_encapsulation,
    RTIBool deserialize_sample, 
    void *endpoint_plugin_qos);

NDDSUSERDllExport extern RTIBool
StationControllerKindPlugin_skip(
    PRESTypePluginEndpointData endpoint_data,
    struct RTICdrStream *stream, 
    RTIBool skip_encapsulation,  
    RTIBool skip_sample, 
    void *endpoint_plugin_qos);

NDDSUSERDllExport extern unsigned int
StationControllerKindPlugin_get_serialized_sample_max_size(
    PRESTypePluginEndpointData endpoint_data,
    RTIBool include_encapsulation,
    RTIEncapsulationId encapsulation_id,
    unsigned int current_alignment);

NDDSUSERDllExport extern unsigned int
StationControllerKindPlugin_get_serialized_sample_min_size(
    PRESTypePluginEndpointData endpoint_data,
    RTIBool include_encapsulation,
    RTIEncapsulationId encapsulation_id,
    unsigned int current_alignment);

NDDSUSERDllExport extern unsigned int
StationControllerKindPlugin_get_serialized_sample_size(
    PRESTypePluginEndpointData endpoint_data,
    RTIBool include_encapsulation,
    RTIEncapsulationId encapsulation_id,
    unsigned int current_alignment,
    const StationControllerKind * sample);


/* ------------------------------------------------------------------------
    Key Management functions:
 * ------------------------------------------------------------------------ */

NDDSUSERDllExport extern RTIBool 
StationControllerKindPlugin_serialize_key(
    PRESTypePluginEndpointData endpoint_data,
    const StationControllerKind *sample,
    struct RTICdrStream *stream,
    RTIBool serialize_encapsulation,
    RTIEncapsulationId encapsulation_id,
    RTIBool serialize_key,
    void *endpoint_plugin_qos);

NDDSUSERDllExport extern RTIBool 
StationControllerKindPlugin_deserialize_key_sample(
    PRESTypePluginEndpointData endpoint_data,
    StationControllerKind *sample,
    struct RTICdrStream *stream,
    RTIBool deserialize_encapsulation,
    RTIBool deserialize_key,
    void *endpoint_plugin_qos);

NDDSUSERDllExport extern unsigned int 
StationControllerKindPlugin_get_serialized_key_max_size(
    PRESTypePluginEndpointData endpoint_data,
    RTIBool include_encapsulation,
    RTIEncapsulationId encapsulation_id,
    unsigned int current_alignment);

NDDSUSERDllExport extern RTIBool
StationControllerKindPlugin_serialized_sample_to_key(
    PRESTypePluginEndpointData endpoint_data,
    StationControllerKind *sample,
    struct RTICdrStream *stream, 
    RTIBool deserialize_encapsulation,  
    RTIBool deserialize_key, 
    void *endpoint_plugin_qos);

 


/* ----------------------------------------------------------------------------
    Support functions:
 * ---------------------------------------------------------------------------- */

NDDSUSERDllExport extern void
StationControllerKindPluginSupport_print_data(
    const StationControllerKind *sample, const char *desc, int indent_level);



/* ------------------------------------------------------------------------
 * (De)Serialization Methods
 * ------------------------------------------------------------------------ */

NDDSUSERDllExport extern RTIBool
LotStatusKindPlugin_serialize(
    PRESTypePluginEndpointData endpoint_data,
    const LotStatusKind *sample, struct RTICdrStream *stream,
    RTIBool serialize_encapsulation,
    RTIEncapsulationId encapsulation_id,
    RTIBool serialize_sample, 
    void *endpoint_plugin_qos);

NDDSUSERDllExport extern RTIBool
LotStatusKindPlugin_deserialize_sample(
    PRESTypePluginEndpointData endpoint_data,
    LotStatusKind *sample, 
    struct RTICdrStream *stream, 
    RTIBool deserialize_encapsulation,
    RTIBool deserialize_sample, 
    void *endpoint_plugin_qos);

NDDSUSERDllExport extern RTIBool
LotStatusKindPlugin_skip(
    PRESTypePluginEndpointData endpoint_data,
    struct RTICdrStream *stream, 
    RTIBool skip_encapsulation,  
    RTIBool skip_sample, 
    void *endpoint_plugin_qos);

NDDSUSERDllExport extern unsigned int
LotStatusKindPlugin_get_serialized_sample_max_size(
    PRESTypePluginEndpointData endpoint_data,
    RTIBool include_encapsulation,
    RTIEncapsulationId encapsulation_id,
    unsigned int current_alignment);

NDDSUSERDllExport extern unsigned int
LotStatusKindPlugin_get_serialized_sample_min_size(
    PRESTypePluginEndpointData endpoint_data,
    RTIBool include_encapsulation,
    RTIEncapsulationId encapsulation_id,
    unsigned int current_alignment);

NDDSUSERDllExport extern unsigned int
LotStatusKindPlugin_get_serialized_sample_size(
    PRESTypePluginEndpointData endpoint_data,
    RTIBool include_encapsulation,
    RTIEncapsulationId encapsulation_id,
    unsigned int current_alignment,
    const LotStatusKind * sample);


/* ------------------------------------------------------------------------
    Key Management functions:
 * ------------------------------------------------------------------------ */

NDDSUSERDllExport extern RTIBool 
LotStatusKindPlugin_serialize_key(
    PRESTypePluginEndpointData endpoint_data,
    const LotStatusKind *sample,
    struct RTICdrStream *stream,
    RTIBool serialize_encapsulation,
    RTIEncapsulationId encapsulation_id,
    RTIBool serialize_key,
    void *endpoint_plugin_qos);

NDDSUSERDllExport extern RTIBool 
LotStatusKindPlugin_deserialize_key_sample(
    PRESTypePluginEndpointData endpoint_data,
    LotStatusKind *sample,
    struct RTICdrStream *stream,
    RTIBool deserialize_encapsulation,
    RTIBool deserialize_key,
    void *endpoint_plugin_qos);

NDDSUSERDllExport extern unsigned int 
LotStatusKindPlugin_get_serialized_key_max_size(
    PRESTypePluginEndpointData endpoint_data,
    RTIBool include_encapsulation,
    RTIEncapsulationId encapsulation_id,
    unsigned int current_alignment);

NDDSUSERDllExport extern RTIBool
LotStatusKindPlugin_serialized_sample_to_key(
    PRESTypePluginEndpointData endpoint_data,
    LotStatusKind *sample,
    struct RTICdrStream *stream, 
    RTIBool deserialize_encapsulation,  
    RTIBool deserialize_key, 
    void *endpoint_plugin_qos);

 


/* ----------------------------------------------------------------------------
    Support functions:
 * ---------------------------------------------------------------------------- */

NDDSUSERDllExport extern void
LotStatusKindPluginSupport_print_data(
    const LotStatusKind *sample, const char *desc, int indent_level);



#define RecipeStepPlugin_get_sample PRESTypePluginDefaultEndpointData_getSample  
#define RecipeStepPlugin_get_buffer PRESTypePluginDefaultEndpointData_getBuffer 
#define RecipeStepPlugin_return_buffer PRESTypePluginDefaultEndpointData_returnBuffer 
 

#define RecipeStepPlugin_create_sample PRESTypePluginDefaultEndpointData_createSample 
#define RecipeStepPlugin_destroy_sample PRESTypePluginDefaultEndpointData_deleteSample 

/* --------------------------------------------------------------------------------------
    Support functions:
 * -------------------------------------------------------------------------------------- */

NDDSUSERDllExport extern RecipeStep*
RecipeStepPluginSupport_create_data_w_params(
    const struct DDS_TypeAllocationParams_t * alloc_params);

NDDSUSERDllExport extern RecipeStep*
RecipeStepPluginSupport_create_data_ex(RTIBool allocate_pointers);

NDDSUSERDllExport extern RecipeStep*
RecipeStepPluginSupport_create_data(void);

NDDSUSERDllExport extern RTIBool 
RecipeStepPluginSupport_copy_data(
    RecipeStep *out,
    const RecipeStep *in);

NDDSUSERDllExport extern void 
RecipeStepPluginSupport_destroy_data_w_params(
    RecipeStep *sample,
    const struct DDS_TypeDeallocationParams_t * dealloc_params);

NDDSUSERDllExport extern void 
RecipeStepPluginSupport_destroy_data_ex(
    RecipeStep *sample,RTIBool deallocate_pointers);

NDDSUSERDllExport extern void 
RecipeStepPluginSupport_destroy_data(
    RecipeStep *sample);

NDDSUSERDllExport extern void 
RecipeStepPluginSupport_print_data(
    const RecipeStep *sample,
    const char *desc,
    unsigned int indent);

 

NDDSUSERDllExport extern RTIBool 
RecipeStepPlugin_copy_sample(
    PRESTypePluginEndpointData endpoint_data,
    RecipeStep *out,
    const RecipeStep *in);

/* --------------------------------------------------------------------------------------
    (De)Serialize functions:
 * -------------------------------------------------------------------------------------- */

NDDSUSERDllExport extern RTIBool 
RecipeStepPlugin_serialize(
    PRESTypePluginEndpointData endpoint_data,
    const RecipeStep *sample,
    struct RTICdrStream *stream, 
    RTIBool serialize_encapsulation,
    RTIEncapsulationId encapsulation_id,
    RTIBool serialize_sample, 
    void *endpoint_plugin_qos);

NDDSUSERDllExport extern RTIBool 
RecipeStepPlugin_deserialize_sample(
    PRESTypePluginEndpointData endpoint_data,
    RecipeStep *sample, 
    struct RTICdrStream *stream,
    RTIBool deserialize_encapsulation,
    RTIBool deserialize_sample, 
    void *endpoint_plugin_qos);

 
NDDSUSERDllExport extern RTIBool 
RecipeStepPlugin_deserialize(
    PRESTypePluginEndpointData endpoint_data,
    RecipeStep **sample, 
    RTIBool * drop_sample,
    struct RTICdrStream *stream,
    RTIBool deserialize_encapsulation,
    RTIBool deserialize_sample, 
    void *endpoint_plugin_qos);




NDDSUSERDllExport extern RTIBool
RecipeStepPlugin_skip(
    PRESTypePluginEndpointData endpoint_data,
    struct RTICdrStream *stream, 
    RTIBool skip_encapsulation,  
    RTIBool skip_sample, 
    void *endpoint_plugin_qos);

NDDSUSERDllExport extern unsigned int 
RecipeStepPlugin_get_serialized_sample_max_size(
    PRESTypePluginEndpointData endpoint_data,
    RTIBool include_encapsulation,
    RTIEncapsulationId encapsulation_id,
    unsigned int current_alignment);

NDDSUSERDllExport extern unsigned int 
RecipeStepPlugin_get_serialized_sample_min_size(
    PRESTypePluginEndpointData endpoint_data,
    RTIBool include_encapsulation,
    RTIEncapsulationId encapsulation_id,
    unsigned int current_alignment);

NDDSUSERDllExport extern unsigned int
RecipeStepPlugin_get_serialized_sample_size(
    PRESTypePluginEndpointData endpoint_data,
    RTIBool include_encapsulation,
    RTIEncapsulationId encapsulation_id,
    unsigned int current_alignment,
    const RecipeStep * sample);



/* --------------------------------------------------------------------------------------
    Key Management functions:
 * -------------------------------------------------------------------------------------- */

NDDSUSERDllExport extern PRESTypePluginKeyKind 
RecipeStepPlugin_get_key_kind(void);

NDDSUSERDllExport extern unsigned int 
RecipeStepPlugin_get_serialized_key_max_size(
    PRESTypePluginEndpointData endpoint_data,
    RTIBool include_encapsulation,
    RTIEncapsulationId encapsulation_id,
    unsigned int current_alignment);

NDDSUSERDllExport extern RTIBool 
RecipeStepPlugin_serialize_key(
    PRESTypePluginEndpointData endpoint_data,
    const RecipeStep *sample,
    struct RTICdrStream *stream,
    RTIBool serialize_encapsulation,
    RTIEncapsulationId encapsulation_id,
    RTIBool serialize_key,
    void *endpoint_plugin_qos);

NDDSUSERDllExport extern RTIBool 
RecipeStepPlugin_deserialize_key_sample(
    PRESTypePluginEndpointData endpoint_data,
    RecipeStep * sample,
    struct RTICdrStream *stream,
    RTIBool deserialize_encapsulation,
    RTIBool deserialize_key,
    void *endpoint_plugin_qos);

 
NDDSUSERDllExport extern RTIBool 
RecipeStepPlugin_deserialize_key(
    PRESTypePluginEndpointData endpoint_data,
    RecipeStep ** sample,
    RTIBool * drop_sample,
    struct RTICdrStream *stream,
    RTIBool deserialize_encapsulation,
    RTIBool deserialize_key,
    void *endpoint_plugin_qos);


NDDSUSERDllExport extern RTIBool
RecipeStepPlugin_serialized_sample_to_key(
    PRESTypePluginEndpointData endpoint_data,
    RecipeStep *sample,
    struct RTICdrStream *stream, 
    RTIBool deserialize_encapsulation,  
    RTIBool deserialize_key, 
    void *endpoint_plugin_qos);


/* The type used to store keys for instances of type struct
 * ChocolateRecipe.
 *
 * By default, this type is struct ChocolateRecipe
 * itself. However, if for some reason this choice is not practical for your
 * system (e.g. if sizeof(struct ChocolateRecipe)
 * is very large), you may redefine this typedef in terms of another type of
 * your choosing. HOWEVER, if you define the KeyHolder type to be something
 * other than struct ChocolateRecipe, the
 * following restriction applies: the key of struct
 * ChocolateRecipe must consist of a
 * single field of your redefined KeyHolder type and that field must be the
 * first field in struct ChocolateRecipe.
*/
typedef  class ChocolateRecipe ChocolateRecipeKeyHolder;


#define ChocolateRecipePlugin_get_sample PRESTypePluginDefaultEndpointData_getSample  
#define ChocolateRecipePlugin_get_buffer PRESTypePluginDefaultEndpointData_getBuffer 
#define ChocolateRecipePlugin_return_buffer PRESTypePluginDefaultEndpointData_returnBuffer 

#define ChocolateRecipePlugin_get_key PRESTypePluginDefaultEndpointData_getKey 
#define ChocolateRecipePlugin_return_key PRESTypePluginDefaultEndpointData_returnKey
 

#define ChocolateRecipePlugin_create_sample PRESTypePluginDefaultEndpointData_createSample 
#define ChocolateRecipePlugin_destroy_sample PRESTypePluginDefaultEndpointData_deleteSample 

/* --------------------------------------------------------------------------------------
    Support functions:
 * -------------------------------------------------------------------------------------- */

NDDSUSERDllExport extern ChocolateRecipe*
ChocolateRecipePluginSupport_create_data_w_params(
    const struct DDS_TypeAllocationParams_t * alloc_params);

NDDSUSERDllExport extern ChocolateRecipe*
ChocolateRecipePluginSupport_create_data_ex(RTIBool allocate_pointers);

NDDSUSERDllExport extern ChocolateRecipe*
ChocolateRecipePluginSupport_create_data(void);

NDDSUSERDllExport extern RTIBool 
ChocolateRecipePluginSupport_copy_data(
    ChocolateRecipe *out,
    const ChocolateRecipe *in);

NDDSUSERDllExport extern void 
ChocolateRecipePluginSupport_destroy_data_w_params(
    ChocolateRecipe *sample,
    const struct DDS_TypeDeallocationParams_t * dealloc_params);

NDDSUSERDllExport extern void 
ChocolateRecipePluginSupport_destroy_data_ex(
    ChocolateRecipe *sample,RTIBool deallocate_pointers);

NDDSUSERDllExport extern void 
ChocolateRecipePluginSupport_destroy_data(
    ChocolateRecipe *sample);

NDDSUSERDllExport extern void 
ChocolateRecipePluginSupport_print_data(
    const ChocolateRecipe *sample,
    const char *desc,
    unsigned int indent);


NDDSUSERDllExport extern ChocolateRecipe*
ChocolateRecipePluginSupport_create_key_ex(RTIBool allocate_pointers);

NDDSUSERDllExport extern ChocolateRecipe*
ChocolateRecipePluginSupport_create_key(void);

NDDSUSERDllExport extern void 
ChocolateRecipePluginSupport_destroy_key_ex(
    ChocolateRecipeKeyHolder *key,RTIBool deallocate_pointers);

NDDSUSERDllExport extern void 
ChocolateRecipePluginSupport_destroy_key(
    ChocolateRecipeKeyHolder *key);

/* ----------------------------------------------------------------------------
    Callback functions:
 * ---------------------------------------------------------------------------- */

NDDSUSERDllExport extern PRESTypePluginParticipantData 
ChocolateRecipePlugin_on_participant_attached(
    void *registration_data, 
    const struct PRESTypePluginParticipantInfo *participant_info,
    RTIBool top_level_registration, 
    void *container_plugin_context,
    RTICdrTypeCode *typeCode);

NDDSUSERDllExport extern void 
ChocolateRecipePlugin_on_participant_detached(
    PRESTypePluginParticipantData participant_data);
    
NDDSUSERDllExport extern PRESTypePluginEndpointData 
ChocolateRecipePlugin_on_endpoint_attached(
    PRESTypePluginParticipantData participant_data,
    const struct PRESTypePluginEndpointInfo *endpoint_info,
    RTIBool top_level_registration, 
    void *container_plugin_context);

NDDSUSERDllExport extern void 
ChocolateRecipePlugin_on_endpoint_detached(
    PRESTypePluginEndpointData endpoint_data);
    
NDDSUSERDllExport extern void    
ChocolateRecipePlugin_return_sample(
    PRESTypePluginEndpointData endpoint_data,
    ChocolateRecipe *sample,
    void *handle);    
 

NDDSUSERDllExport extern RTIBool 
ChocolateRecipePlugin_copy_sample(
    PRESTypePluginEndpointData endpoint_data,
    ChocolateRecipe *out,
    const ChocolateRecipe *in);

/* --------------------------------------------------------------------------------------
    (De)Serialize functions:
 * -------------------------------------------------------------------------------------- */

NDDSUSERDllExport extern RTIBool 
ChocolateRecipePlugin_serialize(
    PRESTypePluginEndpointData endpoint_data,
    const ChocolateRecipe *sample,
    struct RTICdrStream *stream, 
    RTIBool serialize_encapsulation,
    RTIEncapsulationId encapsulation_id,
    RTIBool serialize_sample, 
    void *endpoint_plugin_qos);

NDDSUSERDllExport extern RTIBool 
ChocolateRecipePlugin_deserialize_sample(
    PRESTypePluginEndpointData endpoint_data,
    ChocolateRecipe *sample, 
    struct RTICdrStream *stream,
    RTIBool deserialize_encapsulation,
    RTIBool deserialize_sample, 
    void *endpoint_plugin_qos);

 
NDDSUSERDllExport extern RTIBool 
ChocolateRecipePlugin_deserialize(
    PRESTypePluginEndpointData endpoint_data,
    ChocolateRecipe **sample, 
    RTIBool * drop_sample,
    struct RTICdrStream *stream,
    RTIBool deserialize_encapsulation,
    RTIBool deserialize_sample, 
    void *endpoint_plugin_qos);




NDDSUSERDllExport extern RTIBool
ChocolateRecipePlugin_skip(
    PRESTypePluginEndpointData endpoint_data,
    struct RTICdrStream *stream, 
    RTIBool skip_encapsulation,  
    RTIBool skip_sample, 
    void *endpoint_plugin_qos);

NDDSUSERDllExport extern unsigned int 
ChocolateRecipePlugin_get_serialized_sample_max_size(
    PRESTypePluginEndpointData endpoint_data,
    RTIBool include_encapsulation,
    RTIEncapsulationId encapsulation_id,
    unsigned int current_alignment);

NDDSUSERDllExport extern unsigned int 
ChocolateRecipePlugin_get_serialized_sample_min_size(
    PRESTypePluginEndpointData endpoint_data,
    RTIBool include_encapsulation,
    RTIEncapsulationId encapsulation_id,
    unsigned int current_alignment);

NDDSUSERDllExport extern unsigned int
ChocolateRecipePlugin_get_serialized_sample_size(
    PRESTypePluginEndpointData endpoint_data,
    RTIBool include_encapsulation,
    RTIEncapsulationId encapsulation_id,
    unsigned int current_alignment,
    const ChocolateRecipe * sample);



/* --------------------------------------------------------------------------------------
    Key Management functions:
 * -------------------------------------------------------------------------------------- */

NDDSUSERDllExport extern PRESTypePluginKeyKind 
ChocolateRecipePlugin_get_key_kind(void);

NDDSUSERDllExport extern unsigned int 
ChocolateRecipePlugin_get_serialized_key_max_size(
    PRESTypePluginEndpointData endpoint_data,
    RTIBool include_encapsulation,
    RTIEncapsulationId encapsulation_id,
    unsigned int current_alignment);

NDDSUSERDllExport extern RTIBool 
ChocolateRecipePlugin_serialize_key(
    PRESTypePluginEndpointData endpoint_data,
    const ChocolateRecipe *sample,
    struct RTICdrStream *stream,
    RTIBool serialize_encapsulation,
    RTIEncapsulationId encapsulation_id,
    RTIBool serialize_key,
    void *endpoint_plugin_qos);

NDDSUSERDllExport extern RTIBool 
ChocolateRecipePlugin_deserialize_key_sample(
    PRESTypePluginEndpointData endpoint_data,
    ChocolateRecipe * sample,
    struct RTICdrStream *stream,
    RTIBool deserialize_encapsulation,
    RTIBool deserialize_key,
    void *endpoint_plugin_qos);

 
NDDSUSERDllExport extern RTIBool 
ChocolateRecipePlugin_deserialize_key(
    PRESTypePluginEndpointData endpoint_data,
    ChocolateRecipe ** sample,
    RTIBool * drop_sample,
    struct RTICdrStream *stream,
    RTIBool deserialize_encapsulation,
    RTIBool deserialize_key,
    void *endpoint_plugin_qos);


NDDSUSERDllExport extern RTIBool
ChocolateRecipePlugin_serialized_sample_to_key(
    PRESTypePluginEndpointData endpoint_data,
    ChocolateRecipe *sample,
    struct RTICdrStream *stream, 
    RTIBool deserialize_encapsulation,  
    RTIBool deserialize_key, 
    void *endpoint_plugin_qos);

 
NDDSUSERDllExport extern RTIBool 
ChocolateRecipePlugin_instance_to_key(
    PRESTypePluginEndpointData endpoint_data,
    ChocolateRecipeKeyHolder *key, 
    const ChocolateRecipe *instance);

NDDSUSERDllExport extern RTIBool 
ChocolateRecipePlugin_key_to_instance(
    PRESTypePluginEndpointData endpoint_data,
    ChocolateRecipe *instance, 
    const ChocolateRecipeKeyHolder *key);

NDDSUSERDllExport extern RTIBool 
ChocolateRecipePlugin_instance_to_keyhash(
    PRESTypePluginEndpointData endpoint_data,
    DDS_KeyHash_t *keyhash,
    const ChocolateRecipe *instance);

NDDSUSERDllExport extern RTIBool 
ChocolateRecipePlugin_serialized_sample_to_keyhash(
    PRESTypePluginEndpointData endpoint_data,
    struct RTICdrStream *stream, 
    DDS_KeyHash_t *keyhash,
    RTIBool deserialize_encapsulation,
    void *endpoint_plugin_qos); 
     
/* Plugin Functions */
NDDSUSERDllExport extern struct PRESTypePlugin*
ChocolateRecipePlugin_new(void);

NDDSUSERDllExport extern void
ChocolateRecipePlugin_delete(struct PRESTypePlugin *);

/* The type used to store keys for instances of type struct
 * ChocolateLotState.
 *
 * By default, this type is struct ChocolateLotState
 * itself. However, if for some reason this choice is not practical for your
 * system (e.g. if sizeof(struct ChocolateLotState)
 * is very large), you may redefine this typedef in terms of another type of
 * your choosing. HOWEVER, if you define the KeyHolder type to be something
 * other than struct ChocolateLotState, the
 * following restriction applies: the key of struct
 * ChocolateLotState must consist of a
 * single field of your redefined KeyHolder type and that field must be the
 * first field in struct ChocolateLotState.
*/
typedef  class ChocolateLotState ChocolateLotStateKeyHolder;


#define ChocolateLotStatePlugin_get_sample PRESTypePluginDefaultEndpointData_getSample  
#define ChocolateLotStatePlugin_get_buffer PRESTypePluginDefaultEndpointData_getBuffer 
#define ChocolateLotStatePlugin_return_buffer PRESTypePluginDefaultEndpointData_returnBuffer 

#define ChocolateLotStatePlugin_get_key PRESTypePluginDefaultEndpointData_getKey 
#define ChocolateLotStatePlugin_return_key PRESTypePluginDefaultEndpointData_returnKey
 

#define ChocolateLotStatePlugin_create_sample PRESTypePluginDefaultEndpointData_createSample 
#define ChocolateLotStatePlugin_destroy_sample PRESTypePluginDefaultEndpointData_deleteSample 

/* --------------------------------------------------------------------------------------
    Support functions:
 * -------------------------------------------------------------------------------------- */

NDDSUSERDllExport extern ChocolateLotState*
ChocolateLotStatePluginSupport_create_data_w_params(
    const struct DDS_TypeAllocationParams_t * alloc_params);

NDDSUSERDllExport extern ChocolateLotState*
ChocolateLotStatePluginSupport_create_data_ex(RTIBool allocate_pointers);

NDDSUSERDllExport extern ChocolateLotState*
ChocolateLotStatePluginSupport_create_data(void);

NDDSUSERDllExport extern RTIBool 
ChocolateLotStatePluginSupport_copy_data(
    ChocolateLotState *out,
    const ChocolateLotState *in);

NDDSUSERDllExport extern void 
ChocolateLotStatePluginSupport_destroy_data_w_params(
    ChocolateLotState *sample,
    const struct DDS_TypeDeallocationParams_t * dealloc_params);

NDDSUSERDllExport extern void 
ChocolateLotStatePluginSupport_destroy_data_ex(
    ChocolateLotState *sample,RTIBool deallocate_pointers);

NDDSUSERDllExport extern void 
ChocolateLotStatePluginSupport_destroy_data(
    ChocolateLotState *sample);

NDDSUSERDllExport extern void 
ChocolateLotStatePluginSupport_print_data(
    const ChocolateLotState *sample,
    const char *desc,
    unsigned int indent);


NDDSUSERDllExport extern ChocolateLotState*
ChocolateLotStatePluginSupport_create_key_ex(RTIBool allocate_pointers);

NDDSUSERDllExport extern ChocolateLotState*
ChocolateLotStatePluginSupport_create_key(void);

NDDSUSERDllExport extern void 
ChocolateLotStatePluginSupport_destroy_key_ex(
    ChocolateLotStateKeyHolder *key,RTIBool deallocate_pointers);

NDDSUSERDllExport extern void 
ChocolateLotStatePluginSupport_destroy_key(
    ChocolateLotStateKeyHolder *key);

/* ----------------------------------------------------------------------------
    Callback functions:
 * ---------------------------------------------------------------------------- */

NDDSUSERDllExport extern PRESTypePluginParticipantData 
ChocolateLotStatePlugin_on_participant_attached(
    void *registration_data, 
    const struct PRESTypePluginParticipantInfo *participant_info,
    RTIBool top_level_registration, 
    void *container_plugin_context,
    RTICdrTypeCode *typeCode);

NDDSUSERDllExport extern void 
ChocolateLotStatePlugin_on_participant_detached(
    PRESTypePluginParticipantData participant_data);
    
NDDSUSERDllExport extern PRESTypePluginEndpointData 
ChocolateLotStatePlugin_on_endpoint_attached(
    PRESTypePluginParticipantData participant_data,
    const struct PRESTypePluginEndpointInfo *endpoint_info,
    RTIBool top_level_registration, 
    void *container_plugin_context);

NDDSUSERDllExport extern void 
ChocolateLotStatePlugin_on_endpoint_detached(
    PRESTypePluginEndpointData endpoint_data);
    
NDDSUSERDllExport extern void    
ChocolateLotStatePlugin_return_sample(
    PRESTypePluginEndpointData endpoint_data,
    ChocolateLotState *sample,
    void *handle);    
 

NDDSUSERDllExport extern RTIBool 
ChocolateLotStatePlugin_copy_sample(
    PRESTypePluginEndpointData endpoint_data,
    ChocolateLotState *out,
    const ChocolateLotState *in);

/* --------------------------------------------------------------------------------------
    (De)Serialize functions:
 * -------------------------------------------------------------------------------------- */

NDDSUSERDllExport extern RTIBool 
ChocolateLotStatePlugin_serialize(
    PRESTypePluginEndpointData endpoint_data,
    const ChocolateLotState *sample,
    struct RTICdrStream *stream, 
    RTIBool serialize_encapsulation,
    RTIEncapsulationId encapsulation_id,
    RTIBool serialize_sample, 
    void *endpoint_plugin_qos);

NDDSUSERDllExport extern RTIBool 
ChocolateLotStatePlugin_deserialize_sample(
    PRESTypePluginEndpointData endpoint_data,
    ChocolateLotState *sample, 
    struct RTICdrStream *stream,
    RTIBool deserialize_encapsulation,
    RTIBool deserialize_sample, 
    void *endpoint_plugin_qos);

 
NDDSUSERDllExport extern RTIBool 
ChocolateLotStatePlugin_deserialize(
    PRESTypePluginEndpointData endpoint_data,
    ChocolateLotState **sample, 
    RTIBool * drop_sample,
    struct RTICdrStream *stream,
    RTIBool deserialize_encapsulation,
    RTIBool deserialize_sample, 
    void *endpoint_plugin_qos);




NDDSUSERDllExport extern RTIBool
ChocolateLotStatePlugin_skip(
    PRESTypePluginEndpointData endpoint_data,
    struct RTICdrStream *stream, 
    RTIBool skip_encapsulation,  
    RTIBool skip_sample, 
    void *endpoint_plugin_qos);

NDDSUSERDllExport extern unsigned int 
ChocolateLotStatePlugin_get_serialized_sample_max_size(
    PRESTypePluginEndpointData endpoint_data,
    RTIBool include_encapsulation,
    RTIEncapsulationId encapsulation_id,
    unsigned int current_alignment);

NDDSUSERDllExport extern unsigned int 
ChocolateLotStatePlugin_get_serialized_sample_min_size(
    PRESTypePluginEndpointData endpoint_data,
    RTIBool include_encapsulation,
    RTIEncapsulationId encapsulation_id,
    unsigned int current_alignment);

NDDSUSERDllExport extern unsigned int
ChocolateLotStatePlugin_get_serialized_sample_size(
    PRESTypePluginEndpointData endpoint_data,
    RTIBool include_encapsulation,
    RTIEncapsulationId encapsulation_id,
    unsigned int current_alignment,
    const ChocolateLotState * sample);



/* --------------------------------------------------------------------------------------
    Key Management functions:
 * -------------------------------------------------------------------------------------- */

NDDSUSERDllExport extern PRESTypePluginKeyKind 
ChocolateLotStatePlugin_get_key_kind(void);

NDDSUSERDllExport extern unsigned int 
ChocolateLotStatePlugin_get_serialized_key_max_size(
    PRESTypePluginEndpointData endpoint_data,
    RTIBool include_encapsulation,
    RTIEncapsulationId encapsulation_id,
    unsigned int current_alignment);

NDDSUSERDllExport extern RTIBool 
ChocolateLotStatePlugin_serialize_key(
    PRESTypePluginEndpointData endpoint_data,
    const ChocolateLotState *sample,
    struct RTICdrStream *stream,
    RTIBool serialize_encapsulation,
    RTIEncapsulationId encapsulation_id,
    RTIBool serialize_key,
    void *endpoint_plugin_qos);

NDDSUSERDllExport extern RTIBool 
ChocolateLotStatePlugin_deserialize_key_sample(
    PRESTypePluginEndpointData endpoint_data,
    ChocolateLotState * sample,
    struct RTICdrStream *stream,
    RTIBool deserialize_encapsulation,
    RTIBool deserialize_key,
    void *endpoint_plugin_qos);

 
NDDSUSERDllExport extern RTIBool 
ChocolateLotStatePlugin_deserialize_key(
    PRESTypePluginEndpointData endpoint_data,
    ChocolateLotState ** sample,
    RTIBool * drop_sample,
    struct RTICdrStream *stream,
    RTIBool deserialize_encapsulation,
    RTIBool deserialize_key,
    void *endpoint_plugin_qos);


NDDSUSERDllExport extern RTIBool
ChocolateLotStatePlugin_serialized_sample_to_key(
    PRESTypePluginEndpointData endpoint_data,
    ChocolateLotState *sample,
    struct RTICdrStream *stream, 
    RTIBool deserialize_encapsulation,  
    RTIBool deserialize_key, 
    void *endpoint_plugin_qos);

 
NDDSUSERDllExport extern RTIBool 
ChocolateLotStatePlugin_instance_to_key(
    PRESTypePluginEndpointData endpoint_data,
    ChocolateLotStateKeyHolder *key, 
    const ChocolateLotState *instance);

NDDSUSERDllExport extern RTIBool 
ChocolateLotStatePlugin_key_to_instance(
    PRESTypePluginEndpointData endpoint_data,
    ChocolateLotState *instance, 
    const ChocolateLotStateKeyHolder *key);

NDDSUSERDllExport extern RTIBool 
ChocolateLotStatePlugin_instance_to_keyhash(
    PRESTypePluginEndpointData endpoint_data,
    DDS_KeyHash_t *keyhash,
    const ChocolateLotState *instance);

NDDSUSERDllExport extern RTIBool 
ChocolateLotStatePlugin_serialized_sample_to_keyhash(
    PRESTypePluginEndpointData endpoint_data,
    struct RTICdrStream *stream, 
    DDS_KeyHash_t *keyhash,
    RTIBool deserialize_encapsulation,
    void *endpoint_plugin_qos); 
     
/* Plugin Functions */
NDDSUSERDllExport extern struct PRESTypePlugin*
ChocolateLotStatePlugin_new(void);

NDDSUSERDllExport extern void
ChocolateLotStatePlugin_delete(struct PRESTypePlugin *);

} /* namespace generated */

} /* namespace chocolatefactory */

} /* namespace rti */

} /* namespace com */

        
#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif        

#endif /* ChocolateFactoryPlugin_1774920665_h */
