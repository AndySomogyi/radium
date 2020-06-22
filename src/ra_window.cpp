/*
 * ra_window.cpp
 *
 *  Created on: Jun 10, 2020
 *      Author: andy
 */

#include "ra_window.hpp"
#include <carbon.h>



RaWindow* RaWindow::New(struct GLFWwindow *win)
{
    RaWindow *result = new RaWindow();
    result->window = win;
    result->canvas = NULL;
    return result;
}

CAPI_FUNC(HRESULT) RaWindow_DestroyWindow(RaWindow *window)
{
    return c_error(E_NOTIMPL, "not implemented");
}

int RaWindow_ShouldClose(RaWindow *window)
{
    return c_error(E_NOTIMPL, "not implemented");
}

CAPI_FUNC(HRESULT) RaWindow_SetWindowShouldClose(RaWindow *window, int value)
{
    return c_error(E_NOTIMPL, "not implemented");
}

CAPI_FUNC(HRESULT) RaWindow_SetWindowTitle(RaWindow *window, const char *title)
{
    return c_error(E_NOTIMPL, "not implemented");
}

CAPI_FUNC(HRESULT) RaWindow_GetWindowPos(RaWindow *window, int *xpos, int *ypos)
{
    return c_error(E_NOTIMPL, "not implemented");
}

CAPI_FUNC(HRESULT) RaWindow_SetWindowPos(RaWindow *window, int xpos, int ypos)
{
    return c_error(E_NOTIMPL, "not implemented");
}

CAPI_FUNC(HRESULT) RaWindow_GetWindowSize(RaWindow *window, int *width,
        int *height)
{
    return c_error(E_NOTIMPL, "not implemented");
}

CAPI_FUNC(HRESULT) RaWindow_SetWindowSizeLimits(RaWindow *window, int minwidth,
        int minheight, int maxwidth, int maxheight)
{
    return c_error(E_NOTIMPL, "not implemented");
}

CAPI_FUNC(HRESULT) RaWindow_SetWindowAspectRatio(RaWindow *window, int numer,
        int denom)
{
    return c_error(E_NOTIMPL, "not implemented");
}

CAPI_FUNC(HRESULT) RaWindow_SetWindowSize(RaWindow *window, int width,
        int height)
{
    return c_error(E_NOTIMPL, "not implemented");
}

CAPI_FUNC(HRESULT) RaWindow_GetFramebufferSize(RaWindow *window, int *width,
        int *height)
{
    return c_error(E_NOTIMPL, "not implemented");
}

CAPI_FUNC(HRESULT) RaWindow_GetWindowFrameSize(RaWindow *window, int *left,
        int *top, int *right, int *bottom)
{
    return c_error(E_NOTIMPL, "not implemented");
}

CAPI_FUNC(HRESULT) RaWindow_GetWindowContentScale(RaWindow *window,
        float *xscale, float *yscale)
{
    return c_error(E_NOTIMPL, "not implemented");
}

float RaWindow_GetWindowOpacity(RaWindow *window)
{
    return c_error(E_NOTIMPL, "not implemented");
}

CAPI_FUNC(HRESULT) RaWindow_SetWindowOpacity(RaWindow *window, float opacity)
{
    return c_error(E_NOTIMPL, "not implemented");
}

CAPI_FUNC(HRESULT) RaWindow_IconifyWindow(RaWindow *window)
{
    return c_error(E_NOTIMPL, "not implemented");
}

CAPI_FUNC(HRESULT) RaWindow_RestoreWindow(RaWindow *window)
{
    return c_error(E_NOTIMPL, "not implemented");
}

CAPI_FUNC(HRESULT) RaWindow_MaximizeWindow(RaWindow *window)
{
    return c_error(E_NOTIMPL, "not implemented");
}

CAPI_FUNC(HRESULT) RaWindow_ShowWindow(RaWindow *window)
{
    return c_error(E_NOTIMPL, "not implemented");
}

CAPI_FUNC(HRESULT) RaWindow_HideWindow(RaWindow *window)
{
    return c_error(E_NOTIMPL, "not implemented");
}

CAPI_FUNC(HRESULT) RaWindow_FocusWindow(RaWindow *window)
{
    return c_error(E_NOTIMPL, "not implemented");
}

CAPI_FUNC(HRESULT) RaWindow_RequestWindowAttention(RaWindow *window)
{
    return c_error(E_NOTIMPL, "not implemented");
}

int RaWindow_GetWindowAttrib(RaWindow *window, int attrib)
{
    return c_error(E_NOTIMPL, "not implemented");
}

CAPI_FUNC(HRESULT) RaWindow_SetWindowAttrib(RaWindow *window, int attrib,
        int value)
{
    return c_error(E_NOTIMPL, "not implemented");
}

CAPI_FUNC(HRESULT) RaWindow_SetWindowUserPointer(RaWindow *window,
        void *pointer)
{
    return c_error(E_NOTIMPL, "not implemented");
}

void* RaWindow_GetWindowUserPointer(RaWindow *window)
{
    c_error(E_NOTIMPL, "not implemented");
    return NULL;
}

int RaWindow_GetInputMode(RaWindow *window, int mode)
{
    return c_error(E_NOTIMPL, "not implemented");
}

CAPI_FUNC(HRESULT) RaWindow_SetInputMode(RaWindow *window, int mode, int value)
{
    return c_error(E_NOTIMPL, "not implemented");
}

int RaWindow_RawMouseMotionSupported(void)
{
    return c_error(E_NOTIMPL, "not implemented");
}

const char* RaWindow_GetKeyName(int key, int scancode)
{
    c_error(E_NOTIMPL, "not implemented");
    return NULL;
}

int RaWindow_GetKeyScancode(int key)
{
    return c_error(E_NOTIMPL, "not implemented");
}

int RaWindow_GetKey(RaWindow *window, int key)
{
    return c_error(E_NOTIMPL, "not implemented");
}

int RaWindow_GetMouseButton(RaWindow *window, int button)
{
    return c_error(E_NOTIMPL, "not implemented");
}

CAPI_FUNC(HRESULT) RaWindow_GetCursorPos(RaWindow *window, double *xpos,
        double *ypos)
{
    return c_error(E_NOTIMPL, "not implemented");
}

CAPI_FUNC(HRESULT) RaWindow_SetCursorPos(RaWindow *window, double xpos,
        double ypos)
{
    return c_error(E_NOTIMPL, "not implemented");
}


CAPI_FUNC(HRESULT) RaWindow_SetClipboardString(RaWindow *window,
        const char *string)
{
    return c_error(E_NOTIMPL, "not implemented");
}


CAPI_FUNC(HRESULT) RaWindow_MakeContextCurrent(RaWindow *window)
{
    return c_error(E_NOTIMPL, "not implemented");
}

CAPI_FUNC(RaWindow*) RaWindow_GetCurrent(void)
{
    c_error(E_NOTIMPL, "not implemented");
    return NULL;
}

CAPI_FUNC(HRESULT) RaWindow_SwapBuffers(RaWindow *window)
{
    return c_error(E_NOTIMPL, "not implemented");
}

CAPI_FUNC(HRESULT) RaWindow_SwapInterval(int interval)
{
    return c_error(E_NOTIMPL, "not implemented");
}

int RaWindow_ExtensionSupported(const char *extension)
{
    return c_error(E_NOTIMPL, "not implemented");
}
