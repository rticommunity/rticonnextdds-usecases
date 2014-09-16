
/*
  WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

  This file was generated from VideoData.idl using "rtiddsgen".
  The rtiddsgen tool is part of the RTI Connext distribution.
  For more information, type 'rtiddsgen -help' at a command shell
  or consult the RTI Connext manual.
*/

#ifndef VideoData_1974959798_h
#define VideoData_1974959798_h

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

namespace media{

namespace generated{
             
static const char * VIDEO_TOPIC = "VideoData";             
static const char * QOS_LIBRARY = "RTIExampleQosLibrary";             
static const char * QOS_PROFILE_STREAMING_DATA = "StreamingVideoData";             
static const char * QOS_PROFILE_MULTICAST_DATA = "MulticastVideo";             
static const DDS_Long MAX_BUFFER_SIZE = 1048576;
#define com_rti_media_generated_VideoStream_LAST_MEMBER_ID 3
        
extern const char *VideoStreamTYPENAME;
        


#ifdef __cplusplus
    struct VideoStreamSeq;

#ifndef NDDS_STANDALONE_TYPE
    class VideoStreamTypeSupport;
    class VideoStreamDataWriter;
    class VideoStreamDataReader;
#endif

#endif

            
    
class VideoStream                                        
{
public:            
#ifdef __cplusplus
    typedef struct VideoStreamSeq Seq;

#ifndef NDDS_STANDALONE_TYPE
    typedef VideoStreamTypeSupport TypeSupport;
    typedef VideoStreamDataWriter DataWriter;
    typedef VideoStreamDataReader DataReader;
#endif

#endif
    
    DDS_Long  stream_id;

    DDS_UnsignedLong  flags;

    DDS_UnsignedLong  sequence_number;

     DDS_OctetSeq  frame;

            
};                        
    
                            
#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
  /* If the code is building on Windows, start exporting symbols.
   */
  #undef NDDSUSERDllExport
  #define NDDSUSERDllExport __declspec(dllexport)
#endif

    
NDDSUSERDllExport DDS_TypeCode* VideoStream_get_typecode(void); /* Type code */
    

DDS_SEQUENCE(VideoStreamSeq, VideoStream);
        
NDDSUSERDllExport
RTIBool VideoStream_initialize(
        VideoStream* self);
        
NDDSUSERDllExport
RTIBool VideoStream_initialize_ex(
        VideoStream* self,
        RTIBool allocatePointers,RTIBool allocateMemory);
        
NDDSUSERDllExport
RTIBool VideoStream_initialize_w_params(
        VideoStream* self,
        const struct DDS_TypeAllocationParams_t * allocParams);

NDDSUSERDllExport
void VideoStream_finalize(
        VideoStream* self);
                        
NDDSUSERDllExport
void VideoStream_finalize_ex(
        VideoStream* self,RTIBool deletePointers);
       
NDDSUSERDllExport
void VideoStream_finalize_w_params(
        VideoStream* self,
        const struct DDS_TypeDeallocationParams_t * deallocParams);
        
NDDSUSERDllExport
void VideoStream_finalize_optional_members(
        VideoStream* self, RTIBool deletePointers);        
        
NDDSUSERDllExport
RTIBool VideoStream_copy(
        VideoStream* dst,
        const VideoStream* src);

#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
  /* If the code is building on Windows, stop exporting symbols.
   */
  #undef NDDSUSERDllExport
  #define NDDSUSERDllExport
#endif


} /* namespace generated */

} /* namespace media */

} /* namespace rti */

} /* namespace com */


#endif /* VideoData_1974959798_h */
