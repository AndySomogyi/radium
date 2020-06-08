# build core carbon lib
#add_subdirectory(carbon)

# build glfw here, set up variables so magnum does not try to find it
add_subdirectory(glfw)


set(PYBIND11_CPP_STANDARD -std=c++14)
add_subdirectory(pybind11)

# glfw does not set it's target include directories, but it turns out we
# can set them after the glfw subproject is processed.
# This approach enables us to simply target_link_libraries(MyProgram glfw), and
# all the glfw include directories automatically get added to the MyProgram.
target_include_directories(glfw PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/glfw/include/GLFW>
  )

target_include_directories(glfw PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/glfw/deps>
  )

# magnum likes these names:
#  GLFW::GLFW               - GLFW imported target
#  GLFW_LIBRARY             - GLFW library
#  GLFW_INCLUDE_DIR         - Root include dir
#
add_library(GLFW::GLFW ALIAS glfw)

set(GLFW_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/extern/glfw/include/GLFW)
set(GLFW_FOUND TRUE)


message("GLFW_VERSION_MAJOR: ${GLFW_VERSION_MAJOR}")
message("GLFW_VERSION_MINOR: ${GLFW_VERSION_MINOR}")
message("GLFW_VERSION_PATCH: ${GLFW_VERSION_PATCH}")
message("GLFW_VERSION: ${GLFW_VERSION}")


message("GLFW_INCLUDE_DIR: ${GLFW_INCLUDE_DIR}")
message("GLFW_LIBRARY: ${GLFW_LIBRARY}")

if(TARGET glfw)
  message("glfw is a target")
  get_target_property(GLFW_VERSION glfw VERSION)
  message("GLFW_VERSION: ${GLFW_VERSION}")

else()
  message("glfw is NOT a target")
endif()


# set magnum options
add_subdirectory(corrade)

set(WITH_GLFWAPPLICATION ON CACHE BOOL "build magnum with glfw" FORCE)
set(BUILD_STATIC ON CACHE BOOL "build as static libraries for now..." FORCE)
set(BUILD_SHARED_LIBS OFF CACHE BOOL "build as static libraries for now..." FORCE)
set(BUILD_PLUGINS_STATIC ON CACHE BOOL "build as static libraries for now..." FORCE)
set(BUILD_TESTS OFF CACHE BOOL "build as static libraries for now..." FORCE)
set(BUILD_GL_TESTS OFF CACHE BOOL "build as static libraries for now..." FORCE)

# magnum plugins for mesh import testing
set(WITH_ASSIMPIMPORTER    OFF CACHE BOOL "build Assimp importer" FORCE)
set(WITH_OBJIMPORTER       OFF CACHE BOOL "build Assimp importer" FORCE)
set(WITH_OPENGEXIMPORTER   OFF CACHE BOOL "build Assimp importer" FORCE)
set(WITH_ANYIMAGECONVERTER OFF CACHE BOOL "build Assimp importer" FORCE)
set(WITH_AUDIO             OFF CACHE BOOL "build Assimp importer" FORCE)
set(WITH_ANYSCENEIMPORTER  OFF CACHE BOOL "build Assimp importer" FORCE)
set(WITH_PNGIMPORTER       OFF CACHE BOOL "build PNG importer"    FORCE)


if(APPLE)
  message("building on apple")

  set(WITH_CGLCONTEXT ON CACHE BOOL "Build CglContext library" FORCE)

  set(WITH_WINDOWLESSCGLAPPLICATION ON CACHE BOOL
    "Build WindowlessCglApplication library" FORCE)


elseif(UNIX AND NOT APPLE)
  # for Linux, BSD, Solaris, Minix
  message("building on linux")
    
  set(WITH_WINDOWLESSEGLAPPLICATION ON CACHE BOOL
    "Build WindowlessEglApplication library" FORCE)
   
  set(WITH_WINDOWLESSGLXAPPLICATION ON CACHE BOOL
    "Build WindowlessGlxApplication library" FORCE)

endif()

set(WITH_TGAIMAGECONVERTER ON CACHE BOOL "Build TGA Image Converter" FORCE)

add_subdirectory(magnum)


set(MAGNUM_PYTHON_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/magnum-bindings/src/python/magnum)

set(magnum_SRCS
    #magnum.cpp
    ${MAGNUM_PYTHON_SOURCE_DIR}/math.cpp
    ${MAGNUM_PYTHON_SOURCE_DIR}/math.matrixfloat.cpp
    ${MAGNUM_PYTHON_SOURCE_DIR}/math.matrixdouble.cpp
    ${MAGNUM_PYTHON_SOURCE_DIR}/math.range.cpp
    ${MAGNUM_PYTHON_SOURCE_DIR}/math.vectorfloat.cpp
    ${MAGNUM_PYTHON_SOURCE_DIR}/math.vectorintegral.cpp)


# this is the "object library" target: compiles the sources only once
# need at least one src file in a project for xcode to build it, xcode
# won't work if any product *only* has an object src
add_library(Magnum_PyBind
  OBJECT
  ${magnum_SRCS}
  )

set_target_properties(Magnum_PyBind PROPERTIES
  CXX_VISIBILITY_PRESET hidden
  VISIBILITY_INLINES_HIDDEN 1
  )

set_target_properties(Magnum_PyBind PROPERTIES POSITION_INDEPENDENT_CODE ON)

target_include_directories(Magnum_PyBind PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/magnum-bindings/src/python/
  ${CMAKE_CURRENT_SOURCE_DIR}/magnum-bindings/src/
)

target_link_libraries(Magnum_PyBind PUBLIC
  Magnum::Magnum
  )

target_link_libraries(Magnum_PyBind PRIVATE Magnum::Magnum ${magnum_LIBS})


target_include_directories(Magnum_PyBind PUBLIC
  ${Python_INCLUDE_DIRS}
  ${PYBIND11_INCLUDE_DIR}
  )
