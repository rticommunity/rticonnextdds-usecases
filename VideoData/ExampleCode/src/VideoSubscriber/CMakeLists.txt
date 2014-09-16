########################
# VideoSubscriber
########################

include_directories(
    ${CONNEXTDDS_INCLUDE_DIRS}
    ${GSTREAMER_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}/VideoSubscriber
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
file(GLOB_RECURSE VideoSubscriber_sources
  ${CMAKE_SOURCE_DIR}/CommonInfrastructure/*.cxx
  ${CMAKE_SOURCE_DIR}/CommonInfrastructure/*.h
  ${CMAKE_SOURCE_DIR}/VideoSubscriber/*.h
  ${CMAKE_SOURCE_DIR}/VideoSubscriber/*.cxx
  )
  
add_executable(VideoSubscriber
    ${VideoSubscriber_sources}
)

add_dependencies(VideoSubscriber SharedDataTypes)

if(ARCHITECTURE MATCHES "Win32")
    target_link_libraries(VideoSubscriber 
        SharedDataTypes.lib
        ${GSTREAMER_LIBRARIES}
        ${CONNEXTDDS_LIBRARIES} 
    )    
    SET_TARGET_PROPERTIES( VideoSubscriber
        PROPERTIES LINK_FLAGS "/LIBPATH:${GSTREAMER_LIB_PATH};${StreamingVideo_BIN_DIR}")
elseif (ARCHITECTURE MATCHES "Linux")
    target_link_libraries(VideoSubscriber 
        ${CONNEXTDDS_LIBRARIES} 
        SharedDataTypes
        ${GSTREAMER_LIBRARIES}
    )
elseif (ARCHITECTURE MATCHES "Darwin")
    target_link_libraries(VideoSubscriber 
        ${CONNEXTDDS_LIBRARIES} 
        SharedDataTypes
    )    
endif()

foreach (output_config ${CMAKE_CONFIGURATION_TYPES})
    string(TOUPPER ${output_config} output_config)
    set_target_properties(VideoSubscriber PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY_${output_config} 
            ${StreamingVideo_BIN_DIR}
        LIBRARY_OUTPUT_DIRECTORY_${output_config}
            ${StreamingVideo_BIN_DIR}
        ARCHIVE_OUTPUT_DIRECTORY_${output_config}
            ${StreamingVideo_BIN_DIR}
    )
endforeach()
