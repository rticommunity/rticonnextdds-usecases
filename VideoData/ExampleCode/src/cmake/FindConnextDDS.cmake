#####################################
# FindConnextDDS.cmake
#####################################

# We need NDDSHOME set to know the location of the RTI Connext DDS installation
if (NOT DEFINED NDDSHOME)
    if (DEFINED ENV{NDDSHOME})
        set(NDDSHOME $ENV{NDDSHOME})
    else()
        message(FATAL_ERROR "$NDDSHOME not specified. Please set -DNDDSHOME= to your RTI Connext DDS installation directory")
    endif()
endif()

# We need to know the RTI Connext DDS libraries to compile against
if (NOT DEFINED ARCHITECTURE)
    if(DEFINED ENV{ARCHITECTURE})
        set(ARCHITECTURE $ENV{ARCHITECTURE})
    else()
        message(FATAL_ERROR "$ARCHITECTURE not specified. Please set -DARCHITECTURE= to your RTI Connext DDS architecture")
    endif()
endif()

# Connext DDS Definitions
if (ARCHITECTURE MATCHES "Linux")
    set(CONNEXTDDS_DEFINITIONS "-DRTI_UNIX -DRTI_LINUX")
    if (CMAKE_BUILD_TYPE MATCHES "Debug")
        set(CONNEXTDDS_DEFINITIONS ${CONNEXTDDS_DEFINITIONS} "-DRTI_PRECONDITION_TEST")
        set(nddscore_libname libnddscorezd.a)
        set(nddsc_libname libnddsczd.a)
        set(nddscpp_libname libnddscppzd.a)
    else()
        set(nddscore_libname libnddscorez.a)
        set(nddsc_libname libnddscz.a)
        set(nddscpp_libname libnddscppz.a)
    endif()
    set(external_libs "-ldl -lm -lpthread -lrt")
    add_custom_target(
        RUN_RTIDDSGEN
        COMMAND ${NDDSHOME}/scripts/rtiddsgen ${CMAKE_SOURCE_DIR}/Idl/VideoData.idl -namespace -replace -language C++ -d ${CMAKE_SOURCE_DIR}/Generated 
    )
elseif(ARCHITECTURE MATCHES "Win32")
    set(CONNEXTDDS_DEFINITIONS "-DWIN32 -D_WINDOWS -DRTI_WIN32 -D_BIND_TO_CURRENT_MFC_VERSION=1 -D_BIND_TO_CURRENT_CRT_VERSION=1 -D_CRT_SECURE_NO_WARNING")
    if (CMAKE_BUILD_TYPE MATCHES "Debug")
        set(CONNEXTDDS_DEFINITIONS ${CONNEXTDDS_DEFINITIONS} "-DRTI_PRECONDITION_TEST")
        set(nddscore_libname nddscorezd.lib)
        set(nddsc_libname nddsczd.lib)
        set(nddscpp_libname nddscppzd.lib)
    else()
        set(nddscore_libname nddscorez.lib)
        set(nddsc_libname nddscz.lib)
        set(nddscpp_libname nddscppz.lib)        
    endif()
    set(external_libs ws2_32 netapi32 version)
    add_custom_target(
        RUN_RTIDDSGEN
        COMMAND ${NDDSHOME}/scripts/rtiddsgen ${CMAKE_SOURCE_DIR}/Idl/VideoData.idl -namespace -replace -language C++ -d ${CMAKE_SOURCE_DIR}/Generated
    )
elseif(ARCHITECTURE MATCHES "Darwin")
    set(CONNEXTDDS_DEFINITIONS  "-DRTI_UNIX -DRTI_DARWIN -DRTI_DARWIN10 -DRTI_64BIT -Wno-return-type-c-linkage")
    if (CMAKE_CONFIGURATION_TYPES MATCHES "Debug")
        set(CONNEXTDDS_DEFINITIONS ${CONNEXTDDS_DEFINITIONS} "-DRTI_PRECONDITION_TEST")
        set(nddscore_libname libnddscorezd.a)
        set(nddsc_libname libnddsczd.a)
        set(nddscpp_libname libnddscppzd.a)
    else()
        set(nddscore_libname libnddscorez.a)
        set(nddsc_libname libnddscz.a)
        set(nddscpp_libname libnddscppz.a)    
    endif()
    add_custom_target(
        RUN_RTIDDSGEN
        COMMAND ${NDDSHOME}/scripts/rtiddsgen ${CMAKE_SOURCE_DIR}/Idl/VideoData.idl -namespace -replace -language C++ -d ${CMAKE_SOURCE_DIR}/Generated 
    )
endif()


# Find ndds_c.h header file
find_path(CONNEXTDDS_INCLUDE_DIRS
  NAMES ndds_c.h
  PATHS ${NDDSHOME}/include/ndds
  )

# We need to include both include and include/ndds directories
set(CONNEXTDDS_INCLUDE_DIRS
  ${NDDSHOME}/include
  ${CONNEXTDDS_INCLUDE_DIRS}
  )

# Add Core, C, and C++ libraries for the given architecture
find_library(nddscore_lib 
  NAMES ${nddscore_libname}
  PATHS ${NDDSHOME}/lib/${ARCHITECTURE}
  )

find_library(nddsc_lib 
  NAMES ${nddsc_libname}
  PATHS ${NDDSHOME}/lib/${ARCHITECTURE}
  )

find_library(nddscpp_lib 
  NAMES ${nddscpp_libname}
  PATHS ${NDDSHOME}/lib/${ARCHITECTURE}
  )

set(CONNEXTDDS_LIBRARIES 
  ${nddscpp_lib}
  ${nddsc_lib}
  ${nddscore_lib}
  ${CMAKE_DL_LIBS}
  ${external_libs}
  )
  
