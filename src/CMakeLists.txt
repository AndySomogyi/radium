# LLVM compile options
#add_definitions(${LLVM_LDFLAGS})

add_compile_options(-DMX_STRICT)


# quiet linker warnings on Apple
# set(CMAKE_CXX_VISIBILITY_PRESET hidden)

# Make sure the compiler can find include files for our Hello library
# when other libraries or executables link to Hello
include_directories(PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${LLVM_INCLUDE_DIRS})
include_directories(${GLM_INCLUDE_DIRS})

message(STATUS "numpy: ${NUMPY_INCLUDE_DIR}")


set(SRC
  ra_application.cpp
  ra_canvas.cpp
  ra_renderer.cpp
  ra_window.cpp
  radium.cpp
  )


set(HEADERS
  ${radium_PUBLIC_HEADERS}
  ra_application.hpp
  ra_canvas.hpp
  ra_renderer.hpp
  ra_window.hpp
  radium.hpp
  )




# For development, for the time being, we won't build the object library
# because it takes longer to build if we're only building one library,
# and won't build the py version for a while.

# build all the source as a CMake 'OBJECT' lib, this gets
# linked into the real libraries below.
#add_library(radium_OBJECTS OBJECT ${SRC} ${HEADERS})


# get the include directories of the dependencies that the radium objects use
# really goofy design decision in design of CMake OBJECT libraries -- no transitive includes
#target_include_directories(radium_OBJECTS PRIVATE $<TARGET_PROPERTY:mdcore_single,INTERFACE_INCLUDE_DIRECTORIES>)
#target_include_directories(radium_OBJECTS PRIVATE $<TARGET_PROPERTY:voro++,INTERFACE_INCLUDE_DIRECTORIES> )
#target_include_directories(radium_OBJECTS PRIVATE $<TARGET_PROPERTY:Magnum::Magnum,INTERFACE_INCLUDE_DIRECTORIES>)
#target_include_directories(radium_OBJECTS PRIVATE "${PROJECT_SOURCE_DIR}/include")
#target_include_directories(radium_OBJECTS PRIVATE ${NUMPY_INCLUDE_DIR})



# this is the "object library" target: compiles the sources only once
# need at least one src file in a project for xcode to build it, xcode
# won't work if any product *only* has an object src
add_library(radium_obj
  OBJECT
  ${SRC}
  ${HEADERS}
  )

set_target_properties(radium_obj PROPERTIES
  CXX_VISIBILITY_PRESET hidden
  VISIBILITY_INLINES_HIDDEN 1
  )

#message("Shader Program Res: ${MxMeshShaderProgramRes}")


target_include_directories(radium_obj PRIVATE
  ${PYBIND11_INCLUDE_DIR}
  ${RA_JPEG_INCLUDE_DIRS}
  )

# set_target_properties(radium PROPERTIES POSITION_INDEPENDENT_CODE ON)

# temporarily add add these includes until we get a stable public API
target_include_directories(radium_obj PUBLIC
  $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
  ${Python_INCLUDE_DIRS}
)


target_link_libraries(radium_obj
  glfw
  Magnum::Application
  Magnum::Magnum
  Magnum::Shaders
  ${OPENGL_LIBRARIES}
  )
 
target_link_libraries(radium_obj
  Cairo::Cairo
  JPEG::JPEG
  )

if(RA_WINDOWS)
  target_link_libraries(radium_obj unofficial::cairo::cairo-gobject)
endif()


source_group("Public Header Files" FILES ${radium_PUBLIC_HEADERS})



#message("radium_PUBLIC_HEADERS: ${radium_PUBLIC_HEADERS}")

#message("radium_SRC: ${SRC}")


# Link against LLVM libraries
#link_directories(${LLVM_LIBRARY_DIRS})
#target_link_libraries(radium ${LLVM_LIBRARIES})


# shared libraries need PIC
set_property(TARGET radium_obj PROPERTY POSITION_INDEPENDENT_CODE 1)


# shared and static libraries built from the same object files
add_library(radium_shared SHARED
  $<TARGET_OBJECTS:radium_obj>
  radium.cpp
  )

