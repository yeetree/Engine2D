#include "Engine2D/Renderer/Renderer2D.h"
#include "Renderer/Renderer2DShaders.h"
#include "Engine2D/Core/Log.h"
#include "Engine2D/Renderer/Camera.h"

Color Engine2D::Renderer2D::s_DrawColor;
Engine2D::RendererAPI* Engine2D::Renderer2D::s_RendererAPI;
Engine2D::Window* Engine2D::Renderer2D::s_Window;
std::shared_ptr<Engine2D::Mesh> Engine2D::Renderer2D::s_PrimitiveMesh;
std::shared_ptr<Engine2D::Shader> Engine2D::Renderer2D::s_PrimitiveShader;
glm::mat4 Engine2D::Renderer2D::s_ViewProjection;

void Engine2D::Renderer2D::Init(RendererAPI* rendererAPI, Window* window) {
    s_RendererAPI = rendererAPI;
    s_Window = window;
    s_PrimitiveShader = Shader::Create(k_Renderer2DPrimitiveVertexShader, k_Renderer2DPrimitiveFragmentShader);
    const std::vector<float> vertices = {
        // Pos(x, y)   UV(u, v)     Color(r, g, b, a)
        1.0f, 1.0f,    1.0f, 1.0f,  1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 0.0f,    1.0f, 0.0f,  1.0f, 1.0f, 1.0f, 1.0f,
        0.0f, 0.0f,    0.0f, 0.0f,  1.0f, 1.0f, 1.0f, 1.0f,
        0.0f, 1.0f,    0.0f, 1.0f,  1.0f, 1.0f, 1.0f, 1.0f
    };

    const std::vector<unsigned int> indices = {
		0, 1, 3,
		1, 2, 3
    };
    s_PrimitiveMesh = Mesh::Create(vertices, indices, Engine2D::BufferUsage::STATIC, Engine2D::BufferUsage::STATIC);
}

void Engine2D::Renderer2D::BeginScene(Camera& camera) {
    s_PrimitiveShader->Use();
    s_ViewProjection = camera.GetViewProjectionMatrix();
    s_PrimitiveShader->SetMat4("u_ViewProjection", s_ViewProjection);
}

void Engine2D::Renderer2D::SetDrawColor(Color color) {
    s_PrimitiveShader->Use();
    s_DrawColor = color;
    s_PrimitiveShader->SetVec4("drawColor", color.r, color.g, color.b, color.a);
}

void Engine2D::Renderer2D::DrawFilledRectangle(glm::vec2 position, glm::vec2  size, float rotation) {
    DrawShape(position, size, 2, 0, rotation);
}

void Engine2D::Renderer2D::DrawFilledEllipse(glm::vec2  center, float semiMajor, float semiMinor, float rotation) {
    // Get dimensions
    glm::vec2 radius = glm::vec2(semiMinor, semiMajor);
    glm::vec2 size = radius * 2.0f;
    glm::vec2 position = center - radius; 
    
    DrawShape(position, size, 1, 0, rotation);
}

void Engine2D::Renderer2D::DrawOutlinedRectangle(glm::vec2  position, glm::vec2  size, float thickness, float rotation) {
    DrawShape(position, size, 4, thickness, rotation);
}

void Engine2D::Renderer2D::DrawOutlinedEllipse(glm::vec2  center, float semiMajor, float semiMinor, float thickness, float rotation) {
    // Get dimensions
    glm::vec2 radius = glm::vec2(semiMinor, semiMajor);
    glm::vec2 size = radius * 2.0f;
    glm::vec2 position = center - radius; 
    
    DrawShape(position, size, 3, thickness, rotation);
}

void Engine2D::Renderer2D::DrawShape(glm::vec2 position, glm::vec2 size, int shapeType, float thickness, float rotation) {
    if (size.x <= 0 || size.y <= 0) return;

    // Transformation matrix
    glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(position, 0.0f))
        * glm::rotate(glm::mat4(1.0f), rotation, glm::vec3(0.0f, 0.0f, 1.0f))
        * glm::scale(glm::mat4(1.0f), glm::vec3(size, 1.0f));

    // Set shader uniforms
    s_PrimitiveShader->Use();
    s_PrimitiveShader->SetMat4("u_Transform", transform);
    float sizePixel = 1.0f / size.x + 1.0f / size.y; 
    s_PrimitiveShader->SetFloat("thickness", thickness);
    s_PrimitiveShader->SetFloat("sizePixel", sizePixel);
    s_PrimitiveShader->SetInt("shapeType", shapeType);
    s_PrimitiveShader->SetVec2("u_Dimensions", size);

    // Draw
    s_RendererAPI->DrawMesh(*s_PrimitiveMesh);
}

void Engine2D::Renderer2D::DrawMesh(const Mesh& mesh, const Shader& shader, glm::vec2 position, glm::vec2 scale, float rotation)
{
    if (scale.x <= 0 || scale.y <= 0) return;

    // Transformation matrix
    glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(position, 0.0f))
        * glm::rotate(glm::mat4(1.0f), rotation, glm::vec3(0.0f, 0.0f, 1.0f))
        * glm::scale(glm::mat4(1.0f), glm::vec3(scale, 1.0f));

    // Set shader transform and view matrix uniforms
    shader.Use();
    shader.SetMat4("u_ViewProjection", s_ViewProjection);
    shader.SetMat4("u_Transform", transform);

    // Draw
    s_RendererAPI->DrawMesh(mesh);
}

void Engine2D::Renderer2D::DrawSprite(const Texture& texture, glm::vec2 position, glm::vec2 size, float rotation)
{
    s_PrimitiveShader->Use();
    texture.Bind(0);
    s_PrimitiveShader->SetInt("u_Texture", 0);
    DrawShape(position, size, 5, 0, rotation);
}