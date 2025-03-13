#Set the name and code for the project
project(ChocolateFactory CXX)

#Set the minimum version of cmake required to build this project
cmake_minimum_required(VERSION 3.10)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/../cmake")

#Find the ConnextDDS libraries.This will look fo the core and API libraries
#only
find_package(RTIConnextDDS
  "6.1.0"
  REQUIRED
  COMPONENTS core)

set(IDL_PATH ${CMAKE_CURRENT_SOURCE_DIR}/Idl/ChocolateFactory.idl)
set(CODEGEN_PATH ${CMAKE_CURRENT_SOURCE_DIR}/Generated)
set(MES_PATH ${CMAKE_CURRENT_SOURCE_DIR}/ManufacturingExecutionSystem)
set(RECIPE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/RecipeGenerator)
set(STATION_PATH ${CMAKE_CURRENT_SOURCE_DIR}/StationController)

#Run Codegen to generate the source code files for the types
include(ConnextDdsCodegen)
connextdds_rtiddsgen_run(
  IDL_FILE ${IDL_PATH}
  OUTPUT_DIRECTORY ${CODEGEN_PATH}
  LANG C++11)

set(TYPE_FILES
  "${CODEGEN_PATH}/ChocolateFactory.cxx"
  "${CODEGEN_PATH}/ChocolateFactoryPlugin.cxx")
  
set(TYPE_HEADERS
  "${CODEGEN_PATH}/ChocolateFactory.hpp"
  "${CODEGEN_PATH}/ChocolateFactoryPlugin.hpp")

add_custom_target(codegen_sources
  DEPENDS ${TYPE_FILES})

#Create a library for the Common Infrastructure
set(LIB_COMMON_SRC
  "${CMAKE_CURRENT_SOURCE_DIR}/CommonInfrastructure/DDSCommunicator.cxx"
  "${CMAKE_CURRENT_SOURCE_DIR}/CommonInfrastructure/EnumPrintHelpers.cxx"
  "${CMAKE_CURRENT_SOURCE_DIR}/CommonInfrastructure/InputParser.cxx")

set(LIB_COMMON_H
  "${CMAKE_CURRENT_SOURCE_DIR}/CommonInfrastructure/DDSCommunicator.hpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/CommonInfrastructure/EnumPrintHelpers.hpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/CommonInfrastructure/InputParser.hpp")

add_library(common
  OBJECT ${LIB_COMMON_SRC} ${LIB_COMMON_H} ${TYPE_FILES})

target_link_libraries(common
  RTIConnextDDS::cpp2_api)

#Create the target for the executable
add_executable(ManufacturingExecutionSystem
  "${MES_PATH}/ManufacturingExecutionSystem.cxx"
  "${MES_PATH}/MESInterface.cxx"
  "${MES_PATH}/MESInterface.hpp"
  $<TARGET_OBJECTS:common>)

add_executable(RecipeGenerator
  "${RECIPE_PATH}/RecipeGenerator.cxx"
  "${RECIPE_PATH}/RecipePublisherInterface.cxx"
  "${RECIPE_PATH}/RecipePublisherInterface.hpp"
  $<TARGET_OBJECTS:common>)

add_executable(StationController
  "${STATION_PATH}/StationController.cxx"
  "${STATION_PATH}/StationController.hpp"
  "${STATION_PATH}/StationControllerInterface.cxx"
  "${STATION_PATH}/StationControllerInterface.hpp"
  $<TARGET_OBJECTS:common>)

target_link_libraries(StationController
  RTIConnextDDS::cpp2_api)

target_link_libraries(ManufacturingExecutionSystem
  RTIConnextDDS::cpp2_api)

target_link_libraries(RecipeGenerator
  RTIConnextDDS::cpp2_api)

add_dependencies(common
  codegen_sources)
