# need 3.12 for FindPython support
cmake_minimum_required (VERSION 3.12)


if(DEFINED ENV{VCPKG_ROOT} AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
  set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake"
    CACHE STRING "")
    message(" [INFO] VCPKG CMAKE_TOOLCHAIN_FILE = ${CMAKE_TOOLCHAIN_FILE}")
endif()

message("VCPKG CMAKE_TOOLCHAIN_FILE = ${CMAKE_TOOLCHAIN_FILE}")

project(Radium)

# essets the target types
if(UNIX)
  # Both APPLE and UNIX are defined on OSX
  if(APPLE)
    set(RA_APPLE 1)
  else()
    set(RA_LINUX 1)
  endif()
  set(RA_UNIX 1)
elseif(WIN32)
  set(RA_WINDOWS 1)
endif()

# directory where we build the mechanica python package
set(RA_PYPKG_DIR ${CMAKE_BINARY_DIR}/radium)

# using magnum, so whole project needs C++11
set(CMAKE_CXX_STANDARD 17)

if(RA_WINDOWS)
  # windows needs this to compile the MASSIVE pybind11 stuff. 
  add_compile_options(-bigobj)
endif()

# we're compiling a bunch of shared libs, all should be pos independent.
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# quiet linker warnings on Apple
# set(CMAKE_CXX_VISIBILITY_PRESET hidden)

# Use Magnum's modules to find things, these set up cmake names / aliases using a
# magnum friendly naming scheme, add our module finders to cmake, these find
# stuff mechanica, needs, but magnum does not. Make sure to put Mechanica's
# dir before Magnums, so our versions get picked up *BEFORE* Magnum's.
list(APPEND CMAKE_MODULE_PATH
  ${PROJECT_SOURCE_DIR}/cmake
  ${PROJECT_SOURCE_DIR}/extern/magnum/modules
  ${PROJECT_SOURCE_DIR}/extern/magnum-plugins/modules)


message("CMAKE_SYSTEM_NAME: ${CMAKE_SYSTEM_NAME}")
message("CMAKE_OSX_DEPLOYMENT_TARGET: ${CMAKE_OSX_DEPLOYMENT_TARGET}")
message("MACOSX_DEPLOYMENT_TARGET: ${MACOSX_DEPLOYMENT_TARGET}")
message("CMAKE_OSX_SYSROOT: ${CMAKE_OSX_SYSROOT}")
message("XCODE_VERSION: ${XCODE_VERSION}")
message("CMAKE_GENERATOR: ${CMAKE_GENERATOR}")
message("CMAKE_CXX_COMPILER_ID: ${CMAKE_CXX_COMPILER_ID}")
message("CMAKE_CXX_COMPILER_VERSION: ${CMAKE_CXX_COMPILER_VERSION}")


#find_package(GLFW REQUIRED)

if(RA_WINDOWS)
  find_package(unofficial-cairo CONFIG REQUIRED)
  # add_library(<name> ALIAS <target>)

  # have to set this to create an alias, don't know why...
  set_property(TARGET unofficial::cairo::cairo PROPERTY	IMPORTED_GLOBAL TRUE)
  add_library(Cairo::Cairo ALIAS unofficial::cairo::cairo)
else()
  find_package(Cairo REQUIRED)
endif()

message("cairo: ${unofficial-cairo}")
#message("ucairo: ${unofficial::cairo}")
#message("ucairoc: ${unofficial::cairo::cairo}")

# needed for jpeg image writer
find_package(JPEG REQUIRED)

message("JPEG_INCLUDE_DIRS: ${JPEG_INCLUDE_DIRS}")
message("JPEG_LIBRARIES: ${JPEG_LIBRARIES}")
message("JPEG_VERSION: ${JPEG_VERSION}")

# link statically with JPEG, so we dont have to ship a dylib,
# brew installs newer JPEG, so that conflicts with stuff
set(MX_JPEG_INCLUDE_DIRS ${JPEG_INCLUDE_DIRS})  # /usr/local/include

if(APPLE)
  set(MX_JPEG_LIBRARIES /usr/local/lib/libjpeg.a)     #: /usr/local/lib/libjpeg.dylib
else()
  set(MX_JPEG_LIBRARIES ${JPEG_LIBRARIES})
endif()

message("MX_JPEG_INCLUDE_DIRS: ${MX_JPEG_INCLUDE_DIRS}")
message("MX_JPEG_LIBRARIES: ${MX_JPEG_LIBRARIES}")

set(CMAKE_INSTALL_PREFIX "$ENV{HOME}/local/mechanica" CACHE PATH "Install location for Mechancia")

set(BUILD_SHARED_LIBS ON CACHE BOOL "build shared/dynamic library")

set(MX_MODEL_DIR ${PROJECT_SOURCE_DIR}/testing/models CACHE PATH "directory for mechanica models" FORCE)

find_package(OpenGL REQUIRED)

#find_package(LLVM)

#find_package(OpenMM)

add_definitions(-DCX3D_SUPPORT_OPENGL)


include_directories(${OPENGL_INCLUDE_DIR})


# finds: GLFW_FOUND GLFW_INCLUDE_DIR GLFW_LIBRARIES
# find_package(GLFW 3.2 REQUIRED)


#include_directories(${GLFW_INCLUDE_DIRS})

#message("GLFW_INCLUDE_DIR ${GLFW_INCLUDE_DIR}")

#include_directories(${YOUR_DIRECTORY})

#include_directories(${GLFW_INCLUDE_DIR})

#message("GLFW_LIBRARIES: ${GLFW_LIBRARIES}")

message("before extern include path: ${CMAKE_INCLUDE_PATH}")
get_property(dirs DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY INCLUDE_DIRECTORIES)
foreach(dir ${dirs})
  message( "dir='${dir}'")
endforeach()

#if(MSVC)
#  string(REPLACE "/MD" "/MT" CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})
#  string(REPLACE "/MD" "/MT" CMAKE_CXX_FLAGS_DEBUG ${CMAKE_CXX_FLAGS_DEBUG})
#  string(REPLACE "/MD" "/MT" CMAKE_CXX_FLAGS_RELEASE ${CMAKE_CXX_FLAGS_RELEASE})
#endif(MSVC)



# process dependencies first
add_subdirectory(extern)




# CMake policies: enable MACOSX_RPATH by default
if(POLICY CMP0042)
    cmake_policy(SET CMP0042 NEW)
endif()
# Don't treat imported targets with :: as files
if(POLICY CMP0028)
    cmake_policy(SET CMP0028 NEW)
endif()

find_package(Magnum REQUIRED
  Shaders
  GlfwApplication)


add_subdirectory(include)
add_subdirectory(src)
add_subdirectory(testing)


file(COPY README.md DESTINATION ${CMAKE_BINARY_DIR})
