/*
 * ra_application.cpp
 *
 *  Created on: Jun 10, 2020
 *      Author: andy
 */

#include "ra_application.hpp"
#include "RaGlfwApplication.h"
#include <ra_window.hpp>
#include <carbon.h>

using App = Magnum::Examples::RaGlfwApplication;

#define MXGLFW_ERROR() { \
        const char* glfwErrorDesc = NULL; \
        glfwGetError(&glfwErrorDesc); \
        throw std::domain_error(std::string("GLFW Error in ") + MX_FUNCTION + ": " +  glfwErrorDesc); \
}

#define MXGLFW_CHECK() { \
        const char* glfwErrorDesc = NULL; \
        int ret = glfwGetError(&glfwErrorDesc); \
        return ret == 0 ? S_OK : c_error(ret, glfwErrorDesc); \
}




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

CAPI_FUNC(HRESULT) RaApplication_PollEvents(RaApplication *app)
{
    glfwPollEvents();
    MXGLFW_CHECK();
}

CAPI_FUNC(HRESULT) RaApplication_WaitEvents(RaApplication *app)
{
    glfwWaitEvents();
    MXGLFW_CHECK();
}

CAPI_FUNC(HRESULT) RaApplication_WaitEventsTimeout(RaApplication *app,
        double timeout)
{
    glfwWaitEventsTimeout(timeout);
    MXGLFW_CHECK();
}

CAPI_FUNC(RaWindow*) RaApplication_GetWindow(RaApplication *_app, int id)
{
    App* app = (App*)_app;
    if(!app->win) {
        app->win = RaWindow::New(app->window());
    }

    return app->win;
}