set_target_properties(radium_shared PROPERTIES
  CXX_VISIBILITY_PRESET hidden
  VISIBILITY_INLINES_HIDDEN 1
  )

set_target_properties(radium_shared PROPERTIES OUTPUT_NAME radium)

target_include_directories(radium_shared PUBLIC
  $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
  ${Python_INCLUDE_DIRS}
  #${NUMPY_INCLUDE_DIR}
  #$<INSTALL_INTERFACE:include/mylib>  # <prefix>/include/mylib
)

target_include_directories(radium_shared PRIVATE ${PYBIND11_INCLUDE_DIR})


target_link_libraries(radium_shared
  Python::Python
  Python::NumPy
  glfw
  Magnum::Application
  Magnum::Magnum
  Magnum::Shaders
  MagnumGlfwApplication
  Magnum_PyBind
  Magnum::SceneGraph
  Magnum::Primitives
  Magnum::MeshTools
  ${RA_JPEG_LIBRARIES}
  )
 
target_link_libraries(radium_shared
  Cairo::Cairo
  JPEG::JPEG
  )

if(RA_WINDOWS)
  target_link_libraries(radium_shared unofficial::cairo::cairo-gobject)
endif()

if(RA_APPLE)
  target_link_libraries(radium_shared MagnumWindowlessCglApplication)
elseif(RA_LINUX)
  target_link_libraries(radium_shared MagnumWindowlessEglApplication)
elseif(RA_WINDOWS)
  target_link_libraries(radium_shared MagnumWindowlessWglApplication)
endif()


# shared and static libraries built from the same object files
add_library(radium_static SHARED
  $<TARGET_OBJECTS:radium_obj>
  radium.cpp
  )

set_target_properties(radium_static PROPERTIES
  CXX_VISIBILITY_PRESET hidden
  VISIBILITY_INLINES_HIDDEN 1
  )

set_target_properties(radium_static PROPERTIES OUTPUT_NAME radium)

target_include_directories(radium_static PUBLIC
  $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
  ${Python_INCLUDE_DIRS}
  #${NUMPY_INCLUDE_DIR}
  #$<INSTALL_INTERFACE:include/mylib>  # <prefix>/include/mylib
)

target_include_directories(radium_static PRIVATE ${PYBIND11_INCLUDE_DIR})


target_link_libraries(radium_static
  Python::Python
  Python::NumPy
  glfw
  Magnum::Application
  Magnum::Magnum
  Magnum::Shaders
  MagnumGlfwApplication
  Magnum_PyBind
  Magnum::SceneGraph
  Magnum::Primitives
  Magnum::MeshTools
  ${RA_JPEG_LIBRARIES}
  )
 
target_link_libraries(radium_static
  Cairo::Cairo
  JPEG::JPEG
  )

if(RA_WINDOWS)
  target_link_libraries(radium_static unofficial::cairo::cairo-gobject)
endif()

if(RA_APPLE)
  target_link_libraries(radium_static MagnumWindowlessCglApplication)
elseif(RA_LINUX)
  target_link_libraries(radium_static MagnumWindowlessEglApplication)
elseif(RA_WINDOWS)
  target_link_libraries(radium_static MagnumWindowlessWglApplication)
endif()




# shared and static libraries built from the same object files
#add_library(radium_py SHARED
#  $<TARGET_OBJECTS:radium_obj>
#  radium.cpp
#  )

#set_target_properties(radium_py PROPERTIES
#  CXX_VISIBILITY_PRESET hidden
#  VISIBILITY_INLINES_HIDDEN 1
#  )

# copy the radium py lib to the package dir
#set_target_properties(radium_py PROPERTIES
#  ARCHIVE_OUTPUT_DIRECTORY ${MX_PYPKG_DIR}
#  LIBRARY_OUTPUT_DIRECTORY ${RA_PYPKG_DIR}
#  LIBRARY_OUTPUT_DIRECTORY_DEBUG ${RA_PYPKG_DIR}
#  LIBRARY_OUTPUT_DIRECTORY_RELEASE ${RA_PYPKG_DIR}
#  )


