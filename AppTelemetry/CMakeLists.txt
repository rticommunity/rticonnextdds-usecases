cmake_minimum_required(VERSION 3.10)
project(oteladapter)


# Find RTI Connext dependencies
list(APPEND CMAKE_MODULE_PATH
    "${CMAKE_CURRENT_SOURCE_DIR}/resource/cmake/rticonnextdds-cmake-utils/cmake/Modules"
)

include(ConnextDdsGenerateFiles)
include(ConnextDdsCodegen)

# Find RTI Connext DDS
find_package(
    RTIConnextDDS "6.1.2"
    REQUIRED
    COMPONENTS
        core
        routing_service
)

find_package(CURL REQUIRED)

# Use find_package to include OpenTelemetry C++ requirements
find_package(opentelemetry-cpp CONFIG REQUIRED 
    PATHS "${CMAKE_CURRENT_SOURCE_DIR}/otel-cpp/lib/cmake/opentelemetry-cpp/"
)
find_package(prometheus-cpp CONFIG REQUIRED 
    PATHS "${CMAKE_CURRENT_SOURCE_DIR}/otel-cpp/lib/cmake/prometheus-cpp/"
)

# Include directories
include_directories(
    ${RTIConnextDDS_INCLUDE_DIRS}
    "${CMAKE_CURRENT_SOURCE_DIR}/otel-cpp/include"
)

add_library(${PROJECT_NAME} SHARED
    "${CMAKE_CURRENT_SOURCE_DIR}/src/oteladapter.cxx"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/otelconnection.cxx"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/otelstreamwriter.cxx"    
)

set_target_properties(${PROJECT_NAME}
    PROPERTIES
        CXX_STANDARD 11
        CXX_STANDARD_REQUIRED ON
        LIBRARY_OUTPUT_DIRECTORY "${output_dir}"
        LIBRARY_OUTPUT_DIRECTORY_RELEASE "${output_dir}"
        LIBRARY_OUTPUT_DIRECTORY_DEBUG "${output_dir}"
        ARCHIVE_OUTPUT_DIRECTORY "${output_dir}"
        ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${output_dir}"
        ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${output_dir}"
        RUNTIME_OUTPUT_DIRECTORY "${output_dir}"
        RUNTIME_OUTPUT_DIRECTORY_RELEASE "${output_dir}"
        RUNTIME_OUTPUT_DIRECTORY_DEBUG "${output_dir}"
)

target_link_libraries(${PROJECT_NAME}
    RTIConnextDDS::routing_service_infrastructure
    RTIConnextDDS::cpp2_api
    ${CONNEXTDDS_EXTERNAL_LIBS}
    ${OPENTELEMETRY_CPP_LIBRARIES}
)

# Generator application
connextdds_rtiddsgen_run(
    IDL_FILE
        "${CMAKE_CURRENT_SOURCE_DIR}/generator/telemetry.idl"
    OUTPUT_DIRECTORY
        "${CMAKE_CURRENT_BINARY_DIR}/src/c++11"
    LANG C++11
    VAR "METRICS_TYPE"
    DISABLE_PREPROCESSOR
)

add_executable(generator
    "${CMAKE_CURRENT_SOURCE_DIR}/generator/c++11/generator.cxx"
    ${METRICS_TYPE_CXX11_SOURCES}
    "${CMAKE_CURRENT_SOURCE_DIR}/generator/c++11/application.hpp"
    ${METRICS_TYPE_CXX11_HEADERS}
)
target_link_libraries(generator
    PRIVATE
        RTIConnextDDS::cpp2_api
)
target_include_directories(generator
    PRIVATE
        "${CMAKE_CURRENT_BINARY_DIR}/src/c++11"
)

connextdds_copy_files(
    INPUT_FILES
        "${CMAKE_CURRENT_SOURCE_DIR}/src/RsTelemetryGateway.xml"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/run_tmux.sh"
        "${CMAKE_CURRENT_SOURCE_DIR}/generator/c++11/generator_qos.xml"
    OUTPUT_DIR
        "${CMAKE_CURRENT_BINARY_DIR}/"
)
