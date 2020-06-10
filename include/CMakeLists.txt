function(prepend var)
  set(listVar "")
  foreach(f ${ARGN})
    list(APPEND listVar "${CMAKE_CURRENT_SOURCE_DIR}/${f}")
  endforeach(f)
  set(${var} "${listVar}" PARENT_SCOPE)
endfunction(prepend)


set (_PUBLIC_HEADERS
  c_port.h
  radium.h
  ra_application.h
  ra_renderer.h
  ra_canvas.h
  ra_window.h
  )

prepend(PUBLIC_HEADERS  ${_PUBLIC_HEADERS})

set(RA_PUBLIC_HEADERS ${PUBLIC_HEADERS} PARENT_SCOPE)

set(RA_INCLUDE_DIRS ${RA_INCLUDE_DIRS} PARENT_SCOPE)
