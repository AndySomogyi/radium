#include <cairo.h>
#include <iostream>
#include <jpeglib.h>

#include <radium.h>
#include <cmath>

void cairo_test(RaApplication *app);


int main(int argc, const char** argv) {
  const char* cairo_ver = cairo_version_string ();
  std::cout << "cairo version: " << cairo_ver << std::endl;

  RaApplication *app = RaApplication_Create(argc, argv);

  cairo_test(app);

  RaApplication_Run(app);

  return 0;
}


void cairo_test(RaApplication *app) {
    cairo_public cairo_surface_t *surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, 900, 600);


    cairo_t *cr = cairo_create(surface);
    
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

    // flush all the drawing commands
    cairo_surface_flush(surface);

    unsigned char *data = cairo_image_surface_get_data(surface);

    RaApplication_SetImage(app, 900, 600,0, data);
}

void foo() {

    /*
    cairo_surface_t *surface; cairo_t *cr;

    // initsurface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, width, height);

    cr = cairo_create(surface);

    // in main loopwhile(...)
    {
        render_something_to_surface();
        // get a pointer to the ARGB data
        unsigned char * data = cairo_image_surface_get_data(surface);

        // use the data
        glBindTexture(GL_TEXTURE_2D,tex);

        glTexSubImage2D(GL_TEXTURE_2D, 0, 0,0, width, height,GL_RGBA, GL_UNSIGNED_BYTE, data);}

       // clean upcairo_destroy(cr);cairo_surface_destroy(surface);
    }

    */
}

