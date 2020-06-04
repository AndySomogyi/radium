project (Radium)

cmake_minimum_required(3.15)


if(MSVC)
  set_property(TARGET Radium
    PROPERTY VS_PACKAGE_REFERENCES "cairo_static_1.15.4.5"
    )
endif()
