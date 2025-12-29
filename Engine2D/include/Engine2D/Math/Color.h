#ifndef INCLUDE_ENGINE2D_MATH_COLOR
#define INCLUDE_ENGINE2D_MATH_COLOR

namespace Engine2D
{
    struct Color {
        Color(float r = 0, float g = 0, float b = 0, float a = 0) : r(r), g(g), b(b), a(a) {}
        float r, g, b, a;
    };
} // namespace Engine2D

#endif // INCLUDE_ENGINE2D_MATH_COLOR
