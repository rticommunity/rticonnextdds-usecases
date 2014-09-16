
/*
  WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

  This file was generated from ChocolateFactory.idl using "rtiddsgen".
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



#include "ChocolateFactory.h"


namespace com{

namespace rti{

namespace chocolatefactory{

namespace generated{
/* ========================================================================= */
const char *StationControllerKindTYPENAME = "com::rti::chocolatefactory::generated::StationControllerKind";

DDS_TypeCode* StationControllerKind_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode_Member StationControllerKind_g_tc_members[6] =
    {
        {
            (char *)"INVALID_CONTROLLER",/* Member name */
            {
                0,/* Ignored */
                DDS_BOOLEAN_FALSE, /* Ignored */
                -1, /* Ignored */
                NULL /* Ignored */
            },
            INVALID_CONTROLLER, /* Enumerator ordinal */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            RTI_CDR_REQUIRED_MEMBER, /* Ignored */
            DDS_PRIVATE_MEMBER,/* Ignored */
            1,
            NULL/* Ignored */
        },
        {
            (char *)"SUGAR_CONTROLLER",/* Member name */
            {
                0,/* Ignored */
                DDS_BOOLEAN_FALSE, /* Ignored */
                -1, /* Ignored */
                NULL /* Ignored */
            },
            SUGAR_CONTROLLER, /* Enumerator ordinal */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            RTI_CDR_REQUIRED_MEMBER, /* Ignored */
            DDS_PRIVATE_MEMBER,/* Ignored */
            1,
            NULL/* Ignored */
        },
        {
            (char *)"COCOA_BUTTER_CONTROLLER",/* Member name */
            {
                0,/* Ignored */
                DDS_BOOLEAN_FALSE, /* Ignored */
                -1, /* Ignored */
                NULL /* Ignored */
            },
            COCOA_BUTTER_CONTROLLER, /* Enumerator ordinal */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            RTI_CDR_REQUIRED_MEMBER, /* Ignored */
            DDS_PRIVATE_MEMBER,/* Ignored */
            1,
            NULL/* Ignored */
        },
        {
            (char *)"COCOA_LIQUOR_CONTROLLER",/* Member name */
            {
                0,/* Ignored */
                DDS_BOOLEAN_FALSE, /* Ignored */
                -1, /* Ignored */
                NULL /* Ignored */
            },
            COCOA_LIQUOR_CONTROLLER, /* Enumerator ordinal */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            RTI_CDR_REQUIRED_MEMBER, /* Ignored */
            DDS_PRIVATE_MEMBER,/* Ignored */
            1,
            NULL/* Ignored */
        },
        {
            (char *)"VANILLA_CONTROLLER",/* Member name */
            {
                0,/* Ignored */
                DDS_BOOLEAN_FALSE, /* Ignored */
                -1, /* Ignored */
                NULL /* Ignored */
            },
            VANILLA_CONTROLLER, /* Enumerator ordinal */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            RTI_CDR_REQUIRED_MEMBER, /* Ignored */
            DDS_PRIVATE_MEMBER,/* Ignored */
            1,
            NULL/* Ignored */
        },
        {
            (char *)"MILK_CONTROLLER",/* Member name */
            {
                0,/* Ignored */
                DDS_BOOLEAN_FALSE, /* Ignored */
                -1, /* Ignored */
                NULL /* Ignored */
            },
            MILK_CONTROLLER, /* Enumerator ordinal */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            RTI_CDR_REQUIRED_MEMBER, /* Ignored */
            DDS_PRIVATE_MEMBER,/* Ignored */
            1,
            NULL/* Ignored */
        }
    };

    static DDS_TypeCode StationControllerKind_g_tc = 
    {{
        DDS_TK_ENUM, /* Kind */
        DDS_BOOLEAN_FALSE, /* Ignored */
        -1, /* Ignored */
        (char *)"com::rti::chocolatefactory::generated::StationControllerKind", /* Name */
        NULL, /* Ignored */
        0, /* Ignored */
        0, /* Ignored */
        NULL, /* Ignored */
        6, /* Number of enumerators */
        StationControllerKind_g_tc_members, /* Enumerators */
        DDS_VM_NONE /* Ignored */
}    };

    if (is_initialized) {
        return &StationControllerKind_g_tc;
    }

    is_initialized = RTI_TRUE;
    return &StationControllerKind_g_tc;
}
 

RTIBool StationControllerKind_initialize(
    StationControllerKind* sample)
{
    *sample = INVALID_CONTROLLER;
    return RTI_TRUE;
}
        