#target_include_directories(radium_py PRIVATE
#  $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>
#  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
#  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
#  ${Python_INCLUDE_DIRS}
#  #${NUMPY_INCLUDE_DIR}
#  #$<INSTALL_INTERFACE:include/mylib>  # <prefix>/include/mylib
#)

#target_include_directories(radium_py PRIVATE ${PYBIND11_INCLUDE_DIR})

#target_link_libraries(radium_py PRIVATE
#  glfw
#  Magnum::Application
#  Magnum::Magnum
#  Magnum::Shaders
#  MagnumGlfwApplication
#  Magnum_PyBind
#  Magnum::SceneGraph
#  Magnum::Primitives
#  Magnum::MeshTools
#  ${RA_JPEG_LIBRARIES}
#  )
#
#if(WIN32 OR CYGWIN OR (UNIX AND NOT APPLE))
#  # Link against the Python shared library on Windows
#  target_link_libraries(radium_py PRIVATE ${PYTHON_LIBRARIES})
#
#elseif(APPLE)
#  # It's quite common to have multiple copies of the same Python version
#  # installed on one's system. E.g.: one copy from the OS and another copy
#  # that's statically linked into an application like Blender or Maya.
#  # If we link our plugin library against the OS Python here and import it
#  # into Blender or Maya later on, this will cause segfaults when multiple
#  # conflicting Python instances are active at the same time (even when they
#  # are of the same version).
#
#  # Windows is not affected by this issue since it handles DLL imports
#  # differently. The solution for Linux and Mac OS is simple: we just don't
#  # link against the Python library. The resulting shared library will have
#  # missing symbols, but that's perfectly fine -- they will be resolved at
#  # import time.
#
#  target_link_libraries(radium_py PRIVATE "-undefined dynamic_lookup")
#
#  if(ARG_SHARED)
#    # Suppress CMake >= 3.0 warning for shared libraries
#    set_target_properties(radium_py PROPERTIES MACOSX_RPATH ON)
#  endif()
#endif()
#
#
#if(RA_APPLE)
#  target_link_libraries(radium_py PRIVATE MagnumWindowlessCglApplication)
#elseif(RA_LINUX)
#  target_link_libraries(radium_py PRIVATE MagnumWindowlessEglApplication)
#elseif(RA_WINDOWS)
#  target_link_libraries(radium_py PRIVATE MagnumWindowlessWglApplication)
#endif()
#
#
#set_target_properties(radium_py PROPERTIES PREFIX "")
#set_target_properties(radium_py PROPERTIES OUTPUT_NAME "_radium")
#set_target_properties(radium_py PROPERTIES SUFFIX ".so")
#
#
#add_custom_command(
#  OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/radium.py"
#  POST_BUILD
#  COMMAND ${CMAKE_COMMAND} -E copy
#  ${CMAKE_CURRENT_SRC_DIR}/radium.py
#  ${CMAKE_CURRENT_BINARY_DIR}/radium.py
#  DEPENDS radium.py)
#
#
#add_custom_command(
# TARGET ${destination} POST_BUILD
# COMMAND ${CMAKE_COMMAND} -E copy ${source} ${destination}
# DEPENDS ${source}
# COMMENT "symbolic link resources folder from ${source} => ${destination}"
# )
#
#add_custom_target(radium.py
#  DEPENDS radium.py)
#
#add_custom_command(
#  TARGET radium_py
#  DEPENDS __init__.py
#  POST_BUILD
#  COMMAND ${CMAKE_COMMAND} -E copy  ${CMAKE_CURRENT_SOURCE_DIR}/__init__.py ${RA_PYPKG_DIR}/__init__.py
#  )
#
#file(COPY setup.py DESTINATION ${CMAKE_BINARY_DIR})


add_library(radium ALIAS radium_shared)
add_library(radium::radium ALIAS radium_shared)
add_library(radium::Static ALIAS radium_static)
add_library(radium::Shared ALIAS radium_shared)

#add_library(radium::PythonLib ALIAS radium_py)
