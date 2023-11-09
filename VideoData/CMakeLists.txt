cmake_minimum_required(VERSION 3.7)

project(ConnextGStreamerPlugins)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)


# Find dependencies
set(CMAKE_MODULE_PATH
    ${CMAKE_MODULE_PATH}
    ${CMAKE_CURRENT_SOURCE_DIR}/resource/cmake/rticonnextdds-cmake-utils/cmake/Modules
    ${CMAKE_CURRENT_SOURCE_DIR}/resource/cmake
)

find_package(
    RTIConnextDDS "6.1.1"
    REQUIRED
    COMPONENTS
        core
)

find_package(GStreamer 1.12.0 REQUIRED COMPONENTS video)

# Run Codegen to generate the source code files for the types
include(ConnextDdsCodegen)
connextdds_rtiddsgen_run(
    IDL_FILE
        "${CMAKE_CURRENT_SOURCE_DIR}/idl/video.idl"
    OUTPUT_DIRECTORY
        "${CMAKE_CURRENT_BINARY_DIR}/src/"
    LANG C
    DISABLE_PREPROCESSOR
)

add_library(videoTypes OBJECT
    ${video_C_GENERATED_SOURCES}
)
target_link_libraries(videoTypes
PUBLIC
        RTIConnextDDS::c_api
)

target_include_directories(videoTypes
PUBLIC
    "${CMAKE_CURRENT_BINARY_DIR}/src"
)

# Build the plugins
add_library(gstconnextsink
	SHARED
	"${CMAKE_CURRENT_SOURCE_DIR}/src/gst-connextsink/gstconnextsink.c"
)

target_link_libraries(gstconnextsink
	GStreamer
	GStreamer::video
	videoTypes
)

target_compile_options(gstconnextsink
	PRIVATE
	-Wall -Wextra -pedantic
)

set_target_properties(gstconnextsink
	PROPERTIES
	LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

add_library(gstconnextsrc
	SHARED
	"${CMAKE_CURRENT_SOURCE_DIR}/src/gst-connextsrc/gstconnextsrc.c"
)

target_link_libraries(gstconnextsrc
	GStreamer
	GStreamer::video
	videoTypes
)

target_compile_options(gstconnextsrc
	PRIVATE
	-Wall -Wextra -pedantic
)

set_target_properties(gstconnextsrc
	PROPERTIES
	LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

# Install the plugins to the gstreamer directory

install(TARGETS gstconnextsrc
	LIBRARY
	DESTINATION ${GSTREAMER_PLUGIN_DIR}
)

install(TARGETS gstconnextsink
	LIBRARY
	DESTINATION ${GSTREAMER_PLUGIN_DIR}
)