RTIBool StationControllerKind_initialize_ex(
    StationControllerKind* sample,RTIBool allocatePointers,RTIBool allocateMemory)
{
    if (allocatePointers) {} /* To avoid warnings */
    if (allocateMemory) {} /* To avoid warnings */
    *sample = INVALID_CONTROLLER;
    return RTI_TRUE;
}

RTIBool StationControllerKind_initialize_w_params(
        StationControllerKind* sample,
        const struct DDS_TypeAllocationParams_t * allocParams)
{
    if (allocParams) {} /* To avoid warnings */
    *sample = INVALID_CONTROLLER;
    return RTI_TRUE;
}

void StationControllerKind_finalize(
    StationControllerKind* sample)
{
    if (sample) {} /* To avoid warnings */
    /* empty */
}
        
void StationControllerKind_finalize_ex(
    StationControllerKind* sample,RTIBool deletePointers)
{
    if (sample) {} /* To avoid warnings */
    if (deletePointers) {} /* To avoid warnings */
    /* empty */
}

void StationControllerKind_finalize_w_params(
        StationControllerKind* sample,
        const struct DDS_TypeDeallocationParams_t * deallocParams)
{
    if (sample) {} /* To avoid warnings */
    if (deallocParams) {} /* To avoid warnings */
    /* empty */
}

RTIBool StationControllerKind_copy(
    StationControllerKind* dst,
    const StationControllerKind* src)
{
    return RTICdrType_copyEnum((RTICdrEnum *)dst, (RTICdrEnum *)src);
}


RTIBool StationControllerKind_getValues(StationControllerKindSeq * values) 
    
{
    int i = 0;
    StationControllerKind * buffer;


    if (!values->maximum(6)) {
        return RTI_FALSE;
    }

    if (!values->length(6)) {
        return RTI_FALSE;
    }

    buffer = values->get_contiguous_buffer();
    
    buffer[i] = INVALID_CONTROLLER;
    i++;
    
    buffer[i] = SUGAR_CONTROLLER;
    i++;
    
    buffer[i] = COCOA_BUTTER_CONTROLLER;
    i++;
    
    buffer[i] = COCOA_LIQUOR_CONTROLLER;
    i++;
    
    buffer[i] = VANILLA_CONTROLLER;
    i++;
    
    buffer[i] = MILK_CONTROLLER;
    i++;
    

    return RTI_TRUE;
}

/**
 * <<IMPLEMENTATION>>
 *
 * Defines:  TSeq, T
 *
 * Configure and implement 'StationControllerKind' sequence class.
 */
#define T StationControllerKind
#define TSeq StationControllerKindSeq
#define T_initialize_w_params StationControllerKind_initialize_w_params
#define T_finalize_w_params   StationControllerKind_finalize_w_params
#define T_copy       StationControllerKind_copy

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
/* ========================================================================= */
const char *LotStatusKindTYPENAME = "com::rti::chocolatefactory::generated::LotStatusKind";

DDS_TypeCode* LotStatusKind_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode_Member LotStatusKind_g_tc_members[4] =
    {
        {
            (char *)"ASSIGNED_TO_SC",/* Member name */
            {
                0,/* Ignored */
                DDS_BOOLEAN_FALSE, /* Ignored */
                -1, /* Ignored */
                NULL /* Ignored */
            },
            ASSIGNED_TO_SC, /* Enumerator ordinal */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            RTI_CDR_REQUIRED_MEMBER, /* Ignored */
            DDS_PRIVATE_MEMBER,/* Ignored */
            1,
            NULL/* Ignored */
        },
        {
            (char *)"WAITING_AT_SC",/* Member name */
            {
                0,/* Ignored */
                DDS_BOOLEAN_FALSE, /* Ignored */
                -1, /* Ignored */
                NULL /* Ignored */
            },
            WAITING_AT_SC, /* Enumerator ordinal */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            RTI_CDR_REQUIRED_MEMBER, /* Ignored */
            DDS_PRIVATE_MEMBER,/* Ignored */
            1,
            NULL/* Ignored */
        },
        {
            (char *)"PROCESSING_AT_SC",/* Member name */
            {
                0,/* Ignored */
                DDS_BOOLEAN_FALSE, /* Ignored */
                -1, /* Ignored */
                NULL /* Ignored */
            },
            PROCESSING_AT_SC, /* Enumerator ordinal */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            RTI_CDR_REQUIRED_MEMBER, /* Ignored */
            DDS_PRIVATE_MEMBER,/* Ignored */
            1,
            NULL/* Ignored */
        },
        {
            (char *)"LOT_COMPLETED",/* Member name */
            {
                0,/* Ignored */
                DDS_BOOLEAN_FALSE, /* Ignored */
                -1, /* Ignored */
                NULL /* Ignored */
            },
            LOT_COMPLETED, /* Enumerator ordinal */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            RTI_CDR_REQUIRED_MEMBER, /* Ignored */
            DDS_PRIVATE_MEMBER,/* Ignored */
            1,
            NULL/* Ignored */
        }
    };

    static DDS_TypeCode LotStatusKind_g_tc = 
    {{
        DDS_TK_ENUM, /* Kind */
        DDS_BOOLEAN_FALSE, /* Ignored */
        -1, /* Ignored */
        (char *)"com::rti::chocolatefactory::generated::LotStatusKind", /* Name */
        NULL, /* Ignored */
        0, /* Ignored */
        0, /* Ignored */
        NULL, /* Ignored */
        4, /* Number of enumerators */
        LotStatusKind_g_tc_members, /* Enumerators */
        DDS_VM_NONE /* Ignored */
}    };

    if (is_initialized) {
        return &LotStatusKind_g_tc;
    }

    is_initialized = RTI_TRUE;
    return &LotStatusKind_g_tc;
}
 

