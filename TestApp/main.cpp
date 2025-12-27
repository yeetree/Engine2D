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

        if(GetInput().IsMouseButtonDown(Engine2D::MouseButton::MOUSE_BUTTON_RIGHT)) {
            cam.SetPosition(cam.GetPosition() - cam.ScreenToWorldDelta(GetInput().GetMouseDelta()));
        }

        const float zoom_speed = 1.1f;
        float mw = GetInput().GetMouseWheelY();
        float camzoom = cam.GetZoom();
        if(mw > 0)
        {
            camzoom /= zoom_speed;
        }
        if(mw < 0)
        {
            camzoom *= zoom_speed;
        }
        cam.SetZoom(std::max(0.1f, camzoom));

    }

    void Render() override {
        Engine2D::Renderer2D::BeginScene(cam);
        Engine2D::Renderer2D::DrawMesh(*mesh, *shader, glm::vec2(1.0f, 1.0f), glm::vec2(1, 1));
        Engine2D::Renderer2D::SetDrawColor(Color(1.0, 1.0, 1.0, 1.0));
        Engine2D::Renderer2D::DrawSprite(*texture, cam.ScreenToWorld(GetInput().GetMouse()), glm::vec2(1, 1));
        Engine2D::Renderer2D::SetDrawColor(Color(1.0, 0.0, 0.0, 1.0));
        Engine2D::Renderer2D::DrawFilledEllipse(glm::vec2(200, 200), 100, 50, 0);
        Engine2D::Renderer2D::SetDrawColor(Color(1.0, 1.0, 0.0, 1.0));
        Engine2D::Renderer2D::DrawOutlinedRectangle(glm::vec2(4, 6), glm::vec2(50, 6), 1.0f, 2.0f);
        Engine2D::Renderer2D::SetDrawColor(Color(1.0, 0.0, 1.0, 1.0));
        Engine2D::Renderer2D::DrawOutlinedEllipse(glm::vec2(10, 2), 100, 20, 0.5, -1.0f);
    }
};


int main(int argc, char** argv)
{
    TestApp app(800, 600, "TestApp", argv[0]);
    app.Run();
}