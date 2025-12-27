#ifndef INCLUDE_ENGINE2D_RENDERER_TEXTURE
#define INCLUDE_ENGINE2D_RENDERER_TEXTURE

#include <string>
#include <memory>
#include "Engine2D/Core/Image.h"

namespace Engine2D {

    class Texture {
    public:
        virtual ~Texture() = default;

        virtual unsigned int GetWidth() const = 0;
        virtual unsigned int GetHeight() const = 0;
        virtual unsigned int GetRendererID() const = 0;

        virtual void SetData(void* data) = 0;

        virtual void Bind(unsigned int slot = 0) const = 0;
        virtual void Unbind(unsigned int slot)  const = 0;

        static std::shared_ptr<Texture> Create(unsigned int width, unsigned int height);
        static std::shared_ptr<Texture> Create(const Image& image);
    };

}

#endif // INCLUDE_ENGINE2D_RENDERER_TEXTURE
