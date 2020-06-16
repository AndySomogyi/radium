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

CAPI_FUNC(RaApplication*) RaApplication_Create(int argc, const char** _argv)
{
    char** argv = const_cast<char**>(_argv);

    App *app = new App({argc, argv});

    return app;
}

CAPI_FUNC(HRESULT) RaApplication_Run(RaApplication* _app)
{
    App* app = (App*)_app;
    app->exec();
    return S_OK;
}

CAPI_FUNC(HRESULT) RaApplication_SetImage(RaApplication* _app, uint32_t width, uint32_t height, uint32_t format, const void* data)
{
    App* app = (App*)_app;
    return app->setImage(width, height, format, data);
}
