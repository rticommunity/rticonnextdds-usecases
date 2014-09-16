#####################################
# FindGStreamer.cmake
#####################################

if(ARCHITECTURE MATCHES "Win32")
     # We set the common path to the gstreamer
    set(GSTREAMER_LIB_PATH  ${CMAKE_SOURCE_DIR}/../thirdparty/gstreamer-sdk/win32/0.10/x86/lib)
    set(GLIB_INCLUDE  ${CMAKE_SOURCE_DIR}/../thirdparty/gstreamer-sdk/win32/0.10/x86/include/glib-2.0)
    set(GSTREAMER_INCLUDE ${CMAKE_SOURCE_DIR}/../thirdparty/gstreamer-sdk/win32/0.10/x86/include/gstreamer-0.10)
    set(XML_LIB_PATH ${CMAKE_SOURCE_DIR}/../thirdparty/gstreamer-sdk/win32/0.10/x86/include/libxml2)
    
    set(GSTREAMER_DEFINITIONS "/DSIMCLIST_NO_DUMPRESTORE")
    set(gobject_libname gobject-2.0.lib)
    set(gstreamer_libname gstreamer-0.10.lib)
    set(glib_libname glib-2.0.lib)
    set(gstapp_libname gstapp-0.10.lib)
    set(ADDITIONAL_LIBRARIES Shlwapi.lib Winmm.lib)
elseif(ARCHITECTURE MATCHES "Linux")
    set(GSTREAMER_DEFINITIONS "-lglib-2.0 -lgstreamer-0.10 -lgstapp-0.10 -std=c++0x")
    # We set the common path to the gstreamer
    set(GSTREAMER_LIB_PATH /usr/lib/x86_64-linux-gnu)
    set(GSTREAMER_CONFIG /usr/lib/x86_64-linux-gnu/glib-2.0/include)
    set(GLIB_INCLUDE /usr/include/glib-2.0)
    set(GSTREAMER_INCLUDE /usr/include/gstreamer-0.10)
    set(XML_LIB_PATH /usr/include/libxml2)
    
   
    # If you have installed the GStreamer compiling source code
    set(GSTREAMER_LIB_PATH /usr/local/lib/x86_64-linux-gnu
        ${GSTREAMER_LIB_PATH})
    set(GSTREAMER_CONFIG /usr/lib/x86_64-linux-gnu/glib-2.0/include
        ${GSTREAMER_CONFIG})
    set(GLIB_INCLUDE /usr/local/include/glib-2.0
    ${GLIB_INCLUDE})
    set(GSTREAMER_INCLUDE /usr/local/include/gstreamer-0.10
        ${GSTREAMER_INCLUDE})
    set(XML_LIB_PATH /usr/local/include/libxml2
        ${XML_LIB_PATH})
    
    # Now, we set the name of the libraries
    set(gobject_libname gobject-2.0)
    set(gstreamer_libname gstreamer-0.10)
    set(glib_libname glib-2.0)
    set(gstapp_libname gstapp-0.10)
endif()

# Find gst/gst.h & glib.h header files
find_path(GSTREAMER_INCLUDE_DIRS
  NAMES gst/gst.h
  PATHS ${GSTREAMER_INCLUDE}
  )
 
find_path(GSTREAMER_INCLUDE_DIRS
  NAMES glib.h
  PATHS ${GLIB_INCLUDE}
  )
  
# We need to include the GStreamer directories
set(GSTREAMER_INCLUDE_DIRS
  ${GLIB_INCLUDE}
  ${GSTREAMER_INCLUDE}
  ${GSTREAMER_CONFIG}
  ${XML_LIB_PATH}
  )  

# Add gobject-2.0, gstreamer-0.10, glib-2.0 & gstapp-0.10 libraries
find_library(gobject_lib 
  NAMES ${gobject_libname}
  PATHS ${GSTREAMER_LIB_PATH}
  )
find_library(gstreamer_lib 
  NAMES ${gstreamer_libname}
  PATHS ${GSTREAMER_LIB_PATH}
  )
find_library(glib_lib 
  NAMES ${glib_libname}
  PATHS ${GSTREAMER_LIB_PATH}
  ) 
find_library(gstapp_lib 
  NAMES ${gstapp_libname}
  PATHS ${GSTREAMER_LIB_PATH}
  )

set(GSTREAMER_LIBRARIES 
  ${gobject_lib}
  ${gstreamer_lib}
  ${glib_lib}
  ${gstapp_lib}
  ${ADDITIONAL_LIBRARIES}
  )
 message("LIBRARIES: <${GSTREAMER_LIBRARIES}>")
