#include "Engine2D/Core/Engine.h"
#include "Engine2D/Renderer/Renderer2D.h"
#include "Engine2D/Core/FileSystem.h"
#include "Engine2D/Core/Timer.h"

namespace Engine2D {
    Engine* Engine::s_Instance = nullptr;

    Engine::Engine(int width, int height, std::string title, const char* argv0) {
        s_Instance = this;

        FileSystem::Init(argv0);
        m_Window = Window::Create(width, height, title);
        m_Input = Input::Create(m_Window.get());
        m_RendererAPI = RendererAPI::Create();

        Renderer2D::Init(m_RendererAPI.get(), m_Window.get());
    }

    void Engine::Run() {
        Start();
        Timer timer;

        while (m_Running) {
            float dt = timer.GetDeltaTime();

            m_Input->Update();
            
            if (m_Input->ShouldClose()) 
                m_Running = false;

            Update(dt);

            m_RendererAPI->Clear();

            Render();
            
            m_Window->Swap();
        }

        Shutdown();
    }

    Window& Engine::GetWindow() {
        return *m_Window;
    }

    Input& Engine::GetInput() {
        return *m_Input;
    }

    RendererAPI& Engine::GetRendererAPI() {
        return *m_RendererAPI;
    }
}