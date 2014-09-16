
/*
  WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

  This file was generated from VideoData.idl using "rtiddsgen".
  The rtiddsgen tool is part of the RTI Connext distribution.
  For more information, type 'rtiddsgen -help' at a command shell
  or consult the RTI Connext manual.
*/


#ifndef NDDS_STANDALONE_TYPE
    #ifdef __cplusplus
        #ifndef ndds_cpp_h
            #include "ndds/ndds_cpp.h"
        #endif
        #ifndef dds_c_log_impl_h              
            #include "dds_c/dds_c_log_impl.h"                                
        #endif        
    #else
        #ifndef ndds_c_h
            #include "ndds/ndds_c.h"
        #endif
    #endif
    
    #ifndef cdr_type_h
        #include "cdr/cdr_type.h"
    #endif    

    #ifndef osapi_heap_h
        #include "osapi/osapi_heap.h" 
    #endif
#else
    #include "ndds_standalone_type.h"
#endif



#include "VideoData.h"


namespace com{

namespace rti{

namespace media{

namespace generated{
/* ========================================================================= */
const char *VideoStreamTYPENAME = "com::rti::media::generated::VideoStream";

DDS_TypeCode* VideoStream_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode VideoStream_g_tc_frame_sequence = DDS_INITIALIZE_SEQUENCE_TYPECODE((com::rti::media::generated::MAX_BUFFER_SIZE),NULL);

    static DDS_TypeCode_Member VideoStream_g_tc_members[4]=
    {
        {
            (char *)"stream_id",/* Member name */
            {
                0,/* Representation ID */
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Bitfield bits */
                NULL/* Member type code is assigned later */
            },
            0, /* Ignored */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            RTI_CDR_KEY_MEMBER, /* Member flags */
            DDS_PRIVATE_MEMBER,/* Ignored */
            1,
            NULL/* Ignored */
        },
        {
            (char *)"flags",/* Member name */
            {
                1,/* Representation ID */
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Bitfield bits */
                NULL/* Member type code is assigned later */
            },
            0, /* Ignored */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            RTI_CDR_REQUIRED_MEMBER, /* Member flags */
            DDS_PRIVATE_MEMBER,/* Ignored */
            1,
            NULL/* Ignored */
        },
        {
            (char *)"sequence_number",/* Member name */
            {
                2,/* Representation ID */
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Bitfield bits */
                NULL/* Member type code is assigned later */
            },
            0, /* Ignored */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            RTI_CDR_REQUIRED_MEMBER, /* Member flags */
            DDS_PRIVATE_MEMBER,/* Ignored */
            1,
            NULL/* Ignored */
        },
        {
            (char *)"frame",/* Member name */
            {
                3,/* Representation ID */
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Bitfield bits */
                NULL/* Member type code is assigned later */
            },
            0, /* Ignored */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            RTI_CDR_REQUIRED_MEMBER, /* Member flags */
            DDS_PRIVATE_MEMBER,/* Ignored */
            1,
            NULL/* Ignored */
        }
    };

    static DDS_TypeCode VideoStream_g_tc =
    {{
        DDS_TK_STRUCT,/* Kind */
        DDS_BOOLEAN_FALSE, /* Ignored */
        -1,/* Ignored */
        (char *)"com::rti::media::generated::VideoStream", /* Name */
        NULL, /* Ignored */
        0, /* Ignored */
        0, /* Ignored */
        NULL, /* Ignored */
        4, /* Number of members */
        VideoStream_g_tc_members, /* Members */
        DDS_VM_NONE /* Ignored */
    }}; /* Type code for VideoStream*/

    if (is_initialized) {
        return &VideoStream_g_tc;
    }

    VideoStream_g_tc_frame_sequence._data._typeCode = (RTICdrTypeCode *)&DDS_g_tc_octet;

    VideoStream_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_long;
    VideoStream_g_tc_members[1]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_ulong;
    VideoStream_g_tc_members[2]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_ulong;
    VideoStream_g_tc_members[3]._representation._typeCode = (RTICdrTypeCode *)&VideoStream_g_tc_frame_sequence;

    is_initialized = RTI_TRUE;

