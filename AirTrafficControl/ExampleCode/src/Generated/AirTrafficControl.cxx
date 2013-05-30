
/*
  WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

  This file was generated from AirTrafficControl.idl using "rtiddsgen".
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



#include "AirTrafficControl.h"


namespace com{

namespace rti{

namespace atc{

namespace generated{
/* ========================================================================= */

DDS_TypeCode* FlightId_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode FlightId_g_tc_string = DDS_INITIALIZE_STRING_TYPECODE((com::rti::atc::generated::FLIGHT_ID_LENGTH));

    static DDS_TypeCode FlightId_g_tc =
    {{
        DDS_TK_ALIAS, /* Kind*/
        DDS_BOOLEAN_FALSE, /* Is a pointer? */
        -1, /* Ignored */
        (char *)"com::rti::atc::generated::FlightId", /* Name */
        NULL, /* Content type code is assigned later */
        0, /* Ignored */
        0, /* Ignored */
        NULL, /* Ignored */
        0, /* Ignored */
        NULL, /* Ignored */
        DDS_VM_NONE /* Ignored */
    }}; /* Type code for FlightId */

    if (is_initialized) {
        return &FlightId_g_tc;
    }

    FlightId_g_tc._data._typeCode = (RTICdrTypeCode *)&FlightId_g_tc_string; /* Content type code */

    is_initialized = RTI_TRUE;

    return &FlightId_g_tc;
}


RTIBool FlightId_initialize(
    FlightId* sample)
{
    return ::com::rti::atc::generated::FlightId_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool FlightId_initialize_ex(
    FlightId* sample,RTIBool allocatePointers,RTIBool allocateMemory)
{


    if (allocatePointers) {} /* To avoid warnings */
    if (allocateMemory) {} /* To avoid warnings */



    if (allocateMemory) {
        (*sample) = DDS_String_alloc(((com::rti::atc::generated::FLIGHT_ID_LENGTH)));
        if ((*sample) == NULL) {
            return RTI_FALSE;
        }
    } else {
        if ((*sample) != NULL) { 
            (*sample)[0] = '\0';
        }
    }
            


    return RTI_TRUE;
}

void FlightId_finalize(
    FlightId* sample)
{
    ::com::rti::atc::generated::FlightId_finalize_ex(sample,RTI_TRUE);
}
            
void FlightId_finalize_ex(
    FlightId* sample,RTIBool deletePointers)
{
    if (sample) {} /* To avoid warnings */
    if (deletePointers) {} /* To avoid warnings */


    DDS_String_free((*sample));                
            

}


RTIBool FlightId_copy(
    FlightId* dst,
    const FlightId* src)
{

    if (!RTICdrType_copyString(
        (*dst), (*src), ((com::rti::atc::generated::FLIGHT_ID_LENGTH)) + 1)) {
        return RTI_FALSE;
    }
            


    return RTI_TRUE;
}

    
/**
 * <<IMPLEMENTATION>>
 *
 * Defines:  TSeq, T
 *
 * Configure and implement 'FlightId' sequence class.
 */
#define T            FlightId
#define TSeq         FlightIdSeq
#define T_initialize_ex ::com::rti::atc::generated::FlightId_initialize_ex
#define T_finalize_ex   ::com::rti::atc::generated::FlightId_finalize_ex
#define T_copy       ::com::rti::atc::generated::FlightId_copy


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
#undef T_finalize_ex
#undef T_initialize_ex
#undef TSeq
#undef T

/* ========================================================================= */
const char *TrackTYPENAME = "com::rti::atc::generated::Track";

DDS_TypeCode* Track_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;


    static DDS_TypeCode_Member Track_g_tc_members[6]=
    {
        {
            (char *)"radarId",/* Member name */
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
            DDS_BOOLEAN_TRUE, /* Is a key? */
            DDS_PRIVATE_MEMBER,/* Ignored */
            0,/* Ignored */
            NULL/* Ignored */
        },
        {
            (char *)"trackId",/* Member name */
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
            DDS_BOOLEAN_TRUE, /* Is a key? */
            DDS_PRIVATE_MEMBER,/* Ignored */
            0,/* Ignored */
            NULL/* Ignored */
        },
        {
            (char *)"flightId",/* Member name */
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
            DDS_BOOLEAN_FALSE, /* Is a key? */
            DDS_PRIVATE_MEMBER,/* Ignored */
            0,/* Ignored */
            NULL/* Ignored */
        },
        {
            (char *)"latitude",/* Member name */
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
            DDS_BOOLEAN_FALSE, /* Is a key? */
            DDS_PRIVATE_MEMBER,/* Ignored */
            0,/* Ignored */
            NULL/* Ignored */
        },
        {
            (char *)"longitude",/* Member name */
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
            DDS_BOOLEAN_FALSE, /* Is a key? */
            DDS_PRIVATE_MEMBER,/* Ignored */
            0,/* Ignored */
            NULL/* Ignored */
        },
        {
            (char *)"altitude",/* Member name */
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
            DDS_BOOLEAN_FALSE, /* Is a key? */
            DDS_PRIVATE_MEMBER,/* Ignored */
            0,/* Ignored */
            NULL/* Ignored */
        }
    };

    static DDS_TypeCode Track_g_tc =
    {{
        DDS_TK_STRUCT,/* Kind */
        DDS_BOOLEAN_FALSE, /* Ignored */
        -1,/* Ignored */
        (char *)"com::rti::atc::generated::Track", /* Name */
        NULL, /* Ignored */
        0, /* Ignored */
        0, /* Ignored */
        NULL, /* Ignored */
        6, /* Number of members */
        Track_g_tc_members, /* Members */
        DDS_VM_NONE /* Ignored */
    }}; /* Type code for Track*/

    if (is_initialized) {
        return &Track_g_tc;
    }


    Track_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_long;
    Track_g_tc_members[1]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_long;
    Track_g_tc_members[2]._representation._typeCode = (RTICdrTypeCode *)com::rti::atc::generated::FlightId_get_typecode();
    Track_g_tc_members[3]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_double;
    Track_g_tc_members[4]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_double;
    Track_g_tc_members[5]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_double;

    is_initialized = RTI_TRUE;

    return &Track_g_tc;
}


