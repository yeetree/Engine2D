#include "Engine2D/Core/Timer.h"

namespace Engine2D
{
    Timer::Timer() {
        Reset();
    }

    void Timer::Reset() {
        auto now = std::chrono::high_resolution_clock::now();
        m_Start = now;
        m_LastFrameTime = now;
    }

    float Timer::GetDeltaTime() {
        auto now = std::chrono::high_resolution_clock::now();
        std::chrono::duration<float> elapsed = now - m_LastFrameTime;
        m_LastFrameTime = now;
        return elapsed.count();
    }

    float Timer::GetTotalTime() const {
        return std::chrono::duration<float>(
            std::chrono::high_resolution_clock::now() - m_Start
        ).count();
    }
} // namespace Engine2D
