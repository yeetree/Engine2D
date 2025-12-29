#include "Engine2D/Renderer/RendererAPI.h"
#include <glad/gl.h>

class OpenGLRendererAPI : public Engine2D::RendererAPI {
public:
    OpenGLRendererAPI() {
        
    }

    ~OpenGLRendererAPI() {

    }

    void SetViewport(glm::vec2 position, glm::vec2 size) override {
        glViewport(position.x, position.y, size.x, size.y);
    }

    void SetClearColor(Engine2D::Color color) override {
        glClearColor(color.r, color.g, color.b, color.a);
    }

    void Clear() override {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void DrawMesh(const Engine2D::Mesh& mesh) override {
        mesh.Bind();
        glDrawElements(GL_TRIANGLES, mesh.GetIndexCount(), GL_UNSIGNED_INT, 0);
        mesh.Unbind();
    }
};

// Implementation of IRendererAPI::Init
std::unique_ptr<Engine2D::RendererAPI> Engine2D::RendererAPI::Create() {
    return std::make_unique<OpenGLRendererAPI>();
}