RTIBool LotStatusKind_initialize(
    LotStatusKind* sample)
{
    *sample = ASSIGNED_TO_SC;
    return RTI_TRUE;
}
        
RTIBool LotStatusKind_initialize_ex(
    LotStatusKind* sample,RTIBool allocatePointers,RTIBool allocateMemory)
{
    if (allocatePointers) {} /* To avoid warnings */
    if (allocateMemory) {} /* To avoid warnings */
    *sample = ASSIGNED_TO_SC;
    return RTI_TRUE;
}

RTIBool LotStatusKind_initialize_w_params(
        LotStatusKind* sample,
        const struct DDS_TypeAllocationParams_t * allocParams)
{
    if (allocParams) {} /* To avoid warnings */
    *sample = ASSIGNED_TO_SC;
    return RTI_TRUE;
}

void LotStatusKind_finalize(
    LotStatusKind* sample)
{
    if (sample) {} /* To avoid warnings */
    /* empty */
}
        
void LotStatusKind_finalize_ex(
    LotStatusKind* sample,RTIBool deletePointers)
{
    if (sample) {} /* To avoid warnings */
    if (deletePointers) {} /* To avoid warnings */
    /* empty */
}

void LotStatusKind_finalize_w_params(
        LotStatusKind* sample,
        const struct DDS_TypeDeallocationParams_t * deallocParams)
{
    if (sample) {} /* To avoid warnings */
    if (deallocParams) {} /* To avoid warnings */
    /* empty */
}

RTIBool LotStatusKind_copy(
    LotStatusKind* dst,
    const LotStatusKind* src)
{
    return RTICdrType_copyEnum((RTICdrEnum *)dst, (RTICdrEnum *)src);
}


RTIBool LotStatusKind_getValues(LotStatusKindSeq * values) 
    
{
    int i = 0;
    LotStatusKind * buffer;


    if (!values->maximum(4)) {
        return RTI_FALSE;
    }

    if (!values->length(4)) {
        return RTI_FALSE;
    }

    buffer = values->get_contiguous_buffer();
    
    buffer[i] = ASSIGNED_TO_SC;
    i++;
    
    buffer[i] = WAITING_AT_SC;
    i++;
    
    buffer[i] = PROCESSING_AT_SC;
    i++;
    
    buffer[i] = LOT_COMPLETED;
    i++;
    

    return RTI_TRUE;
}

/**
 * <<IMPLEMENTATION>>
 *
 * Defines:  TSeq, T
 *
 * Configure and implement 'LotStatusKind' sequence class.
 */
#define T LotStatusKind
#define TSeq LotStatusKindSeq
#define T_initialize_w_params LotStatusKind_initialize_w_params
#define T_finalize_w_params   LotStatusKind_finalize_w_params
#define T_copy       LotStatusKind_copy

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
/* ========================================================================= */
const char *RecipeStepTYPENAME = "com::rti::chocolatefactory::generated::RecipeStep";

