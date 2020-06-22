/*
 * ra_canvas.cpp
 *
 *  Created on: Jun 10, 2020
 *      Author: andy
 */



#include <ra_canvas.hpp>
#include <ra_window.hpp>



#include <Corrade/Containers/ArrayView.h>
#include <Corrade/Containers/Optional.h>
#include <Corrade/PluginManager/Manager.h>
#include <Corrade/Utility/Resource.h>
#include <Magnum/ImageView.h>
#include <Magnum/GL/Buffer.h>
#include <Magnum/GL/DefaultFramebuffer.h>
#include <Magnum/GL/Mesh.h>
#include <Magnum/GL/Texture.h>
#include <Magnum/GL/TextureFormat.h>
#include <Magnum/Trade/AbstractImporter.h>
#include <Magnum/Trade/ImageData.h>
#include <Magnum/Platform/GlfwApplication.h>
#include <MagnumPlugins/TgaImporter/TgaImporter.h>
#include "Magnum/PixelFormat.h"
#include <Magnum/GL/PixelFormat.h>

#include <glfw3.h>

using namespace Magnum;
using namespace Magnum::Examples;

CAPI_FUNC(RaCanvas*) RaCanvas_CreateForWindow(RaWindow *win)
{
    int width, height;
    glfwGetFramebufferSize(win->window, &width, &height);

    cairo_surface_t *surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, width, height);

    cairo_t *cr = cairo_create(surface);

    RaCanvas *result = new RaCanvas();

    result->surface = surface;
    result->cr = cr;

    struct TriangleVertex {
        Vector2 position;
        Vector2 textureCoordinates;
    };
    const TriangleVertex data[]{
        {{-1.f, -1.f}, {0.0f, 1.0f}}, /* Left position and texture coordinate */
        {{ 1.f, -1.f}, {1.0f, 1.0f}}, /* Right position and texture coordinate */
        {{-1.f,  1.f}, {0.0f, 0.0f}},  /* Top position and texture coordinate */
        {{ 1.f,  1.f}, {1.0f, 0.0f}}  /* Top position and texture coordinate */
    };

    GL::Buffer buffer;
    buffer.setData(data);
    result->mesh.setCount(4)
        .setPrimitive(Magnum::GL::MeshPrimitive::TriangleStrip)
        .addVertexBuffer(std::move(buffer), 0,
            TexturedTriangleShader::Position{},
            TexturedTriangleShader::TextureCoordinates{});

    result->texture.setWrapping(GL::SamplerWrapping::ClampToEdge)
        .setMagnificationFilter(GL::SamplerFilter::Linear)
        .setMinificationFilter(GL::SamplerFilter::Linear)
        .setStorage(1, GL::TextureFormat::RGBA8, {width, height});


    win->canvas = result;

    return result;
}

CAPI_FUNC(cairo_surface_t*) RaCanvas_Surface(RaCanvas *canvas)
{
    return canvas->surface;
}

CAPI_FUNC(cairo_t*) RaCanvas_Cairo(RaCanvas *canvas)
{
    return canvas->cr;
}

CAPI_FUNC(HRESULT) RaCanvas_Flush(RaCanvas *canvas)
{
    // flush all the drawing commands
    cairo_surface_flush(canvas->surface);

    const void *data = cairo_image_surface_get_data(canvas->surface);

    int width = cairo_image_surface_get_width (canvas->surface);

    int height = cairo_image_surface_get_height(canvas->surface);

    Containers::ArrayView av{data, (unsigned)(width * height * 4)};

    ImageView2D iv{GL::PixelFormat::BGRA, GL::PixelType::UnsignedByte, {width, height}, av};

    canvas->texture.setSubImage(0, {}, iv);

    return S_OK;
}


HRESULT RaCanvas::draw()
{
    using namespace Math::Literals;

    shader
        //.setColor(0xffb2b2_rgbf)
        .bindTexture(texture)
        .draw(mesh);

    return S_OK;
}
