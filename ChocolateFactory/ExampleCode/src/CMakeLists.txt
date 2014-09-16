project(ChocolateFactory)

# Minimum Required Version of CMake is 2.8.12 for Windows
# and 2.8.8 for the rest of platforms.
if (CMAKE_SYSTEM_NAME MATCHES "Windows")
  cmake_minimum_required(VERSION 2.8.12)
else()
  cmake_minimum_required(VERSION 2.8.7)
endif()

# NDDS version
set(RTI_NDDS_VERSION_MAJOR 5)
set(RTI_NDDS_VERSION_MINOR 1)
set(RTI_NDDS_VERSION_RELEASE 0)
set(RTI_NDDS_VERSION_REVISION 00)


# Add subdirectories
##########################################
# chocolate_factory library
# ------------------------
# Add cmake scripts directory to the modules path
# -----------------------------------------------
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_LIST_DIR}/cmake)

if(CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_CONFIGURATION_TYPES Debug Release)
    set(CMAKE_CONFIGURATION_TYPES "${CMAKE_CONFIGURATION_TYPES}"
        CACHE STRING "Reset the configurations to what we need" FORCE)
endif()

find_package(ConnextDDS REQUIRED)

# ChocolateFactory specific configuration
# ----------------------------
set(ChocolateFactory_BIN_DIR ${CMAKE_CURRENT_LIST_DIR}/bin/${ARCHITECTURE})

set ( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${ChocolateFactory_BIN_DIR})

add_subdirectory(ManufacturingExecutionSystem)
add_subdirectory(RecipeGenerator)
add_subdirectory(StationController)
#including library
add_subdirectory(Generated)
