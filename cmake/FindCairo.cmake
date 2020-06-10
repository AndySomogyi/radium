# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

#[=======================================================================[.rst:
FindCairo
---------

Find cairo

Imported targets
^^^^^^^^^^^^^^^^

This module defines the following :prop_tgt:`IMPORTED` targets:

``Cairo::Cairo``
  The Cairo library, if found.

Result variables
^^^^^^^^^^^^^^^^

This module will set the following variables in your project:

``CAIRO_FOUND``
  If false, do not try to use JPEG.
``CAIRO_INCLUDE_DIRS``
  where to find jpeglib.h, etc.
``CAIRO_LIBRARIES``
  the libraries needed to use JPEG.
``CAIRO_VERSION``
  the version of the JPEG library found

Cache variables
^^^^^^^^^^^^^^^

The following cache variables may also be set:

``CAIRO_INCLUDE_DIRS``
  where to find jpeglib.h, etc.
``CAIRO_LIBRARY_RELEASE``
  where to find the JPEG library (optimized).
``CAIRO_LIBRARY_DEBUG``
  where to find the JPEG library (debug).

#]=======================================================================]


find_path(CAIRO_INCLUDE_DIR cairo.h)

message("cairo include dir: ${CAIRO_INCLUDE_DIR}")

if (NOT CAIRO_INLUDE_DIR AND APPLE)

  message("mac looking...")

  # look for brew cairo
  find_path(
    CAIRO_INCLUDE_DIR
    cairo.h
    PATHS
    /usr/local/include
    /usr/local/opt
    /usr/local/opt/cairo
    /usr/local/opt/cairo/include
    /usr/local/opt/cairo/include/cairo
    )
endif()

message("cairo include dir: ${CAIRO_INCLUDE_DIR}")


set(cairo_names ${CAIRO_NAMES} cairo cairo-static libcairo libcairo-static)
foreach(name ${jpeg_names})
  list(APPEND cairo_names_debug "${name}d")
endforeach()

if(NOT CAIRO_LIBRARY)
  find_library(CAIRO_LIBRARY_RELEASE NAMES ${cairo_names})
  find_library(CAIRO_LIBRARY_DEBUG NAMES ${cairo_names_debug})
  include(SelectLibraryConfigurations)
  select_library_configurations(CAIRO)
  mark_as_advanced(CAIRO_LIBRARY_RELEASE CAIRO_LIBRARY_DEBUG)
endif()
unset(cairo_names)
unset(cairo_names_debug)

message("cairo_library: ${CAIRO_LIBRARY}")

message("ciaro release lib: ${CAIRO_LIBRARY_RELEASE}")
message("ciaro debug lib: ${CAIRO_LIBRARY_DEBUG}")


if (CAIRO_INCLUDE_DIR)
  message("looking at ${CAIRO_INCLUDE_DIR}/cairo-version.h")

    if (EXISTS "${CAIRO_INCLUDE_DIR}/cairo-version.h")
        file(READ "${CAIRO_INCLUDE_DIR}/cairo-version.h" CAIRO_VERSION_CONTENT)

        string(REGEX MATCH "#define +CAIRO_VERSION_MAJOR +([0-9]+)" _dummy "${CAIRO_VERSION_CONTENT}")
        set(CAIRO_VERSION_MAJOR "${CMAKE_MATCH_1}")

        string(REGEX MATCH "#define +CAIRO_VERSION_MINOR +([0-9]+)" _dummy "${CAIRO_VERSION_CONTENT}")
        set(CAIRO_VERSION_MINOR "${CMAKE_MATCH_1}")

        string(REGEX MATCH "#define +CAIRO_VERSION_MICRO +([0-9]+)" _dummy "${CAIRO_VERSION_CONTENT}")
        set(CAIRO_VERSION_MICRO "${CMAKE_MATCH_1}")

        set(CAIRO_VERSION "${CAIRO_VERSION_MAJOR}.${CAIRO_VERSION_MINOR}.${CAIRO_VERSION_MICRO}")
    endif ()
endif ()

if ("${Cairo_FIND_VERSION}" VERSION_GREATER "${CAIRO_VERSION}")
    message(FATAL_ERROR "Required version (" ${Cairo_FIND_VERSION} ") is higher than found version (" ${CAIRO_VERSION} ")")
endif ()


message("cairo version: ${CAIRO_VERSION}")

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(CAIRO
  REQUIRED_VARS CAIRO_LIBRARY CAIRO_INCLUDE_DIR
  VERSION_VAR CAIRO_VERSION)

message("CAIRO_FOUND: ${CAIRO_FOUND}")

if(CAIRO_FOUND)
  set(CAIRO_LIBRARIES ${CAIRO_LIBRARY})
  set(CAIRO_INCLUDE_DIRS "${CAIRO_INCLUDE_DIR}")

  if(NOT TARGET Cairo::Cairo)
    add_library(Cairo::Cairo UNKNOWN IMPORTED)
    if(CAIRO_INCLUDE_DIRS)
      set_target_properties(Cairo::Cairo PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES "${CAIRO_INCLUDE_DIRS}")
    endif()
    if(EXISTS "${CAIRO_LIBRARY}")
      set_target_properties(Cairo::Cairo PROPERTIES
        IMPORTED_LINK_INTERFACE_LANGUAGES "C"
        IMPORTED_LOCATION "${CAIRO_LIBRARY}")
    endif()
    if(EXISTS "${CAIRO_LIBRARY_RELEASE}")
      set_property(TARGET Cairo::Cairo APPEND PROPERTY
        IMPORTED_CONFIGURATIONS RELEASE)
      set_target_properties(Cairo::Cairo PROPERTIES
        IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "C"
        IMPORTED_LOCATION_RELEASE "${CAIRO_LIBRARY_RELEASE}")
    endif()
    if(EXISTS "${CAIRO_LIBRARY_DEBUG}")
      set_property(TARGET Cairo::Cairo APPEND PROPERTY
        IMPORTED_CONFIGURATIONS DEBUG)
      set_target_properties(Cairo::Cairo PROPERTIES
        IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "C"
        IMPORTED_LOCATION_DEBUG "${CAIRO_LIBRARY_DEBUG}")
    endif()
  endif()
endif()

mark_as_advanced(CAIRO_LIBRARY CAIRO_INCLUDE_DIR)
