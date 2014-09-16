
/*
  WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

  This file was generated from ChocolateFactory.idl using "rtiddsgen".
  The rtiddsgen tool is part of the RTI Connext distribution.
  For more information, type 'rtiddsgen -help' at a command shell
  or consult the RTI Connext manual.
*/


#include <string.h>

#ifdef __cplusplus
#ifndef ndds_cpp_h
  #include "ndds/ndds_cpp.h"
#endif
#else
#ifndef ndds_c_h
  #include "ndds/ndds_c.h"
#endif
#endif

#ifndef osapi_type_h
  #include "osapi/osapi_type.h"
#endif
#ifndef osapi_heap_h
  #include "osapi/osapi_heap.h"
#endif

#ifndef osapi_utility_h
  #include "osapi/osapi_utility.h"
#endif

#ifndef cdr_type_h
  #include "cdr/cdr_type.h"
#endif

#ifndef cdr_type_object_h
  #include "cdr/cdr_typeObject.h"
#endif

#ifndef cdr_encapsulation_h
  #include "cdr/cdr_encapsulation.h"
#endif

#ifndef cdr_stream_h
  #include "cdr/cdr_stream.h"
#endif

#ifndef pres_typePlugin_h
  #include "pres/pres_typePlugin.h"
#endif



#include "ChocolateFactoryPlugin.h"


