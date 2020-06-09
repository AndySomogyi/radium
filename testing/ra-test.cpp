#include <cairo.h>
#include <iostream>
#include <jpeglib.h>


int main(int argc, const char** argv) {
  const char* cairo_ver = cairo_version_string ();
  std::cout << "cairo version: " << cairo_ver << std::endl;
  return 0;
}

  
