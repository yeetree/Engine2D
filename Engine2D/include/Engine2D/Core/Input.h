#ifndef INCLUDE_ENGINE2D_CORE_INPUT
#define INCLUDE_ENGINE2D_CORE_INPUT

#include "Engine2D/Core/Window.h"
#include <memory>
#include <cstdint>
#include <glm/glm.hpp>

namespace Engine2D {

    // From https://gist.github.com/MightyPork/6da26e382a7ad91b5496ee55fdc73db2
    enum class Scancode : uint16_t {
        KEY_UNKNOWN = 0x00,
        
        KEY_A = 0x04, KEY_B = 0x05, KEY_C = 0x06, KEY_D = 0x07, KEY_E = 0x08, KEY_F = 0x09, KEY_G = 0x0a,
        KEY_H = 0x0b, KEY_I = 0x0c, KEY_J = 0x0d, KEY_K = 0x0e, KEY_L = 0x0f, KEY_M = 0x10, KEY_N = 0x11,
        KEY_O = 0x12, KEY_P = 0x13, KEY_Q = 0x14, KEY_R = 0x15, KEY_S = 0x16, KEY_T = 0x17, KEY_U = 0x18,
        KEY_V = 0x19, KEY_W = 0x1a, KEY_X = 0x1b, KEY_Y = 0x1c, KEY_Z = 0x1d,

        KEY_1 = 0x1e, KEY_2 = 0x1f, KEY_3 = 0x20, KEY_4 = 0x21, KEY_5 = 0x22,
        KEY_6 = 0x23, KEY_7 = 0x24, KEY_8 = 0x25, KEY_9 = 0x26, KEY_0 = 0x27,

        KEY_ENTER = 0x28, KEY_ESCAPE = 0x29, KEY_BACKSPACE = 0x2a, KEY_TAB = 0x2b, KEY_SPACE = 0x2c,
        KEY_MINUS = 0x2d, KEY_EQUAL = 0x2e, KEY_LEFTBRACE = 0x2f, KEY_RIGHTBRACE = 0x30,
        KEY_BACKSLASH = 0x31, KEY_SEMICOLON = 0x33, KEY_APOSTROPHE = 0x34, KEY_GRAVE = 0x35,
        KEY_COMMA = 0x36, KEY_DOT = 0x37, KEY_SLASH = 0x38, KEY_CAPSLOCK = 0x39,

        KEY_F1 = 0x3a, KEY_F2 = 0x3b, KEY_F3 = 0x3c, KEY_F4 = 0x3d, KEY_F5 = 0x3e, KEY_F6 = 0x3f,
        KEY_F7 = 0x40, KEY_F8 = 0x41, KEY_F9 = 0x42, KEY_F10 = 0x43, KEY_F11 = 0x44, KEY_F12 = 0x45,

        KEY_PRINTSCREEN = 0x46, KEY_SCROLLLOCK = 0x47, KEY_PAUSE = 0x48, KEY_INSERT = 0x49,
        KEY_HOME = 0x4a, KEY_PAGEUP = 0x4b, KEY_DELETE = 0x4c, KEY_END = 0x4d, KEY_PAGEDOWN = 0x4e,
        KEY_RIGHT = 0x4f, KEY_LEFT = 0x50, KEY_DOWN = 0x51, KEY_UP = 0x52,

        KEY_LEFTCONTROL = 0xe0, KEY_LEFTSHIFT = 0xe1, KEY_LEFTALT = 0xe2, KEY_LEFTMETA = 0xe3,
        KEY_RIGHTCONTROL = 0xe4, KEY_RIGHTSHIFT = 0xe5, KEY_RIGHTALT = 0xe6, KEY_RIGHTMETA = 0xe7
    };

    enum class MouseButton : uint8_t {
        MOUSE_BUTTON_UNKNOWN = 0,
        MOUSE_BUTTON_LEFT = 1,
        MOUSE_BUTTON_MIDDLE = 2,
        MOUSE_BUTTON_RIGHT = 3,
        MOUSE_BUTTON_X1 = 4,
        MOUSE_BUTTON_X2 = 5,
    };

    class Input {
    public:
        virtual ~Input() {}

        virtual void Update() = 0;

        virtual bool ShouldClose() const = 0;

        virtual bool IsKeyDown(Scancode key) const = 0;
        virtual bool IsKeyPressed(Scancode key) const = 0;
        virtual bool IsKeyReleased(Scancode key) const = 0;
        virtual bool IsMouseButtonDown(MouseButton button) const = 0;
        virtual bool IsMouseButtonPressed(MouseButton button) const = 0;
        virtual bool IsMouseButtonReleased(MouseButton button) const = 0;

        virtual float GetMouseX() const = 0;
        virtual float GetMouseY() const = 0;
        virtual glm::vec2 GetMouse() const = 0;
        virtual float GetMouseDeltaX() const = 0;
        virtual float GetMouseDeltaY() const = 0;
        virtual glm::vec2 GetMouseDelta() const = 0;
        virtual float GetMouseWheelX() const = 0;
        virtual float GetMouseWheelY() const = 0;
        virtual glm::vec2 GetMouseWheel() const = 0;

        static std::unique_ptr<Input> Create(Window* window);
    };
} // namespace Engine2D

#endif // INCLUDE_ENGINE2D_CORE_INPUT