DDS_TypeCode* RecipeStep_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;


    static DDS_TypeCode_Member RecipeStep_g_tc_members[2]=
    {
        {
            (char *)"stationController",/* Member name */
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
            RTI_CDR_REQUIRED_MEMBER, /* Member flags */
            DDS_PRIVATE_MEMBER,/* Ignored */
            1,
            NULL/* Ignored */
        },
        {
            (char *)"seconds",/* Member name */
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
        }
    };

    static DDS_TypeCode RecipeStep_g_tc =
    {{
        DDS_TK_STRUCT,/* Kind */
        DDS_BOOLEAN_FALSE, /* Ignored */
        -1,/* Ignored */
        (char *)"com::rti::chocolatefactory::generated::RecipeStep", /* Name */
        NULL, /* Ignored */
        0, /* Ignored */
        0, /* Ignored */
        NULL, /* Ignored */
        2, /* Number of members */
        RecipeStep_g_tc_members, /* Members */
        DDS_VM_NONE /* Ignored */
    }}; /* Type code for RecipeStep*/

    if (is_initialized) {
        return &RecipeStep_g_tc;
    }


    RecipeStep_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)com::rti::chocolatefactory::generated::StationControllerKind_get_typecode();
    RecipeStep_g_tc_members[1]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_long;

    is_initialized = RTI_TRUE;

    return &RecipeStep_g_tc;
}


RTIBool RecipeStep_initialize(
    RecipeStep* sample) {
  return ::com::rti::chocolatefactory::generated::RecipeStep_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}
        
RTIBool RecipeStep_initialize_ex(
    RecipeStep* sample,RTIBool allocatePointers,RTIBool allocateMemory)
{
    struct DDS_TypeAllocationParams_t allocParams =
        DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;
        
    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;
    
    return ::com::rti::chocolatefactory::generated::RecipeStep_initialize_w_params(
        sample,&allocParams);
}

RTIBool RecipeStep_initialize_w_params(
        RecipeStep* sample,
        const struct DDS_TypeAllocationParams_t * allocParams)
{
        
    
    if (allocParams) {} /* To avoid warnings */
        

    if (!com::rti::chocolatefactory::generated::StationControllerKind_initialize_w_params(&sample->stationController,allocParams)) {
        return RTI_FALSE;
    }
            

    if (!RTICdrType_initLong(&sample->seconds)) {
        return RTI_FALSE;
    }                
            


    return RTI_TRUE;
}

void RecipeStep_finalize(
    RecipeStep* sample)
{
    ::com::rti::chocolatefactory::generated::RecipeStep_finalize_ex(sample,RTI_TRUE);
}
        
void RecipeStep_finalize_ex(
    RecipeStep* sample,RTIBool deletePointers)
{        
    struct DDS_TypeDeallocationParams_t deallocParams =
            DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample) { } /* To avoid warnings */
    
    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    ::com::rti::chocolatefactory::generated::RecipeStep_finalize_w_params(
        sample,&deallocParams);
}

void RecipeStep_finalize_w_params(
        RecipeStep* sample,
        const struct DDS_TypeDeallocationParams_t * deallocParams)
{    
    if (sample) { } /* To avoid warnings */
    if (deallocParams) {} /* To avoid warnings */


    com::rti::chocolatefactory::generated::StationControllerKind_finalize_w_params(&sample->stationController, deallocParams);
            


}

void RecipeStep_finalize_optional_members(
    RecipeStep* sample, RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParamsTmp =
        DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;
    struct DDS_TypeDeallocationParams_t * deallocParams =
        &deallocParamsTmp;
    if (sample) { } /* To avoid warnings */
    if (deallocParams) {} /* To avoid warnings */

        

    deallocParamsTmp.delete_pointers = (DDS_Boolean)deletePointers;
    deallocParamsTmp.delete_optional_members = DDS_BOOLEAN_TRUE;    
             

    com::rti::chocolatefactory::generated::StationControllerKind_finalize_w_params(&sample->stationController, deallocParams);
            


}

RTIBool RecipeStep_copy(
    RecipeStep* dst,
    const RecipeStep* src)
{

    if (!com::rti::chocolatefactory::generated::StationControllerKind_copy(
        &dst->stationController, &src->stationController)) {
        return RTI_FALSE;
    }
            

    if (!RTICdrType_copyLong(
        &dst->seconds, &src->seconds)) {
        return RTI_FALSE;
    }
            


    return RTI_TRUE;
}


/**
 * <<IMPLEMENTATION>>
 *
 * Defines:  TSeq, T
 *
 * Configure and implement 'RecipeStep' sequence class.
 */
