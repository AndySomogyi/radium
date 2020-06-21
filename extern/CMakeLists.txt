# build core carbon lib
add_subdirectory(carbon)

# build glfw here, set up variables so magnum does not try to find it
add_subdirectory(glfw)


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

elseif(WIN32)
  # for Windows
  message("building on Windows")
    
  set(WITH_WINDOWLESSWGLAPPLICATION ON CACHE BOOL
    "Build WindowlessWglApplication library" FORCE)
 
endif()

set(WITH_TGAIMAGECONVERTER ON CACHE BOOL "Build TGA Image Converter" FORCE)
set(WITH_TGAIMPORTER       ON CACHE BOOL "Build TGA Image Importer" FORCE)


add_subdirectory(magnum)
