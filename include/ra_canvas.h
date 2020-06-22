/*
 * ra_canvas.h
 *
 *  Created on: Jun 10, 2020
 *      Author: andy
 */

#ifndef INCLUDE_RA_CANVAS_H_
#define INCLUDE_RA_CANVAS_H_

#include <cairo.h>
#include <carbon.h>
#include <ra_window.h>

/**
 * The canvas represents a 2D surface that's free to move around in 3D space.
 *
 * Canvas itself is a Cairo image surface, that you can use any of the Cairo drawing
 * commands to draw to.
 */

CAPI_STRUCT(RaCanvas);

/**
 * Creates a canvas and attaches it to a window.
 */
CAPI_FUNC(RaCanvas*) RaCanvas_CreateForWindow(RaWindow *win);

/**
 * Gets the cairo surface for this canvas.
 */
CAPI_FUNC(cairo_surface_t*) RaCanvas_Surface(RaCanvas *canvas);

/**
 * Gets the cairo object for the surface in this canvas.
 */
CAPI_FUNC(cairo_t*) RaCanvas_Cairo(RaCanvas *canvas);

/**
 * Flushes all drawing commands from cairo, and copies the drawn image
 * to the texture.
 *
 * Use this instead of  cairo_surface_flush(surface);
 */
CAPI_FUNC(HRESULT) RaCanvas_Flush(RaCanvas *canvas);



#endif /* INCLUDE_RA_CANVAS_H_ */
