#ifndef INCLUDE_ENGINE2D_CORE_TIMER
#define INCLUDE_ENGINE2D_CORE_TIMER

#include <chrono>

namespace Engine2D {
    class Timer {
    public:
        Timer();
        void Reset();

        float GetDeltaTime();
        float GetTotalTime() const;
    private:
        std::chrono::time_point<std::chrono::high_resolution_clock> m_Start;
        std::chrono::time_point<std::chrono::high_resolution_clock> m_LastFrameTime;
    };
}

#endif // INCLUDE_ENGINE2D_CORE_TIMER
