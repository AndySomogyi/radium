/*
 * ra_application.cpp
 *
 *  Created on: Jun 10, 2020
 *      Author: andy
 */

#include "ra_application.hpp"
#include "RaGlfwApplication.h"

using App = Magnum::Examples::RaGlfwApplication;



HRESULT ra_main(int argc, const char** _argv) {

    char** argv = const_cast<char**>(_argv);

    App app({argc, argv});
    return app.exec();
}