namespace com{

namespace rti{

namespace chocolatefactory{

namespace generated{


/* ------------------------------------------------------------------------
   Enum Type: StationControllerKind
 * ------------------------------------------------------------------------- */
 
/* ------------------------------------------------------------------------
 * (De)Serialization Methods
 * ------------------------------------------------------------------------ */


RTIBool StationControllerKindPlugin_serialize(
    PRESTypePluginEndpointData endpoint_data,
    const StationControllerKind *sample,
    struct RTICdrStream *stream, 
    RTIBool serialize_encapsulation,
    RTIEncapsulationId encapsulation_id,
    RTIBool serialize_sample,
    void *endpoint_plugin_qos)
{
    char * position = NULL;


    if (endpoint_data) {} /* To avoid warnings */
    if (endpoint_plugin_qos) {} /* To avoid warnings */



    if(serialize_encapsulation) {
        if (!RTICdrStream_serializeAndSetCdrEncapsulation(stream, encapsulation_id)) {
            return RTI_FALSE;
        }


        position = RTICdrStream_resetAlignment(stream);

    }

    if(serialize_sample) {

        if (!RTICdrStream_serializeEnum(stream, sample))
        {
            return RTI_FALSE;
        }

    }


    if(serialize_encapsulation) {
        RTICdrStream_restoreAlignment(stream,position);
    }


    return RTI_TRUE;
}


RTIBool 
StationControllerKindPlugin_deserialize_sample(
    PRESTypePluginEndpointData endpoint_data,
    StationControllerKind *sample,
    struct RTICdrStream *stream, 
    RTIBool deserialize_encapsulation,  
    RTIBool deserialize_sample, 
    void *endpoint_plugin_qos)
{
    char * position = NULL;
 
    DDS_Enum enum_tmp; 

    if (endpoint_data) {} /* To avoid warnings */
    if (endpoint_plugin_qos) {} /* To avoid warnings */

    if(deserialize_encapsulation) {
        if (!RTICdrStream_deserializeAndSetCdrEncapsulation(stream)) {
            return RTI_FALSE;
        }


        position = RTICdrStream_resetAlignment(stream);

    }

    if(deserialize_sample) {
 
        if (!RTICdrStream_deserializeEnum(stream, &enum_tmp))
        {
            return RTI_FALSE;
        }
        switch (enum_tmp) {

            case INVALID_CONTROLLER:
                *sample=INVALID_CONTROLLER;
                break;
            case SUGAR_CONTROLLER:
                *sample=SUGAR_CONTROLLER;
                break;
            case COCOA_BUTTER_CONTROLLER:
                *sample=COCOA_BUTTER_CONTROLLER;
                break;
            case COCOA_LIQUOR_CONTROLLER:
                *sample=COCOA_LIQUOR_CONTROLLER;
                break;
            case VANILLA_CONTROLLER:
                *sample=VANILLA_CONTROLLER;
                break;
            case MILK_CONTROLLER:
                *sample=MILK_CONTROLLER;
                break;
            default:
            {
                stream->_xTypesState.unassignable = RTI_TRUE;
                return RTI_FALSE;
            }
        }

    }


    if(deserialize_encapsulation) {
        RTICdrStream_restoreAlignment(stream,position);
    }


    return RTI_TRUE;
}


RTIBool StationControllerKindPlugin_skip(
    PRESTypePluginEndpointData endpoint_data,
    struct RTICdrStream *stream, 
    RTIBool skip_encapsulation,  
    RTIBool skip_sample, 
    void *endpoint_plugin_qos)
{
    char * position = NULL;


    if (endpoint_data) {} /* To avoid warnings */
    if (endpoint_plugin_qos) {} /* To avoid warnings */

    if(skip_encapsulation) {
        if (!RTICdrStream_skipEncapsulation(stream)) {
            return RTI_FALSE;
        }


        position = RTICdrStream_resetAlignment(stream);

    }

    if(skip_sample) {

        if (!RTICdrStream_skipEnum(stream)) {
            return RTI_FALSE;
        }


    }


    if(skip_encapsulation) {
        RTICdrStream_restoreAlignment(stream,position);
    }


    return RTI_TRUE;
}


unsigned int StationControllerKindPlugin_get_serialized_sample_max_size(
    PRESTypePluginEndpointData endpoint_data,
    RTIBool include_encapsulation,
    RTIEncapsulationId encapsulation_id,
    unsigned int current_alignment)
{
    unsigned int initial_alignment = current_alignment;

    unsigned int encapsulation_size = current_alignment;


    if (endpoint_data) {} /* To avoid warnings */

    if (include_encapsulation) {
        if (!RTICdrEncapsulation_validEncapsulationId(encapsulation_id)) {
            return 1;
        }


        RTICdrStream_getEncapsulationSize(encapsulation_size);
        encapsulation_size -= current_alignment;
        current_alignment = 0;
        initial_alignment = 0;

    }

    current_alignment += RTICdrType_getEnumMaxSizeSerialized(current_alignment);


    if (include_encapsulation) {
        current_alignment += encapsulation_size;
    }


    return current_alignment - initial_alignment;
}


unsigned int StationControllerKindPlugin_get_serialized_sample_min_size(
    PRESTypePluginEndpointData endpoint_data,
    RTIBool include_encapsulation,
    RTIEncapsulationId encapsulation_id,
    unsigned int current_alignment)
{
    unsigned int initial_alignment = current_alignment;

    current_alignment += ::com::rti::chocolatefactory::generated::StationControllerKindPlugin_get_serialized_sample_max_size(
        endpoint_data,include_encapsulation,
        encapsulation_id, current_alignment);

    return current_alignment - initial_alignment;
}


unsigned int
StationControllerKindPlugin_get_serialized_sample_size(
    PRESTypePluginEndpointData endpoint_data,
    RTIBool include_encapsulation,
    RTIEncapsulationId encapsulation_id,
    unsigned int current_alignment,
    const StationControllerKind * sample) 
{
    unsigned int initial_alignment = current_alignment;

    if (sample) {} /* To avoid warnings */ 

    current_alignment += ::com::rti::chocolatefactory::generated::StationControllerKindPlugin_get_serialized_sample_max_size(
        endpoint_data,include_encapsulation,
        encapsulation_id, current_alignment);

    return current_alignment - initial_alignment;
}






/* ------------------------------------------------------------------------
    Key Management functions:
 * ------------------------------------------------------------------------ */


RTIBool StationControllerKindPlugin_serialize_key(
    PRESTypePluginEndpointData endpoint_data,
    const StationControllerKind *sample, 
    struct RTICdrStream *stream, 
    RTIBool serialize_encapsulation,
    RTIEncapsulationId encapsulation_id,
    RTIBool serialize_key,
    void *endpoint_plugin_qos)
{   
    return ::com::rti::chocolatefactory::generated::StationControllerKindPlugin_serialize(
            endpoint_data, sample, stream, 
            serialize_encapsulation, encapsulation_id, 
            serialize_key, endpoint_plugin_qos);
}


RTIBool StationControllerKindPlugin_deserialize_key_sample(
    PRESTypePluginEndpointData endpoint_data,
    StationControllerKind *sample,
    struct RTICdrStream *stream, 
    RTIBool deserialize_encapsulation,  
    RTIBool deserialize_key, 
    void *endpoint_plugin_qos)
{   
    return ::com::rti::chocolatefactory::generated::StationControllerKindPlugin_deserialize_sample(
            endpoint_data, sample, stream, deserialize_encapsulation, 
            deserialize_key, endpoint_plugin_qos);
}


unsigned int StationControllerKindPlugin_get_serialized_key_max_size(
    PRESTypePluginEndpointData endpoint_data,
    RTIBool include_encapsulation,
    RTIEncapsulationId encapsulation_id,
    unsigned int current_alignment)
{
    unsigned int initial_alignment = current_alignment;

    current_alignment += ::com::rti::chocolatefactory::generated::StationControllerKindPlugin_get_serialized_sample_max_size(
        endpoint_data,include_encapsulation,
        encapsulation_id, current_alignment);

    return current_alignment - initial_alignment;
}


RTIBool 
StationControllerKindPlugin_serialized_sample_to_key(
    PRESTypePluginEndpointData endpoint_data,
    StationControllerKind *sample,
    struct RTICdrStream *stream, 
    RTIBool deserialize_encapsulation,  
    RTIBool deserialize_key, 
    void *endpoint_plugin_qos)
{    
    return ::com::rti::chocolatefactory::generated::StationControllerKindPlugin_deserialize_sample(
            endpoint_data, sample, stream, deserialize_encapsulation, 
            deserialize_key, endpoint_plugin_qos);
}

 
/* ----------------------------------------------------------------------------
    Support functions:
 * ---------------------------------------------------------------------------- */


void StationControllerKindPluginSupport_print_data(
    const StationControllerKind *sample,
    const char *description, int indent_level)
{
    if (description != NULL) {
        RTICdrType_printIndent(indent_level);
        RTILog_debug("%s:\n", description);
    }

    if (sample == NULL) {
        RTICdrType_printIndent(indent_level+1);
        RTILog_debug("NULL\n");
        return;
    }

    RTICdrType_printEnum((RTICdrEnum *)sample, "StationControllerKind", indent_level + 1);
}



/* ------------------------------------------------------------------------
   Enum Type: LotStatusKind
 * ------------------------------------------------------------------------- */
 
/* ------------------------------------------------------------------------
 * (De)Serialization Methods
 * ------------------------------------------------------------------------ */


RTIBool LotStatusKindPlugin_serialize(
    PRESTypePluginEndpointData endpoint_data,
    const LotStatusKind *sample,
    struct RTICdrStream *stream, 
    RTIBool serialize_encapsulation,
    RTIEncapsulationId encapsulation_id,
    RTIBool serialize_sample,
    void *endpoint_plugin_qos)
{
    char * position = NULL;


    if (endpoint_data) {} /* To avoid warnings */
    if (endpoint_plugin_qos) {} /* To avoid warnings */



    if(serialize_encapsulation) {
        if (!RTICdrStream_serializeAndSetCdrEncapsulation(stream, encapsulation_id)) {
            return RTI_FALSE;
        }


        position = RTICdrStream_resetAlignment(stream);

    }

    if(serialize_sample) {

        if (!RTICdrStream_serializeEnum(stream, sample))
        {
            return RTI_FALSE;
        }

    }


    if(serialize_encapsulation) {
        RTICdrStream_restoreAlignment(stream,position);
    }


    return RTI_TRUE;
}


RTIBool 
LotStatusKindPlugin_deserialize_sample(
    PRESTypePluginEndpointData endpoint_data,
    LotStatusKind *sample,
    struct RTICdrStream *stream, 
    RTIBool deserialize_encapsulation,  
    RTIBool deserialize_sample, 
    void *endpoint_plugin_qos)
{
    char * position = NULL;
 
    DDS_Enum enum_tmp; 

    if (endpoint_data) {} /* To avoid warnings */
    if (endpoint_plugin_qos) {} /* To avoid warnings */

    if(deserialize_encapsulation) {
        if (!RTICdrStream_deserializeAndSetCdrEncapsulation(stream)) {
            return RTI_FALSE;
        }


        position = RTICdrStream_resetAlignment(stream);

    }

    if(deserialize_sample) {
 
        if (!RTICdrStream_deserializeEnum(stream, &enum_tmp))
        {
            return RTI_FALSE;
        }
        switch (enum_tmp) {

            case ASSIGNED_TO_SC:
                *sample=ASSIGNED_TO_SC;
                break;
            case WAITING_AT_SC:
                *sample=WAITING_AT_SC;
                break;
            case PROCESSING_AT_SC:
                *sample=PROCESSING_AT_SC;
                break;
            case LOT_COMPLETED:
                *sample=LOT_COMPLETED;
                break;
            default:
            {
                stream->_xTypesState.unassignable = RTI_TRUE;
                return RTI_FALSE;
            }
        }

    }


    if(deserialize_encapsulation) {
        RTICdrStream_restoreAlignment(stream,position);
    }


    return RTI_TRUE;
}


RTIBool LotStatusKindPlugin_skip(
    PRESTypePluginEndpointData endpoint_data,
    struct RTICdrStream *stream, 
    RTIBool skip_encapsulation,  
    RTIBool skip_sample, 
    void *endpoint_plugin_qos)
{
    char * position = NULL;


    if (endpoint_data) {} /* To avoid warnings */
    if (endpoint_plugin_qos) {} /* To avoid warnings */

    if(skip_encapsulation) {
        if (!RTICdrStream_skipEncapsulation(stream)) {
            return RTI_FALSE;
        }


        position = RTICdrStream_resetAlignment(stream);

    }

    if(skip_sample) {

        if (!RTICdrStream_skipEnum(stream)) {
            return RTI_FALSE;
        }


    }


    if(skip_encapsulation) {
        RTICdrStream_restoreAlignment(stream,position);
    }


    return RTI_TRUE;
}


unsigned int LotStatusKindPlugin_get_serialized_sample_max_size(
    PRESTypePluginEndpointData endpoint_data,
    RTIBool include_encapsulation,
    RTIEncapsulationId encapsulation_id,
    unsigned int current_alignment)
{
    unsigned int initial_alignment = current_alignment;

    unsigned int encapsulation_size = current_alignment;


    if (endpoint_data) {} /* To avoid warnings */

    if (include_encapsulation) {
        if (!RTICdrEncapsulation_validEncapsulationId(encapsulation_id)) {
            return 1;
        }


        RTICdrStream_getEncapsulationSize(encapsulation_size);
        encapsulation_size -= current_alignment;
        current_alignment = 0;
        initial_alignment = 0;

    }

    current_alignment += RTICdrType_getEnumMaxSizeSerialized(current_alignment);


    if (include_encapsulation) {
        current_alignment += encapsulation_size;
    }


    return current_alignment - initial_alignment;
}


unsigned int LotStatusKindPlugin_get_serialized_sample_min_size(
    PRESTypePluginEndpointData endpoint_data,
    RTIBool include_encapsulation,
    RTIEncapsulationId encapsulation_id,
    unsigned int current_alignment)
{
    unsigned int initial_alignment = current_alignment;

    current_alignment += ::com::rti::chocolatefactory::generated::LotStatusKindPlugin_get_serialized_sample_max_size(
        endpoint_data,include_encapsulation,
        encapsulation_id, current_alignment);

    return current_alignment - initial_alignment;
}


unsigned int
LotStatusKindPlugin_get_serialized_sample_size(
    PRESTypePluginEndpointData endpoint_data,
    RTIBool include_encapsulation,
    RTIEncapsulationId encapsulation_id,
    unsigned int current_alignment,
    const LotStatusKind * sample) 
{
    unsigned int initial_alignment = current_alignment;

    if (sample) {} /* To avoid warnings */ 

    current_alignment += ::com::rti::chocolatefactory::generated::LotStatusKindPlugin_get_serialized_sample_max_size(
        endpoint_data,include_encapsulation,
        encapsulation_id, current_alignment);

    return current_alignment - initial_alignment;
}






/* ------------------------------------------------------------------------
    Key Management functions:
 * ------------------------------------------------------------------------ */


RTIBool LotStatusKindPlugin_serialize_key(
    PRESTypePluginEndpointData endpoint_data,
    const LotStatusKind *sample, 
    struct RTICdrStream *stream, 
    RTIBool serialize_encapsulation,
    RTIEncapsulationId encapsulation_id,
    RTIBool serialize_key,
    void *endpoint_plugin_qos)
{   
    return ::com::rti::chocolatefactory::generated::LotStatusKindPlugin_serialize(
            endpoint_data, sample, stream, 
            serialize_encapsulation, encapsulation_id, 
            serialize_key, endpoint_plugin_qos);
}


RTIBool LotStatusKindPlugin_deserialize_key_sample(
    PRESTypePluginEndpointData endpoint_data,
    LotStatusKind *sample,
    struct RTICdrStream *stream, 
    RTIBool deserialize_encapsulation,  
    RTIBool deserialize_key, 
    void *endpoint_plugin_qos)
{   
    return ::com::rti::chocolatefactory::generated::LotStatusKindPlugin_deserialize_sample(
            endpoint_data, sample, stream, deserialize_encapsulation, 
            deserialize_key, endpoint_plugin_qos);
}


unsigned int LotStatusKindPlugin_get_serialized_key_max_size(
    PRESTypePluginEndpointData endpoint_data,
    RTIBool include_encapsulation,
    RTIEncapsulationId encapsulation_id,
    unsigned int current_alignment)
{
    unsigned int initial_alignment = current_alignment;

    current_alignment += ::com::rti::chocolatefactory::generated::LotStatusKindPlugin_get_serialized_sample_max_size(
        endpoint_data,include_encapsulation,
        encapsulation_id, current_alignment);

    return current_alignment - initial_alignment;
}


RTIBool 
LotStatusKindPlugin_serialized_sample_to_key(
    PRESTypePluginEndpointData endpoint_data,
    LotStatusKind *sample,
    struct RTICdrStream *stream, 
    RTIBool deserialize_encapsulation,  
    RTIBool deserialize_key, 
    void *endpoint_plugin_qos)
{    
    return ::com::rti::chocolatefactory::generated::LotStatusKindPlugin_deserialize_sample(
            endpoint_data, sample, stream, deserialize_encapsulation, 
            deserialize_key, endpoint_plugin_qos);
}

 
/* ----------------------------------------------------------------------------
    Support functions:
 * ---------------------------------------------------------------------------- */


void LotStatusKindPluginSupport_print_data(
    const LotStatusKind *sample,
    const char *description, int indent_level)
{
    if (description != NULL) {
        RTICdrType_printIndent(indent_level);
        RTILog_debug("%s:\n", description);
    }

    if (sample == NULL) {
        RTICdrType_printIndent(indent_level+1);
        RTILog_debug("NULL\n");
        return;
    }

    RTICdrType_printEnum((RTICdrEnum *)sample, "LotStatusKind", indent_level + 1);
}


/* --------------------------------------------------------------------------------------
 *  Type RecipeStep
 * -------------------------------------------------------------------------------------- */

/* --------------------------------------------------------------------------------------
    Support functions:
 * -------------------------------------------------------------------------------------- */

RecipeStep*
RecipeStepPluginSupport_create_data_w_params(
    const struct DDS_TypeAllocationParams_t * alloc_params){
    RecipeStep *sample = NULL;

    RTIOsapiHeap_allocateStructure(
        &sample, RecipeStep);

    if(sample != NULL) {
        if (!::com::rti::chocolatefactory::generated::RecipeStep_initialize_w_params(sample,alloc_params)) {
            RTIOsapiHeap_freeStructure(sample);
            return NULL;
        }
    }        
    return sample; 
}


RecipeStep *
RecipeStepPluginSupport_create_data_ex(RTIBool allocate_pointers){
    RecipeStep *sample = NULL;

    RTIOsapiHeap_allocateStructure(
        &sample, RecipeStep);

    if(sample != NULL) {
        if (!::com::rti::chocolatefactory::generated::RecipeStep_initialize_ex(sample,allocate_pointers, RTI_TRUE)) {
            RTIOsapiHeap_freeStructure(sample);
            return NULL;
        }
    }        
    return sample; 
}


RecipeStep *
RecipeStepPluginSupport_create_data(void)
{
    return ::com::rti::chocolatefactory::generated::RecipeStepPluginSupport_create_data_ex(RTI_TRUE);
}


void 
RecipeStepPluginSupport_destroy_data_w_params(
    RecipeStep *sample,
    const struct DDS_TypeDeallocationParams_t * dealloc_params) {

    ::com::rti::chocolatefactory::generated::RecipeStep_finalize_w_params(sample,dealloc_params);

    RTIOsapiHeap_freeStructure(sample);
}


void 
RecipeStepPluginSupport_destroy_data_ex(
    RecipeStep *sample,RTIBool deallocate_pointers) {

    ::com::rti::chocolatefactory::generated::RecipeStep_finalize_ex(sample,deallocate_pointers);

    RTIOsapiHeap_freeStructure(sample);
}


void 
RecipeStepPluginSupport_destroy_data(
    RecipeStep *sample) {

    ::com::rti::chocolatefactory::generated::RecipeStepPluginSupport_destroy_data_ex(sample,RTI_TRUE);

}


RTIBool 
RecipeStepPluginSupport_copy_data(
    RecipeStep *dst,
    const RecipeStep *src)
{
    return ::com::rti::chocolatefactory::generated::RecipeStep_copy(dst,src);
}


void 
RecipeStepPluginSupport_print_data(
    const RecipeStep *sample,
    const char *desc,
    unsigned int indent_level)
{


    RTICdrType_printIndent(indent_level);

    if (desc != NULL) {
      RTILog_debug("%s:\n", desc);
    } else {
      RTILog_debug("\n");
    }

    if (sample == NULL) {
      RTILog_debug("NULL\n");
      return;
    }


    com::rti::chocolatefactory::generated::StationControllerKindPluginSupport_print_data(
        &sample->stationController, "stationController", indent_level + 1);
            

    RTICdrType_printLong(
        &sample->seconds, "seconds", indent_level + 1);
            


}

 


RTIBool 
RecipeStepPlugin_copy_sample(
    PRESTypePluginEndpointData endpoint_data,
    RecipeStep *dst,
    const RecipeStep *src)
{
    if (endpoint_data) {} /* To avoid warnings */
    return ::com::rti::chocolatefactory::generated::RecipeStepPluginSupport_copy_data(dst,src);
}

/* --------------------------------------------------------------------------------------
    (De)Serialize functions:
 * -------------------------------------------------------------------------------------- */

unsigned int 
RecipeStepPlugin_get_serialized_sample_max_size(
    PRESTypePluginEndpointData endpoint_data,
    RTIBool include_encapsulation,
    RTIEncapsulationId encapsulation_id,
    unsigned int current_alignment);


RTIBool 
RecipeStepPlugin_serialize(
    PRESTypePluginEndpointData endpoint_data,
    const RecipeStep *sample, 
    struct RTICdrStream *stream,    
    RTIBool serialize_encapsulation,
    RTIEncapsulationId encapsulation_id,
    RTIBool serialize_sample, 
    void *endpoint_plugin_qos)
{
    char * position = NULL;
    RTIBool retval = RTI_TRUE;

    if (endpoint_data) {} /* To avoid warnings */
    if (endpoint_plugin_qos) {} /* To avoid warnings */


    if(serialize_encapsulation) {
  
        if (!RTICdrStream_serializeAndSetCdrEncapsulation(stream, encapsulation_id)) {
            return RTI_FALSE;
        }

        position = RTICdrStream_resetAlignment(stream);

    }


    if(serialize_sample) {
    
    if (!com::rti::chocolatefactory::generated::StationControllerKindPlugin_serialize(
            endpoint_data,
            &sample->stationController, 
            stream, 
            RTI_FALSE, encapsulation_id, 
            RTI_TRUE, 
            endpoint_plugin_qos)) {
        return RTI_FALSE;
    }
            

    if (!RTICdrStream_serializeLong(
        stream, &sample->seconds)) {
        return RTI_FALSE;
    }
            

    }


    if(serialize_encapsulation) {
        RTICdrStream_restoreAlignment(stream,position);
    }


  return retval;
}


RTIBool 
RecipeStepPlugin_deserialize_sample(
    PRESTypePluginEndpointData endpoint_data,
    RecipeStep *sample,
    struct RTICdrStream *stream,   
    RTIBool deserialize_encapsulation,
    RTIBool deserialize_sample, 
    void *endpoint_plugin_qos)
{
    char * position = NULL;

    RTIBool done = RTI_FALSE;

    if (endpoint_data) {} /* To avoid warnings */
    if (endpoint_plugin_qos) {} /* To avoid warnings */


    if(deserialize_encapsulation) {
        /* Deserialize encapsulation */
        if (!RTICdrStream_deserializeAndSetCdrEncapsulation(stream)) {
            return RTI_FALSE;
        }

        position = RTICdrStream_resetAlignment(stream);

    }
    
    
    if(deserialize_sample) {
        ::com::rti::chocolatefactory::generated::RecipeStep_initialize_ex(sample, RTI_FALSE, RTI_FALSE);
    
    if (!com::rti::chocolatefactory::generated::StationControllerKindPlugin_deserialize_sample(
            endpoint_data,
            &sample->stationController,
            stream, 
            RTI_FALSE, RTI_TRUE, 
            endpoint_plugin_qos)) {
        goto fin;
    }
            

    if (!RTICdrStream_deserializeLong(
        stream, &sample->seconds)) {
        goto fin;
    }

    }

    done = RTI_TRUE;
fin:
    if (done != RTI_TRUE && 
        RTICdrStream_getRemainder(stream) >=
            RTI_CDR_PARAMETER_HEADER_ALIGNMENT) {
        return RTI_FALSE;   
    }

    if(deserialize_encapsulation) {
        RTICdrStream_restoreAlignment(stream,position);
    }


    return RTI_TRUE;
}

 
 

RTIBool 
RecipeStepPlugin_deserialize(
    PRESTypePluginEndpointData endpoint_data,
    RecipeStep **sample,
    RTIBool * drop_sample,
    struct RTICdrStream *stream,   
    RTIBool deserialize_encapsulation,
    RTIBool deserialize_sample, 
    void *endpoint_plugin_qos)
{

    RTIBool result;
    if (drop_sample) {} /* To avoid warnings */
    
    stream->_xTypesState.unassignable = RTI_FALSE;

    result = ::com::rti::chocolatefactory::generated::RecipeStepPlugin_deserialize_sample( 
        endpoint_data, (sample != NULL)?*sample:NULL,
        stream, deserialize_encapsulation, deserialize_sample, 
        endpoint_plugin_qos);
        
    if (result) {
        if (stream->_xTypesState.unassignable) {
            result = RTI_FALSE;
        }
    }
    
    return result;
 
}




RTIBool RecipeStepPlugin_skip(
    PRESTypePluginEndpointData endpoint_data,
    struct RTICdrStream *stream,   
    RTIBool skip_encapsulation,
    RTIBool skip_sample, 
    void *endpoint_plugin_qos)
{
    char * position = NULL;

    RTIBool done = RTI_FALSE;

    if (endpoint_data) {} /* To avoid warnings */
    if (endpoint_plugin_qos) {} /* To avoid warnings */


    if(skip_encapsulation) {
        if (!RTICdrStream_skipEncapsulation(stream)) {
            return RTI_FALSE;
        }


        position = RTICdrStream_resetAlignment(stream);

    }

    if (skip_sample) {

    if (!com::rti::chocolatefactory::generated::StationControllerKindPlugin_skip(
            endpoint_data,
            stream, 
            RTI_FALSE, RTI_TRUE, 
            endpoint_plugin_qos)) {
        goto fin;
    }
            

    if (!RTICdrStream_skipLong(stream)) {
        goto fin;
    }
            


    }
    

    done = RTI_TRUE;
fin:
    if (done != RTI_TRUE && 
        RTICdrStream_getRemainder(stream) >=
            RTI_CDR_PARAMETER_HEADER_ALIGNMENT) {
        return RTI_FALSE;   
    }

    if(skip_encapsulation) {
        RTICdrStream_restoreAlignment(stream,position);
    }


    return RTI_TRUE;
}


unsigned int 
RecipeStepPlugin_get_serialized_sample_max_size(
    PRESTypePluginEndpointData endpoint_data,
    RTIBool include_encapsulation,
    RTIEncapsulationId encapsulation_id,
    unsigned int current_alignment)
{

    unsigned int initial_alignment = current_alignment;

    unsigned int encapsulation_size = current_alignment;

    if (endpoint_data) {} /* To avoid warnings */


    if (include_encapsulation) {

        if (!RTICdrEncapsulation_validEncapsulationId(encapsulation_id)) {
            return 1;
        }

        RTICdrStream_getEncapsulationSize(encapsulation_size);
        encapsulation_size -= current_alignment;
        current_alignment = 0;
        initial_alignment = 0;

    }


    current_alignment +=  com::rti::chocolatefactory::generated::StationControllerKindPlugin_get_serialized_sample_max_size(
        endpoint_data,RTI_FALSE,encapsulation_id,current_alignment);
            

    current_alignment +=  RTICdrType_getLongMaxSizeSerialized(
        current_alignment);
            

    if (include_encapsulation) {
        current_alignment += encapsulation_size;
    }

    return current_alignment - initial_alignment;
}


unsigned int 
RecipeStepPlugin_get_serialized_sample_min_size(
    PRESTypePluginEndpointData endpoint_data,
    RTIBool include_encapsulation,
    RTIEncapsulationId encapsulation_id,
    unsigned int current_alignment)
{

    unsigned int initial_alignment = current_alignment;

    unsigned int encapsulation_size = current_alignment;

    if (endpoint_data) {} /* To avoid warnings */


    if (include_encapsulation) {

        if (!RTICdrEncapsulation_validEncapsulationId(encapsulation_id)) {
            return 1;
        }

        RTICdrStream_getEncapsulationSize(encapsulation_size);
        encapsulation_size -= current_alignment;
        current_alignment = 0;
        initial_alignment = 0;

    }


    current_alignment +=  com::rti::chocolatefactory::generated::StationControllerKindPlugin_get_serialized_sample_min_size(
        endpoint_data,RTI_FALSE,encapsulation_id,current_alignment);
            

    current_alignment +=  RTICdrType_getLongMaxSizeSerialized(
        current_alignment);
            

    if (include_encapsulation) {
        current_alignment += encapsulation_size;
    }

    return current_alignment - initial_alignment;
}


/* Returns the size of the sample in its serialized form (in bytes).
 * It can also be an estimation in excess of the real buffer needed 
 * during a call to the serialize() function.
 * The value reported does not have to include the space for the
 * encapsulation flags.
 */
unsigned int
RecipeStepPlugin_get_serialized_sample_size(
    PRESTypePluginEndpointData endpoint_data,
    RTIBool include_encapsulation,
    RTIEncapsulationId encapsulation_id,
    unsigned int current_alignment,
    const RecipeStep * sample) 
{

    unsigned int initial_alignment = current_alignment;

    unsigned int encapsulation_size = current_alignment;

    if (endpoint_data) {} /* To avoid warnings */
    if (sample) {} /* To avoid warnings */


    if (include_encapsulation) {

        if (!RTICdrEncapsulation_validEncapsulationId(encapsulation_id)) {
            return 1;
        }

        RTICdrStream_getEncapsulationSize(encapsulation_size);
        encapsulation_size -= current_alignment;
        current_alignment = 0;
        initial_alignment = 0;

    }


    current_alignment += com::rti::chocolatefactory::generated::StationControllerKindPlugin_get_serialized_sample_size(
        endpoint_data,RTI_FALSE, encapsulation_id, 
        current_alignment, &sample->stationController);
            

    current_alignment += RTICdrType_getLongMaxSizeSerialized(
        current_alignment);
            

    if (include_encapsulation) {
        current_alignment += encapsulation_size;
    }

    return current_alignment - initial_alignment;
}







/* --------------------------------------------------------------------------------------
    Key Management functions:
 * -------------------------------------------------------------------------------------- */


PRESTypePluginKeyKind 
RecipeStepPlugin_get_key_kind(void)
{

    return PRES_TYPEPLUGIN_NO_KEY;
     
}


RTIBool 
RecipeStepPlugin_serialize_key(
    PRESTypePluginEndpointData endpoint_data,
    const RecipeStep *sample, 
    struct RTICdrStream *stream,    
    RTIBool serialize_encapsulation,
    RTIEncapsulationId encapsulation_id,
    RTIBool serialize_key,
    void *endpoint_plugin_qos)
{
    char * position = NULL;

    if (endpoint_data) {} /* To avoid warnings */
    if (endpoint_plugin_qos) {} /* To avoid warnings */


    if(serialize_encapsulation) {
    
        if (!RTICdrStream_serializeAndSetCdrEncapsulation(stream, encapsulation_id)) {
            return RTI_FALSE;
        }


        position = RTICdrStream_resetAlignment(stream);

    }

    if(serialize_key) {

        if (!::com::rti::chocolatefactory::generated::RecipeStepPlugin_serialize(
                endpoint_data,
                sample,
                stream,
                RTI_FALSE, encapsulation_id,
                RTI_TRUE,
                endpoint_plugin_qos)) {
            return RTI_FALSE;
        }
    
    }


    if(serialize_encapsulation) {
        RTICdrStream_restoreAlignment(stream,position);
    }


    return RTI_TRUE;
}


RTIBool RecipeStepPlugin_deserialize_key_sample(
    PRESTypePluginEndpointData endpoint_data,
    RecipeStep *sample, 
    struct RTICdrStream *stream,
    RTIBool deserialize_encapsulation,
    RTIBool deserialize_key,
    void *endpoint_plugin_qos)
{
    char * position = NULL;

    if (endpoint_data) {} /* To avoid warnings */
    if (endpoint_plugin_qos) {} /* To avoid warnings */


    if(deserialize_encapsulation) {
        /* Deserialize encapsulation */
        if (!RTICdrStream_deserializeAndSetCdrEncapsulation(stream)) {
            return RTI_FALSE;  
        }


        position = RTICdrStream_resetAlignment(stream);

    }

    if (deserialize_key) {

        if (!::com::rti::chocolatefactory::generated::RecipeStepPlugin_deserialize_sample(
                endpoint_data, sample, stream,
                RTI_FALSE, RTI_TRUE, 
                endpoint_plugin_qos)) {
            return RTI_FALSE;
        }
    
    }


    if(deserialize_encapsulation) {
        RTICdrStream_restoreAlignment(stream,position);
    }


    return RTI_TRUE;
}


 
RTIBool RecipeStepPlugin_deserialize_key(
    PRESTypePluginEndpointData endpoint_data,
    RecipeStep **sample, 
    RTIBool * drop_sample,
    struct RTICdrStream *stream,
    RTIBool deserialize_encapsulation,
    RTIBool deserialize_key,
    void *endpoint_plugin_qos)
{
    RTIBool result;
    if (drop_sample) {} /* To avoid warnings */
    
    stream->_xTypesState.unassignable = RTI_FALSE;
    
    result = ::com::rti::chocolatefactory::generated::RecipeStepPlugin_deserialize_key_sample(
        endpoint_data, (sample != NULL)?*sample:NULL, stream,
        deserialize_encapsulation, deserialize_key, endpoint_plugin_qos);
        
    if (result) {
        if (stream->_xTypesState.unassignable) {
            result = RTI_FALSE;
        }
    }
    
    return result;
}



unsigned int
RecipeStepPlugin_get_serialized_key_max_size(
    PRESTypePluginEndpointData endpoint_data,
    RTIBool include_encapsulation,
    RTIEncapsulationId encapsulation_id,
    unsigned int current_alignment)
{

    unsigned int encapsulation_size = current_alignment;


    unsigned int initial_alignment = current_alignment;


    if (endpoint_data) {} /* To avoid warnings */


    if (include_encapsulation) {
        if (!RTICdrEncapsulation_validEncapsulationId(encapsulation_id)) {
            return 1;
        }


        RTICdrStream_getEncapsulationSize(encapsulation_size);
        encapsulation_size -= current_alignment;
        current_alignment = 0;
        initial_alignment = 0;

    }
        

    current_alignment += ::com::rti::chocolatefactory::generated::RecipeStepPlugin_get_serialized_sample_max_size(
        endpoint_data,RTI_FALSE, encapsulation_id, current_alignment);
    
    if (include_encapsulation) {
        current_alignment += encapsulation_size;
    }

    return current_alignment - initial_alignment;
}


RTIBool 
RecipeStepPlugin_serialized_sample_to_key(
    PRESTypePluginEndpointData endpoint_data,
    RecipeStep *sample,
    struct RTICdrStream *stream, 
    RTIBool deserialize_encapsulation,  
    RTIBool deserialize_key, 
    void *endpoint_plugin_qos)
{
    char * position = NULL;

    RTIBool done = RTI_FALSE;

    if (stream == NULL) goto fin; /* To avoid warnings */


    if(deserialize_encapsulation) {
        if (!RTICdrStream_deserializeAndSetCdrEncapsulation(stream)) {
            return RTI_FALSE;
        }

        position = RTICdrStream_resetAlignment(stream);

    }

    if (deserialize_key) {

        if (!::com::rti::chocolatefactory::generated::RecipeStepPlugin_deserialize_sample(
            endpoint_data, sample, stream, RTI_FALSE, 
            RTI_TRUE, endpoint_plugin_qos)) {
            return RTI_FALSE;
        }

    }


    done = RTI_TRUE;
fin:
    if (done != RTI_TRUE && 
        RTICdrStream_getRemainder(stream) >=
            RTI_CDR_PARAMETER_HEADER_ALIGNMENT) {
        return RTI_FALSE;   
    }

    if(deserialize_encapsulation) {
        RTICdrStream_restoreAlignment(stream,position);
    }


    return RTI_TRUE;
}




/* ------------------------------------------------------------------------
 * Plug-in Installation Methods
 * ------------------------------------------------------------------------ */

/* --------------------------------------------------------------------------------------
 *  Type ChocolateRecipe
 * -------------------------------------------------------------------------------------- */

/* --------------------------------------------------------------------------------------
    Support functions:
 * -------------------------------------------------------------------------------------- */

ChocolateRecipe*
ChocolateRecipePluginSupport_create_data_w_params(
    const struct DDS_TypeAllocationParams_t * alloc_params){
    ChocolateRecipe *sample = NULL;

    RTIOsapiHeap_allocateStructure(
        &sample, ChocolateRecipe);

    if(sample != NULL) {
        if (!::com::rti::chocolatefactory::generated::ChocolateRecipe_initialize_w_params(sample,alloc_params)) {
            RTIOsapiHeap_freeStructure(sample);
            return NULL;
        }
    }        
    return sample; 
}


ChocolateRecipe *
ChocolateRecipePluginSupport_create_data_ex(RTIBool allocate_pointers){
    ChocolateRecipe *sample = NULL;

    RTIOsapiHeap_allocateStructure(
        &sample, ChocolateRecipe);

    if(sample != NULL) {
        if (!::com::rti::chocolatefactory::generated::ChocolateRecipe_initialize_ex(sample,allocate_pointers, RTI_TRUE)) {
            RTIOsapiHeap_freeStructure(sample);
            return NULL;
        }
    }        
    return sample; 
}


ChocolateRecipe *
ChocolateRecipePluginSupport_create_data(void)
{
    return ::com::rti::chocolatefactory::generated::ChocolateRecipePluginSupport_create_data_ex(RTI_TRUE);
}


void 
ChocolateRecipePluginSupport_destroy_data_w_params(
    ChocolateRecipe *sample,
    const struct DDS_TypeDeallocationParams_t * dealloc_params) {

    ::com::rti::chocolatefactory::generated::ChocolateRecipe_finalize_w_params(sample,dealloc_params);

    RTIOsapiHeap_freeStructure(sample);
}


void 
ChocolateRecipePluginSupport_destroy_data_ex(
    ChocolateRecipe *sample,RTIBool deallocate_pointers) {

    ::com::rti::chocolatefactory::generated::ChocolateRecipe_finalize_ex(sample,deallocate_pointers);

    RTIOsapiHeap_freeStructure(sample);
}


void 
ChocolateRecipePluginSupport_destroy_data(
    ChocolateRecipe *sample) {

    ::com::rti::chocolatefactory::generated::ChocolateRecipePluginSupport_destroy_data_ex(sample,RTI_TRUE);

}


RTIBool 
ChocolateRecipePluginSupport_copy_data(
    ChocolateRecipe *dst,
    const ChocolateRecipe *src)
{
    return ::com::rti::chocolatefactory::generated::ChocolateRecipe_copy(dst,src);
}


void 
ChocolateRecipePluginSupport_print_data(
    const ChocolateRecipe *sample,
    const char *desc,
    unsigned int indent_level)
{


    RTICdrType_printIndent(indent_level);

    if (desc != NULL) {
      RTILog_debug("%s:\n", desc);
    } else {
      RTILog_debug("\n");
    }

    if (sample == NULL) {
      RTILog_debug("NULL\n");
      return;
    }


    if (&sample->recipeName==NULL) {
        RTICdrType_printString(
            NULL, "recipeName", indent_level + 1);                
    } else {
        RTICdrType_printString(
            sample->recipeName, "recipeName", indent_level + 1);                
    }
            

    if (&sample->steps == NULL) {
        RTICdrType_printIndent(indent_level+1);
        RTILog_debug("steps: NULL\n");    
    } else {
                
        if (com::rti::chocolatefactory::generated::RecipeStepSeq_get_contiguous_bufferI(&sample->steps) != NULL) {
            RTICdrType_printArray(
                com::rti::chocolatefactory::generated::RecipeStepSeq_get_contiguous_bufferI(&sample->steps), 
                com::rti::chocolatefactory::generated::RecipeStepSeq_get_length(&sample->steps),
                sizeof(com::rti::chocolatefactory::generated::RecipeStep),
                (RTICdrTypePrintFunction)com::rti::chocolatefactory::generated::RecipeStepPluginSupport_print_data,
                "steps", indent_level + 1);
        } else {
            RTICdrType_printPointerArray(
                com::rti::chocolatefactory::generated::RecipeStepSeq_get_discontiguous_bufferI(&sample->steps), 
                com::rti::chocolatefactory::generated::RecipeStepSeq_get_length(&sample->steps),
                (RTICdrTypePrintFunction)com::rti::chocolatefactory::generated::RecipeStepPluginSupport_print_data,
                "steps", indent_level + 1);
        }
    
    }
            


}

ChocolateRecipe *
ChocolateRecipePluginSupport_create_key_ex(RTIBool allocate_pointers){
    ChocolateRecipe *key = NULL;

    RTIOsapiHeap_allocateStructure(
        &key, ChocolateRecipeKeyHolder);

    ::com::rti::chocolatefactory::generated::ChocolateRecipe_initialize_ex(key,allocate_pointers,RTI_TRUE);
    return key;
}


ChocolateRecipe *
ChocolateRecipePluginSupport_create_key(void)
{
    return  ::com::rti::chocolatefactory::generated::ChocolateRecipePluginSupport_create_key_ex(RTI_TRUE);
}


void 
ChocolateRecipePluginSupport_destroy_key_ex(
    ChocolateRecipeKeyHolder *key,RTIBool deallocate_pointers)
{
    ::com::rti::chocolatefactory::generated::ChocolateRecipe_finalize_ex(key,deallocate_pointers);

    RTIOsapiHeap_freeStructure(key);
}


void 
ChocolateRecipePluginSupport_destroy_key(
    ChocolateRecipeKeyHolder *key) {

  ::com::rti::chocolatefactory::generated::ChocolateRecipePluginSupport_destroy_key_ex(key,RTI_TRUE);

}


/* ----------------------------------------------------------------------------
    Callback functions:
 * ---------------------------------------------------------------------------- */



PRESTypePluginParticipantData 
ChocolateRecipePlugin_on_participant_attached(
    void *registration_data,
    const struct PRESTypePluginParticipantInfo *participant_info,
    RTIBool top_level_registration,
    void *container_plugin_context,
    RTICdrTypeCode *type_code)
{

    if (registration_data) {} /* To avoid warnings */
    if (participant_info) {} /* To avoid warnings */
    if (top_level_registration) {} /* To avoid warnings */
    if (container_plugin_context) {} /* To avoid warnings */
    if (type_code) {} /* To avoid warnings */
    return PRESTypePluginDefaultParticipantData_new(participant_info);

}


void 
ChocolateRecipePlugin_on_participant_detached(
    PRESTypePluginParticipantData participant_data)
{

  PRESTypePluginDefaultParticipantData_delete(participant_data);
}


PRESTypePluginEndpointData
ChocolateRecipePlugin_on_endpoint_attached(
    PRESTypePluginParticipantData participant_data,
    const struct PRESTypePluginEndpointInfo *endpoint_info,
    RTIBool top_level_registration, 
    void *containerPluginContext)
{
    PRESTypePluginEndpointData epd = NULL;

    unsigned int serializedSampleMaxSize;

    unsigned int serializedKeyMaxSize;

    if (top_level_registration) {} /* To avoid warnings */
    if (containerPluginContext) {} /* To avoid warnings */


    epd = PRESTypePluginDefaultEndpointData_new(
            participant_data,
            endpoint_info,
            (PRESTypePluginDefaultEndpointDataCreateSampleFunction)
            ::com::rti::chocolatefactory::generated::ChocolateRecipePluginSupport_create_data,
            (PRESTypePluginDefaultEndpointDataDestroySampleFunction)
            ::com::rti::chocolatefactory::generated::ChocolateRecipePluginSupport_destroy_data,
            (PRESTypePluginDefaultEndpointDataCreateKeyFunction)
            ::com::rti::chocolatefactory::generated::ChocolateRecipePluginSupport_create_key,
            (PRESTypePluginDefaultEndpointDataDestroyKeyFunction)
            ::com::rti::chocolatefactory::generated::ChocolateRecipePluginSupport_destroy_key);

    if (epd == NULL) {
        return NULL;
    }
   
    serializedKeyMaxSize = ::com::rti::chocolatefactory::generated::ChocolateRecipePlugin_get_serialized_key_max_size(
        epd,RTI_FALSE,RTI_CDR_ENCAPSULATION_ID_CDR_BE,0);
    
    if (!PRESTypePluginDefaultEndpointData_createMD5Stream(
            epd,serializedKeyMaxSize)) 
    {
        PRESTypePluginDefaultEndpointData_delete(epd);
        return NULL;
    }
    
    

    if (endpoint_info->endpointKind == PRES_TYPEPLUGIN_ENDPOINT_WRITER) {
        serializedSampleMaxSize = ::com::rti::chocolatefactory::generated::ChocolateRecipePlugin_get_serialized_sample_max_size(
            epd,RTI_FALSE,RTI_CDR_ENCAPSULATION_ID_CDR_BE,0);
            
        PRESTypePluginDefaultEndpointData_setMaxSizeSerializedSample(epd, serializedSampleMaxSize);

        if (PRESTypePluginDefaultEndpointData_createWriterPool(
                epd,
                endpoint_info,
            (PRESTypePluginGetSerializedSampleMaxSizeFunction)
                ::com::rti::chocolatefactory::generated::ChocolateRecipePlugin_get_serialized_sample_max_size, epd,
            (PRESTypePluginGetSerializedSampleSizeFunction)
            ::com::rti::chocolatefactory::generated::ChocolateRecipePlugin_get_serialized_sample_size,
            epd) == RTI_FALSE) {
            PRESTypePluginDefaultEndpointData_delete(epd);
            return NULL;
        }
    }
    


    return epd;    
}


void 
ChocolateRecipePlugin_on_endpoint_detached(
    PRESTypePluginEndpointData endpoint_data)
{  

    PRESTypePluginDefaultEndpointData_delete(endpoint_data);
}


void    
ChocolateRecipePlugin_return_sample(
    PRESTypePluginEndpointData endpoint_data,
    ChocolateRecipe *sample,
    void *handle)
{
    
    ChocolateRecipe_finalize_optional_members(sample, RTI_TRUE);
           
    PRESTypePluginDefaultEndpointData_returnSample(
        endpoint_data, sample, handle);
}
 


RTIBool 
ChocolateRecipePlugin_copy_sample(
    PRESTypePluginEndpointData endpoint_data,
    ChocolateRecipe *dst,
    const ChocolateRecipe *src)
{
    if (endpoint_data) {} /* To avoid warnings */
    return ::com::rti::chocolatefactory::generated::ChocolateRecipePluginSupport_copy_data(dst,src);
}

/* --------------------------------------------------------------------------------------
    (De)Serialize functions:
 * -------------------------------------------------------------------------------------- */

unsigned int 
ChocolateRecipePlugin_get_serialized_sample_max_size(
    PRESTypePluginEndpointData endpoint_data,
    RTIBool include_encapsulation,
    RTIEncapsulationId encapsulation_id,
    unsigned int current_alignment);


RTIBool 
ChocolateRecipePlugin_serialize(
    PRESTypePluginEndpointData endpoint_data,
    const ChocolateRecipe *sample, 
    struct RTICdrStream *stream,    
    RTIBool serialize_encapsulation,
    RTIEncapsulationId encapsulation_id,
    RTIBool serialize_sample, 
    void *endpoint_plugin_qos)
{
    char * position = NULL;
    RTIBool retval = RTI_TRUE;

    if (endpoint_data) {} /* To avoid warnings */
    if (endpoint_plugin_qos) {} /* To avoid warnings */


    if(serialize_encapsulation) {
  
        if (!RTICdrStream_serializeAndSetCdrEncapsulation(stream, encapsulation_id)) {
            return RTI_FALSE;
        }

        position = RTICdrStream_resetAlignment(stream);

    }


    if(serialize_sample) {
    
    if (!RTICdrStream_serializeString(
        stream, sample->recipeName, ((com::rti::chocolatefactory::generated::MAX_STRING_LENGTH)) + 1)) {
        return RTI_FALSE;
    }
            

    if (com::rti::chocolatefactory::generated::RecipeStepSeq_get_contiguous_bufferI(&sample->steps) != NULL) {
        if (!RTICdrStream_serializeNonPrimitiveSequence(
            stream,
            com::rti::chocolatefactory::generated::RecipeStepSeq_get_contiguous_bufferI(&sample->steps),
            com::rti::chocolatefactory::generated::RecipeStepSeq_get_length(&sample->steps),
            ((com::rti::chocolatefactory::generated::MAX_RECIPE_STEPS)),
            sizeof(com::rti::chocolatefactory::generated::RecipeStep),
            (RTICdrStreamSerializeFunction)com::rti::chocolatefactory::generated::RecipeStepPlugin_serialize,
            RTI_FALSE, encapsulation_id,RTI_TRUE,
            endpoint_data,endpoint_plugin_qos)) {
            return RTI_FALSE;
        }
    } else {
        if (!RTICdrStream_serializeNonPrimitivePointerSequence(
            stream,
            (const void **)com::rti::chocolatefactory::generated::RecipeStepSeq_get_discontiguous_bufferI(&sample->steps),
            com::rti::chocolatefactory::generated::RecipeStepSeq_get_length(&sample->steps),
            ((com::rti::chocolatefactory::generated::MAX_RECIPE_STEPS)),
            (RTICdrStreamSerializeFunction)com::rti::chocolatefactory::generated::RecipeStepPlugin_serialize,
            RTI_FALSE, encapsulation_id,RTI_TRUE,
            endpoint_data,endpoint_plugin_qos)) {
            return RTI_FALSE;
        }
    }
            

    }


    if(serialize_encapsulation) {
        RTICdrStream_restoreAlignment(stream,position);
    }


  return retval;
}


RTIBool 
ChocolateRecipePlugin_deserialize_sample(
    PRESTypePluginEndpointData endpoint_data,
    ChocolateRecipe *sample,
    struct RTICdrStream *stream,   
    RTIBool deserialize_encapsulation,
    RTIBool deserialize_sample, 
    void *endpoint_plugin_qos)
{
    char * position = NULL;

    RTIBool done = RTI_FALSE;

    if (endpoint_data) {} /* To avoid warnings */
    if (endpoint_plugin_qos) {} /* To avoid warnings */


    if(deserialize_encapsulation) {
        /* Deserialize encapsulation */
        if (!RTICdrStream_deserializeAndSetCdrEncapsulation(stream)) {
            return RTI_FALSE;
        }

        position = RTICdrStream_resetAlignment(stream);

    }
    
    
    if(deserialize_sample) {
        ::com::rti::chocolatefactory::generated::ChocolateRecipe_initialize_ex(sample, RTI_FALSE, RTI_FALSE);
    
    if (!RTICdrStream_deserializeString(
        stream, sample->recipeName, ((com::rti::chocolatefactory::generated::MAX_STRING_LENGTH)) + 1)) {
        goto fin;
    }
            

    {
        RTICdrUnsignedLong sequence_length;

        if (com::rti::chocolatefactory::generated::RecipeStepSeq_get_contiguous_bufferI(&sample->steps) != NULL) {
            if (!RTICdrStream_deserializeNonPrimitiveSequence(
                stream,
                com::rti::chocolatefactory::generated::RecipeStepSeq_get_contiguous_bufferI(&sample->steps),
                &sequence_length,
                com::rti::chocolatefactory::generated::RecipeStepSeq_get_maximum(&sample->steps),
                sizeof(com::rti::chocolatefactory::generated::RecipeStep),
                (RTICdrStreamDeserializeFunction)com::rti::chocolatefactory::generated::RecipeStepPlugin_deserialize_sample,
                RTI_FALSE,RTI_TRUE,
                endpoint_data,endpoint_plugin_qos)) {
                goto fin;
            }
        } else {
            if (!RTICdrStream_deserializeNonPrimitivePointerSequence(
                stream,
                (void **)com::rti::chocolatefactory::generated::RecipeStepSeq_get_discontiguous_bufferI(&sample->steps),
                &sequence_length,
                com::rti::chocolatefactory::generated::RecipeStepSeq_get_maximum(&sample->steps),
                (RTICdrStreamDeserializeFunction)com::rti::chocolatefactory::generated::RecipeStepPlugin_deserialize_sample,
                RTI_FALSE,RTI_TRUE,
                endpoint_data,endpoint_plugin_qos)) {
                goto fin;
            }
        }
        if (!com::rti::chocolatefactory::generated::RecipeStepSeq_set_length(
            &sample->steps, sequence_length)) {
            return RTI_FALSE;
        }
    }
            

    }

    done = RTI_TRUE;
fin:
    if (done != RTI_TRUE && 
        RTICdrStream_getRemainder(stream) >=
            RTI_CDR_PARAMETER_HEADER_ALIGNMENT) {
        return RTI_FALSE;   
    }

    if(deserialize_encapsulation) {
        RTICdrStream_restoreAlignment(stream,position);
    }


    return RTI_TRUE;
}

 
 

RTIBool 
ChocolateRecipePlugin_deserialize(
    PRESTypePluginEndpointData endpoint_data,
    ChocolateRecipe **sample,
    RTIBool * drop_sample,
    struct RTICdrStream *stream,   
    RTIBool deserialize_encapsulation,
    RTIBool deserialize_sample, 
    void *endpoint_plugin_qos)
{

    RTIBool result;
    if (drop_sample) {} /* To avoid warnings */
    
    stream->_xTypesState.unassignable = RTI_FALSE;

    result = ::com::rti::chocolatefactory::generated::ChocolateRecipePlugin_deserialize_sample( 
        endpoint_data, (sample != NULL)?*sample:NULL,
        stream, deserialize_encapsulation, deserialize_sample, 
        endpoint_plugin_qos);
        
    if (result) {
        if (stream->_xTypesState.unassignable) {
            result = RTI_FALSE;
        }
    }
    
    return result;
 
}




RTIBool ChocolateRecipePlugin_skip(
    PRESTypePluginEndpointData endpoint_data,
    struct RTICdrStream *stream,   
    RTIBool skip_encapsulation,
    RTIBool skip_sample, 
    void *endpoint_plugin_qos)
{
    char * position = NULL;

    RTIBool done = RTI_FALSE;

    if (endpoint_data) {} /* To avoid warnings */
    if (endpoint_plugin_qos) {} /* To avoid warnings */


    if(skip_encapsulation) {
        if (!RTICdrStream_skipEncapsulation(stream)) {
            return RTI_FALSE;
        }


        position = RTICdrStream_resetAlignment(stream);

    }

    if (skip_sample) {

    if (!RTICdrStream_skipString(stream, ((com::rti::chocolatefactory::generated::MAX_STRING_LENGTH)) + 1)) {
        goto fin;
    }
            

    {
        RTICdrUnsignedLong sequence_length;

        if (!RTICdrStream_skipNonPrimitiveSequence(
            stream,
            &sequence_length,
            sizeof(com::rti::chocolatefactory::generated::RecipeStep),
            (RTICdrStreamSkipFunction)com::rti::chocolatefactory::generated::RecipeStepPlugin_skip,
            RTI_FALSE,RTI_TRUE,
            endpoint_data,endpoint_plugin_qos)) {
            goto fin;
        }
    }
            


    }
    

    done = RTI_TRUE;
fin:
    if (done != RTI_TRUE && 
        RTICdrStream_getRemainder(stream) >=
            RTI_CDR_PARAMETER_HEADER_ALIGNMENT) {
        return RTI_FALSE;   
    }

    if(skip_encapsulation) {
        RTICdrStream_restoreAlignment(stream,position);
    }


    return RTI_TRUE;
}


unsigned int 
ChocolateRecipePlugin_get_serialized_sample_max_size(
    PRESTypePluginEndpointData endpoint_data,
    RTIBool include_encapsulation,
    RTIEncapsulationId encapsulation_id,
    unsigned int current_alignment)
{

    unsigned int initial_alignment = current_alignment;

    unsigned int encapsulation_size = current_alignment;

    if (endpoint_data) {} /* To avoid warnings */


    if (include_encapsulation) {

        if (!RTICdrEncapsulation_validEncapsulationId(encapsulation_id)) {
            return 1;
        }

        RTICdrStream_getEncapsulationSize(encapsulation_size);
        encapsulation_size -= current_alignment;
        current_alignment = 0;
        initial_alignment = 0;

    }


    current_alignment +=  RTICdrType_getStringMaxSizeSerialized(
        current_alignment, ((com::rti::chocolatefactory::generated::MAX_STRING_LENGTH)) + 1);
            

    current_alignment +=  RTICdrType_getNonPrimitiveSequenceMaxSizeSerialized(
        current_alignment, ((com::rti::chocolatefactory::generated::MAX_RECIPE_STEPS)),
        com::rti::chocolatefactory::generated::RecipeStepPlugin_get_serialized_sample_max_size,RTI_FALSE,encapsulation_id,endpoint_data);
            

    if (include_encapsulation) {
        current_alignment += encapsulation_size;
    }

    return current_alignment - initial_alignment;
}


unsigned int 
ChocolateRecipePlugin_get_serialized_sample_min_size(
    PRESTypePluginEndpointData endpoint_data,
    RTIBool include_encapsulation,
    RTIEncapsulationId encapsulation_id,
    unsigned int current_alignment)
{

    unsigned int initial_alignment = current_alignment;

    unsigned int encapsulation_size = current_alignment;

    if (endpoint_data) {} /* To avoid warnings */


    if (include_encapsulation) {

        if (!RTICdrEncapsulation_validEncapsulationId(encapsulation_id)) {
            return 1;
        }

        RTICdrStream_getEncapsulationSize(encapsulation_size);
        encapsulation_size -= current_alignment;
        current_alignment = 0;
        initial_alignment = 0;

    }


    current_alignment +=  RTICdrType_getStringMaxSizeSerialized(
        current_alignment, 1);
            

    current_alignment +=  RTICdrType_getNonPrimitiveSequenceMaxSizeSerialized(
        current_alignment, 0,
        com::rti::chocolatefactory::generated::RecipeStepPlugin_get_serialized_sample_min_size,RTI_FALSE,encapsulation_id,endpoint_data);
            

    if (include_encapsulation) {
        current_alignment += encapsulation_size;
    }

    return current_alignment - initial_alignment;
}


/* Returns the size of the sample in its serialized form (in bytes).
 * It can also be an estimation in excess of the real buffer needed 
 * during a call to the serialize() function.
 * The value reported does not have to include the space for the
 * encapsulation flags.
 */
unsigned int
ChocolateRecipePlugin_get_serialized_sample_size(
    PRESTypePluginEndpointData endpoint_data,
    RTIBool include_encapsulation,
    RTIEncapsulationId encapsulation_id,
    unsigned int current_alignment,
    const ChocolateRecipe * sample) 
{

    unsigned int initial_alignment = current_alignment;

    unsigned int encapsulation_size = current_alignment;

    if (endpoint_data) {} /* To avoid warnings */
    if (sample) {} /* To avoid warnings */


    if (include_encapsulation) {

        if (!RTICdrEncapsulation_validEncapsulationId(encapsulation_id)) {
            return 1;
        }

        RTICdrStream_getEncapsulationSize(encapsulation_size);
        encapsulation_size -= current_alignment;
        current_alignment = 0;
        initial_alignment = 0;

    }


    current_alignment += RTICdrType_getStringSerializedSize(
        current_alignment, sample->recipeName);
            

    if (com::rti::chocolatefactory::generated::RecipeStepSeq_get_contiguous_bufferI(&sample->steps) != NULL) {
        current_alignment += RTICdrStream_getNonPrimitiveSequenceSerializedSize(
            current_alignment, com::rti::chocolatefactory::generated::RecipeStepSeq_get_length(&sample->steps),
            sizeof(com::rti::chocolatefactory::generated::RecipeStep),
            (RTICdrTypeGetSerializedSampleSizeFunction)com::rti::chocolatefactory::generated::RecipeStepPlugin_get_serialized_sample_size,
            RTI_FALSE,encapsulation_id,
            com::rti::chocolatefactory::generated::RecipeStepSeq_get_contiguous_bufferI(&sample->steps),
            endpoint_data);
    } else {
        current_alignment += RTICdrStream_getNonPrimitivePointerSequenceSerializedSize(
            current_alignment, com::rti::chocolatefactory::generated::RecipeStepSeq_get_length(&sample->steps),
            sizeof(com::rti::chocolatefactory::generated::RecipeStep),
            (RTICdrTypeGetSerializedSampleSizeFunction)com::rti::chocolatefactory::generated::RecipeStepPlugin_get_serialized_sample_size,
            RTI_FALSE,encapsulation_id,
            (const void **)com::rti::chocolatefactory::generated::RecipeStepSeq_get_discontiguous_bufferI(&sample->steps),
            endpoint_data);
    }
            

    if (include_encapsulation) {
        current_alignment += encapsulation_size;
    }

    return current_alignment - initial_alignment;
}







/* --------------------------------------------------------------------------------------
    Key Management functions:
 * -------------------------------------------------------------------------------------- */


PRESTypePluginKeyKind 
ChocolateRecipePlugin_get_key_kind(void)
{

    return PRES_TYPEPLUGIN_USER_KEY;
     
}


RTIBool 
ChocolateRecipePlugin_serialize_key(
    PRESTypePluginEndpointData endpoint_data,
    const ChocolateRecipe *sample, 
    struct RTICdrStream *stream,    
    RTIBool serialize_encapsulation,
    RTIEncapsulationId encapsulation_id,
    RTIBool serialize_key,
    void *endpoint_plugin_qos)
{
    char * position = NULL;

    if (endpoint_data) {} /* To avoid warnings */
    if (endpoint_plugin_qos) {} /* To avoid warnings */


    if(serialize_encapsulation) {
    
        if (!RTICdrStream_serializeAndSetCdrEncapsulation(stream, encapsulation_id)) {
            return RTI_FALSE;
        }


        position = RTICdrStream_resetAlignment(stream);

    }

    if(serialize_key) {

    if (!RTICdrStream_serializeString(
        stream, sample->recipeName, ((com::rti::chocolatefactory::generated::MAX_STRING_LENGTH)) + 1)) {
        return RTI_FALSE;
    }
            

    }


    if(serialize_encapsulation) {
        RTICdrStream_restoreAlignment(stream,position);
    }


    return RTI_TRUE;
}


RTIBool ChocolateRecipePlugin_deserialize_key_sample(
    PRESTypePluginEndpointData endpoint_data,
    ChocolateRecipe *sample, 
    struct RTICdrStream *stream,
    RTIBool deserialize_encapsulation,
    RTIBool deserialize_key,
    void *endpoint_plugin_qos)
{
    char * position = NULL;

    if (endpoint_data) {} /* To avoid warnings */
    if (endpoint_plugin_qos) {} /* To avoid warnings */


    if(deserialize_encapsulation) {
        /* Deserialize encapsulation */
        if (!RTICdrStream_deserializeAndSetCdrEncapsulation(stream)) {
            return RTI_FALSE;  
        }


        position = RTICdrStream_resetAlignment(stream);

    }

    if (deserialize_key) {

    if (!RTICdrStream_deserializeString(
        stream, sample->recipeName, ((com::rti::chocolatefactory::generated::MAX_STRING_LENGTH)) + 1)) {
        return RTI_FALSE;
    }
            

    }


    if(deserialize_encapsulation) {
        RTICdrStream_restoreAlignment(stream,position);
    }


    return RTI_TRUE;
}


 
RTIBool ChocolateRecipePlugin_deserialize_key(
    PRESTypePluginEndpointData endpoint_data,
    ChocolateRecipe **sample, 
    RTIBool * drop_sample,
    struct RTICdrStream *stream,
    RTIBool deserialize_encapsulation,
    RTIBool deserialize_key,
    void *endpoint_plugin_qos)
{
    RTIBool result;
    if (drop_sample) {} /* To avoid warnings */
    
    stream->_xTypesState.unassignable = RTI_FALSE;
    
    result = ::com::rti::chocolatefactory::generated::ChocolateRecipePlugin_deserialize_key_sample(
        endpoint_data, (sample != NULL)?*sample:NULL, stream,
        deserialize_encapsulation, deserialize_key, endpoint_plugin_qos);
        
    if (result) {
        if (stream->_xTypesState.unassignable) {
            result = RTI_FALSE;
        }
    }
    
    return result;
}



unsigned int
ChocolateRecipePlugin_get_serialized_key_max_size(
    PRESTypePluginEndpointData endpoint_data,
    RTIBool include_encapsulation,
    RTIEncapsulationId encapsulation_id,
    unsigned int current_alignment)
{

    unsigned int encapsulation_size = current_alignment;


    unsigned int initial_alignment = current_alignment;


    if (endpoint_data) {} /* To avoid warnings */


    if (include_encapsulation) {
        if (!RTICdrEncapsulation_validEncapsulationId(encapsulation_id)) {
            return 1;
        }


        RTICdrStream_getEncapsulationSize(encapsulation_size);
        encapsulation_size -= current_alignment;
        current_alignment = 0;
        initial_alignment = 0;

    }
        

    current_alignment +=  RTICdrType_getStringMaxSizeSerialized(
        current_alignment, ((com::rti::chocolatefactory::generated::MAX_STRING_LENGTH)) + 1);
            

    if (include_encapsulation) {
        current_alignment += encapsulation_size;
    }

    return current_alignment - initial_alignment;
}


RTIBool 
ChocolateRecipePlugin_serialized_sample_to_key(
    PRESTypePluginEndpointData endpoint_data,
    ChocolateRecipe *sample,
    struct RTICdrStream *stream, 
    RTIBool deserialize_encapsulation,  
    RTIBool deserialize_key, 
    void *endpoint_plugin_qos)
{
    char * position = NULL;

    RTIBool done = RTI_FALSE;

    if (endpoint_data) {} /* To avoid warnings */
    if (endpoint_plugin_qos) {} /* To avoid warnings */

    if (stream == NULL) goto fin; /* To avoid warnings */


    if(deserialize_encapsulation) {
        if (!RTICdrStream_deserializeAndSetCdrEncapsulation(stream)) {
            return RTI_FALSE;
        }

        position = RTICdrStream_resetAlignment(stream);

    }

    if (deserialize_key) {

    if (!RTICdrStream_deserializeString(
        stream, sample->recipeName, ((com::rti::chocolatefactory::generated::MAX_STRING_LENGTH)) + 1)) {
        return RTI_FALSE;
    }
            

    {
        RTICdrUnsignedLong sequence_length;

        if (!RTICdrStream_skipNonPrimitiveSequence(
            stream,
            &sequence_length,
            sizeof(com::rti::chocolatefactory::generated::RecipeStep),
            (RTICdrStreamSkipFunction)com::rti::chocolatefactory::generated::RecipeStepPlugin_skip,
            RTI_FALSE,RTI_TRUE,
            endpoint_data,endpoint_plugin_qos)) {
            goto fin;
        }
    }
            

    }


    done = RTI_TRUE;
fin:
    if (done != RTI_TRUE && 
        RTICdrStream_getRemainder(stream) >=
            RTI_CDR_PARAMETER_HEADER_ALIGNMENT) {
        return RTI_FALSE;   
    }

    if(deserialize_encapsulation) {
        RTICdrStream_restoreAlignment(stream,position);
    }


    return RTI_TRUE;
}





RTIBool 
ChocolateRecipePlugin_instance_to_key(
    PRESTypePluginEndpointData endpoint_data,
    ChocolateRecipeKeyHolder *dst, 
    const ChocolateRecipe *src)
{  

    if (endpoint_data) {} /* To avoid warnings */

    if (!RTICdrType_copyString(
        dst->recipeName, src->recipeName, ((com::rti::chocolatefactory::generated::MAX_STRING_LENGTH)) + 1)) {
        return RTI_FALSE;
    }
            

    return RTI_TRUE;
}


RTIBool 
ChocolateRecipePlugin_key_to_instance(
    PRESTypePluginEndpointData endpoint_data,
    ChocolateRecipe *dst, const
    ChocolateRecipeKeyHolder *src)
{

    if (endpoint_data) {} /* To avoid warnings */

    if (!RTICdrType_copyString(
        dst->recipeName, src->recipeName, ((com::rti::chocolatefactory::generated::MAX_STRING_LENGTH)) + 1)) {
        return RTI_FALSE;
    }
            

    return RTI_TRUE;
}


RTIBool 
ChocolateRecipePlugin_instance_to_keyhash(
    PRESTypePluginEndpointData endpoint_data,
    DDS_KeyHash_t *keyhash,
    const ChocolateRecipe *instance)
{
    struct RTICdrStream * md5Stream = NULL;

    md5Stream = PRESTypePluginDefaultEndpointData_getMD5Stream(endpoint_data);

    if (md5Stream == NULL) {
        return RTI_FALSE;
    }

    RTIOsapiMemory_zero(
        RTICdrStream_getBuffer(md5Stream),
        RTICdrStream_getBufferLength(md5Stream));
    RTICdrStream_resetPosition(md5Stream);
    RTICdrStream_setDirtyBit(md5Stream, RTI_TRUE);

    if (!::com::rti::chocolatefactory::generated::ChocolateRecipePlugin_serialize_key(
            endpoint_data,instance,md5Stream, RTI_FALSE, RTI_CDR_ENCAPSULATION_ID_CDR_BE, RTI_TRUE,NULL)) {
        return RTI_FALSE;
    }
    
    if (PRESTypePluginDefaultEndpointData_getMaxSizeSerializedKey(endpoint_data) > (unsigned int)(MIG_RTPS_KEY_HASH_MAX_LENGTH)) {
        RTICdrStream_computeMD5(md5Stream, keyhash->value);
    } else {
        RTIOsapiMemory_zero(keyhash->value,MIG_RTPS_KEY_HASH_MAX_LENGTH);
        RTIOsapiMemory_copy(
            keyhash->value, 
            RTICdrStream_getBuffer(md5Stream), 
            RTICdrStream_getCurrentPositionOffset(md5Stream));
    }

    keyhash->length = MIG_RTPS_KEY_HASH_MAX_LENGTH;
    return RTI_TRUE;
}


RTIBool 
ChocolateRecipePlugin_serialized_sample_to_keyhash(
    PRESTypePluginEndpointData endpoint_data,
    struct RTICdrStream *stream, 
    DDS_KeyHash_t *keyhash,
    RTIBool deserialize_encapsulation,
    void *endpoint_plugin_qos) 
{   
    char * position = NULL;

    RTIBool done = RTI_FALSE;
    ChocolateRecipe * sample = NULL;

    if (endpoint_plugin_qos) {} /* To avoid warnings */


    if (stream == NULL) goto fin; /* To avoid warnings */


    if(deserialize_encapsulation) {
        if (!RTICdrStream_deserializeAndSetCdrEncapsulation(stream)) {
            return RTI_FALSE;
        }

        position = RTICdrStream_resetAlignment(stream);
    }


    sample = (ChocolateRecipe *)
                PRESTypePluginDefaultEndpointData_getTempSample(endpoint_data);

    if (sample == NULL) {
        return RTI_FALSE;
    }


    if (!RTICdrStream_deserializeString(
        stream, sample->recipeName, ((com::rti::chocolatefactory::generated::MAX_STRING_LENGTH)) + 1)) {
        return RTI_FALSE;
    }
            

    done = RTI_TRUE;
fin:
    if (done != RTI_TRUE && 
        RTICdrStream_getRemainder(stream) >=
            RTI_CDR_PARAMETER_HEADER_ALIGNMENT) {
        return RTI_FALSE;   
    }

    if(deserialize_encapsulation) {
        RTICdrStream_restoreAlignment(stream,position);
    }


    if (!::com::rti::chocolatefactory::generated::ChocolateRecipePlugin_instance_to_keyhash(
            endpoint_data, keyhash, sample)) {
        return RTI_FALSE;
    }

    return RTI_TRUE;
}


/* ------------------------------------------------------------------------
 * Plug-in Installation Methods
 * ------------------------------------------------------------------------ */
 
struct PRESTypePlugin *ChocolateRecipePlugin_new(void) 
{ 
    struct PRESTypePlugin *plugin = NULL;
    const struct PRESTypePluginVersion PLUGIN_VERSION = 
        PRES_TYPE_PLUGIN_VERSION_2_0;