#define T RecipeStep
#define TSeq RecipeStepSeq
#define T_initialize_w_params ::com::rti::chocolatefactory::generated::RecipeStep_initialize_w_params
#define T_finalize_w_params   ::com::rti::chocolatefactory::generated::RecipeStep_finalize_w_params
#define T_copy       ::com::rti::chocolatefactory::generated::RecipeStep_copy

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

/* ========================================================================= */
const char *ChocolateRecipeTYPENAME = "com::rti::chocolatefactory::generated::ChocolateRecipe";

DDS_TypeCode* ChocolateRecipe_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode ChocolateRecipe_g_tc_recipeName_string = DDS_INITIALIZE_STRING_TYPECODE((com::rti::chocolatefactory::generated::MAX_STRING_LENGTH));
    static DDS_TypeCode ChocolateRecipe_g_tc_steps_sequence = DDS_INITIALIZE_SEQUENCE_TYPECODE((com::rti::chocolatefactory::generated::MAX_RECIPE_STEPS),NULL);

    static DDS_TypeCode_Member ChocolateRecipe_g_tc_members[2]=
    {
        {
            (char *)"recipeName",/* Member name */
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
            (char *)"steps",/* Member name */
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
        }
    };

    static DDS_TypeCode ChocolateRecipe_g_tc =
    {{
        DDS_TK_STRUCT,/* Kind */
        DDS_BOOLEAN_FALSE, /* Ignored */
        -1,/* Ignored */
        (char *)"com::rti::chocolatefactory::generated::ChocolateRecipe", /* Name */
        NULL, /* Ignored */
        0, /* Ignored */
        0, /* Ignored */
        NULL, /* Ignored */
        2, /* Number of members */
        ChocolateRecipe_g_tc_members, /* Members */
        DDS_VM_NONE /* Ignored */
    }}; /* Type code for ChocolateRecipe*/

    if (is_initialized) {
        return &ChocolateRecipe_g_tc;
    }

    ChocolateRecipe_g_tc_steps_sequence._data._typeCode = (RTICdrTypeCode *)com::rti::chocolatefactory::generated::RecipeStep_get_typecode();

    ChocolateRecipe_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)&ChocolateRecipe_g_tc_recipeName_string;
    ChocolateRecipe_g_tc_members[1]._representation._typeCode = (RTICdrTypeCode *)&ChocolateRecipe_g_tc_steps_sequence;

    is_initialized = RTI_TRUE;

    return &ChocolateRecipe_g_tc;
}


RTIBool ChocolateRecipe_initialize(
    ChocolateRecipe* sample) {
  return ::com::rti::chocolatefactory::generated::ChocolateRecipe_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}
        
RTIBool ChocolateRecipe_initialize_ex(
    ChocolateRecipe* sample,RTIBool allocatePointers,RTIBool allocateMemory)
{
    struct DDS_TypeAllocationParams_t allocParams =
        DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;
        
    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;
    
    return ::com::rti::chocolatefactory::generated::ChocolateRecipe_initialize_w_params(
        sample,&allocParams);
}

RTIBool ChocolateRecipe_initialize_w_params(
        ChocolateRecipe* sample,
        const struct DDS_TypeAllocationParams_t * allocParams)
{

    void* buffer = NULL;
    if (buffer) {} /* To avoid warnings */
        
    
    if (allocParams) {} /* To avoid warnings */
        

    if (allocParams->allocate_memory) {
        sample->recipeName = DDS_String_alloc(((com::rti::chocolatefactory::generated::MAX_STRING_LENGTH)));
        if (sample->recipeName == NULL) {
            return RTI_FALSE;
        }
    } else {
        if (sample->recipeName != NULL) { 
            sample->recipeName[0] = '\0';
        }
    }
            

    if (allocParams->allocate_memory) {
        com::rti::chocolatefactory::generated::RecipeStepSeq_initialize(&sample->steps);
        com::rti::chocolatefactory::generated::RecipeStepSeq_set_element_allocation_params(&sample->steps,allocParams);
        if (!com::rti::chocolatefactory::generated::RecipeStepSeq_set_maximum(&sample->steps,
                                           ((com::rti::chocolatefactory::generated::MAX_RECIPE_STEPS)))) {
            return RTI_FALSE;
        }
    } else {
        com::rti::chocolatefactory::generated::RecipeStepSeq_set_length(&sample->steps,0);
    }
            


    return RTI_TRUE;
}

void ChocolateRecipe_finalize(
    ChocolateRecipe* sample)
{
    ::com::rti::chocolatefactory::generated::ChocolateRecipe_finalize_ex(sample,RTI_TRUE);
}
        