RTIBool Track_initialize(
    Track* sample) {
  return ::com::rti::atc::generated::Track_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}
        
RTIBool Track_initialize_ex(
    Track* sample,RTIBool allocatePointers,RTIBool allocateMemory)
{
        
    
    if (allocatePointers) {} /* To avoid warnings */
    if (allocateMemory) {} /* To avoid warnings */

    if (!RTICdrType_initLong(&sample->radarId)) {
        return RTI_FALSE;
    }                
            

    if (!RTICdrType_initLong(&sample->trackId)) {
        return RTI_FALSE;
    }                
            

    if (!com::rti::atc::generated::FlightId_initialize_ex(&sample->flightId,allocatePointers,allocateMemory)) {
        return RTI_FALSE;
    }
            

    if (!RTICdrType_initDouble(&sample->latitude)) {
        return RTI_FALSE;
    }                
            

    if (!RTICdrType_initDouble(&sample->longitude)) {
        return RTI_FALSE;
    }                
            

    if (!RTICdrType_initDouble(&sample->altitude)) {
        return RTI_FALSE;
    }                
            


    return RTI_TRUE;
}

void Track_finalize(
    Track* sample)
{
    ::com::rti::atc::generated::Track_finalize_ex(sample,RTI_TRUE);
}
        
void Track_finalize_ex(
    Track* sample,RTIBool deletePointers)
{        
    if (sample) { } /* To avoid warnings */
    if (deletePointers) {} /* To avoid warnings */




    com::rti::atc::generated::FlightId_finalize_ex(&sample->flightId,deletePointers);
            




}

RTIBool Track_copy(
    Track* dst,
    const Track* src)
{        

    if (!RTICdrType_copyLong(
        &dst->radarId, &src->radarId)) {
        return RTI_FALSE;
    }
            

    if (!RTICdrType_copyLong(
        &dst->trackId, &src->trackId)) {
        return RTI_FALSE;
    }
            

    if (!com::rti::atc::generated::FlightId_copy(
        &dst->flightId, &src->flightId)) {
        return RTI_FALSE;
    }
            

    if (!RTICdrType_copyDouble(
        &dst->latitude, &src->latitude)) {
        return RTI_FALSE;
    }
            

    if (!RTICdrType_copyDouble(
        &dst->longitude, &src->longitude)) {
        return RTI_FALSE;
    }
            

    if (!RTICdrType_copyDouble(
        &dst->altitude, &src->altitude)) {
        return RTI_FALSE;
    }
            


    return RTI_TRUE;
}


/**
 * <<IMPLEMENTATION>>
 *
 * Defines:  TSeq, T
 *
 * Configure and implement 'Track' sequence class.
 */
#define T Track
#define TSeq TrackSeq
#define T_initialize_ex ::com::rti::atc::generated::Track_initialize_ex
#define T_finalize_ex   ::com::rti::atc::generated::Track_finalize_ex
#define T_copy       ::com::rti::atc::generated::Track_copy

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
#undef T_finalize_ex
#undef T_initialize_ex
#undef TSeq
#undef T

/* ========================================================================= */
const char *FlightRulesKindTYPENAME = "com::rti::atc::generated::FlightRulesKind";

