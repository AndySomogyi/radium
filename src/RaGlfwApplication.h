/*
 * RaGlfwApplication.h
 *
 *  Created on: Mar 27, 2019
 *      Author: andy
 *
 */

#ifndef SRC_RaGlfwApplication_H_
#define SRC_RaGlfwApplication_H_

#include <ra_application.hpp>

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

#include "TexturedTriangleShader.h"

namespace Magnum { namespace Examples {

class RaGlfwApplication : public RaApplication, public Platform::GlfwApplication {
    public:
        explicit RaGlfwApplication(const Arguments& arguments);

       HRESULT setImage(uint32_t width, uint32_t height, uint32_t format, const void* data);

       /**
        * Pointer to wrapper window.
        */
       RaWindow *win;

    private:
        void drawEvent() override;

        GL::Mesh _mesh;
        TexturedTriangleShader _shader;
        GL::Texture2D _texture;
};

}}


#endif /* SRC_RaGlfwApplication_H_ */