void ChocolateRecipe_finalize_ex(
    ChocolateRecipe* sample,RTIBool deletePointers)
{        
    struct DDS_TypeDeallocationParams_t deallocParams =
            DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample) { } /* To avoid warnings */
    
    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    ::com::rti::chocolatefactory::generated::ChocolateRecipe_finalize_w_params(
        sample,&deallocParams);
}

void ChocolateRecipe_finalize_w_params(
        ChocolateRecipe* sample,
        const struct DDS_TypeDeallocationParams_t * deallocParams)
{    
    if (sample) { } /* To avoid warnings */
    if (deallocParams) {} /* To avoid warnings */


    if (sample->recipeName != NULL) {    
        DDS_String_free(sample->recipeName);
        sample->recipeName = NULL;
    }
            

    com::rti::chocolatefactory::generated::RecipeStepSeq_set_element_deallocation_params(&sample->steps,deallocParams);
    com::rti::chocolatefactory::generated::RecipeStepSeq_finalize(&sample->steps);
            

}

void ChocolateRecipe_finalize_optional_members(
    ChocolateRecipe* sample, RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParamsTmp =
        DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;
    struct DDS_TypeDeallocationParams_t * deallocParams =
        &deallocParamsTmp;
    if (sample) { } /* To avoid warnings */
    if (deallocParams) {} /* To avoid warnings */

        

    deallocParamsTmp.delete_pointers = (DDS_Boolean)deletePointers;
    deallocParamsTmp.delete_optional_members = DDS_BOOLEAN_TRUE;    
             


    {
        DDS_UnsignedLong i, length;
        length = com::rti::chocolatefactory::generated::RecipeStepSeq_get_length(
            &sample->steps);

        for (i = 0; i < length; i++) {
            com::rti::chocolatefactory::generated::RecipeStep_finalize_optional_members(
                com::rti::chocolatefactory::generated::RecipeStepSeq_get_reference(
                    &sample->steps, i), deallocParams->delete_pointers);
        }
    }         
            

}

RTIBool ChocolateRecipe_copy(
    ChocolateRecipe* dst,
    const ChocolateRecipe* src)
{

    if (!RTICdrType_copyString(
        dst->recipeName, src->recipeName, ((com::rti::chocolatefactory::generated::MAX_STRING_LENGTH)) + 1)) {
        return RTI_FALSE;
    }
            

    if (!com::rti::chocolatefactory::generated::RecipeStepSeq_copy(&dst->steps,
                                          &src->steps)) {
        return RTI_FALSE;
    }
            


    return RTI_TRUE;
}


/**
 * <<IMPLEMENTATION>>
 *
 * Defines:  TSeq, T
 *
 * Configure and implement 'ChocolateRecipe' sequence class.
 */
#define T ChocolateRecipe
#define TSeq ChocolateRecipeSeq
#define T_initialize_w_params ::com::rti::chocolatefactory::generated::ChocolateRecipe_initialize_w_params
#define T_finalize_w_params   ::com::rti::chocolatefactory::generated::ChocolateRecipe_finalize_w_params
#define T_copy       ::com::rti::chocolatefactory::generated::ChocolateRecipe_copy

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

/* ========================================================================= */
const char *ChocolateLotStateTYPENAME = "com::rti::chocolatefactory::generated::ChocolateLotState";

