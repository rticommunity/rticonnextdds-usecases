
/*
  WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

  This file was generated from ChocolateFactory.idl using "rtiddsgen".
  The rtiddsgen tool is part of the RTI Connext distribution.
  For more information, type 'rtiddsgen -help' at a command shell
  or consult the RTI Connext manual.
*/

#ifndef ChocolateFactorySupport_1774920665_h
#define ChocolateFactorySupport_1774920665_h

/* Uses */
#include "ChocolateFactory.h"



#ifdef __cplusplus
#ifndef ndds_cpp_h
  #include "ndds/ndds_cpp.h"
#endif
#else
#ifndef ndds_c_h
  #include "ndds/ndds_c.h"
#endif
#endif


namespace com{

namespace rti{

namespace chocolatefactory{

namespace generated{
        

/* ========================================================================= */
/**
   Uses:     T

   Defines:  TTypeSupport, TDataWriter, TDataReader

   Organized using the well-documented "Generics Pattern" for
   implementing generics in C and C++.
*/

#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
  /* If the code is building on Windows, start exporting symbols.
  */
  #undef NDDSUSERDllExport
  #define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifdef __cplusplus

DDS_TYPESUPPORT_CPP(ChocolateRecipeTypeSupport, ChocolateRecipe);

DDS_DATAWRITER_CPP(ChocolateRecipeDataWriter, ChocolateRecipe);
DDS_DATAREADER_CPP(ChocolateRecipeDataReader, ChocolateRecipeSeq, ChocolateRecipe);


#else

DDS_TYPESUPPORT_C(ChocolateRecipeTypeSupport, ChocolateRecipe);
DDS_DATAWRITER_C(ChocolateRecipeDataWriter, ChocolateRecipe);
DDS_DATAREADER_C(ChocolateRecipeDataReader, ChocolateRecipeSeq, ChocolateRecipe);

#endif

#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
  /* If the code is building on Windows, stop exporting symbols.
   */
  #undef NDDSUSERDllExport
  #define NDDSUSERDllExport
#endif

        

/* ========================================================================= */
/**
   Uses:     T

   Defines:  TTypeSupport, TDataWriter, TDataReader

   Organized using the well-documented "Generics Pattern" for
   implementing generics in C and C++.
*/

#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
  /* If the code is building on Windows, start exporting symbols.
  */
  #undef NDDSUSERDllExport
  #define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifdef __cplusplus

DDS_TYPESUPPORT_CPP(ChocolateLotStateTypeSupport, ChocolateLotState);

DDS_DATAWRITER_CPP(ChocolateLotStateDataWriter, ChocolateLotState);
DDS_DATAREADER_CPP(ChocolateLotStateDataReader, ChocolateLotStateSeq, ChocolateLotState);


#else

DDS_TYPESUPPORT_C(ChocolateLotStateTypeSupport, ChocolateLotState);
DDS_DATAWRITER_C(ChocolateLotStateDataWriter, ChocolateLotState);
DDS_DATAREADER_C(ChocolateLotStateDataReader, ChocolateLotStateSeq, ChocolateLotState);

#endif

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


#endif  /* ChocolateFactorySupport_1774920665_h */