DDS_TypeCode* FlightRulesKind_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode_Member FlightRulesKind_g_tc_members[4] =
    {
        {
            (char *)"IFR",/* Member name */
            {
                0,/* Ignored */
                DDS_BOOLEAN_FALSE, /* Ignored */
                -1, /* Ignored */
                NULL /* Ignored */
            },
            IFR, /* Enumerator ordinal */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            DDS_BOOLEAN_FALSE, /* Ignored */
            DDS_PRIVATE_MEMBER,/* Ignored */
            0,/* Ignored */
            NULL/* Ignored */
        },
        {
            (char *)"VFR",/* Member name */
            {
                0,/* Ignored */
                DDS_BOOLEAN_FALSE, /* Ignored */
                -1, /* Ignored */
                NULL /* Ignored */
            },
            VFR, /* Enumerator ordinal */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            DDS_BOOLEAN_FALSE, /* Ignored */
            DDS_PRIVATE_MEMBER,/* Ignored */
            0,/* Ignored */
            NULL/* Ignored */
        },
        {
            (char *)"IFR_THEN_CHANGE",/* Member name */
            {
                0,/* Ignored */
                DDS_BOOLEAN_FALSE, /* Ignored */
                -1, /* Ignored */
                NULL /* Ignored */
            },
            IFR_THEN_CHANGE, /* Enumerator ordinal */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            DDS_BOOLEAN_FALSE, /* Ignored */
            DDS_PRIVATE_MEMBER,/* Ignored */
            0,/* Ignored */
            NULL/* Ignored */
        },
        {
            (char *)"VFR_THEN_CHANGE",/* Member name */
            {
                0,/* Ignored */
                DDS_BOOLEAN_FALSE, /* Ignored */
                -1, /* Ignored */
                NULL /* Ignored */
            },
            VFR_THEN_CHANGE, /* Enumerator ordinal */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            DDS_BOOLEAN_FALSE, /* Ignored */
            DDS_PRIVATE_MEMBER,/* Ignored */
            0,/* Ignored */
            NULL/* Ignored */
        }
    };

    static DDS_TypeCode FlightRulesKind_g_tc = 
    {{
        DDS_TK_ENUM, /* Kind */
        DDS_BOOLEAN_FALSE, /* Ignored */
        -1, /* Ignored */
        (char *)"com::rti::atc::generated::FlightRulesKind", /* Name */
        NULL, /* Ignored */
        0, /* Ignored */
        0, /* Ignored */
        NULL, /* Ignored */
        4, /* Number of enumerators */
        FlightRulesKind_g_tc_members, /* Enumerators */
        DDS_VM_NONE /* Ignored */
}    };

    if (is_initialized) {
        return &FlightRulesKind_g_tc;
    }

    is_initialized = RTI_TRUE;
    return &FlightRulesKind_g_tc;
}
 

RTIBool FlightRulesKind_initialize(
    FlightRulesKind* sample)
{
    *sample = IFR;
    return RTI_TRUE;
}
        
RTIBool FlightRulesKind_initialize_ex(
    FlightRulesKind* sample,RTIBool allocatePointers,RTIBool allocateMemory)
{
    /* The following method initializes the enum value to zero. However,
     * some enumerations may not have a member with the value zero. In such
     * cases, it may be desirable to modify the generated code to use a valid
     * enumeration member instead.
     */
    if (allocatePointers) {} /* To avoid warnings */
    if (allocateMemory) {} /* To avoid warnings */
    *sample = IFR;
    return RTI_TRUE;
}

void FlightRulesKind_finalize(
    FlightRulesKind* sample)
{
    if (sample) {} /* To avoid warnings */
    /* empty */
}
        
void FlightRulesKind_finalize_ex(
    FlightRulesKind* sample,RTIBool deletePointers)
{
    if (sample) {} /* To avoid warnings */
    if (deletePointers) {} /* To avoid warnings */
    /* empty */
}

RTIBool FlightRulesKind_copy(
    FlightRulesKind* dst,
    const FlightRulesKind* src)
{
    return RTICdrType_copyEnum((RTICdrEnum *)dst, (RTICdrEnum *)src);
}


RTIBool FlightRulesKind_getValues(FlightRulesKindSeq * values) 
    
{
    int i = 0;
    FlightRulesKind * buffer;


    if (!values->maximum(4)) {
        return RTI_FALSE;
    }

    if (!values->length(4)) {
        return RTI_FALSE;
    }

    buffer = values->get_contiguous_buffer();
    
    buffer[i] = IFR;
    i++;
    
    buffer[i] = VFR;
    i++;
    
    buffer[i] = IFR_THEN_CHANGE;
    i++;
    
    buffer[i] = VFR_THEN_CHANGE;
    i++;
    

    return RTI_TRUE;
}

