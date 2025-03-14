# - Try to find Glib and its components (gio, gobject etc)
# Once done, this will define
#
#  GLIB_FOUND - system has Glib
#  GLIB_INCLUDE_DIRS - the Glib include directories
#  GLIB_LIBRARIES - link these to use Glib
#
# Optionally, the COMPONENTS keyword can be passed to FIND_PACKAGE()
# and Glib components can be looked for.  Currently, the following
# components can be used, and they define the following variables if
# found:
#
#  gio:             GLIB_GIO_LIBRARIES
#  gobject:         GLIB_GOBJECT_LIBRARIES
#  gmodule:         GLIB_GMODULE_LIBRARIES
#  gthread:         GLIB_GTHREAD_LIBRARIES
#
# Note that the respective _INCLUDE_DIR variables are not set, since
# all headers are in the same directory as GLIB_INCLUDE_DIRS.
#
# Copyright (C) 2012 Raphael Kubo da Costa <rakuco@webkit.org>
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
# 1.  Redistributions of source code must retain the above copyright
#     notice, this list of conditions and the following disclaimer.
# 2.  Redistributions in binary form must reproduce the above copyright
#     notice, this list of conditions and the following disclaimer in the
#     documentation and/or other materials provided with the distribution.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDER AND ITS CONTRIBUTORS ``AS
# IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
# THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
# PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR ITS
# CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
# EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
# PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
# OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
# WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
# OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
# ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

find_package(PkgConfig)
pkg_check_modules(PC_GLIB QUIET glib-2.0)

FIND_LIBRARY(GLIB_LIBRARIES
    NAMES glib-2.0
    HINTS ${PC_GLIB_LIBDIR}
          ${PC_GLIB_LIBRARY_DIRS}
)

# Files in glib's main include path may include glibconfig.h, which,
# for some odd reason, is normally in $LIBDIR/glib-2.0/include.
GET_FILENAME_COMPONENT(_GLIB_LIBRARY_DIR ${GLIB_LIBRARIES} PATH)
FIND_PATH(GLIBCONFIG_INCLUDE_DIR
    NAMES glibconfig.h
    HINTS ${PC_LIBDIR} ${PC_LIBRARY_DIRS} ${_GLIB_LIBRARY_DIR}
    PATH_SUFFIXES glib-2.0/include
)

FIND_PATH(GLIB_INCLUDE_DIR
    NAMES glib.h
    HINTS ${PC_GLIB_INCLUDEDIR}
          ${PC_GLIB_INCLUDE_DIRS}
    PATH_SUFFIXES glib-2.0
)

SET(GLIB_INCLUDE_DIRS ${GLIB_INCLUDE_DIR} ${GLIBCONFIG_INCLUDE_DIR})

# Version detection
FILE(READ "${GLIBCONFIG_INCLUDE_DIR}/glibconfig.h" GLIBCONFIG_H_CONTENTS)
STRING(REGEX MATCH "#define GLIB_MAJOR_VERSION ([0-9]+)" _dummy "${GLIBCONFIG_H_CONTENTS}")
SET(GLIB_VERSION_MAJOR "${CMAKE_MATCH_1}")
STRING(REGEX MATCH "#define GLIB_MINOR_VERSION ([0-9]+)" _dummy "${GLIBCONFIG_H_CONTENTS}")
SET(GLIB_VERSION_MINOR "${CMAKE_MATCH_1}")
STRING(REGEX MATCH "#define GLIB_MICRO_VERSION ([0-9]+)" _dummy "${GLIBCONFIG_H_CONTENTS}")
SET(GLIB_VERSION_MICRO "${CMAKE_MATCH_1}")
SET(GLIB_VERSION "${GLIB_VERSION_MAJOR}.${GLIB_VERSION_MINOR}.${GLIB_VERSION_MICRO}")

# Additional Glib components.  We only look for libraries, as not all of them
# have corresponding headers and all headers are installed alongside the main
# glib ones.
FOREACH (_component ${GLIB_FIND_COMPONENTS})
    IF (${_component} STREQUAL "gio")
        FIND_LIBRARY(GLIB_GIO_LIBRARIES NAMES gio-2.0 HINTS ${_GLIB_LIBRARY_DIR})
        SET(ADDITIONAL_REQUIRED_VARS ${ADDITIONAL_REQUIRED_VARS} GLIB_GIO_LIBRARIES)
    ELSEIF (${_component} STREQUAL "gobject")
        FIND_LIBRARY(GLIB_GOBJECT_LIBRARIES NAMES gobject-2.0 HINTS ${_GLIB_LIBRARY_DIR})
        SET(ADDITIONAL_REQUIRED_VARS ${ADDITIONAL_REQUIRED_VARS} GLIB_GOBJECT_LIBRARIES)
    ELSEIF (${_component} STREQUAL "gmodule")
        FIND_LIBRARY(GLIB_GMODULE_LIBRARIES NAMES gmodule-2.0 HINTS ${_GLIB_LIBRARY_DIR})
        SET(ADDITIONAL_REQUIRED_VARS ${ADDITIONAL_REQUIRED_VARS} GLIB_GMODULE_LIBRARIES)
    ELSEIF (${_component} STREQUAL "gthread")
        FIND_LIBRARY(GLIB_GTHREAD_LIBRARIES NAMES gthread-2.0 HINTS ${_GLIB_LIBRARY_DIR})
        SET(ADDITIONAL_REQUIRED_VARS ${ADDITIONAL_REQUIRED_VARS} GLIB_GTHREAD_LIBRARIES)
    ENDIF ()
ENDFOREACH ()

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(GLIB REQUIRED_VARS GLIB_INCLUDE_DIRS GLIB_LIBRARIES ${ADDITIONAL_REQUIRED_VARS}
                                       VERSION_VAR   GLIB_VERSION)


find_program(GLIB2_GENMARSHAL_UTIL glib-genmarshal)

macro(glib2_genmarshal output_name)
    file(REMOVE ${CMAKE_CURRENT_BINARY_DIR}/genmarshal_tmp)
    foreach(_declaration ${ARGN})
        file(APPEND ${CMAKE_CURRENT_BINARY_DIR}/genmarshal_tmp "${_declaration}\n")
    endforeach()
    add_custom_command(
        OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/${output_name}.h ${CMAKE_CURRENT_BINARY_DIR}/${output_name}.c
        COMMAND ${GLIB2_GENMARSHAL_UTIL} --header genmarshal_tmp > ${output_name}.h
        COMMAND ${GLIB2_GENMARSHAL_UTIL} --body genmarshal_tmp > ${output_name}.c
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    )
endmacro()