    RTIOsapiHeap_allocateStructure(
        &plugin, struct PRESTypePlugin);
    if (plugin == NULL) {
       return NULL;
    }

    plugin->version = PLUGIN_VERSION;

    /* set up parent's function pointers */
    plugin->onParticipantAttached =
        (PRESTypePluginOnParticipantAttachedCallback)
        ::com::rti::chocolatefactory::generated::ChocolateRecipePlugin_on_participant_attached;
    plugin->onParticipantDetached =
        (PRESTypePluginOnParticipantDetachedCallback)
        ::com::rti::chocolatefactory::generated::ChocolateRecipePlugin_on_participant_detached;
    plugin->onEndpointAttached =
        (PRESTypePluginOnEndpointAttachedCallback)
        ::com::rti::chocolatefactory::generated::ChocolateRecipePlugin_on_endpoint_attached;
    plugin->onEndpointDetached =
        (PRESTypePluginOnEndpointDetachedCallback)
        ::com::rti::chocolatefactory::generated::ChocolateRecipePlugin_on_endpoint_detached;

    plugin->copySampleFnc =
        (PRESTypePluginCopySampleFunction)
        ::com::rti::chocolatefactory::generated::ChocolateRecipePlugin_copy_sample;
    plugin->createSampleFnc =
        (PRESTypePluginCreateSampleFunction)
        ChocolateRecipePlugin_create_sample;
    plugin->destroySampleFnc =
        (PRESTypePluginDestroySampleFunction)
        ChocolateRecipePlugin_destroy_sample;