/**
 * <<IMPLEMENTATION>>
 *
 * Defines:  TSeq, T
 *
 * Configure and implement 'FlightRulesKind' sequence class.
 */
#define T FlightRulesKind
#define TSeq FlightRulesKindSeq
#define T_initialize_ex FlightRulesKind_initialize_ex
#define T_finalize_ex   FlightRulesKind_finalize_ex
#define T_copy       FlightRulesKind_copy

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
#undef T_finalize_ex
#undef T_initialize_ex
#undef TSeq
#undef T
/* ========================================================================= */
const char *FlightTypeKindTYPENAME = "com::rti::atc::generated::FlightTypeKind";

DDS_TypeCode* FlightTypeKind_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode_Member FlightTypeKind_g_tc_members[4] =
    {
        {
            (char *)"SCHEDULED_AIR_SERVICE",/* Member name */
            {
                0,/* Ignored */
                DDS_BOOLEAN_FALSE, /* Ignored */
                -1, /* Ignored */
                NULL /* Ignored */
            },
            SCHEDULED_AIR_SERVICE, /* Enumerator ordinal */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            DDS_BOOLEAN_FALSE, /* Ignored */
            DDS_PRIVATE_MEMBER,/* Ignored */
            0,/* Ignored */
            NULL/* Ignored */
        },
        {
            (char *)"NON_SCHEDULED_AIR_TRANSPORT",/* Member name */
            {
                0,/* Ignored */
                DDS_BOOLEAN_FALSE, /* Ignored */
                -1, /* Ignored */
                NULL /* Ignored */
            },
            NON_SCHEDULED_AIR_TRANSPORT, /* Enumerator ordinal */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            DDS_BOOLEAN_FALSE, /* Ignored */
            DDS_PRIVATE_MEMBER,/* Ignored */
            0,/* Ignored */
            NULL/* Ignored */
        },
        {
            (char *)"GENERAL_AVIATION",/* Member name */
            {
                0,/* Ignored */
                DDS_BOOLEAN_FALSE, /* Ignored */
                -1, /* Ignored */
                NULL /* Ignored */
            },
            GENERAL_AVIATION, /* Enumerator ordinal */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            DDS_BOOLEAN_FALSE, /* Ignored */
            DDS_PRIVATE_MEMBER,/* Ignored */
            0,/* Ignored */
            NULL/* Ignored */
        },
        {
            (char *)"MILITARY",/* Member name */
            {
                0,/* Ignored */
                DDS_BOOLEAN_FALSE, /* Ignored */
                -1, /* Ignored */
                NULL /* Ignored */
            },
            MILITARY, /* Enumerator ordinal */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            DDS_BOOLEAN_FALSE, /* Ignored */
            DDS_PRIVATE_MEMBER,/* Ignored */
            0,/* Ignored */
            NULL/* Ignored */
        }
    };

    static DDS_TypeCode FlightTypeKind_g_tc = 
    {{
        DDS_TK_ENUM, /* Kind */
        DDS_BOOLEAN_FALSE, /* Ignored */
        -1, /* Ignored */
        (char *)"com::rti::atc::generated::FlightTypeKind", /* Name */
        NULL, /* Ignored */
        0, /* Ignored */
        0, /* Ignored */
        NULL, /* Ignored */
        4, /* Number of enumerators */
        FlightTypeKind_g_tc_members, /* Enumerators */
        DDS_VM_NONE /* Ignored */
}    };

    if (is_initialized) {
        return &FlightTypeKind_g_tc;
    }

    is_initialized = RTI_TRUE;
    return &FlightTypeKind_g_tc;
}
 

RTIBool FlightTypeKind_initialize(
    FlightTypeKind* sample)
{
    *sample = SCHEDULED_AIR_SERVICE;
    return RTI_TRUE;
}
        
RTIBool FlightTypeKind_initialize_ex(
    FlightTypeKind* sample,RTIBool allocatePointers,RTIBool allocateMemory)
{
    /* The following method initializes the enum value to zero. However,
     * some enumerations may not have a member with the value zero. In such
     * cases, it may be desirable to modify the generated code to use a valid
     * enumeration member instead.
     */
    if (allocatePointers) {} /* To avoid warnings */
    if (allocateMemory) {} /* To avoid warnings */
    *sample = SCHEDULED_AIR_SERVICE;
    return RTI_TRUE;
}

void FlightTypeKind_finalize(
    FlightTypeKind* sample)
{
    if (sample) {} /* To avoid warnings */
    /* empty */
}
        
void FlightTypeKind_finalize_ex(
    FlightTypeKind* sample,RTIBool deletePointers)
{
    if (sample) {} /* To avoid warnings */
    if (deletePointers) {} /* To avoid warnings */
    /* empty */
}

