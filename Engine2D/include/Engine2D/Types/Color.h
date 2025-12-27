#ifndef SOURCE_TYPES_COLOR
#define SOURCE_TYPES_COLOR

struct Color {
    Color(float r = 0, float g = 0, float b = 0, float a = 0) : r(r), g(g), b(b), a(a) {}
    float r, g, b, a;
};

#endif // SOURCE_TYPES_COLOR
