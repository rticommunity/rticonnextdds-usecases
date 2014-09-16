########################
# VideoPublisher
########################

include_directories(
    ${CONNEXTDDS_INCLUDE_DIRS}
    ${GSTREAMER_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}/VideoPublisher
    ${CMAKE_SOURCE_DIR}/CommonInfrastructure
)

add_definitions(
    ${CONNEXTDDS_DEFINITIONS}
    ${GSTREAMER_DEFINITIONS}
)

# Executable
###########
# Include directories for the Executable build

# Files to include in the Executable build
file(GLOB_RECURSE VideoPublisher_sources
  ${CMAKE_SOURCE_DIR}/CommonInfrastructure/DDSCommunicator.cxx
  ${CMAKE_SOURCE_DIR}/CommonInfrastructure/DDSCommunicator.h
  ${CMAKE_SOURCE_DIR}/CommonInfrastructure/DDSTypeWrapper.h
  ${CMAKE_SOURCE_DIR}/CommonInfrastructure/OSAPI.cxx
  ${CMAKE_SOURCE_DIR}/CommonInfrastructure/OSAPI.h
  ${CMAKE_SOURCE_DIR}/CommonInfrastructure/SimCList.cxx
  ${CMAKE_SOURCE_DIR}/CommonInfrastructure/simclist.h
  ${CMAKE_SOURCE_DIR}/CommonInfrastructure/VideoBuffer.cxx
  ${CMAKE_SOURCE_DIR}/CommonInfrastructure/VideoBuffer.h
  ${CMAKE_SOURCE_DIR}/CommonInfrastructure/VideoEvent.h
  ${CMAKE_SOURCE_DIR}/CommonInfrastructure/VideoSource.cxx
  ${CMAKE_SOURCE_DIR}/CommonInfrastructure/VideoSource.h
  ${CMAKE_SOURCE_DIR}/VideoPublisher/*.h
  ${CMAKE_SOURCE_DIR}/VideoPublisher/*.cxx
  )
  
add_executable(VideoPublisher
    ${VideoPublisher_sources}
)

add_dependencies(VideoPublisher SharedDataTypes)

if(ARCHITECTURE MATCHES "Win32")
    target_link_libraries(VideoPublisher 
        SharedDataTypes.lib
        ${GSTREAMER_LIBRARIES}
        ${CONNEXTDDS_LIBRARIES} 
    )    
    SET_TARGET_PROPERTIES( VideoPublisher
        PROPERTIES LINK_FLAGS "/LIBPATH:${GSTREAMER_LIB_PATH};${StreamingVideo_BIN_DIR}")
elseif (ARCHITECTURE MATCHES "Linux")
    target_link_libraries(VideoPublisher 
        ${GSTREAMER_LIBRARIES}
        ${CONNEXTDDS_LIBRARIES} 
        SharedDataTypes
    )
elseif (ARCHITECTURE MATCHES "Darwin")
    target_link_libraries(VideoPublisher 
        ${CONNEXTDDS_LIBRARIES} 
        SharedDataTypes
    )    
endif()

foreach (output_config ${CMAKE_CONFIGURATION_TYPES})
    string(TOUPPER ${output_config} output_config)
    set_target_properties(VideoPublisher PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY_${output_config} 
            ${StreamingVideo_BIN_DIR}
        LIBRARY_OUTPUT_DIRECTORY_${output_config}
            ${StreamingVideo_BIN_DIR}
        ARCHIVE_OUTPUT_DIRECTORY_${output_config}
            ${StreamingVideo_BIN_DIR}
    )
endforeach()