RTIBool FlightTypeKind_copy(
    FlightTypeKind* dst,
    const FlightTypeKind* src)
{
    return RTICdrType_copyEnum((RTICdrEnum *)dst, (RTICdrEnum *)src);
}


RTIBool FlightTypeKind_getValues(FlightTypeKindSeq * values) 
    
{
    int i = 0;
    FlightTypeKind * buffer;


    if (!values->maximum(4)) {
        return RTI_FALSE;
    }

    if (!values->length(4)) {
        return RTI_FALSE;
    }

    buffer = values->get_contiguous_buffer();
    
    buffer[i] = SCHEDULED_AIR_SERVICE;
    i++;
    
    buffer[i] = NON_SCHEDULED_AIR_TRANSPORT;
    i++;
    
    buffer[i] = GENERAL_AVIATION;
    i++;
    
    buffer[i] = MILITARY;
    i++;
    

    return RTI_TRUE;
}

/**
 * <<IMPLEMENTATION>>
 *
 * Defines:  TSeq, T
 *
 * Configure and implement 'FlightTypeKind' sequence class.
 */
#define T FlightTypeKind
#define TSeq FlightTypeKindSeq
#define T_initialize_ex FlightTypeKind_initialize_ex
#define T_finalize_ex   FlightTypeKind_finalize_ex
#define T_copy       FlightTypeKind_copy

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
#undef T_finalize_ex
#undef T_initialize_ex
#undef TSeq
#undef T
/* ========================================================================= */
const char *EquipmentKindTYPENAME = "com::rti::atc::generated::EquipmentKind";

DDS_TypeCode* EquipmentKind_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode_Member EquipmentKind_g_tc_members[2] =
    {
        {
            (char *)"NO_COMMS",/* Member name */
            {
                0,/* Ignored */
                DDS_BOOLEAN_FALSE, /* Ignored */
                -1, /* Ignored */
                NULL /* Ignored */
            },
            NO_COMMS, /* Enumerator ordinal */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            DDS_BOOLEAN_FALSE, /* Ignored */
            DDS_PRIVATE_MEMBER,/* Ignored */
            0,/* Ignored */
            NULL/* Ignored */
        },
        {
            (char *)"STANDARD_COMMS",/* Member name */
            {
                0,/* Ignored */
                DDS_BOOLEAN_FALSE, /* Ignored */
                -1, /* Ignored */
                NULL /* Ignored */
            },
            STANDARD_COMMS, /* Enumerator ordinal */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            DDS_BOOLEAN_FALSE, /* Ignored */
            DDS_PRIVATE_MEMBER,/* Ignored */
            0,/* Ignored */
            NULL/* Ignored */
        }
    };

    static DDS_TypeCode EquipmentKind_g_tc = 
    {{
        DDS_TK_ENUM, /* Kind */
        DDS_BOOLEAN_FALSE, /* Ignored */
        -1, /* Ignored */
        (char *)"com::rti::atc::generated::EquipmentKind", /* Name */
        NULL, /* Ignored */
        0, /* Ignored */
        0, /* Ignored */
        NULL, /* Ignored */
        2, /* Number of enumerators */
        EquipmentKind_g_tc_members, /* Enumerators */
        DDS_VM_NONE /* Ignored */
}    };

    if (is_initialized) {
        return &EquipmentKind_g_tc;
    }

    is_initialized = RTI_TRUE;
    return &EquipmentKind_g_tc;
}
 

RTIBool EquipmentKind_initialize(
    EquipmentKind* sample)
{
    *sample = NO_COMMS;
    return RTI_TRUE;
}
        
RTIBool EquipmentKind_initialize_ex(
    EquipmentKind* sample,RTIBool allocatePointers,RTIBool allocateMemory)
{
    /* The following method initializes the enum value to zero. However,
     * some enumerations may not have a member with the value zero. In such
     * cases, it may be desirable to modify the generated code to use a valid
     * enumeration member instead.
     */
    if (allocatePointers) {} /* To avoid warnings */
    if (allocateMemory) {} /* To avoid warnings */
    *sample = NO_COMMS;
    return RTI_TRUE;
}

void EquipmentKind_finalize(
    EquipmentKind* sample)
{
    if (sample) {} /* To avoid warnings */
    /* empty */
}
        
void EquipmentKind_finalize_ex(
    EquipmentKind* sample,RTIBool deletePointers)
{
    if (sample) {} /* To avoid warnings */
    if (deletePointers) {} /* To avoid warnings */
    /* empty */
}

RTIBool EquipmentKind_copy(
    EquipmentKind* dst,
    const EquipmentKind* src)
{
    return RTICdrType_copyEnum((RTICdrEnum *)dst, (RTICdrEnum *)src);
}


RTIBool EquipmentKind_getValues(EquipmentKindSeq * values) 
    
