
/*
  WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

  This file was generated from ChocolateFactory.idl using "rtiddsgen".
  The rtiddsgen tool is part of the RTI Connext distribution.
  For more information, type 'rtiddsgen -help' at a command shell
  or consult the RTI Connext manual.
*/

#ifndef ChocolateFactory_1774920665_h
#define ChocolateFactory_1774920665_h

#ifndef NDDS_STANDALONE_TYPE
    #ifdef __cplusplus
        #ifndef ndds_cpp_h
            #include "ndds/ndds_cpp.h"
        #endif
    #else
        #ifndef ndds_c_h
            #include "ndds/ndds_c.h"
        #endif
    #endif
#else
    #include "ndds_standalone_type.h"
#endif


namespace com{

namespace rti{

namespace chocolatefactory{

namespace generated{
             
static const char * RECIPE_TOPIC = "ChocolateRecipes";             
static const char * CHOCOLATE_LOT_TOPIC = "ChocolateLotState";             
static const char * QOS_LIBRARY = "RTIExampleQosLibrary";             
static const char * QOS_PROFILE_STATE_DATA = "FactoryStateData";             
static const DDS_Long MAX_INGREDIENT_LIST = 9;             
static const DDS_Long MAX_RECIPE_STEPS = 9;             
static const DDS_Long MAX_STRING_LENGTH = 256; 
typedef enum StationControllerKind
{
    INVALID_CONTROLLER,
    SUGAR_CONTROLLER,
    COCOA_BUTTER_CONTROLLER,
    COCOA_LIQUOR_CONTROLLER,
    VANILLA_CONTROLLER,
    MILK_CONTROLLER
} StationControllerKind;
    

#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
  /* If the code is building on Windows, start exporting symbols.
   */
  #undef NDDSUSERDllExport
  #define NDDSUSERDllExport __declspec(dllexport)
#endif

    
NDDSUSERDllExport DDS_TypeCode* StationControllerKind_get_typecode(void); /* Type code */
    

DDS_SEQUENCE(StationControllerKindSeq, StationControllerKind);
        
NDDSUSERDllExport
RTIBool StationControllerKind_initialize(
        StationControllerKind* self);
        
NDDSUSERDllExport
RTIBool StationControllerKind_initialize_ex(
        StationControllerKind* self,
        RTIBool allocatePointers,RTIBool allocateMemory);
        
NDDSUSERDllExport
RTIBool StationControllerKind_initialize_w_params(
        StationControllerKind* self,
        const struct DDS_TypeAllocationParams_t * allocParams);

NDDSUSERDllExport
void StationControllerKind_finalize(
        StationControllerKind* self);
                        
NDDSUSERDllExport
void StationControllerKind_finalize_ex(
        StationControllerKind* self,RTIBool deletePointers);
        
NDDSUSERDllExport
void StationControllerKind_finalize_w_params(
        StationControllerKind* self,
        const struct DDS_TypeDeallocationParams_t * deallocParams);

NDDSUSERDllExport
void StationControllerKind_finalize_optional_members(
        StationControllerKind* self, RTIBool deletePointers);
                
NDDSUSERDllExport
RTIBool StationControllerKind_copy(
        StationControllerKind* dst,
        const StationControllerKind* src);


NDDSUSERDllExport
RTIBool StationControllerKind_getValues(StationControllerKindSeq * values);
    

#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
  /* If the code is building on Windows, stop exporting symbols.
   */
  #undef NDDSUSERDllExport
  #define NDDSUSERDllExport
#endif

 
typedef enum LotStatusKind
{
    ASSIGNED_TO_SC,
    WAITING_AT_SC,
    PROCESSING_AT_SC,
    LOT_COMPLETED
} LotStatusKind;
    

#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
  /* If the code is building on Windows, start exporting symbols.
   */
  #undef NDDSUSERDllExport
  #define NDDSUSERDllExport __declspec(dllexport)
#endif

    
NDDSUSERDllExport DDS_TypeCode* LotStatusKind_get_typecode(void); /* Type code */
    

DDS_SEQUENCE(LotStatusKindSeq, LotStatusKind);
        
NDDSUSERDllExport
RTIBool LotStatusKind_initialize(
        LotStatusKind* self);
        
NDDSUSERDllExport
RTIBool LotStatusKind_initialize_ex(
        LotStatusKind* self,
        RTIBool allocatePointers,RTIBool allocateMemory);
        
NDDSUSERDllExport
RTIBool LotStatusKind_initialize_w_params(
        LotStatusKind* self,
        const struct DDS_TypeAllocationParams_t * allocParams);

NDDSUSERDllExport
void LotStatusKind_finalize(
        LotStatusKind* self);
                        
NDDSUSERDllExport
void LotStatusKind_finalize_ex(
        LotStatusKind* self,RTIBool deletePointers);
        
NDDSUSERDllExport
void LotStatusKind_finalize_w_params(
        LotStatusKind* self,
        const struct DDS_TypeDeallocationParams_t * deallocParams);

NDDSUSERDllExport
void LotStatusKind_finalize_optional_members(
        LotStatusKind* self, RTIBool deletePointers);
                
NDDSUSERDllExport
RTIBool LotStatusKind_copy(
        LotStatusKind* dst,
        const LotStatusKind* src);


NDDSUSERDllExport
RTIBool LotStatusKind_getValues(LotStatusKindSeq * values);
    

#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
  /* If the code is building on Windows, stop exporting symbols.
   */
  #undef NDDSUSERDllExport
  #define NDDSUSERDllExport
#endif


#define com_rti_chocolatefactory_generated_RecipeStep_LAST_MEMBER_ID 1
        
extern const char *RecipeStepTYPENAME;
        


#ifdef __cplusplus
    struct RecipeStepSeq;

#endif

            
    
class RecipeStep                                        
{
public:            
#ifdef __cplusplus
    typedef struct RecipeStepSeq Seq;

#endif
    
