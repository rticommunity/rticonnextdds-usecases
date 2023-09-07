# - Try to find GStreamer and its plugins using FindPkgConfig
#
# This module will define:
#  GStreamer_FOUND - system has GStreamer
#  GStreamer_INCLUDE_DIRS - the GStreamer include directories
#  GStreamer_LIBRARIES - link these to use GStreamer
#  GStreamer_<component>_INCLUDE_DIRS - the GStreamer include directories for each component
#  GStreamer_<component>_LIBRARIES - link these to use GStreamer for each component
#

find_package(PkgConfig REQUIRED QUIET)


pkg_get_variable(GSTREAMER_PLUGIN_DIR gstreamer-1.0 pluginsdir) #to get the gstreamer plugins directory
set(GStreamer_PLUGIN_DIR ${GSTREAMER_PLUGIN_DIR} CACHE PATH "The path to the gstreamer plugins installation directory")


#########
# Imported Targets
# for the base GStreamer-1.0
pkg_check_modules(GStreamer REQUIRED QUIET gstreamer-1.0>=${GStreamer_FIND_VERSION})
add_library(GStreamer INTERFACE IMPORTED)
set_target_properties(GStreamer
	PROPERTIES
	INTERFACE_INCLUDE_DIRECTORIES "${GStreamer_INCLUDE_DIRS}"
	INTERFACE_LINK_LIBRARIES "${GStreamer_LIBRARIES}"
)

set(_GStreamer_REQUIRED_VARS GStreamer_INCLUDE_DIRS GStreamer_LIBRARIES)

foreach (_component ${GStreamer_FIND_COMPONENTS})
	# message(DEBUG "GStreamer components requested " ${_component})

	pkg_check_modules(GStreamer_${_component} REQUIRED QUIET gstreamer-${_component}-1.0>=${GStreamer_FIND_VERSION})
	add_library(GStreamer::${_component} INTERFACE IMPORTED)
	set_target_properties(GStreamer::${_component}
		PROPERTIES
			INTERFACE_INCLUDE_DIRECTORIES "${GStreamer_${_component}_INCLUDE_DIRS}"
			INTERFACE_LINK_LIBRARIES "${GStreamer_${_component}_LIBRARIES}"
		)
	list(APPEND _GStreamer_REQUIRED_VARS  GStreamer_${_component}_VERSION GStreamer_${_component}_INCLUDE_DIRS GStreamer_${_component}_LIBRARIES)
endforeach ()

#########
# Find Arguments Handling
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(GStreamer
	REQUIRED_VARS
		GStreamer_VERSION GStreamer_PLUGIN_DIR _GStreamer_REQUIRED_VARS
	VERSION_VAR
		GStreamer_VERSION
	HANDLE_COMPONENTS
)