{
    int i = 0;
    EquipmentKind * buffer;


    if (!values->maximum(2)) {
        return RTI_FALSE;
    }

    if (!values->length(2)) {
        return RTI_FALSE;
    }

    buffer = values->get_contiguous_buffer();
    
    buffer[i] = NO_COMMS;
    i++;
    
    buffer[i] = STANDARD_COMMS;
    i++;
    

    return RTI_TRUE;
}

/**
 * <<IMPLEMENTATION>>
 *
 * Defines:  TSeq, T
 *
 * Configure and implement 'EquipmentKind' sequence class.
 */
#define T EquipmentKind
#define TSeq EquipmentKindSeq
#define T_initialize_ex EquipmentKind_initialize_ex
#define T_finalize_ex   EquipmentKind_finalize_ex
#define T_copy       EquipmentKind_copy

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
#undef T_finalize_ex
#undef T_initialize_ex
#undef TSeq
#undef T
/* ========================================================================= */
const char *FlightPlanTYPENAME = "com::rti::atc::generated::FlightPlan";

DDS_TypeCode* FlightPlan_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode FlightPlan_g_tc_departureAerodrome_string = DDS_INITIALIZE_STRING_TYPECODE((com::rti::atc::generated::AERODROME_ID_LENGTH));
    static DDS_TypeCode FlightPlan_g_tc_destinationAerodrome_string = DDS_INITIALIZE_STRING_TYPECODE((com::rti::atc::generated::AERODROME_ID_LENGTH));
    static DDS_TypeCode FlightPlan_g_tc_alternateAerodromes_string = DDS_INITIALIZE_STRING_TYPECODE((com::rti::atc::generated::AERODROME_ID_LENGTH));
    static DDS_TypeCode FlightPlan_g_tc_alternateAerodromes_sequence = DDS_INITIALIZE_SEQUENCE_TYPECODE((com::rti::atc::generated::ALTERNATE_AERODROME_NUM),NULL);

    static DDS_TypeCode_Member FlightPlan_g_tc_members[11]=
    {
        {
            (char *)"flightId",/* Member name */
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
            DDS_BOOLEAN_TRUE, /* Is a key? */
            DDS_PRIVATE_MEMBER,/* Ignored */
            0,/* Ignored */
            NULL/* Ignored */
        },
        {
            (char *)"flightRules",/* Member name */
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
            DDS_BOOLEAN_FALSE, /* Is a key? */
            DDS_PRIVATE_MEMBER,/* Ignored */
            0,/* Ignored */
            NULL/* Ignored */
        },
        {
            (char *)"flightType",/* Member name */
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
            DDS_BOOLEAN_FALSE, /* Is a key? */
            DDS_PRIVATE_MEMBER,/* Ignored */
            0,/* Ignored */
            NULL/* Ignored */
        },
        {
            (char *)"equipmentType",/* Member name */
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
            DDS_BOOLEAN_FALSE, /* Is a key? */
            DDS_PRIVATE_MEMBER,/* Ignored */
            0,/* Ignored */
            NULL/* Ignored */
        },
        {
            (char *)"departureAerodrome",/* Member name */
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
            DDS_BOOLEAN_FALSE, /* Is a key? */
            DDS_PRIVATE_MEMBER,/* Ignored */
            0,/* Ignored */
            NULL/* Ignored */
        },
        {
            (char *)"departureHour",/* Member name */
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
            DDS_BOOLEAN_FALSE, /* Is a key? */
            DDS_PRIVATE_MEMBER,/* Ignored */
            0,/* Ignored */
            NULL/* Ignored */
        },
        {
            (char *)"departureMin",/* Member name */
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
            DDS_BOOLEAN_FALSE, /* Is a key? */
            DDS_PRIVATE_MEMBER,/* Ignored */
            0,/* Ignored */
            NULL/* Ignored */
        },
        {
            (char *)"destinationAerodrome",/* Member name */
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
            DDS_BOOLEAN_FALSE, /* Is a key? */
            DDS_PRIVATE_MEMBER,/* Ignored */
            0,/* Ignored */
            NULL/* Ignored */
        },
        {
            (char *)"estimatedHours",/* Member name */
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
            DDS_BOOLEAN_FALSE, /* Is a key? */
            DDS_PRIVATE_MEMBER,/* Ignored */
            0,/* Ignored */
            NULL/* Ignored */
        },
        {
            (char *)"estimatedMinutes",/* Member name */
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
            DDS_BOOLEAN_FALSE, /* Is a key? */
            DDS_PRIVATE_MEMBER,/* Ignored */
            0,/* Ignored */
            NULL/* Ignored */
        },
        {
            (char *)"alternateAerodromes",/* Member name */
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
            DDS_BOOLEAN_FALSE, /* Is a key? */
            DDS_PRIVATE_MEMBER,/* Ignored */
            0,/* Ignored */
            NULL/* Ignored */
        }
    };

    static DDS_TypeCode FlightPlan_g_tc =
    {{
        DDS_TK_STRUCT,/* Kind */
        DDS_BOOLEAN_FALSE, /* Ignored */
        -1,/* Ignored */
        (char *)"com::rti::atc::generated::FlightPlan", /* Name */
        NULL, /* Ignored */
        0, /* Ignored */
        0, /* Ignored */
        NULL, /* Ignored */
        11, /* Number of members */
        FlightPlan_g_tc_members, /* Members */
        DDS_VM_NONE /* Ignored */
    }}; /* Type code for FlightPlan*/

    if (is_initialized) {
        return &FlightPlan_g_tc;
    }

    FlightPlan_g_tc_alternateAerodromes_sequence._data._typeCode = (RTICdrTypeCode *)&FlightPlan_g_tc_alternateAerodromes_string;

    FlightPlan_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)com::rti::atc::generated::FlightId_get_typecode();
    FlightPlan_g_tc_members[1]._representation._typeCode = (RTICdrTypeCode *)com::rti::atc::generated::FlightRulesKind_get_typecode();
    FlightPlan_g_tc_members[2]._representation._typeCode = (RTICdrTypeCode *)com::rti::atc::generated::FlightTypeKind_get_typecode();
    FlightPlan_g_tc_members[3]._representation._typeCode = (RTICdrTypeCode *)com::rti::atc::generated::EquipmentKind_get_typecode();
    FlightPlan_g_tc_members[4]._representation._typeCode = (RTICdrTypeCode *)&FlightPlan_g_tc_departureAerodrome_string;
    FlightPlan_g_tc_members[5]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_short;
    FlightPlan_g_tc_members[6]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_short;
    FlightPlan_g_tc_members[7]._representation._typeCode = (RTICdrTypeCode *)&FlightPlan_g_tc_destinationAerodrome_string;
    FlightPlan_g_tc_members[8]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_short;
    FlightPlan_g_tc_members[9]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_short;
    FlightPlan_g_tc_members[10]._representation._typeCode = (RTICdrTypeCode *)&FlightPlan_g_tc_alternateAerodromes_sequence;

    is_initialized = RTI_TRUE;

    return &FlightPlan_g_tc;
}