DDS_TypeCode* ChocolateLotState_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode ChocolateLotState_g_tc_recipeName_string = DDS_INITIALIZE_STRING_TYPECODE((com::rti::chocolatefactory::generated::MAX_STRING_LENGTH));
    static DDS_TypeCode ChocolateLotState_g_tc_ingredients_string = DDS_INITIALIZE_STRING_TYPECODE((com::rti::chocolatefactory::generated::MAX_STRING_LENGTH));
    static DDS_TypeCode ChocolateLotState_g_tc_ingredients_sequence = DDS_INITIALIZE_SEQUENCE_TYPECODE((com::rti::chocolatefactory::generated::MAX_INGREDIENT_LIST),NULL);

    static DDS_TypeCode_Member ChocolateLotState_g_tc_members[6]=
    {
        {
            (char *)"lotID",/* Member name */
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
            (char *)"controller",/* Member name */
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
            RTI_CDR_KEY_MEMBER, /* Member flags */
            DDS_PRIVATE_MEMBER,/* Ignored */
            1,
            NULL/* Ignored */
        },
        {
            (char *)"recipeName",/* Member name */
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
            (char *)"nextController",/* Member name */
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
        },
        {
            (char *)"lotStatus",/* Member name */
            {
                4,/* Representation ID */
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
            (char *)"ingredients",/* Member name */
            {
                5,/* Representation ID */
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

    static DDS_TypeCode ChocolateLotState_g_tc =
    {{
        DDS_TK_STRUCT,/* Kind */
        DDS_BOOLEAN_FALSE, /* Ignored */
        -1,/* Ignored */
        (char *)"com::rti::chocolatefactory::generated::ChocolateLotState", /* Name */
        NULL, /* Ignored */
        0, /* Ignored */
        0, /* Ignored */
        NULL, /* Ignored */
        6, /* Number of members */
        ChocolateLotState_g_tc_members, /* Members */
        DDS_VM_NONE /* Ignored */
    }}; /* Type code for ChocolateLotState*/

    if (is_initialized) {
        return &ChocolateLotState_g_tc;
    }

    ChocolateLotState_g_tc_ingredients_sequence._data._typeCode = (RTICdrTypeCode *)&ChocolateLotState_g_tc_ingredients_string;

    ChocolateLotState_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_long;
    ChocolateLotState_g_tc_members[1]._representation._typeCode = (RTICdrTypeCode *)com::rti::chocolatefactory::generated::StationControllerKind_get_typecode();
    ChocolateLotState_g_tc_members[2]._representation._typeCode = (RTICdrTypeCode *)&ChocolateLotState_g_tc_recipeName_string;
    ChocolateLotState_g_tc_members[3]._representation._typeCode = (RTICdrTypeCode *)com::rti::chocolatefactory::generated::StationControllerKind_get_typecode();
    ChocolateLotState_g_tc_members[4]._representation._typeCode = (RTICdrTypeCode *)com::rti::chocolatefactory::generated::LotStatusKind_get_typecode();
    ChocolateLotState_g_tc_members[5]._representation._typeCode = (RTICdrTypeCode *)&ChocolateLotState_g_tc_ingredients_sequence;

    is_initialized = RTI_TRUE;

    return &ChocolateLotState_g_tc;
}


RTIBool ChocolateLotState_initialize(
    ChocolateLotState* sample) {
  return ::com::rti::chocolatefactory::generated::ChocolateLotState_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}
        
RTIBool ChocolateLotState_initialize_ex(
    ChocolateLotState* sample,RTIBool allocatePointers,RTIBool allocateMemory)
{
    struct DDS_TypeAllocationParams_t allocParams =
        DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;
        
    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;
    
    return ::com::rti::chocolatefactory::generated::ChocolateLotState_initialize_w_params(
        sample,&allocParams);
}

RTIBool ChocolateLotState_initialize_w_params(
        ChocolateLotState* sample,
        const struct DDS_TypeAllocationParams_t * allocParams)
{

    void* buffer = NULL;
    if (buffer) {} /* To avoid warnings */
        
    
    if (allocParams) {} /* To avoid warnings */
        

    if (!RTICdrType_initLong(&sample->lotID)) {
        return RTI_FALSE;
    }                
            

    if (!com::rti::chocolatefactory::generated::StationControllerKind_initialize_w_params(&sample->controller,allocParams)) {
        return RTI_FALSE;
    }
            

    if (allocParams->allocate_memory) {
        sample->recipeName = DDS_String_alloc(((com::rti::chocolatefactory::generated::MAX_STRING_LENGTH)));
        if (sample->recipeName == NULL) {
            return RTI_FALSE;
        }
    } else {
        if (sample->recipeName != NULL) { 
            sample->recipeName[0] = '\0';
        }
    }
            

    if (!com::rti::chocolatefactory::generated::StationControllerKind_initialize_w_params(&sample->nextController,allocParams)) {
        return RTI_FALSE;
    }
            

    if (!com::rti::chocolatefactory::generated::LotStatusKind_initialize_w_params(&sample->lotStatus,allocParams)) {
        return RTI_FALSE;
    }
            

    if (allocParams->allocate_memory) {    
        DDS_StringSeq_initialize(&sample->ingredients);
        if (!DDS_StringSeq_set_maximum(&sample->ingredients,
                                       ((com::rti::chocolatefactory::generated::MAX_INGREDIENT_LIST)))) {
            return RTI_FALSE;
        }
        buffer = DDS_StringSeq_get_contiguous_bufferI(&sample->ingredients);
        if (buffer == NULL) {
            return RTI_FALSE;
        }
        if (!RTICdrType_initStringArray(buffer, ((com::rti::chocolatefactory::generated::MAX_INGREDIENT_LIST)),((com::rti::chocolatefactory::generated::MAX_STRING_LENGTH))+1,
            RTI_CDR_CHAR_TYPE)) {
            return RTI_FALSE;
        }
    } else {
        DDS_StringSeq_set_length(&sample->ingredients, 0);
    }
            


    return RTI_TRUE;
}

void ChocolateLotState_finalize(
    ChocolateLotState* sample)
{
    ::com::rti::chocolatefactory::generated::ChocolateLotState_finalize_ex(sample,RTI_TRUE);
}
        
void ChocolateLotState_finalize_ex(
    ChocolateLotState* sample,RTIBool deletePointers)
{        
    struct DDS_TypeDeallocationParams_t deallocParams =
            DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample) { } /* To avoid warnings */
    
    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    ::com::rti::chocolatefactory::generated::ChocolateLotState_finalize_w_params(
        sample,&deallocParams);
}

void ChocolateLotState_finalize_w_params(
        ChocolateLotState* sample,
        const struct DDS_TypeDeallocationParams_t * deallocParams)
{    
    if (sample) { } /* To avoid warnings */
    if (deallocParams) {} /* To avoid warnings */



    com::rti::chocolatefactory::generated::StationControllerKind_finalize_w_params(&sample->controller, deallocParams);
            

    if (sample->recipeName != NULL) {    
        DDS_String_free(sample->recipeName);
        sample->recipeName = NULL;
    }
            

    com::rti::chocolatefactory::generated::StationControllerKind_finalize_w_params(&sample->nextController, deallocParams);
            

    com::rti::chocolatefactory::generated::LotStatusKind_finalize_w_params(&sample->lotStatus, deallocParams);
            

    DDS_StringSeq_finalize(&sample->ingredients);
            

}

void ChocolateLotState_finalize_optional_members(
    ChocolateLotState* sample, RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParamsTmp =
        DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;
    struct DDS_TypeDeallocationParams_t * deallocParams =
        &deallocParamsTmp;
    if (sample) { } /* To avoid warnings */
    if (deallocParams) {} /* To avoid warnings */

        

    deallocParamsTmp.delete_pointers = (DDS_Boolean)deletePointers;
    deallocParamsTmp.delete_optional_members = DDS_BOOLEAN_TRUE;    
             


    com::rti::chocolatefactory::generated::StationControllerKind_finalize_w_params(&sample->controller, deallocParams);
            


    com::rti::chocolatefactory::generated::StationControllerKind_finalize_w_params(&sample->nextController, deallocParams);
            

    com::rti::chocolatefactory::generated::LotStatusKind_finalize_w_params(&sample->lotStatus, deallocParams);
            


}

RTIBool ChocolateLotState_copy(
    ChocolateLotState* dst,
    const ChocolateLotState* src)
{

    if (!RTICdrType_copyLong(
        &dst->lotID, &src->lotID)) {
        return RTI_FALSE;
    }
            

    if (!com::rti::chocolatefactory::generated::StationControllerKind_copy(
        &dst->controller, &src->controller)) {
        return RTI_FALSE;
    }
            

    if (!RTICdrType_copyString(
        dst->recipeName, src->recipeName, ((com::rti::chocolatefactory::generated::MAX_STRING_LENGTH)) + 1)) {
        return RTI_FALSE;
    }
            

    if (!com::rti::chocolatefactory::generated::StationControllerKind_copy(
        &dst->nextController, &src->nextController)) {
        return RTI_FALSE;
    }
            

    if (!com::rti::chocolatefactory::generated::LotStatusKind_copy(
        &dst->lotStatus, &src->lotStatus)) {
        return RTI_FALSE;
    }
            

    if (!DDS_StringSeq_copy(&dst->ingredients,
                                      &src->ingredients)) {
        return RTI_FALSE;
    }
            


    return RTI_TRUE;
}


/**
 * <<IMPLEMENTATION>>
 *
 * Defines:  TSeq, T
 *
 * Configure and implement 'ChocolateLotState' sequence class.
 */
#define T ChocolateLotState
#define TSeq ChocolateLotStateSeq
#define T_initialize_w_params ::com::rti::chocolatefactory::generated::ChocolateLotState_initialize_w_params
#define T_finalize_w_params   ::com::rti::chocolatefactory::generated::ChocolateLotState_finalize_w_params
#define T_copy       ::com::rti::chocolatefactory::generated::ChocolateLotState_copy

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

} /* namespace chocolatefactory */

} /* namespace rti */

} /* namespace com */
