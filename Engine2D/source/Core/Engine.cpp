#include "Engine2D/Core/Engine.h"
#include "Engine2D/Renderer/Renderer2D.h"
#include "Engine2D/Core/FileSystem.h"
#include "Engine2D/Core/Timer.h"

#ifdef E2D_ENABLE_IMGUI
    #include <imgui.h>
    #include <backends/imgui_impl_sdl3.h>
    #include <backends/imgui_impl_opengl3.h>
#endif

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
#ifdef E2D_ENABLE_IMGUI
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplSDL3_NewFrame();
            ImGui::NewFrame();
#endif

            m_RendererAPI->Clear();

            Render();
#ifdef E2D_ENABLE_IMGUI
            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
#endif
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