RTIBool FlightPlan_initialize(
    FlightPlan* sample) {
  return ::com::rti::atc::generated::FlightPlan_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}
        
RTIBool FlightPlan_initialize_ex(
    FlightPlan* sample,RTIBool allocatePointers,RTIBool allocateMemory)
{

    void* buffer = NULL;
    if (buffer) {} /* To avoid warnings */
        
    
    if (allocatePointers) {} /* To avoid warnings */
    if (allocateMemory) {} /* To avoid warnings */

    if (!com::rti::atc::generated::FlightId_initialize_ex(&sample->flightId,allocatePointers,allocateMemory)) {
        return RTI_FALSE;
    }
            

    if (!com::rti::atc::generated::FlightRulesKind_initialize_ex(&sample->flightRules,allocatePointers,allocateMemory)) {
        return RTI_FALSE;
    }
            

    if (!com::rti::atc::generated::FlightTypeKind_initialize_ex(&sample->flightType,allocatePointers,allocateMemory)) {
        return RTI_FALSE;
    }
            

    if (!com::rti::atc::generated::EquipmentKind_initialize_ex(&sample->equipmentType,allocatePointers,allocateMemory)) {
        return RTI_FALSE;
    }
            

    if (allocateMemory) {
        sample->departureAerodrome = DDS_String_alloc(((com::rti::atc::generated::AERODROME_ID_LENGTH)));
        if (sample->departureAerodrome == NULL) {
            return RTI_FALSE;
        }
    } else {
        if (sample->departureAerodrome != NULL) { 
            sample->departureAerodrome[0] = '\0';
        }
    }
            

    if (!RTICdrType_initShort(&sample->departureHour)) {
        return RTI_FALSE;
    }                
            

    if (!RTICdrType_initShort(&sample->departureMin)) {
        return RTI_FALSE;
    }                
            

    if (allocateMemory) {
        sample->destinationAerodrome = DDS_String_alloc(((com::rti::atc::generated::AERODROME_ID_LENGTH)));
        if (sample->destinationAerodrome == NULL) {
            return RTI_FALSE;
        }
    } else {
        if (sample->destinationAerodrome != NULL) { 
            sample->destinationAerodrome[0] = '\0';
        }
    }
            

    if (!RTICdrType_initShort(&sample->estimatedHours)) {
        return RTI_FALSE;
    }                
            

    if (!RTICdrType_initShort(&sample->estimatedMinutes)) {
        return RTI_FALSE;
    }                
            

    if (allocateMemory) {    
        DDS_StringSeq_initialize(&sample->alternateAerodromes);
        if (!DDS_StringSeq_set_maximum(&sample->alternateAerodromes,
                                       ((com::rti::atc::generated::ALTERNATE_AERODROME_NUM)))) {
            return RTI_FALSE;
        }
        buffer = DDS_StringSeq_get_contiguous_bufferI(&sample->alternateAerodromes);
        if (buffer == NULL) {
            return RTI_FALSE;
        }
        if (!RTICdrType_initStringArray(buffer, ((com::rti::atc::generated::ALTERNATE_AERODROME_NUM)),((com::rti::atc::generated::AERODROME_ID_LENGTH))+1,
            RTI_CDR_CHAR_TYPE)) {
            return RTI_FALSE;
        }
    } else {
        DDS_StringSeq_set_length(&sample->alternateAerodromes, 0);
    }
            


    return RTI_TRUE;
}