    plugin->serializeFnc =
        (PRESTypePluginSerializeFunction)
        ::com::rti::chocolatefactory::generated::ChocolateRecipePlugin_serialize;
    plugin->deserializeFnc =
        (PRESTypePluginDeserializeFunction)
        ::com::rti::chocolatefactory::generated::ChocolateRecipePlugin_deserialize;
    plugin->getSerializedSampleMaxSizeFnc =
        (PRESTypePluginGetSerializedSampleMaxSizeFunction)
        ::com::rti::chocolatefactory::generated::ChocolateRecipePlugin_get_serialized_sample_max_size;
    plugin->getSerializedSampleMinSizeFnc =
        (PRESTypePluginGetSerializedSampleMinSizeFunction)
        ::com::rti::chocolatefactory::generated::ChocolateRecipePlugin_get_serialized_sample_min_size;


    plugin->getSampleFnc =
        (PRESTypePluginGetSampleFunction)
        ChocolateRecipePlugin_get_sample;
    plugin->returnSampleFnc =
        (PRESTypePluginReturnSampleFunction)
        ChocolateRecipePlugin_return_sample;

    plugin->getKeyKindFnc =
        (PRESTypePluginGetKeyKindFunction)
        ::com::rti::chocolatefactory::generated::ChocolateRecipePlugin_get_key_kind;


