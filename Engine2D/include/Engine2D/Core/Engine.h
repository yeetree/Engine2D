#ifndef SOURCE_CORE_ENGINE
#define SOURCE_CORE_ENGINE

#include "Engine2D/Core/Window.h"
#include "Engine2D/Core/Input.h"
#include "Engine2D/Renderer/RendererAPI.h"

namespace Engine2D {

    class Engine {
    public:
        Engine(int width, int height, std::string title, const char* argv0);
        virtual ~Engine() = default;

        static Engine& Get() { return *s_Instance; }

        void Run();
        
        virtual void Start() = 0;
        virtual void Update(float dt) = 0;
        virtual void Render() = 0;
        virtual void Shutdown() = 0;

        Window& GetWindow();
        Input& GetInput();
        RendererAPI& GetRendererAPI();

    private:
        static Engine* s_Instance;

        bool m_Running = true;
        std::unique_ptr<Window> m_Window;
        std::unique_ptr<Input> m_Input;
        std::unique_ptr<RendererAPI> m_RendererAPI;
    };

}

#endif // SOURCE_CORE_ENGINE
