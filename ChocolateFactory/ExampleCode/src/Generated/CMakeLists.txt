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

# Executable
###########
# Include directories for the Executable build

# Files to include in the Executable build
file(GLOB_RECURSE SharedDataTypes_sources
  ${CMAKE_SOURCE_DIR}/Generated/ChocolateFactory.cxx
  ${CMAKE_SOURCE_DIR}/Generated/ChocolateFactory.h
  ${CMAKE_SOURCE_DIR}/Generated/ChocolateFactoryPlugin.cxx
  ${CMAKE_SOURCE_DIR}/Generated/ChocolateFactoryPlugin.h
  ${CMAKE_SOURCE_DIR}/Generated/ChocolateFactorySupport.cxx
  ${CMAKE_SOURCE_DIR}/Generated/ChocolateFactorySupport.h
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
            ${ChocolateFactory_BIN_DIR}
        LIBRARY_OUTPUT_DIRECTORY_${output_config}
            ${ChocolateFactory_BIN_DIR}
        ARCHIVE_OUTPUT_DIRECTORY_${output_config}
            ${ChocolateFactory_BIN_DIR}
    )
endforeach()
