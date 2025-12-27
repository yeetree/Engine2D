#include "Engine2D/Core/Input.h"
#include <SDL3/SDL.h>
#include <glad/gl.h>
#include <memory>

#ifdef E2D_ENABLE_IMGUI
    #include <imgui.h>
    #include <backends/imgui_impl_sdl3.h>
    #include <backends/imgui_impl_opengl3.h>
#endif

class SDL3Input : public Engine2D::Input {
public:
    SDL3Input(Engine2D::Window* window) : m_Window(window), m_ShouldClose(false) {

    }

    ~SDL3Input() {

    }

    void Update() override {
        SDL_Event event;
        
        while(SDL_PollEvent(&event))
        {
#ifdef E2D_ENABLE_IMGUI
            ImGui_ImplSDL3_ProcessEvent(&event);
#endif
            switch(event.type)
            {
                case SDL_EVENT_QUIT:
                    m_ShouldClose = true;
                    break;
            }
        }
    }

    virtual bool ShouldClose() override {
        return m_ShouldClose;
    }

private:
    Engine2D::Window* m_Window;
    bool m_ShouldClose;
};

// Implementation of IInput::Init
std::unique_ptr<Engine2D::Input> Engine2D::Input::Create(Window* window) {
    return std::make_unique<SDL3Input>(window);
}