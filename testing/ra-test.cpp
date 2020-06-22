#include <cairo.h>
#include <iostream>
#include <jpeglib.h>

#include <radium.h>
#include <cmath>

#define _USE_MATH_DEFINES // for C
#include <math.h>

void cairo_test(RaApplication *app);

void foo();

int main(int argc, const char** argv) {
  const char* cairo_ver = cairo_version_string ();
  std::cout << "cairo version: " << cairo_ver << std::endl;

  RaApplication *app = RaApplication_Create(argc, argv);

  cairo_test(app);

  RaApplication_Run(app);

  foo();

  return 0;
}


void cairo_test(RaApplication *app) {

    RaWindow *win = RaApplication_GetWindow(app, 0);

    RaCanvas *canvas = RaCanvas_CreateForWindow(win);

    cairo_t *cr = RaCanvas_Cairo(canvas);

    cairo_set_source_rgba(cr, 1.0, 1.0, 1.0, 1.0);

    cairo_set_source_rgb (cr, 1, 1, 1);
    cairo_rectangle (cr, 0.0, 0.0, 0.5, 0.5);
    cairo_fill (cr);


    cairo_text_extents_t extents;

    const char *utf8 = "Cairo Testy";
    double x,y;

    cairo_select_font_face (cr, "Sans",
        CAIRO_FONT_SLANT_NORMAL,
        CAIRO_FONT_WEIGHT_NORMAL);

    cairo_set_font_size (cr, 156);
    cairo_text_extents (cr, utf8, &extents);
    x = 420    -(extents.width/2 + extents.x_bearing);
    y = 256-(extents.height/2 + extents.y_bearing);

    cairo_move_to (cr, x, y);
    cairo_show_text (cr, utf8);

    // draw helping lines
    cairo_set_source_rgba (cr, 1, 0.2, 0.2, 0.6);
    cairo_set_line_width (cr, 6.0);
    cairo_arc (cr, x, y, 10.0, 0, 2*M_PI);
    cairo_fill (cr);
    cairo_move_to (cr, 256, 0);
    cairo_rel_line_to (cr, 0, 512);
    cairo_move_to (cr, 0, 256);
    cairo_rel_line_to (cr, 512, 0);
    cairo_stroke (cr);

    RaCanvas_Flush(canvas);
}



void foo() {
    CCompartment_t *c = CCompartment_create();
}