    com::rti::chocolatefactory::generated::StationControllerKind  stationController;

    DDS_Long  seconds;

            
};                        
    
                            
#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
  /* If the code is building on Windows, start exporting symbols.
   */
  #undef NDDSUSERDllExport
  #define NDDSUSERDllExport __declspec(dllexport)
#endif

    
NDDSUSERDllExport DDS_TypeCode* RecipeStep_get_typecode(void); /* Type code */
    

DDS_SEQUENCE(RecipeStepSeq, RecipeStep);
        
NDDSUSERDllExport
RTIBool RecipeStep_initialize(
        RecipeStep* self);
        
NDDSUSERDllExport
RTIBool RecipeStep_initialize_ex(
        RecipeStep* self,
        RTIBool allocatePointers,RTIBool allocateMemory);
        
NDDSUSERDllExport
RTIBool RecipeStep_initialize_w_params(
        RecipeStep* self,
        const struct DDS_TypeAllocationParams_t * allocParams);

NDDSUSERDllExport
void RecipeStep_finalize(
        RecipeStep* self);
                        
NDDSUSERDllExport
void RecipeStep_finalize_ex(
        RecipeStep* self,RTIBool deletePointers);
       
NDDSUSERDllExport
void RecipeStep_finalize_w_params(
        RecipeStep* self,
        const struct DDS_TypeDeallocationParams_t * deallocParams);
        
NDDSUSERDllExport
void RecipeStep_finalize_optional_members(
        RecipeStep* self, RTIBool deletePointers);        
        
NDDSUSERDllExport
RTIBool RecipeStep_copy(
        RecipeStep* dst,
        const RecipeStep* src);

#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
  /* If the code is building on Windows, stop exporting symbols.
   */
  #undef NDDSUSERDllExport
  #define NDDSUSERDllExport
#endif


#define com_rti_chocolatefactory_generated_ChocolateRecipe_LAST_MEMBER_ID 1
        
extern const char *ChocolateRecipeTYPENAME;
        


#ifdef __cplusplus
    struct ChocolateRecipeSeq;

#ifndef NDDS_STANDALONE_TYPE
    class ChocolateRecipeTypeSupport;
    class ChocolateRecipeDataWriter;
    class ChocolateRecipeDataReader;
#endif

#endif

            
    
class ChocolateRecipe                                        
{
public:            
#ifdef __cplusplus
    typedef struct ChocolateRecipeSeq Seq;

#ifndef NDDS_STANDALONE_TYPE
    typedef ChocolateRecipeTypeSupport TypeSupport;
    typedef ChocolateRecipeDataWriter DataWriter;
    typedef ChocolateRecipeDataReader DataReader;
#endif

#endif
    
    char*  recipeName; /* maximum length = ((com::rti::chocolatefactory::generated::MAX_STRING_LENGTH)) */

