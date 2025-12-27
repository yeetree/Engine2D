#ifndef SOURCE_CORE_WINDOW
#define SOURCE_CORE_WINDOW

#include <string>
#include <memory>

namespace Engine2D
{
    class Window {
    public:
        virtual ~Window() {}

        virtual void Swap() = 0;
        virtual int GetWidth() const = 0;
        virtual int GetHeight() const = 0;

        static std::unique_ptr<Window> Create(int width, int height, const std::string &title);
    };
} // namespace Engine2D

#endif // SOURCE_CORE_WINDOW
