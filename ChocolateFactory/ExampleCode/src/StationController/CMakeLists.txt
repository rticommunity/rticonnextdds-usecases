########################
# StationController
########################

include_directories(
    ${CONNEXTDDS_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}/StationController
    ${CMAKE_SOURCE_DIR}/CommonInfrastructure
)

add_definitions(
    ${CONNEXTDDS_DEFINITIONS}
)

# Executable
###########
# Include directories for the Executable build

# Files to include in the Executable build
file(GLOB_RECURSE StationController_sources
  ${CMAKE_SOURCE_DIR}/CommonInfrastructure/*.h
  ${CMAKE_SOURCE_DIR}/CommonInfrastructure/*.cxx
  ${CMAKE_SOURCE_DIR}/StationController/*.h
  ${CMAKE_SOURCE_DIR}/StationController/*.cxx
  )

  
add_executable(StationController
    ${StationController_sources}
)

add_dependencies(StationController SharedDataTypes)

if(ARCHITECTURE MATCHES "Win32")
    target_link_libraries(StationController 
        ${CONNEXTDDS_LIBRARIES} 
        SharedDataTypes.lib
    )    
    SET_TARGET_PROPERTIES( StationController
        PROPERTIES LINK_FLAGS "/LIBPATH:${ChocolateFactory_BIN_DIR}" )
elseif (ARCHITECTURE MATCHES "Linux")
    target_link_libraries(StationController 
        ${CONNEXTDDS_LIBRARIES} 
        SharedDataTypes
    )    
elseif (ARCHITECTURE MATCHES "Darwin")
    target_link_libraries(StationController 
        ${CONNEXTDDS_LIBRARIES} 
        SharedDataTypes
    )    
endif()

foreach (output_config ${CMAKE_CONFIGURATION_TYPES})
    string(TOUPPER ${output_config} output_config)
    set_target_properties(StationController PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY_${output_config} 
            ${ChocolateFactory_BIN_DIR}
        LIBRARY_OUTPUT_DIRECTORY_${output_config}
            ${ChocolateFactory_BIN_DIR}
        ARCHIVE_OUTPUT_DIRECTORY_${output_config}
            ${ChocolateFactory_BIN_DIR}
    )
endforeach()
