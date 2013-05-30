
/*
  WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

  This file was generated from AirTrafficControl.idl using "rtiddsgen".
  The rtiddsgen tool is part of the RTI Connext distribution.
  For more information, type 'rtiddsgen -help' at a command shell
  or consult the RTI Connext manual.
*/

#ifndef AirTrafficControl_1144379923_h
#define AirTrafficControl_1144379923_h

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

namespace atc{

namespace generated{
             
static const char * AIR_TRACK_TOPIC = "AirTrack";             
static const DDS_Short FLIGHT_ID_LENGTH = 8;             
static const DDS_Short AERODROME_ID_LENGTH = 5;             
static const DDS_Short ALTERNATE_AERODROME_NUM = 2;
typedef char *  FlightId;                
        
        
#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
  /* If the code is building on Windows, start exporting symbols. */
  #undef NDDSUSERDllExport
  #define NDDSUSERDllExport __declspec(dllexport)
#endif

    
NDDSUSERDllExport DDS_TypeCode* FlightId_get_typecode(void); /* Type code */
    
DDS_SEQUENCE(FlightIdSeq, FlightId);                                        
            
NDDSUSERDllExport
RTIBool FlightId_initialize(
        FlightId* self);
            
NDDSUSERDllExport
RTIBool FlightId_initialize_ex(
        FlightId* self,RTIBool allocatePointers,RTIBool allocateMemory);
                    
NDDSUSERDllExport
void FlightId_finalize(
        FlightId* self);
            
NDDSUSERDllExport
void FlightId_finalize_ex(
        FlightId* self,RTIBool deletePointers);
                    
NDDSUSERDllExport
RTIBool FlightId_copy(
        FlightId* dst,
        const FlightId* src);

    

#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
  /* If the code is building on Windows, stop exporting symbols. */
  #undef NDDSUSERDllExport
  #define NDDSUSERDllExport
#endif


        
extern const char *TrackTYPENAME;
        


#ifdef __cplusplus
    struct TrackSeq;

#ifndef NDDS_STANDALONE_TYPE
    class TrackTypeSupport;
    class TrackDataWriter;
    class TrackDataReader;
#endif

#endif

            
    
class Track                                        
{
public:            
#ifdef __cplusplus
    typedef struct TrackSeq Seq;

#ifndef NDDS_STANDALONE_TYPE
    typedef TrackTypeSupport TypeSupport;
    typedef TrackDataWriter DataWriter;
    typedef TrackDataReader DataReader;
#endif

#endif
    
    DDS_Long  radarId;

    DDS_Long  trackId;

    com::rti::atc::generated::FlightId  flightId;

    DDS_Double  latitude;

    DDS_Double  longitude;