    plugin->getSerializedKeyMaxSizeFnc =   
        (PRESTypePluginGetSerializedKeyMaxSizeFunction)
        ::com::rti::chocolatefactory::generated::ChocolateRecipePlugin_get_serialized_key_max_size;
    plugin->serializeKeyFnc =
        (PRESTypePluginSerializeKeyFunction)
        ::com::rti::chocolatefactory::generated::ChocolateRecipePlugin_serialize_key;
    plugin->deserializeKeyFnc =
        (PRESTypePluginDeserializeKeyFunction)
        ::com::rti::chocolatefactory::generated::ChocolateRecipePlugin_deserialize_key;
    plugin->deserializeKeySampleFnc =
        (PRESTypePluginDeserializeKeySampleFunction)
        ::com::rti::chocolatefactory::generated::ChocolateRecipePlugin_deserialize_key_sample;

    plugin->instanceToKeyHashFnc = 
        (PRESTypePluginInstanceToKeyHashFunction)
        ::com::rti::chocolatefactory::generated::ChocolateRecipePlugin_instance_to_keyhash;
    plugin->serializedSampleToKeyHashFnc = 
        (PRESTypePluginSerializedSampleToKeyHashFunction)
        ::com::rti::chocolatefactory::generated::ChocolateRecipePlugin_serialized_sample_to_keyhash;

    plugin->getKeyFnc =
        (PRESTypePluginGetKeyFunction)
        ChocolateRecipePlugin_get_key;
    plugin->returnKeyFnc =
        (PRESTypePluginReturnKeyFunction)
        ChocolateRecipePlugin_return_key;

    plugin->instanceToKeyFnc =
        (PRESTypePluginInstanceToKeyFunction)
        ::com::rti::chocolatefactory::generated::ChocolateRecipePlugin_instance_to_key;
    plugin->keyToInstanceFnc =
        (PRESTypePluginKeyToInstanceFunction)
        ::com::rti::chocolatefactory::generated::ChocolateRecipePlugin_key_to_instance;
    plugin->serializedKeyToKeyHashFnc = NULL; /* Not supported yet */
    
    plugin->typeCode =  (struct RTICdrTypeCode *)::com::rti::chocolatefactory::generated::ChocolateRecipe_get_typecode();
    
    plugin->languageKind = PRES_TYPEPLUGIN_DDS_TYPE; 

