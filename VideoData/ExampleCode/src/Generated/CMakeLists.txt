########################
# SharedDataTypes
########################

include_directories(
    ${CONNEXTDDS_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}/Generated
)

add_definitions(
    ${CONNEXTDDS_DEFINITIONS}
)

# Library
###########
# Include directories for the Executable build

# Files to include in the Executable build
file(GLOB_RECURSE SharedDataTypes_sources
  ${CMAKE_SOURCE_DIR}/Generated/VideoData.cxx
  ${CMAKE_SOURCE_DIR}/Generated/VideoData.h
  ${CMAKE_SOURCE_DIR}/Generated/VideoDataPlugin.cxx
  ${CMAKE_SOURCE_DIR}/Generated/VideoDataPlugin.h
  ${CMAKE_SOURCE_DIR}/Generated/VideoDataSupport.cxx
  ${CMAKE_SOURCE_DIR}/Generated/VideoDataSupport.h
  )
  
# Create object library
add_library(SharedDataTypes ${SharedDataTypes_sources})
add_dependencies(SharedDataTypes RUN_RTIDDSGEN)

target_link_libraries(SharedDataTypes 
    ${CONNEXTDDS_LIBRARIES}
)

set_target_properties(SharedDataTypes PROPERTIES PREFIX "")


foreach (output_config ${CMAKE_CONFIGURATION_TYPES})
    string(TOUPPER ${output_config} output_config)
    set_target_properties(SharedDataTypes PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY_${output_config} 
            ${StreamingVideo_BIN_DIR}
        LIBRARY_OUTPUT_DIRECTORY_${output_config}
            ${StreamingVideo_BIN_DIR}
        ARCHIVE_OUTPUT_DIRECTORY_${output_config}
            ${StreamingVideo_BIN_DIR}
    )
endforeach()
