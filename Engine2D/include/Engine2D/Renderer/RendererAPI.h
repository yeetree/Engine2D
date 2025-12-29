#ifndef SOURCE_RENDERER_RENDERERAPI
#define SOURCE_RENDERER_RENDERERAPI

#include <glm/glm.hpp>
#include "Engine2D/Math/Color.h"
#include "Engine2D/Core/Window.h"
#include "Engine2D/Renderer/Mesh.h"
#include <memory>

namespace Engine2D
{
    class RendererAPI {
    public:
        virtual ~RendererAPI() {}

        virtual void SetViewport(glm::vec2 position, glm::vec2 size) = 0;
        virtual void SetClearColor(Color color) = 0;
        virtual void Clear() = 0;

        virtual void DrawMesh(const Mesh& mesh) = 0;

        static std::unique_ptr<RendererAPI> Create();
    };
} // namespace Engine2D

#endif // SOURCE_RENDERER_RENDERERAPI
