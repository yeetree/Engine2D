#include "Engine2D/Core/Window.h"
#include <SDL3/SDL.h>
#include <glad/gl.h>
#include <memory>

#ifdef E2D_ENABLE_IMGUI
    #include <imgui.h>
    #include <backends/imgui_impl_sdl3.h>
    #include <backends/imgui_impl_opengl3.h>
#endif

class SDL3_OpenGLWindow : public Engine2D::Window {
public:
    SDL3_OpenGLWindow(int width, int height, const std::string &title): m_Width(width), m_Height(height) {
        // Initialize SDL
        if(!SDL_Init(SDL_INIT_VIDEO))
        {
            SDL_Log("SDL could not initialize! SDL error: %s\n", SDL_GetError());
            return; // Failure
        }

        // Set OpenGL Attributes: OpenGL 3.3 Core
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1); // Enable double buffering
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24); // Request a depth buffer

        const SDL_WindowFlags flags = SDL_WINDOW_OPENGL;

        // Create window
        m_Window = SDL_CreateWindow(title.c_str(), m_Width, m_Height, flags);
        if(m_Window == nullptr)
        {
            SDL_Log("Window could not be created! SDL error: %s\n", SDL_GetError());
            return; // Failure
        }

        // Create OpenGL context
        m_GLContext = SDL_GL_CreateContext(m_Window);
        if(m_GLContext == nullptr)
        {
            SDL_Log("OpenGL context could not be created! SDL error: %s\n", SDL_GetError());
            return; // Failure
        }

        // Initialize glad
        int version = gladLoadGL((GLADloadfunc)SDL_GL_GetProcAddress);

        if (version == 0) {
            SDL_Log("Failed to initialize GLAD");
            return;
        }

        // Print the loaded OpenGL version
        int major = GLAD_VERSION_MAJOR(version);
        int minor = GLAD_VERSION_MINOR(version);
        SDL_Log("Loaded OpenGL version %d.%d", major, minor);

        SDL_GL_MakeCurrent(m_Window, m_GLContext);
        SDL_GL_SetSwapInterval(1); // Enable vsync

        // Enable depth test
        glEnable(GL_DEPTH_TEST);
        glDisable(GL_CULL_FACE);
        glFrontFace(GL_CCW);

#ifdef E2D_ENABLE_IMGUI
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGui_ImplSDL3_InitForOpenGL(m_Window, m_GLContext);
        ImGui_ImplOpenGL3_Init("#version 330");
#endif
    }

    ~SDL3_OpenGLWindow() {
        // Destroy SDL glContext and window
        SDL_GL_DestroyContext(m_GLContext);
        SDL_DestroyWindow(m_Window);
        // Quit SDL
        SDL_Quit();
    }

    void Swap() override {
        SDL_GL_SwapWindow(m_Window);
    }

    int GetWidth() const override { return m_Width; }
    int GetHeight() const override { return m_Height; }

private:
    SDL_Window* m_Window;
    SDL_GLContext m_GLContext;
    int m_Width, m_Height;
};

// Implementation of IWindow::Init
std::unique_ptr<Engine2D::Window> Engine2D::Window::Create(int width, int height, const std::string &title) {
    return std::make_unique<SDL3_OpenGLWindow>(width, height, title);
}