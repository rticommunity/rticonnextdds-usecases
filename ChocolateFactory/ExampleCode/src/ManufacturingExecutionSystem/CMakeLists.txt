########################
# ManufacturingExecutionSystem
########################

include_directories(
    ${CONNEXTDDS_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}/ManufacturingExecutionSystem
    ${CMAKE_SOURCE_DIR}/CommonInfrastructure
)

add_definitions(
    ${CONNEXTDDS_DEFINITIONS}
)

# Executable
###########
# Include directories for the Executable build

# Files to include in the Executable build
file(GLOB_RECURSE ManufacturingExecutionSystem_sources
  ${CMAKE_SOURCE_DIR}/CommonInfrastructure/*.h
  ${CMAKE_SOURCE_DIR}/CommonInfrastructure/*.cxx
  ${CMAKE_SOURCE_DIR}/ManufacturingExecutionSystem/*.h
  ${CMAKE_SOURCE_DIR}/ManufacturingExecutionSystem/*.cxx
  )
  
add_executable(ManufacturingExecutionSystem
    ${ManufacturingExecutionSystem_sources}
)

add_dependencies(ManufacturingExecutionSystem SharedDataTypes)

if(ARCHITECTURE MATCHES "Win32")
    target_link_libraries(ManufacturingExecutionSystem 
        ${CONNEXTDDS_LIBRARIES} 
        SharedDataTypes.lib
    )    
    SET_TARGET_PROPERTIES( ManufacturingExecutionSystem
        PROPERTIES LINK_FLAGS "/LIBPATH:${ChocolateFactory_BIN_DIR}" )
elseif (ARCHITECTURE MATCHES "Linux")
    target_link_libraries(ManufacturingExecutionSystem 
        ${CONNEXTDDS_LIBRARIES} 
        SharedDataTypes
    )    
elseif (ARCHITECTURE MATCHES "Darwin")
    target_link_libraries(ManufacturingExecutionSystem 
        ${CONNEXTDDS_LIBRARIES} 
        SharedDataTypes
    )    
endif()

foreach (output_config ${CMAKE_CONFIGURATION_TYPES})
    string(TOUPPER ${output_config} output_config)
    set_target_properties(ManufacturingExecutionSystem PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY_${output_config} 
            ${ChocolateFactory_BIN_DIR}
        LIBRARY_OUTPUT_DIRECTORY_${output_config}
            ${ChocolateFactory_BIN_DIR}
        ARCHIVE_OUTPUT_DIRECTORY_${output_config}
            ${ChocolateFactory_BIN_DIR}
    )
endforeach()