     com::rti::chocolatefactory::generated::RecipeStepSeq  steps;

            
};                        
    
                            
#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
  /* If the code is building on Windows, start exporting symbols.
   */
  #undef NDDSUSERDllExport
  #define NDDSUSERDllExport __declspec(dllexport)
#endif

    
NDDSUSERDllExport DDS_TypeCode* ChocolateRecipe_get_typecode(void); /* Type code */
    

DDS_SEQUENCE(ChocolateRecipeSeq, ChocolateRecipe);
        
NDDSUSERDllExport
RTIBool ChocolateRecipe_initialize(
        ChocolateRecipe* self);
        
NDDSUSERDllExport
RTIBool ChocolateRecipe_initialize_ex(
        ChocolateRecipe* self,
        RTIBool allocatePointers,RTIBool allocateMemory);
        
NDDSUSERDllExport
RTIBool ChocolateRecipe_initialize_w_params(
        ChocolateRecipe* self,
        const struct DDS_TypeAllocationParams_t * allocParams);

NDDSUSERDllExport
void ChocolateRecipe_finalize(
        ChocolateRecipe* self);
                        
NDDSUSERDllExport
void ChocolateRecipe_finalize_ex(
        ChocolateRecipe* self,RTIBool deletePointers);
       
NDDSUSERDllExport
void ChocolateRecipe_finalize_w_params(
        ChocolateRecipe* self,
        const struct DDS_TypeDeallocationParams_t * deallocParams);
        
NDDSUSERDllExport
void ChocolateRecipe_finalize_optional_members(
        ChocolateRecipe* self, RTIBool deletePointers);        
        
NDDSUSERDllExport
RTIBool ChocolateRecipe_copy(
        ChocolateRecipe* dst,
        const ChocolateRecipe* src);

#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
  /* If the code is building on Windows, stop exporting symbols.
   */
  #undef NDDSUSERDllExport
  #define NDDSUSERDllExport
#endif


#define com_rti_chocolatefactory_generated_ChocolateLotState_LAST_MEMBER_ID 5
        
extern const char *ChocolateLotStateTYPENAME;
        


#ifdef __cplusplus
    struct ChocolateLotStateSeq;

#ifndef NDDS_STANDALONE_TYPE
    class ChocolateLotStateTypeSupport;
    class ChocolateLotStateDataWriter;
    class ChocolateLotStateDataReader;
#endif

#endif

            
    
class ChocolateLotState                                        
{
public:            
#ifdef __cplusplus
    typedef struct ChocolateLotStateSeq Seq;

#ifndef NDDS_STANDALONE_TYPE
    typedef ChocolateLotStateTypeSupport TypeSupport;
    typedef ChocolateLotStateDataWriter DataWriter;
    typedef ChocolateLotStateDataReader DataReader;
#endif

#endif
    
    DDS_Long  lotID;

    com::rti::chocolatefactory::generated::StationControllerKind  controller;

    char*  recipeName; /* maximum length = ((com::rti::chocolatefactory::generated::MAX_STRING_LENGTH)) */

    com::rti::chocolatefactory::generated::StationControllerKind  nextController;

    com::rti::chocolatefactory::generated::LotStatusKind  lotStatus;

     DDS_StringSeq  ingredients;

            
};                        
    
                            
#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
  /* If the code is building on Windows, start exporting symbols.
   */
  #undef NDDSUSERDllExport
  #define NDDSUSERDllExport __declspec(dllexport)
#endif

    
NDDSUSERDllExport DDS_TypeCode* ChocolateLotState_get_typecode(void); /* Type code */
    

DDS_SEQUENCE(ChocolateLotStateSeq, ChocolateLotState);
        
NDDSUSERDllExport
RTIBool ChocolateLotState_initialize(
        ChocolateLotState* self);
        
NDDSUSERDllExport
RTIBool ChocolateLotState_initialize_ex(
        ChocolateLotState* self,
        RTIBool allocatePointers,RTIBool allocateMemory);
        
NDDSUSERDllExport
RTIBool ChocolateLotState_initialize_w_params(
        ChocolateLotState* self,
        const struct DDS_TypeAllocationParams_t * allocParams);

NDDSUSERDllExport
void ChocolateLotState_finalize(
        ChocolateLotState* self);
                        
NDDSUSERDllExport
void ChocolateLotState_finalize_ex(
        ChocolateLotState* self,RTIBool deletePointers);
       
NDDSUSERDllExport
void ChocolateLotState_finalize_w_params(
        ChocolateLotState* self,
        const struct DDS_TypeDeallocationParams_t * deallocParams);
        
NDDSUSERDllExport
void ChocolateLotState_finalize_optional_members(
        ChocolateLotState* self, RTIBool deletePointers);        
        
NDDSUSERDllExport
RTIBool ChocolateLotState_copy(
        ChocolateLotState* dst,
        const ChocolateLotState* src);

#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
  /* If the code is building on Windows, stop exporting symbols.
   */
  #undef NDDSUSERDllExport
  #define NDDSUSERDllExport
#endif


} /* namespace generated */

} /* namespace chocolatefactory */

} /* namespace rti */

} /* namespace com */


#endif /* ChocolateFactory_1774920665_h */
