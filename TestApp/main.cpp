#include "Engine2D/Engine2D.h"
#include "Engine2D/Core/Log.h"

class TestApp : public Engine2D::Engine {
public:

    TestApp(int width, int height, std::string title, const char* argv0) : Engine(width, height, title, argv0) {};
    ~TestApp() {}

    float et = 0;
    Engine2D::Camera cam;

    const std::vector<float> vertices = {
        0.5, -0.5, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0,
        -0.5, -0.5, 0.0, 0.0, 0.0, 1.0, 0.0, 1.0,
        0.0, 0.5, 0.0, 0.0, 0.0, 0.0, 1.0, 1.0
    };

    const std::vector<unsigned int> indices = {
        0, 1, 2
    };

    std::shared_ptr<Engine2D::Mesh> mesh;
    std::shared_ptr<Engine2D::Shader> shader;

    std::shared_ptr<Engine2D::Texture> texture;

    void Start() override {
        mesh = Engine2D::Mesh::Create(vertices, indices, Engine2D::BufferUsage::STATIC, Engine2D::BufferUsage::STATIC);
        shader = Engine2D::AssetManager::Get().LoadShader("Basic", "./Assets/Shaders/Basic.vert", "./Assets/Shaders/Basic.frag");
        texture = Engine2D::AssetManager::Get().LoadTextureFromImage("./Assets/Images/container.jpg");
        cam = Engine2D::Camera(GetWindow().GetWidth(), GetWindow().GetHeight());
    }

    void Shutdown() override {

    }

    void Update(float dt) override {
        et += 10.0f * dt;
        cam.SetPosition(glm::vec2(sinf(et) * 100.0f, 0.0f));
    }

    void Render() override {
        Engine2D::Renderer2D::BeginScene(cam);
        Engine2D::Renderer2D::DrawMesh(*mesh, *shader, glm::vec2(100.0f, 100.0f), glm::vec2(100, 100));
        Engine2D::Renderer2D::SetDrawColor(Color(1.0, 1.0, 1.0, 1.0));
        Engine2D::Renderer2D::DrawSprite(*texture, glm::vec2(400, 100), glm::vec2(100, 100), et * 0.5f);
        Engine2D::Renderer2D::SetDrawColor(Color(1.0, 0.0, 0.0, 1.0));
        Engine2D::Renderer2D::DrawFilledEllipse(glm::vec2(200, 200), 100, 50, 0);
    }
};


int main(int argc, char** argv)
{
    TestApp app(800, 600, "TestApp", argv[0]);
    app.Run();
}