/*
 * ra_canvas.hpp
 *
 *  Created on: Jun 10, 2020
 *      Author: andy
 */

#ifndef INCLUDE_RA_CANVAS_HPP_
#define INCLUDE_RA_CANVAS_HPP_

#include <ra_canvas.h>
#include <Magnum/SceneGraph/SceneGraph.h>
#include <Magnum/SceneGraph/Object.h>
#include <Magnum/GL/Mesh.h>
#include <TexturedTriangleShader.h>

struct RaCanvas {
    Magnum::GL::Mesh mesh;
    Magnum::Examples::TexturedTriangleShader shader;
    Magnum::GL::Texture2D texture;
    cairo_surface_t *surface;
    cairo_t *cr;

    /**
     * draw the canvas to the current context, does not swap buffers.
     */
    HRESULT draw();
};

#endif /* INCLUDE_RA_CANVAS_H_ */
