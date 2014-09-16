########################
# RecipeGenerator
########################

include_directories(
    ${CONNEXTDDS_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}/RecipeGenerator
    ${CMAKE_SOURCE_DIR}/CommonInfrastructure
)

add_definitions(
    ${CONNEXTDDS_DEFINITIONS}
)

# Executable
###########
# Include directories for the Executable build

# Files to include in the Executable build
file(GLOB_RECURSE ReceipeGenerator_sources
  ${CMAKE_SOURCE_DIR}/CommonInfrastructure/DDSTypeWrapper.h
  ${CMAKE_SOURCE_DIR}/CommonInfrastructure/DDSCommunicator.cxx
  ${CMAKE_SOURCE_DIR}/CommonInfrastructure/DDSCommunicator.h
  ${CMAKE_SOURCE_DIR}/CommonInfrastructure/OSAPI.cxx
  ${CMAKE_SOURCE_DIR}/CommonInfrastructure/OSAPI.h
  ${CMAKE_SOURCE_DIR}/RecipeGenerator/*.h
  ${CMAKE_SOURCE_DIR}/RecipeGenerator/*.cxx
  )

  
add_executable(RecipeGenerator
    ${ReceipeGenerator_sources}
)

add_dependencies(RecipeGenerator SharedDataTypes)

if(ARCHITECTURE MATCHES "Win32")
    target_link_libraries(RecipeGenerator 
        ${CONNEXTDDS_LIBRARIES} 
        SharedDataTypes.lib
    )    
    SET_TARGET_PROPERTIES( RecipeGenerator
        PROPERTIES LINK_FLAGS "/LIBPATH:${ChocolateFactory_BIN_DIR}" )
elseif (ARCHITECTURE MATCHES "Linux")
    target_link_libraries(RecipeGenerator 
        ${CONNEXTDDS_LIBRARIES} 
        SharedDataTypes
    )    
elseif (ARCHITECTURE MATCHES "Darwin")
    target_link_libraries(RecipeGenerator 
        ${CONNEXTDDS_LIBRARIES} 
        SharedDataTypes
    )    
endif()


foreach (output_config ${CMAKE_CONFIGURATION_TYPES})
    string(TOUPPER ${output_config} output_config)
    set_target_properties(RecipeGenerator PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY_${output_config} 
            ${ChocolateFactory_BIN_DIR}
        LIBRARY_OUTPUT_DIRECTORY_${output_config}
            ${ChocolateFactory_BIN_DIR}
        ARCHIVE_OUTPUT_DIRECTORY_${output_config}
            ${ChocolateFactory_BIN_DIR}
    )
endforeach()