    return &VideoStream_g_tc;
}


RTIBool VideoStream_initialize(
    VideoStream* sample) {
  return ::com::rti::media::generated::VideoStream_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}
        
RTIBool VideoStream_initialize_ex(
    VideoStream* sample,RTIBool allocatePointers,RTIBool allocateMemory)
{
    struct DDS_TypeAllocationParams_t allocParams =
        DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;
        
    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;
    
    return ::com::rti::media::generated::VideoStream_initialize_w_params(
        sample,&allocParams);
}

RTIBool VideoStream_initialize_w_params(
        VideoStream* sample,
        const struct DDS_TypeAllocationParams_t * allocParams)
{

    void* buffer = NULL;
    if (buffer) {} /* To avoid warnings */
        
    
    if (allocParams) {} /* To avoid warnings */
        

    if (!RTICdrType_initLong(&sample->stream_id)) {
        return RTI_FALSE;
    }                
            

    if (!RTICdrType_initUnsignedLong(&sample->flags)) {
        return RTI_FALSE;
    }                
            

    if (!RTICdrType_initUnsignedLong(&sample->sequence_number)) {
        return RTI_FALSE;
    }                
            

    if (allocParams->allocate_memory) {
        DDS_OctetSeq_initialize(&sample->frame);
        if (!DDS_OctetSeq_set_maximum(&sample->frame,
                ((com::rti::media::generated::MAX_BUFFER_SIZE)))) {
            return RTI_FALSE;
        }
    } else {
        DDS_OctetSeq_set_length(&sample->frame, 0); 
    }
            


    return RTI_TRUE;
}

void VideoStream_finalize(
    VideoStream* sample)
{
    ::com::rti::media::generated::VideoStream_finalize_ex(sample,RTI_TRUE);
}
        
void VideoStream_finalize_ex(
    VideoStream* sample,RTIBool deletePointers)
{        
    struct DDS_TypeDeallocationParams_t deallocParams =
            DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample) { } /* To avoid warnings */
    
    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    ::com::rti::media::generated::VideoStream_finalize_w_params(
        sample,&deallocParams);
}

void VideoStream_finalize_w_params(
        VideoStream* sample,
        const struct DDS_TypeDeallocationParams_t * deallocParams)
{    
    if (sample) { } /* To avoid warnings */
    if (deallocParams) {} /* To avoid warnings */





    DDS_OctetSeq_finalize(&sample->frame);
            

}

void VideoStream_finalize_optional_members(
    VideoStream* sample, RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParamsTmp =
        DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;
    struct DDS_TypeDeallocationParams_t * deallocParams =
        &deallocParamsTmp;
    if (sample) { } /* To avoid warnings */
    if (deallocParams) {} /* To avoid warnings */

        

    deallocParamsTmp.delete_pointers = (DDS_Boolean)deletePointers;
    deallocParamsTmp.delete_optional_members = DDS_BOOLEAN_TRUE;    
             





}

RTIBool VideoStream_copy(
    VideoStream* dst,
    const VideoStream* src)
{

    if (!RTICdrType_copyLong(
        &dst->stream_id, &src->stream_id)) {
        return RTI_FALSE;
    }
            

    if (!RTICdrType_copyUnsignedLong(
        &dst->flags, &src->flags)) {
        return RTI_FALSE;
    }
            

    if (!RTICdrType_copyUnsignedLong(
        &dst->sequence_number, &src->sequence_number)) {
        return RTI_FALSE;
    }
            

    if (!DDS_OctetSeq_copy(&dst->frame,
                                          &src->frame)) {
        return RTI_FALSE;
    }
            


    return RTI_TRUE;
}


/**
 * <<IMPLEMENTATION>>
 *
 * Defines:  TSeq, T
 *
 * Configure and implement 'VideoStream' sequence class.
 */
#define T VideoStream
#define TSeq VideoStreamSeq
#define T_initialize_w_params ::com::rti::media::generated::VideoStream_initialize_w_params
#define T_finalize_w_params   ::com::rti::media::generated::VideoStream_finalize_w_params
#define T_copy       ::com::rti::media::generated::VideoStream_copy

#ifndef NDDS_STANDALONE_TYPE
#include "dds_c/generic/dds_c_sequence_TSeq.gen"
#ifdef __cplusplus
#include "dds_cpp/generic/dds_cpp_sequence_TSeq.gen"
#endif
#else
#include "dds_c_sequence_TSeq.gen"
#ifdef __cplusplus
#include "dds_cpp_sequence_TSeq.gen"
#endif
#endif

#undef T_copy
#undef T_finalize_w_params
#undef T_initialize_w_params
#undef TSeq
#undef T


} /* namespace generated */

} /* namespace media */

} /* namespace rti */

} /* namespace com */
