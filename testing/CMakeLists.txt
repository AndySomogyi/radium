
add_executable(ra-test
   ra-test.cpp)

#
#    find_package(unofficial-cairo CONFIG REQUIRED)
target_link_libraries(ra-test
  PRIVATE
  unofficial::cairo::cairo
  unofficial::cairo::cairo-gobject
  JPEG::JPEG
  )


# Get the include directories for the target.
get_target_property(LIBA_INCLUDES ra-test INC)

message("iclude dirs: ${INC}")