    /* Serialized buffer */
    plugin->getBuffer = 
        (PRESTypePluginGetBufferFunction)
        ChocolateRecipePlugin_get_buffer;
    plugin->returnBuffer = 
        (PRESTypePluginReturnBufferFunction)
        ChocolateRecipePlugin_return_buffer;
    plugin->getSerializedSampleSizeFnc =
        (PRESTypePluginGetSerializedSampleSizeFunction)
        ::com::rti::chocolatefactory::generated::ChocolateRecipePlugin_get_serialized_sample_size;

    plugin->endpointTypeName = ChocolateRecipeTYPENAME;

    return plugin;
}

void
ChocolateRecipePlugin_delete(struct PRESTypePlugin *plugin)
{
    RTIOsapiHeap_freeStructure(plugin);
} 

/* --------------------------------------------------------------------------------------
 *  Type ChocolateLotState
 * -------------------------------------------------------------------------------------- */

/* --------------------------------------------------------------------------------------
    Support functions:
 * -------------------------------------------------------------------------------------- */

ChocolateLotState*
ChocolateLotStatePluginSupport_create_data_w_params(
    const struct DDS_TypeAllocationParams_t * alloc_params){
    ChocolateLotState *sample = NULL;

    RTIOsapiHeap_allocateStructure(
        &sample, ChocolateLotState);

    if(sample != NULL) {
        if (!::com::rti::chocolatefactory::generated::ChocolateLotState_initialize_w_params(sample,alloc_params)) {
            RTIOsapiHeap_freeStructure(sample);
            return NULL;
        }
    }        
    return sample; 
}


ChocolateLotState *
ChocolateLotStatePluginSupport_create_data_ex(RTIBool allocate_pointers){
    ChocolateLotState *sample = NULL;

    RTIOsapiHeap_allocateStructure(
        &sample, ChocolateLotState);

    if(sample != NULL) {
        if (!::com::rti::chocolatefactory::generated::ChocolateLotState_initialize_ex(sample,allocate_pointers, RTI_TRUE)) {
            RTIOsapiHeap_freeStructure(sample);
            return NULL;
        }
    }        
    return sample; 
}


ChocolateLotState *
ChocolateLotStatePluginSupport_create_data(void)
{
    return ::com::rti::chocolatefactory::generated::ChocolateLotStatePluginSupport_create_data_ex(RTI_TRUE);
}


void 
ChocolateLotStatePluginSupport_destroy_data_w_params(
    ChocolateLotState *sample,
    const struct DDS_TypeDeallocationParams_t * dealloc_params) {

    ::com::rti::chocolatefactory::generated::ChocolateLotState_finalize_w_params(sample,dealloc_params);

    RTIOsapiHeap_freeStructure(sample);
}


void 
ChocolateLotStatePluginSupport_destroy_data_ex(
    ChocolateLotState *sample,RTIBool deallocate_pointers) {

    ::com::rti::chocolatefactory::generated::ChocolateLotState_finalize_ex(sample,deallocate_pointers);

    RTIOsapiHeap_freeStructure(sample);
}


void 
ChocolateLotStatePluginSupport_destroy_data(
    ChocolateLotState *sample) {

    ::com::rti::chocolatefactory::generated::ChocolateLotStatePluginSupport_destroy_data_ex(sample,RTI_TRUE);

}


RTIBool 
ChocolateLotStatePluginSupport_copy_data(
    ChocolateLotState *dst,
    const ChocolateLotState *src)
{
    return ::com::rti::chocolatefactory::generated::ChocolateLotState_copy(dst,src);
}


void 
ChocolateLotStatePluginSupport_print_data(
    const ChocolateLotState *sample,
    const char *desc,
    unsigned int indent_level)
{


    RTICdrType_printIndent(indent_level);

    if (desc != NULL) {
      RTILog_debug("%s:\n", desc);
    } else {
      RTILog_debug("\n");
    }

    if (sample == NULL) {
      RTILog_debug("NULL\n");
      return;
    }


    RTICdrType_printLong(
        &sample->lotID, "lotID", indent_level + 1);
            

    com::rti::chocolatefactory::generated::StationControllerKindPluginSupport_print_data(
        &sample->controller, "controller", indent_level + 1);
            

    if (&sample->recipeName==NULL) {
        RTICdrType_printString(
            NULL, "recipeName", indent_level + 1);                
    } else {
        RTICdrType_printString(
            sample->recipeName, "recipeName", indent_level + 1);                
    }
            

    com::rti::chocolatefactory::generated::StationControllerKindPluginSupport_print_data(
        &sample->nextController, "nextController", indent_level + 1);
            

    com::rti::chocolatefactory::generated::LotStatusKindPluginSupport_print_data(
        &sample->lotStatus, "lotStatus", indent_level + 1);
            

    if (&sample->ingredients == NULL) {
        RTICdrType_printIndent(indent_level+1);
        RTILog_debug("ingredients: NULL\n");    
    } else {
                
        if (DDS_StringSeq_get_contiguous_bufferI(&sample->ingredients) != NULL) {
            RTICdrType_printStringArray(
                DDS_StringSeq_get_contiguous_bufferI(&sample->ingredients),
                DDS_StringSeq_get_length(&sample->ingredients),
                "ingredients", indent_level + 1,
                RTI_CDR_CHAR_TYPE);
        } else {
            RTICdrType_printStringPointerArray(
                DDS_StringSeq_get_discontiguous_bufferI(&sample->ingredients),
                DDS_StringSeq_get_length(&sample->ingredients),
                "ingredients", indent_level + 1,
                RTI_CDR_CHAR_TYPE);
        }
    
    }
            


}

ChocolateLotState *
ChocolateLotStatePluginSupport_create_key_ex(RTIBool allocate_pointers){
    ChocolateLotState *key = NULL;

    RTIOsapiHeap_allocateStructure(
        &key, ChocolateLotStateKeyHolder);

    ::com::rti::chocolatefactory::generated::ChocolateLotState_initialize_ex(key,allocate_pointers,RTI_TRUE);
    return key;
}


ChocolateLotState *
ChocolateLotStatePluginSupport_create_key(void)
{
    return  ::com::rti::chocolatefactory::generated::ChocolateLotStatePluginSupport_create_key_ex(RTI_TRUE);
}


void 
ChocolateLotStatePluginSupport_destroy_key_ex(
    ChocolateLotStateKeyHolder *key,RTIBool deallocate_pointers)
{
    ::com::rti::chocolatefactory::generated::ChocolateLotState_finalize_ex(key,deallocate_pointers);

    RTIOsapiHeap_freeStructure(key);
}


void 
ChocolateLotStatePluginSupport_destroy_key(
    ChocolateLotStateKeyHolder *key) {

  ::com::rti::chocolatefactory::generated::ChocolateLotStatePluginSupport_destroy_key_ex(key,RTI_TRUE);

}


/* ----------------------------------------------------------------------------
    Callback functions:
 * ---------------------------------------------------------------------------- */



PRESTypePluginParticipantData 
ChocolateLotStatePlugin_on_participant_attached(
    void *registration_data,
    const struct PRESTypePluginParticipantInfo *participant_info,
    RTIBool top_level_registration,
    void *container_plugin_context,
    RTICdrTypeCode *type_code)
{

    if (registration_data) {} /* To avoid warnings */
    if (participant_info) {} /* To avoid warnings */
    if (top_level_registration) {} /* To avoid warnings */
    if (container_plugin_context) {} /* To avoid warnings */
    if (type_code) {} /* To avoid warnings */
    return PRESTypePluginDefaultParticipantData_new(participant_info);

}


void 
ChocolateLotStatePlugin_on_participant_detached(
    PRESTypePluginParticipantData participant_data)
{

  PRESTypePluginDefaultParticipantData_delete(participant_data);
}


PRESTypePluginEndpointData
ChocolateLotStatePlugin_on_endpoint_attached(
    PRESTypePluginParticipantData participant_data,
    const struct PRESTypePluginEndpointInfo *endpoint_info,
    RTIBool top_level_registration, 
    void *containerPluginContext)
{
    PRESTypePluginEndpointData epd = NULL;

    unsigned int serializedSampleMaxSize;

    unsigned int serializedKeyMaxSize;

    if (top_level_registration) {} /* To avoid warnings */
    if (containerPluginContext) {} /* To avoid warnings */


    epd = PRESTypePluginDefaultEndpointData_new(
            participant_data,
            endpoint_info,
            (PRESTypePluginDefaultEndpointDataCreateSampleFunction)
            ::com::rti::chocolatefactory::generated::ChocolateLotStatePluginSupport_create_data,
            (PRESTypePluginDefaultEndpointDataDestroySampleFunction)
            ::com::rti::chocolatefactory::generated::ChocolateLotStatePluginSupport_destroy_data,
            (PRESTypePluginDefaultEndpointDataCreateKeyFunction)
            ::com::rti::chocolatefactory::generated::ChocolateLotStatePluginSupport_create_key,
            (PRESTypePluginDefaultEndpointDataDestroyKeyFunction)
            ::com::rti::chocolatefactory::generated::ChocolateLotStatePluginSupport_destroy_key);

    if (epd == NULL) {
        return NULL;
    }
   
    serializedKeyMaxSize = ::com::rti::chocolatefactory::generated::ChocolateLotStatePlugin_get_serialized_key_max_size(
        epd,RTI_FALSE,RTI_CDR_ENCAPSULATION_ID_CDR_BE,0);
    
    if (!PRESTypePluginDefaultEndpointData_createMD5Stream(
            epd,serializedKeyMaxSize)) 
    {
        PRESTypePluginDefaultEndpointData_delete(epd);
        return NULL;
    }
    
    

    if (endpoint_info->endpointKind == PRES_TYPEPLUGIN_ENDPOINT_WRITER) {
        serializedSampleMaxSize = ::com::rti::chocolatefactory::generated::ChocolateLotStatePlugin_get_serialized_sample_max_size(
            epd,RTI_FALSE,RTI_CDR_ENCAPSULATION_ID_CDR_BE,0);
            
        PRESTypePluginDefaultEndpointData_setMaxSizeSerializedSample(epd, serializedSampleMaxSize);

        if (PRESTypePluginDefaultEndpointData_createWriterPool(
                epd,
                endpoint_info,
            (PRESTypePluginGetSerializedSampleMaxSizeFunction)
                ::com::rti::chocolatefactory::generated::ChocolateLotStatePlugin_get_serialized_sample_max_size, epd,
            (PRESTypePluginGetSerializedSampleSizeFunction)
            ::com::rti::chocolatefactory::generated::ChocolateLotStatePlugin_get_serialized_sample_size,
            epd) == RTI_FALSE) {
            PRESTypePluginDefaultEndpointData_delete(epd);
            return NULL;
        }
    }
    


    return epd;    
}


void 
ChocolateLotStatePlugin_on_endpoint_detached(
    PRESTypePluginEndpointData endpoint_data)
{  

    PRESTypePluginDefaultEndpointData_delete(endpoint_data);
}


void    
ChocolateLotStatePlugin_return_sample(
    PRESTypePluginEndpointData endpoint_data,
    ChocolateLotState *sample,
    void *handle)
{
    
    ChocolateLotState_finalize_optional_members(sample, RTI_TRUE);
           
    PRESTypePluginDefaultEndpointData_returnSample(
        endpoint_data, sample, handle);
}
 


RTIBool 
ChocolateLotStatePlugin_copy_sample(
    PRESTypePluginEndpointData endpoint_data,
    ChocolateLotState *dst,
    const ChocolateLotState *src)
{
    if (endpoint_data) {} /* To avoid warnings */
    return ::com::rti::chocolatefactory::generated::ChocolateLotStatePluginSupport_copy_data(dst,src);
}

/* --------------------------------------------------------------------------------------
    (De)Serialize functions:
 * -------------------------------------------------------------------------------------- */

unsigned int 
ChocolateLotStatePlugin_get_serialized_sample_max_size(
    PRESTypePluginEndpointData endpoint_data,
    RTIBool include_encapsulation,
    RTIEncapsulationId encapsulation_id,
    unsigned int current_alignment);


RTIBool 
ChocolateLotStatePlugin_serialize(
    PRESTypePluginEndpointData endpoint_data,
    const ChocolateLotState *sample, 
    struct RTICdrStream *stream,    
    RTIBool serialize_encapsulation,
    RTIEncapsulationId encapsulation_id,
    RTIBool serialize_sample, 
    void *endpoint_plugin_qos)
{
    char * position = NULL;
    RTIBool retval = RTI_TRUE;

    if (endpoint_data) {} /* To avoid warnings */
    if (endpoint_plugin_qos) {} /* To avoid warnings */


    if(serialize_encapsulation) {
  
        if (!RTICdrStream_serializeAndSetCdrEncapsulation(stream, encapsulation_id)) {
            return RTI_FALSE;
        }

        position = RTICdrStream_resetAlignment(stream);

    }


    if(serialize_sample) {
    
    if (!RTICdrStream_serializeLong(
        stream, &sample->lotID)) {
        return RTI_FALSE;
    }
            

    if (!com::rti::chocolatefactory::generated::StationControllerKindPlugin_serialize(
            endpoint_data,
            &sample->controller, 
            stream, 
            RTI_FALSE, encapsulation_id, 
            RTI_TRUE, 
            endpoint_plugin_qos)) {
        return RTI_FALSE;
    }
            

    if (!RTICdrStream_serializeString(
        stream, sample->recipeName, ((com::rti::chocolatefactory::generated::MAX_STRING_LENGTH)) + 1)) {
        return RTI_FALSE;
    }
            

    if (!com::rti::chocolatefactory::generated::StationControllerKindPlugin_serialize(
            endpoint_data,
            &sample->nextController, 
            stream, 
            RTI_FALSE, encapsulation_id, 
            RTI_TRUE, 
            endpoint_plugin_qos)) {
        return RTI_FALSE;
    }
            

    if (!com::rti::chocolatefactory::generated::LotStatusKindPlugin_serialize(
            endpoint_data,
            &sample->lotStatus, 
            stream, 
            RTI_FALSE, encapsulation_id, 
            RTI_TRUE, 
            endpoint_plugin_qos)) {
        return RTI_FALSE;
    }
            

    if (DDS_StringSeq_get_contiguous_bufferI(&sample->ingredients) != NULL) {
        if (!RTICdrStream_serializeStringSequence(
            stream,
            DDS_StringSeq_get_contiguous_bufferI(&sample->ingredients),
            DDS_StringSeq_get_length(&sample->ingredients),
            ((com::rti::chocolatefactory::generated::MAX_INGREDIENT_LIST)),
            ((com::rti::chocolatefactory::generated::MAX_STRING_LENGTH)) + 1,
            RTI_CDR_CHAR_TYPE)) {
            return RTI_FALSE;
        }
    } else {
        if (!RTICdrStream_serializeStringPointerSequence(
            stream,
            (const void **)DDS_StringSeq_get_discontiguous_bufferI(&sample->ingredients),
            DDS_StringSeq_get_length(&sample->ingredients),
            ((com::rti::chocolatefactory::generated::MAX_INGREDIENT_LIST)),
            ((com::rti::chocolatefactory::generated::MAX_STRING_LENGTH)) + 1,
            RTI_CDR_CHAR_TYPE)) {
            return RTI_FALSE;
        }
    }
            

    }


    if(serialize_encapsulation) {
        RTICdrStream_restoreAlignment(stream,position);
    }


  return retval;
}


RTIBool 
ChocolateLotStatePlugin_deserialize_sample(
    PRESTypePluginEndpointData endpoint_data,
    ChocolateLotState *sample,
    struct RTICdrStream *stream,   
    RTIBool deserialize_encapsulation,
    RTIBool deserialize_sample, 
    void *endpoint_plugin_qos)
{
    char * position = NULL;

    RTIBool done = RTI_FALSE;

    if (endpoint_data) {} /* To avoid warnings */
    if (endpoint_plugin_qos) {} /* To avoid warnings */


    if(deserialize_encapsulation) {
        /* Deserialize encapsulation */
        if (!RTICdrStream_deserializeAndSetCdrEncapsulation(stream)) {
            return RTI_FALSE;
        }

        position = RTICdrStream_resetAlignment(stream);

    }
    
    
    if(deserialize_sample) {
        ::com::rti::chocolatefactory::generated::ChocolateLotState_initialize_ex(sample, RTI_FALSE, RTI_FALSE);
    
    if (!RTICdrStream_deserializeLong(
        stream, &sample->lotID)) {
        goto fin;
    }

    if (!com::rti::chocolatefactory::generated::StationControllerKindPlugin_deserialize_sample(
            endpoint_data,
            &sample->controller,
            stream, 
            RTI_FALSE, RTI_TRUE, 
            endpoint_plugin_qos)) {
        goto fin;
    }
            

    if (!RTICdrStream_deserializeString(
        stream, sample->recipeName, ((com::rti::chocolatefactory::generated::MAX_STRING_LENGTH)) + 1)) {
        goto fin;
    }
            

    if (!com::rti::chocolatefactory::generated::StationControllerKindPlugin_deserialize_sample(
            endpoint_data,
            &sample->nextController,
            stream, 
            RTI_FALSE, RTI_TRUE, 
            endpoint_plugin_qos)) {
        goto fin;
    }
            

    if (!com::rti::chocolatefactory::generated::LotStatusKindPlugin_deserialize_sample(
            endpoint_data,
            &sample->lotStatus,
            stream, 
            RTI_FALSE, RTI_TRUE, 
            endpoint_plugin_qos)) {
        goto fin;
    }
            

    {
        RTICdrUnsignedLong sequence_length;

        if (DDS_StringSeq_get_contiguous_bufferI(&sample->ingredients) != NULL) {
            if (!RTICdrStream_deserializeStringSequence(
                stream,
                DDS_StringSeq_get_contiguous_bufferI(&sample->ingredients),
                &sequence_length,
                DDS_StringSeq_get_maximum(&sample->ingredients),
                ((com::rti::chocolatefactory::generated::MAX_STRING_LENGTH)) + 1,            
                RTI_CDR_CHAR_TYPE)){
                goto fin;
            }
        } else {
            if (!RTICdrStream_deserializeStringPointerSequence(
                stream,
                (void **)DDS_StringSeq_get_discontiguous_bufferI(&sample->ingredients),
                &sequence_length,
                DDS_StringSeq_get_maximum(&sample->ingredients),
                ((com::rti::chocolatefactory::generated::MAX_STRING_LENGTH)) + 1,            
                RTI_CDR_CHAR_TYPE)){
                goto fin;
            }
        }
        if (!DDS_StringSeq_set_length(&sample->ingredients, sequence_length)) {
            return RTI_FALSE;
        }                
    }
            

    }

    done = RTI_TRUE;
fin:
    if (done != RTI_TRUE && 
        RTICdrStream_getRemainder(stream) >=
            RTI_CDR_PARAMETER_HEADER_ALIGNMENT) {
        return RTI_FALSE;   
    }

    if(deserialize_encapsulation) {
        RTICdrStream_restoreAlignment(stream,position);
    }


    return RTI_TRUE;
}

 
 

RTIBool 
ChocolateLotStatePlugin_deserialize(
    PRESTypePluginEndpointData endpoint_data,
    ChocolateLotState **sample,
    RTIBool * drop_sample,
    struct RTICdrStream *stream,   
    RTIBool deserialize_encapsulation,
    RTIBool deserialize_sample, 
    void *endpoint_plugin_qos)
{

    RTIBool result;
    if (drop_sample) {} /* To avoid warnings */
    
    stream->_xTypesState.unassignable = RTI_FALSE;

    result = ::com::rti::chocolatefactory::generated::ChocolateLotStatePlugin_deserialize_sample( 
        endpoint_data, (sample != NULL)?*sample:NULL,
        stream, deserialize_encapsulation, deserialize_sample, 
        endpoint_plugin_qos);
        
    if (result) {
        if (stream->_xTypesState.unassignable) {
            result = RTI_FALSE;
        }
    }
    
    return result;
 
}




RTIBool ChocolateLotStatePlugin_skip(
    PRESTypePluginEndpointData endpoint_data,
    struct RTICdrStream *stream,   
    RTIBool skip_encapsulation,
    RTIBool skip_sample, 
    void *endpoint_plugin_qos)
{
    char * position = NULL;

    RTIBool done = RTI_FALSE;

    if (endpoint_data) {} /* To avoid warnings */
    if (endpoint_plugin_qos) {} /* To avoid warnings */


    if(skip_encapsulation) {
        if (!RTICdrStream_skipEncapsulation(stream)) {
            return RTI_FALSE;
        }


        position = RTICdrStream_resetAlignment(stream);

    }

    if (skip_sample) {

    if (!RTICdrStream_skipLong(stream)) {
        goto fin;
    }
            

    if (!com::rti::chocolatefactory::generated::StationControllerKindPlugin_skip(
            endpoint_data,
            stream, 
            RTI_FALSE, RTI_TRUE, 
            endpoint_plugin_qos)) {
        goto fin;
    }
            

    if (!RTICdrStream_skipString(stream, ((com::rti::chocolatefactory::generated::MAX_STRING_LENGTH)) + 1)) {
        goto fin;
    }
            

    if (!com::rti::chocolatefactory::generated::StationControllerKindPlugin_skip(
            endpoint_data,
            stream, 
            RTI_FALSE, RTI_TRUE, 
            endpoint_plugin_qos)) {
        goto fin;
    }
            

    if (!com::rti::chocolatefactory::generated::LotStatusKindPlugin_skip(
            endpoint_data,
            stream, 
            RTI_FALSE, RTI_TRUE, 
            endpoint_plugin_qos)) {
        goto fin;
    }
            

    {
        RTICdrUnsignedLong sequence_length;

        if (!RTICdrStream_skipStringSequence(
            stream,
            &sequence_length,
            ((com::rti::chocolatefactory::generated::MAX_STRING_LENGTH)) + 1,            
            RTI_CDR_CHAR_TYPE)){
            goto fin;
        }          
    }
            


    }
    

    done = RTI_TRUE;
fin:
    if (done != RTI_TRUE && 
        RTICdrStream_getRemainder(stream) >=
            RTI_CDR_PARAMETER_HEADER_ALIGNMENT) {
        return RTI_FALSE;   
    }

    if(skip_encapsulation) {
        RTICdrStream_restoreAlignment(stream,position);
    }


    return RTI_TRUE;
}


unsigned int 
ChocolateLotStatePlugin_get_serialized_sample_max_size(
    PRESTypePluginEndpointData endpoint_data,
    RTIBool include_encapsulation,
    RTIEncapsulationId encapsulation_id,
    unsigned int current_alignment)
{

    unsigned int initial_alignment = current_alignment;

    unsigned int encapsulation_size = current_alignment;

    if (endpoint_data) {} /* To avoid warnings */


    if (include_encapsulation) {

        if (!RTICdrEncapsulation_validEncapsulationId(encapsulation_id)) {
            return 1;
        }

        RTICdrStream_getEncapsulationSize(encapsulation_size);
        encapsulation_size -= current_alignment;
        current_alignment = 0;
        initial_alignment = 0;

    }


    current_alignment +=  RTICdrType_getLongMaxSizeSerialized(
        current_alignment);
            

    current_alignment +=  com::rti::chocolatefactory::generated::StationControllerKindPlugin_get_serialized_sample_max_size(
        endpoint_data,RTI_FALSE,encapsulation_id,current_alignment);
            

    current_alignment +=  RTICdrType_getStringMaxSizeSerialized(
        current_alignment, ((com::rti::chocolatefactory::generated::MAX_STRING_LENGTH)) + 1);
            

    current_alignment +=  com::rti::chocolatefactory::generated::StationControllerKindPlugin_get_serialized_sample_max_size(
        endpoint_data,RTI_FALSE,encapsulation_id,current_alignment);
            

    current_alignment +=  com::rti::chocolatefactory::generated::LotStatusKindPlugin_get_serialized_sample_max_size(
        endpoint_data,RTI_FALSE,encapsulation_id,current_alignment);
            

    current_alignment +=  RTICdrType_getStringSequenceMaxSizeSerialized(
        current_alignment,((com::rti::chocolatefactory::generated::MAX_INGREDIENT_LIST)),((com::rti::chocolatefactory::generated::MAX_STRING_LENGTH)) + 1,RTI_CDR_CHAR_TYPE);                
            

    if (include_encapsulation) {
        current_alignment += encapsulation_size;
    }

    return current_alignment - initial_alignment;
}


unsigned int 
ChocolateLotStatePlugin_get_serialized_sample_min_size(
    PRESTypePluginEndpointData endpoint_data,
    RTIBool include_encapsulation,
    RTIEncapsulationId encapsulation_id,
    unsigned int current_alignment)
{

    unsigned int initial_alignment = current_alignment;

    unsigned int encapsulation_size = current_alignment;

    if (endpoint_data) {} /* To avoid warnings */


    if (include_encapsulation) {

        if (!RTICdrEncapsulation_validEncapsulationId(encapsulation_id)) {
            return 1;
        }

        RTICdrStream_getEncapsulationSize(encapsulation_size);
        encapsulation_size -= current_alignment;
        current_alignment = 0;
        initial_alignment = 0;

    }


    current_alignment +=  RTICdrType_getLongMaxSizeSerialized(
        current_alignment);
            

    current_alignment +=  com::rti::chocolatefactory::generated::StationControllerKindPlugin_get_serialized_sample_min_size(
        endpoint_data,RTI_FALSE,encapsulation_id,current_alignment);
            

    current_alignment +=  RTICdrType_getStringMaxSizeSerialized(
        current_alignment, 1);
            

    current_alignment +=  com::rti::chocolatefactory::generated::StationControllerKindPlugin_get_serialized_sample_min_size(
        endpoint_data,RTI_FALSE,encapsulation_id,current_alignment);
            

    current_alignment +=  com::rti::chocolatefactory::generated::LotStatusKindPlugin_get_serialized_sample_min_size(
        endpoint_data,RTI_FALSE,encapsulation_id,current_alignment);
            

    current_alignment +=  RTICdrType_getStringSequenceMaxSizeSerialized(
        current_alignment,0,1,RTI_CDR_CHAR_TYPE);                
            

    if (include_encapsulation) {
        current_alignment += encapsulation_size;
    }

    return current_alignment - initial_alignment;
}


/* Returns the size of the sample in its serialized form (in bytes).
 * It can also be an estimation in excess of the real buffer needed 
 * during a call to the serialize() function.
 * The value reported does not have to include the space for the
 * encapsulation flags.
 */
unsigned int
ChocolateLotStatePlugin_get_serialized_sample_size(
    PRESTypePluginEndpointData endpoint_data,
    RTIBool include_encapsulation,
    RTIEncapsulationId encapsulation_id,
    unsigned int current_alignment,
    const ChocolateLotState * sample) 
{

    unsigned int initial_alignment = current_alignment;

    unsigned int encapsulation_size = current_alignment;

    if (endpoint_data) {} /* To avoid warnings */
    if (sample) {} /* To avoid warnings */


    if (include_encapsulation) {

        if (!RTICdrEncapsulation_validEncapsulationId(encapsulation_id)) {
            return 1;
        }

        RTICdrStream_getEncapsulationSize(encapsulation_size);
        encapsulation_size -= current_alignment;
        current_alignment = 0;
        initial_alignment = 0;

    }


    current_alignment += RTICdrType_getLongMaxSizeSerialized(
        current_alignment);
            

    current_alignment += com::rti::chocolatefactory::generated::StationControllerKindPlugin_get_serialized_sample_size(
        endpoint_data,RTI_FALSE, encapsulation_id, 
        current_alignment, &sample->controller);
            

    current_alignment += RTICdrType_getStringSerializedSize(
        current_alignment, sample->recipeName);
            

    current_alignment += com::rti::chocolatefactory::generated::StationControllerKindPlugin_get_serialized_sample_size(
        endpoint_data,RTI_FALSE, encapsulation_id, 
        current_alignment, &sample->nextController);
            

    current_alignment += com::rti::chocolatefactory::generated::LotStatusKindPlugin_get_serialized_sample_size(
        endpoint_data,RTI_FALSE, encapsulation_id, 
        current_alignment, &sample->lotStatus);
            

    if (DDS_StringSeq_get_contiguous_bufferI(&sample->ingredients) != NULL) {
         current_alignment += RTICdrStream_getStringSequenceSerializedSize(
            current_alignment,
            DDS_StringSeq_get_contiguous_bufferI(&sample->ingredients),
            DDS_StringSeq_get_length(&sample->ingredients),
            RTI_CDR_CHAR_TYPE);
    } else {
         current_alignment += RTICdrStream_getStringPointerSequenceSerializedSize(
            current_alignment,
            (const void **)DDS_StringSeq_get_discontiguous_bufferI(&sample->ingredients),
            DDS_StringSeq_get_length(&sample->ingredients),
            RTI_CDR_CHAR_TYPE);
    }
            

    if (include_encapsulation) {
        current_alignment += encapsulation_size;
    }

    return current_alignment - initial_alignment;
}







/* --------------------------------------------------------------------------------------
    Key Management functions:
 * -------------------------------------------------------------------------------------- */


PRESTypePluginKeyKind 
ChocolateLotStatePlugin_get_key_kind(void)
{

    return PRES_TYPEPLUGIN_USER_KEY;
     
}


RTIBool 
ChocolateLotStatePlugin_serialize_key(
    PRESTypePluginEndpointData endpoint_data,
    const ChocolateLotState *sample, 
    struct RTICdrStream *stream,    
    RTIBool serialize_encapsulation,
    RTIEncapsulationId encapsulation_id,
    RTIBool serialize_key,
    void *endpoint_plugin_qos)
{
    char * position = NULL;

    if (endpoint_data) {} /* To avoid warnings */
    if (endpoint_plugin_qos) {} /* To avoid warnings */


    if(serialize_encapsulation) {
    
        if (!RTICdrStream_serializeAndSetCdrEncapsulation(stream, encapsulation_id)) {
            return RTI_FALSE;
        }


        position = RTICdrStream_resetAlignment(stream);

    }

    if(serialize_key) {

    if (!RTICdrStream_serializeLong(
        stream, &sample->lotID)) {
        return RTI_FALSE;
    }
            

    if (!com::rti::chocolatefactory::generated::StationControllerKindPlugin_serialize_key(
            endpoint_data,
            &sample->controller, 
            stream, 
            RTI_FALSE, encapsulation_id, 
            RTI_TRUE, 
            endpoint_plugin_qos)) {
        return RTI_FALSE;
    }
            

    }


    if(serialize_encapsulation) {
        RTICdrStream_restoreAlignment(stream,position);
    }


    return RTI_TRUE;
}


RTIBool ChocolateLotStatePlugin_deserialize_key_sample(
    PRESTypePluginEndpointData endpoint_data,
    ChocolateLotState *sample, 
    struct RTICdrStream *stream,
    RTIBool deserialize_encapsulation,
    RTIBool deserialize_key,
    void *endpoint_plugin_qos)
{
    char * position = NULL;

    if (endpoint_data) {} /* To avoid warnings */
    if (endpoint_plugin_qos) {} /* To avoid warnings */


    if(deserialize_encapsulation) {
        /* Deserialize encapsulation */
        if (!RTICdrStream_deserializeAndSetCdrEncapsulation(stream)) {
            return RTI_FALSE;  
        }


        position = RTICdrStream_resetAlignment(stream);

    }

    if (deserialize_key) {

    if (!RTICdrStream_deserializeLong(
        stream, &sample->lotID)) {
        return RTI_FALSE;
    }

    if (!com::rti::chocolatefactory::generated::StationControllerKindPlugin_deserialize_key_sample(
            endpoint_data,
            &sample->controller,
            stream, 
            RTI_FALSE, RTI_TRUE, 
            endpoint_plugin_qos)) {
        return RTI_FALSE;
    }
            

    }


    if(deserialize_encapsulation) {
        RTICdrStream_restoreAlignment(stream,position);
    }


    return RTI_TRUE;
}


 
RTIBool ChocolateLotStatePlugin_deserialize_key(
    PRESTypePluginEndpointData endpoint_data,
    ChocolateLotState **sample, 
    RTIBool * drop_sample,
    struct RTICdrStream *stream,
    RTIBool deserialize_encapsulation,
    RTIBool deserialize_key,
    void *endpoint_plugin_qos)
{
    RTIBool result;
    if (drop_sample) {} /* To avoid warnings */
    
    stream->_xTypesState.unassignable = RTI_FALSE;
    
    result = ::com::rti::chocolatefactory::generated::ChocolateLotStatePlugin_deserialize_key_sample(
        endpoint_data, (sample != NULL)?*sample:NULL, stream,
        deserialize_encapsulation, deserialize_key, endpoint_plugin_qos);
        
    if (result) {
        if (stream->_xTypesState.unassignable) {
            result = RTI_FALSE;
        }
    }
    
    return result;
}



unsigned int
ChocolateLotStatePlugin_get_serialized_key_max_size(
    PRESTypePluginEndpointData endpoint_data,
    RTIBool include_encapsulation,
    RTIEncapsulationId encapsulation_id,
    unsigned int current_alignment)
{

    unsigned int encapsulation_size = current_alignment;


    unsigned int initial_alignment = current_alignment;


    if (endpoint_data) {} /* To avoid warnings */


    if (include_encapsulation) {
        if (!RTICdrEncapsulation_validEncapsulationId(encapsulation_id)) {
            return 1;
        }


        RTICdrStream_getEncapsulationSize(encapsulation_size);
        encapsulation_size -= current_alignment;
        current_alignment = 0;
        initial_alignment = 0;

    }
        

    current_alignment +=  RTICdrType_getLongMaxSizeSerialized(
        current_alignment);
            

    current_alignment +=  com::rti::chocolatefactory::generated::StationControllerKindPlugin_get_serialized_key_max_size(
        endpoint_data,RTI_FALSE,encapsulation_id,current_alignment);
            

    if (include_encapsulation) {
        current_alignment += encapsulation_size;
    }

    return current_alignment - initial_alignment;
}


RTIBool 
ChocolateLotStatePlugin_serialized_sample_to_key(
    PRESTypePluginEndpointData endpoint_data,
    ChocolateLotState *sample,
    struct RTICdrStream *stream, 
    RTIBool deserialize_encapsulation,  
    RTIBool deserialize_key, 
    void *endpoint_plugin_qos)
{
    char * position = NULL;

    RTIBool done = RTI_FALSE;

    if (endpoint_data) {} /* To avoid warnings */
    if (endpoint_plugin_qos) {} /* To avoid warnings */

    if (stream == NULL) goto fin; /* To avoid warnings */


    if(deserialize_encapsulation) {
        if (!RTICdrStream_deserializeAndSetCdrEncapsulation(stream)) {
            return RTI_FALSE;
        }

        position = RTICdrStream_resetAlignment(stream);

    }

    if (deserialize_key) {

    if (!RTICdrStream_deserializeLong(
        stream, &sample->lotID)) {
        return RTI_FALSE;
    }

    if (!com::rti::chocolatefactory::generated::StationControllerKindPlugin_serialized_sample_to_key(
            endpoint_data,
            &sample->controller,
            stream, 
            RTI_FALSE, RTI_TRUE, 
            endpoint_plugin_qos)) {
        return RTI_FALSE;
    }
            

    if (!RTICdrStream_skipString(stream, ((com::rti::chocolatefactory::generated::MAX_STRING_LENGTH)) + 1)) {
        goto fin;
    }
            

    if (!com::rti::chocolatefactory::generated::StationControllerKindPlugin_skip(
            endpoint_data,
            stream, 
            RTI_FALSE, RTI_TRUE, 
            endpoint_plugin_qos)) {
        goto fin;
    }
            

    if (!com::rti::chocolatefactory::generated::LotStatusKindPlugin_skip(
            endpoint_data,
            stream, 
            RTI_FALSE, RTI_TRUE, 
            endpoint_plugin_qos)) {
        goto fin;
    }
            

    {
        RTICdrUnsignedLong sequence_length;

        if (!RTICdrStream_skipStringSequence(
            stream,
            &sequence_length,
            ((com::rti::chocolatefactory::generated::MAX_STRING_LENGTH)) + 1,            
            RTI_CDR_CHAR_TYPE)){
            goto fin;
        }          
    }
            

    }


    done = RTI_TRUE;
fin:
    if (done != RTI_TRUE && 
        RTICdrStream_getRemainder(stream) >=
            RTI_CDR_PARAMETER_HEADER_ALIGNMENT) {
        return RTI_FALSE;   
    }

    if(deserialize_encapsulation) {
        RTICdrStream_restoreAlignment(stream,position);
    }


    return RTI_TRUE;
}





RTIBool 
ChocolateLotStatePlugin_instance_to_key(
    PRESTypePluginEndpointData endpoint_data,
    ChocolateLotStateKeyHolder *dst, 
    const ChocolateLotState *src)
{  

    if (endpoint_data) {} /* To avoid warnings */

    if (!RTICdrType_copyLong(
        &dst->lotID, &src->lotID)) {
        return RTI_FALSE;
    }
            

    if (!com::rti::chocolatefactory::generated::StationControllerKind_copy(
        &dst->controller, &src->controller)) {
        return RTI_FALSE;
    }
            

    return RTI_TRUE;
}


RTIBool 
ChocolateLotStatePlugin_key_to_instance(
    PRESTypePluginEndpointData endpoint_data,
    ChocolateLotState *dst, const
    ChocolateLotStateKeyHolder *src)
{

    if (endpoint_data) {} /* To avoid warnings */

    if (!RTICdrType_copyLong(
        &dst->lotID, &src->lotID)) {
        return RTI_FALSE;
    }
            

    if (!com::rti::chocolatefactory::generated::StationControllerKind_copy(
        &dst->controller, &src->controller)) {
        return RTI_FALSE;
    }
            

    return RTI_TRUE;
}


RTIBool 
ChocolateLotStatePlugin_instance_to_keyhash(
    PRESTypePluginEndpointData endpoint_data,
    DDS_KeyHash_t *keyhash,
    const ChocolateLotState *instance)
{
    struct RTICdrStream * md5Stream = NULL;

    md5Stream = PRESTypePluginDefaultEndpointData_getMD5Stream(endpoint_data);

    if (md5Stream == NULL) {
        return RTI_FALSE;
    }

    RTIOsapiMemory_zero(
        RTICdrStream_getBuffer(md5Stream),
        RTICdrStream_getBufferLength(md5Stream));
    RTICdrStream_resetPosition(md5Stream);
    RTICdrStream_setDirtyBit(md5Stream, RTI_TRUE);

    if (!::com::rti::chocolatefactory::generated::ChocolateLotStatePlugin_serialize_key(
            endpoint_data,instance,md5Stream, RTI_FALSE, RTI_CDR_ENCAPSULATION_ID_CDR_BE, RTI_TRUE,NULL)) {
        return RTI_FALSE;
    }
    
    if (PRESTypePluginDefaultEndpointData_getMaxSizeSerializedKey(endpoint_data) > (unsigned int)(MIG_RTPS_KEY_HASH_MAX_LENGTH)) {
        RTICdrStream_computeMD5(md5Stream, keyhash->value);
    } else {
        RTIOsapiMemory_zero(keyhash->value,MIG_RTPS_KEY_HASH_MAX_LENGTH);
        RTIOsapiMemory_copy(
            keyhash->value, 
            RTICdrStream_getBuffer(md5Stream), 
            RTICdrStream_getCurrentPositionOffset(md5Stream));
    }

    keyhash->length = MIG_RTPS_KEY_HASH_MAX_LENGTH;
    return RTI_TRUE;
}


RTIBool 
ChocolateLotStatePlugin_serialized_sample_to_keyhash(
    PRESTypePluginEndpointData endpoint_data,
    struct RTICdrStream *stream, 
    DDS_KeyHash_t *keyhash,
    RTIBool deserialize_encapsulation,
    void *endpoint_plugin_qos) 
{   
    char * position = NULL;

    RTIBool done = RTI_FALSE;
    ChocolateLotState * sample = NULL;

    if (endpoint_plugin_qos) {} /* To avoid warnings */


    if (stream == NULL) goto fin; /* To avoid warnings */


    if(deserialize_encapsulation) {
        if (!RTICdrStream_deserializeAndSetCdrEncapsulation(stream)) {
            return RTI_FALSE;
        }

        position = RTICdrStream_resetAlignment(stream);
    }


    sample = (ChocolateLotState *)
                PRESTypePluginDefaultEndpointData_getTempSample(endpoint_data);

    if (sample == NULL) {
        return RTI_FALSE;
    }


    if (!RTICdrStream_deserializeLong(
        stream, &sample->lotID)) {
        return RTI_FALSE;
    }

    if (!com::rti::chocolatefactory::generated::StationControllerKindPlugin_serialized_sample_to_key(
            endpoint_data,
            &sample->controller,
            stream, 
            RTI_FALSE, RTI_TRUE, 
            endpoint_plugin_qos)) {
        return RTI_FALSE;
    }
            

    done = RTI_TRUE;
fin:
    if (done != RTI_TRUE && 
        RTICdrStream_getRemainder(stream) >=
            RTI_CDR_PARAMETER_HEADER_ALIGNMENT) {
        return RTI_FALSE;   
    }

    if(deserialize_encapsulation) {
        RTICdrStream_restoreAlignment(stream,position);
    }


    if (!::com::rti::chocolatefactory::generated::ChocolateLotStatePlugin_instance_to_keyhash(
            endpoint_data, keyhash, sample)) {
        return RTI_FALSE;
    }

    return RTI_TRUE;
}


/* ------------------------------------------------------------------------
 * Plug-in Installation Methods
 * ------------------------------------------------------------------------ */
 
struct PRESTypePlugin *ChocolateLotStatePlugin_new(void) 
{ 
    struct PRESTypePlugin *plugin = NULL;
    const struct PRESTypePluginVersion PLUGIN_VERSION = 
        PRES_TYPE_PLUGIN_VERSION_2_0;

