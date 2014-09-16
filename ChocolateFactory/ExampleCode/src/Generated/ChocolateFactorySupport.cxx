
/*
  WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

  This file was generated from ChocolateFactory.idl using "rtiddsgen".
  The rtiddsgen tool is part of the RTI Connext distribution.
  For more information, type 'rtiddsgen -help' at a command shell
  or consult the RTI Connext manual.
*/

#include "ChocolateFactorySupport.h"
#include "ChocolateFactoryPlugin.h"



#ifdef __cplusplus  
    #ifndef dds_c_log_impl_h              
         #include "dds_c/dds_c_log_impl.h"                                
    #endif        
#endif        


namespace com{

namespace rti{

namespace chocolatefactory{

namespace generated{



/* ========================================================================= */
/**
   <<IMPLEMENTATION>>

   Defines:   TData,
              TDataWriter,
              TDataReader,
              TTypeSupport

   Configure and implement 'ChocolateRecipe' support classes.

   Note: Only the #defined classes get defined
*/

/* ----------------------------------------------------------------- */
/* DDSDataWriter
*/

/**
  <<IMPLEMENTATION >>

   Defines:   TDataWriter, TData
*/

/* Requires */
#define TTYPENAME   ChocolateRecipeTYPENAME

/* Defines */
#define TDataWriter ChocolateRecipeDataWriter
#define TData       ::com::rti::chocolatefactory::generated::ChocolateRecipe


#ifdef __cplusplus
#include "dds_cpp/generic/dds_cpp_data_TDataWriter.gen"
#else
#include "dds_c/generic/dds_c_data_TDataWriter.gen"
#endif


#undef TDataWriter
#undef TData

#undef TTYPENAME

/* ----------------------------------------------------------------- */
/* DDSDataReader
*/

/**
  <<IMPLEMENTATION >>

   Defines:   TDataReader, TDataSeq, TData
*/

/* Requires */
#define TTYPENAME   ChocolateRecipeTYPENAME

/* Defines */
#define TDataReader ChocolateRecipeDataReader
#define TDataSeq    ChocolateRecipeSeq
#define TData       ::com::rti::chocolatefactory::generated::ChocolateRecipe


#ifdef __cplusplus
#include "dds_cpp/generic/dds_cpp_data_TDataReader.gen"
#else
#include "dds_c/generic/dds_c_data_TDataReader.gen"
#endif


#undef TDataReader
#undef TDataSeq
#undef TData

#undef TTYPENAME

/* ----------------------------------------------------------------- */
/* TypeSupport

  <<IMPLEMENTATION >>

   Requires:  TTYPENAME,
              TPlugin_new
              TPlugin_delete
   Defines:   TTypeSupport, TData, TDataReader, TDataWriter
*/

/* Requires */
#define TTYPENAME    ChocolateRecipeTYPENAME
#define TPlugin_new  ::com::rti::chocolatefactory::generated::ChocolateRecipePlugin_new
#define TPlugin_delete  ::com::rti::chocolatefactory::generated::ChocolateRecipePlugin_delete

/* Defines */
#define TTypeSupport ChocolateRecipeTypeSupport
#define TData        ::com::rti::chocolatefactory::generated::ChocolateRecipe
#define TDataReader  ChocolateRecipeDataReader
#define TDataWriter  ChocolateRecipeDataWriter
#ifdef __cplusplus



#include "dds_cpp/generic/dds_cpp_data_TTypeSupport.gen"



#else
#include "dds_c/generic/dds_c_data_TTypeSupport.gen"
#endif
#undef TTypeSupport
#undef TData
#undef TDataReader
#undef TDataWriter

#undef TTYPENAME
#undef TPlugin_new
#undef TPlugin_delete





/* ========================================================================= */
/**
   <<IMPLEMENTATION>>

   Defines:   TData,
              TDataWriter,
              TDataReader,
              TTypeSupport

   Configure and implement 'ChocolateLotState' support classes.

   Note: Only the #defined classes get defined
*/

/* ----------------------------------------------------------------- */
/* DDSDataWriter
*/

/**
  <<IMPLEMENTATION >>

   Defines:   TDataWriter, TData
*/

/* Requires */
#define TTYPENAME   ChocolateLotStateTYPENAME

/* Defines */
#define TDataWriter ChocolateLotStateDataWriter
#define TData       ::com::rti::chocolatefactory::generated::ChocolateLotState


#ifdef __cplusplus
#include "dds_cpp/generic/dds_cpp_data_TDataWriter.gen"
#else
#include "dds_c/generic/dds_c_data_TDataWriter.gen"
#endif


#undef TDataWriter
#undef TData

#undef TTYPENAME

/* ----------------------------------------------------------------- */
/* DDSDataReader
*/

/**
  <<IMPLEMENTATION >>

   Defines:   TDataReader, TDataSeq, TData
*/

/* Requires */
#define TTYPENAME   ChocolateLotStateTYPENAME

/* Defines */
#define TDataReader ChocolateLotStateDataReader
#define TDataSeq    ChocolateLotStateSeq
#define TData       ::com::rti::chocolatefactory::generated::ChocolateLotState


#ifdef __cplusplus
#include "dds_cpp/generic/dds_cpp_data_TDataReader.gen"
#else
#include "dds_c/generic/dds_c_data_TDataReader.gen"
#endif


#undef TDataReader
#undef TDataSeq
#undef TData

#undef TTYPENAME

/* ----------------------------------------------------------------- */
/* TypeSupport

  <<IMPLEMENTATION >>

   Requires:  TTYPENAME,
              TPlugin_new
              TPlugin_delete
   Defines:   TTypeSupport, TData, TDataReader, TDataWriter
*/

/* Requires */
#define TTYPENAME    ChocolateLotStateTYPENAME
#define TPlugin_new  ::com::rti::chocolatefactory::generated::ChocolateLotStatePlugin_new
#define TPlugin_delete  ::com::rti::chocolatefactory::generated::ChocolateLotStatePlugin_delete

/* Defines */
#define TTypeSupport ChocolateLotStateTypeSupport
#define TData        ::com::rti::chocolatefactory::generated::ChocolateLotState
#define TDataReader  ChocolateLotStateDataReader
#define TDataWriter  ChocolateLotStateDataWriter
#ifdef __cplusplus



#include "dds_cpp/generic/dds_cpp_data_TTypeSupport.gen"



#else
#include "dds_c/generic/dds_c_data_TTypeSupport.gen"
#endif
#undef TTypeSupport
#undef TData
#undef TDataReader
#undef TDataWriter

#undef TTYPENAME
#undef TPlugin_new
#undef TPlugin_delete



} /* namespace generated */

} /* namespace chocolatefactory */

} /* namespace rti */

} /* namespace com */