void FlightPlan_finalize(
    FlightPlan* sample)
{
    ::com::rti::atc::generated::FlightPlan_finalize_ex(sample,RTI_TRUE);
}
        
void FlightPlan_finalize_ex(
    FlightPlan* sample,RTIBool deletePointers)
{        
    if (sample) { } /* To avoid warnings */
    if (deletePointers) {} /* To avoid warnings */


    com::rti::atc::generated::FlightId_finalize_ex(&sample->flightId,deletePointers);
            

    com::rti::atc::generated::FlightRulesKind_finalize_ex(&sample->flightRules,deletePointers);
            

    com::rti::atc::generated::FlightTypeKind_finalize_ex(&sample->flightType,deletePointers);
            

    com::rti::atc::generated::EquipmentKind_finalize_ex(&sample->equipmentType,deletePointers);
            

    DDS_String_free(sample->departureAerodrome);                
            



    DDS_String_free(sample->destinationAerodrome);                
            



    DDS_StringSeq_finalize(&sample->alternateAerodromes);
            

}

RTIBool FlightPlan_copy(
    FlightPlan* dst,
    const FlightPlan* src)
{        

    if (!com::rti::atc::generated::FlightId_copy(
        &dst->flightId, &src->flightId)) {
        return RTI_FALSE;
    }
            

    if (!com::rti::atc::generated::FlightRulesKind_copy(
        &dst->flightRules, &src->flightRules)) {
        return RTI_FALSE;
    }
            

    if (!com::rti::atc::generated::FlightTypeKind_copy(
        &dst->flightType, &src->flightType)) {
        return RTI_FALSE;
    }
            

    if (!com::rti::atc::generated::EquipmentKind_copy(
        &dst->equipmentType, &src->equipmentType)) {
        return RTI_FALSE;
    }
            

    if (!RTICdrType_copyString(
        dst->departureAerodrome, src->departureAerodrome, ((com::rti::atc::generated::AERODROME_ID_LENGTH)) + 1)) {
        return RTI_FALSE;
    }
            

    if (!RTICdrType_copyShort(
        &dst->departureHour, &src->departureHour)) {
        return RTI_FALSE;
    }
            

    if (!RTICdrType_copyShort(
        &dst->departureMin, &src->departureMin)) {
        return RTI_FALSE;
    }
            

    if (!RTICdrType_copyString(
        dst->destinationAerodrome, src->destinationAerodrome, ((com::rti::atc::generated::AERODROME_ID_LENGTH)) + 1)) {
        return RTI_FALSE;
    }
            

    if (!RTICdrType_copyShort(
        &dst->estimatedHours, &src->estimatedHours)) {
        return RTI_FALSE;
    }
            

    if (!RTICdrType_copyShort(
        &dst->estimatedMinutes, &src->estimatedMinutes)) {
        return RTI_FALSE;
    }
            

    if (!DDS_StringSeq_copy_no_alloc(&dst->alternateAerodromes,
                                      &src->alternateAerodromes)) {
        return RTI_FALSE;
    }
            


    return RTI_TRUE;
}


/**
 * <<IMPLEMENTATION>>
 *
 * Defines:  TSeq, T
 *
 * Configure and implement 'FlightPlan' sequence class.
 */
#define T FlightPlan
#define TSeq FlightPlanSeq
#define T_initialize_ex ::com::rti::atc::generated::FlightPlan_initialize_ex
#define T_finalize_ex   ::com::rti::atc::generated::FlightPlan_finalize_ex
#define T_copy       ::com::rti::atc::generated::FlightPlan_copy

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
#undef T_finalize_ex
#undef T_initialize_ex
#undef TSeq
#undef T


} /* namespace generated */

} /* namespace atc */

} /* namespace rti */

} /* namespace com */