    RTIOsapiHeap_allocateStructure(
        &plugin, struct PRESTypePlugin);
    if (plugin == NULL) {
       return NULL;
    }

    plugin->version = PLUGIN_VERSION;

    /* set up parent's function pointers */
    plugin->onParticipantAttached =
        (PRESTypePluginOnParticipantAttachedCallback)
        ::com::rti::chocolatefactory::generated::ChocolateLotStatePlugin_on_participant_attached;
    plugin->onParticipantDetached =
        (PRESTypePluginOnParticipantDetachedCallback)
        ::com::rti::chocolatefactory::generated::ChocolateLotStatePlugin_on_participant_detached;
    plugin->onEndpointAttached =
        (PRESTypePluginOnEndpointAttachedCallback)
        ::com::rti::chocolatefactory::generated::ChocolateLotStatePlugin_on_endpoint_attached;
    plugin->onEndpointDetached =
        (PRESTypePluginOnEndpointDetachedCallback)
        ::com::rti::chocolatefactory::generated::ChocolateLotStatePlugin_on_endpoint_detached;

    plugin->copySampleFnc =
        (PRESTypePluginCopySampleFunction)
        ::com::rti::chocolatefactory::generated::ChocolateLotStatePlugin_copy_sample;
    plugin->createSampleFnc =
        (PRESTypePluginCreateSampleFunction)
        ChocolateLotStatePlugin_create_sample;
    plugin->destroySampleFnc =
        (PRESTypePluginDestroySampleFunction)
        ChocolateLotStatePlugin_destroy_sample;

