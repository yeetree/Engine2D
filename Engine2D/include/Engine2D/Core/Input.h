#ifndef SOURCE_CORE_INPUT
#define SOURCE_CORE_INPUT

#include "Engine2D/Core/Window.h"
#include <memory>

namespace Engine2D
{
    class Input {
    public:
        virtual ~Input() {}

        virtual void Update() = 0;

        virtual bool ShouldClose() = 0;

        static std::unique_ptr<Input> Create(Window* window);
    };
} // namespace Engine2D

#endif // SOURCE_CORE_INPUT
