/*
 * ra_window.hpp
 *
 *  Created on: Jun 10, 2020
 *      Author: andy
 */

#ifndef INCLUDE_RA_WINDOW_HPP_
#define INCLUDE_RA_WINDOW_HPP_


#include <ra_window.h>

struct RaWindow {
    struct GLFWwindow *window;

    struct RaCanvas *canvas;

    static RaWindow *New(struct GLFWwindow *win);
};

#endif /* INCLUDE_RA_WINDOW_H_ */