    plugin->serializeFnc =
        (PRESTypePluginSerializeFunction)
        ::com::rti::chocolatefactory::generated::ChocolateLotStatePlugin_serialize;
    plugin->deserializeFnc =
        (PRESTypePluginDeserializeFunction)
        ::com::rti::chocolatefactory::generated::ChocolateLotStatePlugin_deserialize;
    plugin->getSerializedSampleMaxSizeFnc =
        (PRESTypePluginGetSerializedSampleMaxSizeFunction)
        ::com::rti::chocolatefactory::generated::ChocolateLotStatePlugin_get_serialized_sample_max_size;
    plugin->getSerializedSampleMinSizeFnc =
        (PRESTypePluginGetSerializedSampleMinSizeFunction)
        ::com::rti::chocolatefactory::generated::ChocolateLotStatePlugin_get_serialized_sample_min_size;


    plugin->getSampleFnc =
        (PRESTypePluginGetSampleFunction)
        ChocolateLotStatePlugin_get_sample;
    plugin->returnSampleFnc =
        (PRESTypePluginReturnSampleFunction)
        ChocolateLotStatePlugin_return_sample;

    plugin->getKeyKindFnc =
        (PRESTypePluginGetKeyKindFunction)
        ::com::rti::chocolatefactory::generated::ChocolateLotStatePlugin_get_key_kind;


    plugin->getSerializedKeyMaxSizeFnc =   
        (PRESTypePluginGetSerializedKeyMaxSizeFunction)
        ::com::rti::chocolatefactory::generated::ChocolateLotStatePlugin_get_serialized_key_max_size;
    plugin->serializeKeyFnc =
        (PRESTypePluginSerializeKeyFunction)
        ::com::rti::chocolatefactory::generated::ChocolateLotStatePlugin_serialize_key;
    plugin->deserializeKeyFnc =
        (PRESTypePluginDeserializeKeyFunction)
        ::com::rti::chocolatefactory::generated::ChocolateLotStatePlugin_deserialize_key;
    plugin->deserializeKeySampleFnc =
        (PRESTypePluginDeserializeKeySampleFunction)
        ::com::rti::chocolatefactory::generated::ChocolateLotStatePlugin_deserialize_key_sample;

    plugin->instanceToKeyHashFnc = 
        (PRESTypePluginInstanceToKeyHashFunction)
        ::com::rti::chocolatefactory::generated::ChocolateLotStatePlugin_instance_to_keyhash;
    plugin->serializedSampleToKeyHashFnc = 
        (PRESTypePluginSerializedSampleToKeyHashFunction)
        ::com::rti::chocolatefactory::generated::ChocolateLotStatePlugin_serialized_sample_to_keyhash;

    plugin->getKeyFnc =
        (PRESTypePluginGetKeyFunction)
        ChocolateLotStatePlugin_get_key;
    plugin->returnKeyFnc =
        (PRESTypePluginReturnKeyFunction)
        ChocolateLotStatePlugin_return_key;

    plugin->instanceToKeyFnc =
        (PRESTypePluginInstanceToKeyFunction)
        ::com::rti::chocolatefactory::generated::ChocolateLotStatePlugin_instance_to_key;
    plugin->keyToInstanceFnc =
        (PRESTypePluginKeyToInstanceFunction)
        ::com::rti::chocolatefactory::generated::ChocolateLotStatePlugin_key_to_instance;
    plugin->serializedKeyToKeyHashFnc = NULL; /* Not supported yet */
    
    plugin->typeCode =  (struct RTICdrTypeCode *)::com::rti::chocolatefactory::generated::ChocolateLotState_get_typecode();
    
    plugin->languageKind = PRES_TYPEPLUGIN_DDS_TYPE; 

    /* Serialized buffer */
    plugin->getBuffer = 
        (PRESTypePluginGetBufferFunction)
        ChocolateLotStatePlugin_get_buffer;
    plugin->returnBuffer = 
        (PRESTypePluginReturnBufferFunction)
        ChocolateLotStatePlugin_return_buffer;
    plugin->getSerializedSampleSizeFnc =
        (PRESTypePluginGetSerializedSampleSizeFunction)
        ::com::rti::chocolatefactory::generated::ChocolateLotStatePlugin_get_serialized_sample_size;

    plugin->endpointTypeName = ChocolateLotStateTYPENAME;

    return plugin;
}

void
ChocolateLotStatePlugin_delete(struct PRESTypePlugin *plugin)
{
    RTIOsapiHeap_freeStructure(plugin);
} 

} /* namespace generated */

} /* namespace chocolatefactory */

} /* namespace rti */

} /* namespace com */
