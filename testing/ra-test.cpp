#include <cairo.h>
#include <iostream>
#include <jpeglib.h>

#include <radium.h>


int main(int argc, const char** argv) {
  const char* cairo_ver = cairo_version_string ();
  std::cout << "cairo version: " << cairo_ver << std::endl;

  int result = ra_main(argc, argv);

  return result;
}