    DDS_Double  altitude;

            
};                        
    
                            
#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
  /* If the code is building on Windows, start exporting symbols.
   */
  #undef NDDSUSERDllExport
  #define NDDSUSERDllExport __declspec(dllexport)
#endif

    
NDDSUSERDllExport DDS_TypeCode* Track_get_typecode(void); /* Type code */
    

DDS_SEQUENCE(TrackSeq, Track);
        
NDDSUSERDllExport
RTIBool Track_initialize(
        Track* self);
        
NDDSUSERDllExport
RTIBool Track_initialize_ex(
        Track* self,RTIBool allocatePointers,RTIBool allocateMemory);

NDDSUSERDllExport
void Track_finalize(
        Track* self);
                        
NDDSUSERDllExport
void Track_finalize_ex(
        Track* self,RTIBool deletePointers);
        
NDDSUSERDllExport
RTIBool Track_copy(
        Track* dst,
        const Track* src);

#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
  /* If the code is building on Windows, stop exporting symbols.
   */
  #undef NDDSUSERDllExport
  #define NDDSUSERDllExport
#endif

             
static const char * AIRCRAFT_FLIGHT_PLAN_TOPIC = "FlightPlan"; 
typedef enum FlightRulesKind
{
    IFR,
    VFR,
    IFR_THEN_CHANGE,
    VFR_THEN_CHANGE
} FlightRulesKind;
    

#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
  /* If the code is building on Windows, start exporting symbols.
   */
  #undef NDDSUSERDllExport
  #define NDDSUSERDllExport __declspec(dllexport)
#endif

    
NDDSUSERDllExport DDS_TypeCode* FlightRulesKind_get_typecode(void); /* Type code */
    

DDS_SEQUENCE(FlightRulesKindSeq, FlightRulesKind);
        
NDDSUSERDllExport
RTIBool FlightRulesKind_initialize(
        FlightRulesKind* self);
        
NDDSUSERDllExport
RTIBool FlightRulesKind_initialize_ex(
        FlightRulesKind* self,RTIBool allocatePointers,RTIBool allocateMemory);

NDDSUSERDllExport
void FlightRulesKind_finalize(
        FlightRulesKind* self);
                        
NDDSUSERDllExport
void FlightRulesKind_finalize_ex(
        FlightRulesKind* self,RTIBool deletePointers);
        
NDDSUSERDllExport
RTIBool FlightRulesKind_copy(
        FlightRulesKind* dst,
        const FlightRulesKind* src);


NDDSUSERDllExport
RTIBool FlightRulesKind_getValues(FlightRulesKindSeq * values);
    

#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
  /* If the code is building on Windows, stop exporting symbols.
   */
  #undef NDDSUSERDllExport
  #define NDDSUSERDllExport
#endif

 
typedef enum FlightTypeKind
{
    SCHEDULED_AIR_SERVICE,
    NON_SCHEDULED_AIR_TRANSPORT,
    GENERAL_AVIATION,
    MILITARY
} FlightTypeKind;
    

#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
  /* If the code is building on Windows, start exporting symbols.
   */
  #undef NDDSUSERDllExport
  #define NDDSUSERDllExport __declspec(dllexport)
#endif

    
NDDSUSERDllExport DDS_TypeCode* FlightTypeKind_get_typecode(void); /* Type code */
    

DDS_SEQUENCE(FlightTypeKindSeq, FlightTypeKind);
        
NDDSUSERDllExport
RTIBool FlightTypeKind_initialize(
        FlightTypeKind* self);
        
NDDSUSERDllExport
RTIBool FlightTypeKind_initialize_ex(
        FlightTypeKind* self,RTIBool allocatePointers,RTIBool allocateMemory);

NDDSUSERDllExport
void FlightTypeKind_finalize(
        FlightTypeKind* self);
                        
NDDSUSERDllExport
void FlightTypeKind_finalize_ex(
        FlightTypeKind* self,RTIBool deletePointers);
        
NDDSUSERDllExport
RTIBool FlightTypeKind_copy(
        FlightTypeKind* dst,
        const FlightTypeKind* src);


NDDSUSERDllExport
RTIBool FlightTypeKind_getValues(FlightTypeKindSeq * values);
    

#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
  /* If the code is building on Windows, stop exporting symbols.
   */
  #undef NDDSUSERDllExport
  #define NDDSUSERDllExport
#endif

 
typedef enum EquipmentKind
{
    NO_COMMS,
    STANDARD_COMMS
} EquipmentKind;
    

#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
  /* If the code is building on Windows, start exporting symbols.
   */
  #undef NDDSUSERDllExport
  #define NDDSUSERDllExport __declspec(dllexport)
#endif

    
NDDSUSERDllExport DDS_TypeCode* EquipmentKind_get_typecode(void); /* Type code */
    

DDS_SEQUENCE(EquipmentKindSeq, EquipmentKind);
        
NDDSUSERDllExport
RTIBool EquipmentKind_initialize(
        EquipmentKind* self);
        
NDDSUSERDllExport
RTIBool EquipmentKind_initialize_ex(
        EquipmentKind* self,RTIBool allocatePointers,RTIBool allocateMemory);

NDDSUSERDllExport
void EquipmentKind_finalize(
        EquipmentKind* self);
                        
NDDSUSERDllExport
void EquipmentKind_finalize_ex(
        EquipmentKind* self,RTIBool deletePointers);
        
NDDSUSERDllExport
RTIBool EquipmentKind_copy(
        EquipmentKind* dst,
        const EquipmentKind* src);


NDDSUSERDllExport
RTIBool EquipmentKind_getValues(EquipmentKindSeq * values);
    

#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
  /* If the code is building on Windows, stop exporting symbols.
   */
  #undef NDDSUSERDllExport
  #define NDDSUSERDllExport
#endif


        
extern const char *FlightPlanTYPENAME;
        


#ifdef __cplusplus
    struct FlightPlanSeq;

#ifndef NDDS_STANDALONE_TYPE
    class FlightPlanTypeSupport;
    class FlightPlanDataWriter;
    class FlightPlanDataReader;
#endif

#endif

            
    
class FlightPlan                                        
{
public:            
#ifdef __cplusplus
    typedef struct FlightPlanSeq Seq;

#ifndef NDDS_STANDALONE_TYPE
    typedef FlightPlanTypeSupport TypeSupport;
    typedef FlightPlanDataWriter DataWriter;
    typedef FlightPlanDataReader DataReader;
#endif

#endif
    
    com::rti::atc::generated::FlightId  flightId;

    com::rti::atc::generated::FlightRulesKind  flightRules;

    com::rti::atc::generated::FlightTypeKind  flightType;

    com::rti::atc::generated::EquipmentKind  equipmentType;

    char*  departureAerodrome; /* maximum length = ((com::rti::atc::generated::AERODROME_ID_LENGTH)) */

    DDS_Short  departureHour;

    DDS_Short  departureMin;

    char*  destinationAerodrome; /* maximum length = ((com::rti::atc::generated::AERODROME_ID_LENGTH)) */

    DDS_Short  estimatedHours;

    DDS_Short  estimatedMinutes;

     DDS_StringSeq  alternateAerodromes;

            
};                        
    
                            
#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
  /* If the code is building on Windows, start exporting symbols.
   */
  #undef NDDSUSERDllExport
  #define NDDSUSERDllExport __declspec(dllexport)
#endif

    
NDDSUSERDllExport DDS_TypeCode* FlightPlan_get_typecode(void); /* Type code */
    

DDS_SEQUENCE(FlightPlanSeq, FlightPlan);
        
NDDSUSERDllExport
RTIBool FlightPlan_initialize(
        FlightPlan* self);
        
NDDSUSERDllExport
RTIBool FlightPlan_initialize_ex(
        FlightPlan* self,RTIBool allocatePointers,RTIBool allocateMemory);

NDDSUSERDllExport
void FlightPlan_finalize(
        FlightPlan* self);
                        
NDDSUSERDllExport
void FlightPlan_finalize_ex(
        FlightPlan* self,RTIBool deletePointers);
        
NDDSUSERDllExport
RTIBool FlightPlan_copy(
        FlightPlan* dst,
        const FlightPlan* src);

#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
  /* If the code is building on Windows, stop exporting symbols.
   */
  #undef NDDSUSERDllExport
  #define NDDSUSERDllExport
#endif


} /* namespace generated */

} /* namespace atc */

} /* namespace rti */

} /* namespace com */


#endif /* AirTrafficControl_1144379923_h */
