#ifndef INCLUDE_ENGINE2D_RENDERER_RENDERER2D
#define INCLUDE_ENGINE2D_RENDERER_RENDERER2D

#include "Engine2D/Math/Color.h"
#include "Engine2D/Core/Window.h"
#include "Engine2D/Renderer/RendererAPI.h"
#include "Engine2D/Renderer/Mesh.h"
#include "Engine2D/Renderer/Shader.h"
#include "Engine2D/Renderer/Camera.h"
#include "Engine2D/Renderer/Texture.h"
#include <memory>

namespace Engine2D
{
    class Renderer2D {
    private:
        static void DrawShape(glm::vec2 position, glm::vec2 size, int shapeType, float thickness, float rotation);

        static Color s_DrawColor;
        static RendererAPI* s_RendererAPI;
        static Window* s_Window;
        static std::shared_ptr<Mesh> s_PrimitiveMesh;
        static std::shared_ptr<Shader> s_PrimitiveShader;
        static glm::mat4 s_ViewProjection;
        
    public:
        static void Init(RendererAPI* rendererAPI, Window* window);
        
        static void BeginScene(Camera& camera);
        static void SetDrawColor(Color color);

        static void DrawFilledRectangle(glm::vec2 position, glm::vec2 size, float rotation = 0);
        static void DrawFilledEllipse(glm::vec2  center, float semiMajor, float semiMinor, float rotation = 0);
        static void DrawOutlinedRectangle(glm::vec2  position, glm::vec2 size, float thickness = 0, float rotation = 0);
        static void DrawOutlinedEllipse(glm::vec2  center, float semiMajor, float semiMinor, float thickness = 0, float rotation = 0);
    
        static void DrawMesh(const Mesh& mesh, const Shader& shader, glm::vec2 position, glm::vec2 scale, float rotation = 0);
        static void DrawSprite(const Texture& texture, glm::vec2 position, glm::vec2 size, float rotation = 0);
    };
} // namespace Engine2D

#endif // INCLUDE_ENGINE2D_RENDERER_RENDERER2D
