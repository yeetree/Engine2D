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
    SDL3Input(Engine2D::Window* window) : m_Window(window), m_ShouldClose(false), m_CurrentMouseX(0), m_CurrentMouseY(0), m_PreviousMouseX(0), m_PreviousMouseY(0) {
        memset(m_CurrentState, 0, sizeof(m_CurrentState));
        memset(m_PreviousState, 0, sizeof(m_PreviousState));
        memset(m_CurrentMouseState, 0, sizeof(m_CurrentState));
        memset(m_PreviousMouseState, 0, sizeof(m_PreviousMouseState));
    }

    ~SDL3Input() {

    }

    void Update() override {
        SDL_Event event;
        memcpy(m_PreviousState, m_CurrentState, sizeof(m_CurrentState));
        memcpy(m_PreviousMouseState, m_CurrentMouseState, sizeof(m_CurrentMouseState));
        m_PreviousMouseX = m_CurrentMouseX;
        m_PreviousMouseY = m_CurrentMouseY;

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
                case SDL_EVENT_KEY_DOWN:
                    if (event.key.repeat) break;
                    m_CurrentState[(uint16_t)SDLScancodeToEngine2D(event.key.scancode)] = true;
                    break;
                case SDL_EVENT_KEY_UP:
                    m_CurrentState[(uint16_t)SDLScancodeToEngine2D(event.key.scancode)] = false;
                    break;
                case SDL_EVENT_MOUSE_BUTTON_DOWN:
                    m_CurrentMouseState[(uint8_t)SDLMouseButtonToEngine2D(event.button.button)] = true;
                    break;
                case SDL_EVENT_MOUSE_BUTTON_UP:
                    m_CurrentMouseState[(uint8_t)SDLMouseButtonToEngine2D(event.button.button)] = false;
                    break;
            }
        }

        SDL_GetMouseState(&m_CurrentMouseX, &m_CurrentMouseY);
    }

    bool ShouldClose() const override {
        return m_ShouldClose;
    }

    bool IsKeyDown(Engine2D::Scancode key) const override {
        return m_CurrentState[(uint16_t)key];
    }

    bool IsKeyPressed(Engine2D::Scancode key) const override {
        return m_CurrentState[(uint16_t)key] && !m_PreviousState[(uint16_t)key];
    }

    bool IsKeyReleased(Engine2D::Scancode key) const override {
        return !m_CurrentState[(uint16_t)key] && m_PreviousState[(uint16_t)key];
    }

    bool IsMouseButtonDown(Engine2D::MouseButton button) const override {
        return m_CurrentMouseState[(uint8_t)button];
    }

    bool IsMouseButtonPressed(Engine2D::MouseButton button) const override {
        return m_CurrentMouseState[(uint8_t)button] && !m_PreviousMouseState[(uint8_t)button];
    }

    bool IsMouseButtonReleased(Engine2D::MouseButton button) const override {
        return !m_CurrentMouseState[(uint8_t)button] && m_PreviousMouseState[(uint8_t)button];
    }

    float GetMouseX() const override { 
        return m_CurrentMouseX;
    }

    float GetMouseY() const override {
        return m_CurrentMouseY;
    }

    float GetMouseDeltaX() const override {
        return m_CurrentMouseX - m_PreviousMouseX;
    }

    float GetMouseDeltaY() const override {
        return m_CurrentMouseY - m_PreviousMouseY;
    }

private:
    // Technically unecessary, but this is to keep consistency if another backend is implemented
    // as SDL_Scancodes are not 1 to 1 with Engine2D
    Engine2D::Scancode SDLScancodeToEngine2D(SDL_Scancode scancode) {
        switch(scancode) {
            case SDL_SCANCODE_UNKNOWN:      return Engine2D::Scancode::KEY_UNKNOWN;
            
            case SDL_SCANCODE_A:            return Engine2D::Scancode::KEY_A;
            case SDL_SCANCODE_B:            return Engine2D::Scancode::KEY_B;
            case SDL_SCANCODE_C:            return Engine2D::Scancode::KEY_C;
            case SDL_SCANCODE_D:            return Engine2D::Scancode::KEY_D;
            case SDL_SCANCODE_E:            return Engine2D::Scancode::KEY_E;
            case SDL_SCANCODE_F:            return Engine2D::Scancode::KEY_F;
            case SDL_SCANCODE_G:            return Engine2D::Scancode::KEY_G;
            case SDL_SCANCODE_H:            return Engine2D::Scancode::KEY_H;
            case SDL_SCANCODE_I:            return Engine2D::Scancode::KEY_I;
            case SDL_SCANCODE_J:            return Engine2D::Scancode::KEY_J;
            case SDL_SCANCODE_K:            return Engine2D::Scancode::KEY_K;
            case SDL_SCANCODE_L:            return Engine2D::Scancode::KEY_L;
            case SDL_SCANCODE_M:            return Engine2D::Scancode::KEY_M;
            case SDL_SCANCODE_N:            return Engine2D::Scancode::KEY_N;
            case SDL_SCANCODE_O:            return Engine2D::Scancode::KEY_O;
            case SDL_SCANCODE_P:            return Engine2D::Scancode::KEY_P;
            case SDL_SCANCODE_Q:            return Engine2D::Scancode::KEY_Q;
            case SDL_SCANCODE_R:            return Engine2D::Scancode::KEY_R;
            case SDL_SCANCODE_S:            return Engine2D::Scancode::KEY_S;
            case SDL_SCANCODE_T:            return Engine2D::Scancode::KEY_T;
            case SDL_SCANCODE_U:            return Engine2D::Scancode::KEY_U;
            case SDL_SCANCODE_V:            return Engine2D::Scancode::KEY_V;
            case SDL_SCANCODE_W:            return Engine2D::Scancode::KEY_W;
            case SDL_SCANCODE_X:            return Engine2D::Scancode::KEY_X;
            case SDL_SCANCODE_Y:            return Engine2D::Scancode::KEY_Y;
            case SDL_SCANCODE_Z:            return Engine2D::Scancode::KEY_Z;

            case SDL_SCANCODE_1:            return Engine2D::Scancode::KEY_1;
            case SDL_SCANCODE_2:            return Engine2D::Scancode::KEY_2;
            case SDL_SCANCODE_3:            return Engine2D::Scancode::KEY_3;
            case SDL_SCANCODE_4:            return Engine2D::Scancode::KEY_4;
            case SDL_SCANCODE_5:            return Engine2D::Scancode::KEY_5;
            case SDL_SCANCODE_6:            return Engine2D::Scancode::KEY_6;
            case SDL_SCANCODE_7:            return Engine2D::Scancode::KEY_7;
            case SDL_SCANCODE_8:            return Engine2D::Scancode::KEY_8;
            case SDL_SCANCODE_9:            return Engine2D::Scancode::KEY_9;
            case SDL_SCANCODE_0:            return Engine2D::Scancode::KEY_0;

            case SDL_SCANCODE_RETURN:       return Engine2D::Scancode::KEY_ENTER;
            case SDL_SCANCODE_ESCAPE:       return Engine2D::Scancode::KEY_ESCAPE;
            case SDL_SCANCODE_BACKSPACE:    return Engine2D::Scancode::KEY_BACKSPACE;
            case SDL_SCANCODE_TAB:          return Engine2D::Scancode::KEY_TAB;
            case SDL_SCANCODE_SPACE:        return Engine2D::Scancode::KEY_SPACE;
            case SDL_SCANCODE_MINUS:        return Engine2D::Scancode::KEY_MINUS;
            case SDL_SCANCODE_EQUALS:       return Engine2D::Scancode::KEY_EQUAL;
            case SDL_SCANCODE_LEFTBRACKET:  return Engine2D::Scancode::KEY_LEFTBRACE;
            case SDL_SCANCODE_RIGHTBRACKET: return Engine2D::Scancode::KEY_RIGHTBRACE;
            case SDL_SCANCODE_BACKSLASH:    return Engine2D::Scancode::KEY_BACKSLASH;
            case SDL_SCANCODE_SEMICOLON:    return Engine2D::Scancode::KEY_SEMICOLON;
            case SDL_SCANCODE_APOSTROPHE:   return Engine2D::Scancode::KEY_APOSTROPHE;
            case SDL_SCANCODE_GRAVE:        return Engine2D::Scancode::KEY_GRAVE;
            case SDL_SCANCODE_COMMA:        return Engine2D::Scancode::KEY_COMMA;
            case SDL_SCANCODE_PERIOD:       return Engine2D::Scancode::KEY_DOT;
            case SDL_SCANCODE_SLASH:        return Engine2D::Scancode::KEY_SLASH;
            case SDL_SCANCODE_CAPSLOCK:     return Engine2D::Scancode::KEY_CAPSLOCK;

            case SDL_SCANCODE_F1:           return Engine2D::Scancode::KEY_F1;
            case SDL_SCANCODE_F2:           return Engine2D::Scancode::KEY_F2;
            case SDL_SCANCODE_F3:           return Engine2D::Scancode::KEY_F3;
            case SDL_SCANCODE_F4:           return Engine2D::Scancode::KEY_F4;
            case SDL_SCANCODE_F5:           return Engine2D::Scancode::KEY_F5;
            case SDL_SCANCODE_F6:           return Engine2D::Scancode::KEY_F6;
            case SDL_SCANCODE_F7:           return Engine2D::Scancode::KEY_F7;
            case SDL_SCANCODE_F8:           return Engine2D::Scancode::KEY_F8;
            case SDL_SCANCODE_F9:           return Engine2D::Scancode::KEY_F9;
            case SDL_SCANCODE_F10:          return Engine2D::Scancode::KEY_F10;
            case SDL_SCANCODE_F11:          return Engine2D::Scancode::KEY_F11;
            case SDL_SCANCODE_F12:          return Engine2D::Scancode::KEY_F12;

            case SDL_SCANCODE_PRINTSCREEN:  return Engine2D::Scancode::KEY_PRINTSCREEN;
            case SDL_SCANCODE_SCROLLLOCK:   return Engine2D::Scancode::KEY_SCROLLLOCK;
            case SDL_SCANCODE_PAUSE:        return Engine2D::Scancode::KEY_PAUSE;
            case SDL_SCANCODE_INSERT:       return Engine2D::Scancode::KEY_INSERT;
            case SDL_SCANCODE_HOME:         return Engine2D::Scancode::KEY_HOME;
            case SDL_SCANCODE_PAGEUP:       return Engine2D::Scancode::KEY_PAGEUP;
            case SDL_SCANCODE_DELETE:       return Engine2D::Scancode::KEY_DELETE;
            case SDL_SCANCODE_END:          return Engine2D::Scancode::KEY_END;
            case SDL_SCANCODE_PAGEDOWN:     return Engine2D::Scancode::KEY_PAGEDOWN;
            case SDL_SCANCODE_RIGHT:        return Engine2D::Scancode::KEY_RIGHT;
            case SDL_SCANCODE_LEFT:         return Engine2D::Scancode::KEY_LEFT;
            case SDL_SCANCODE_DOWN:         return Engine2D::Scancode::KEY_DOWN;
            case SDL_SCANCODE_UP:           return Engine2D::Scancode::KEY_UP;

            case SDL_SCANCODE_LCTRL:        return Engine2D::Scancode::KEY_LEFTCONTROL;
            case SDL_SCANCODE_LSHIFT:       return Engine2D::Scancode::KEY_LEFTSHIFT;
            case SDL_SCANCODE_LALT:         return Engine2D::Scancode::KEY_LEFTALT;
            case SDL_SCANCODE_LGUI:         return Engine2D::Scancode::KEY_LEFTMETA;
            case SDL_SCANCODE_RCTRL:        return Engine2D::Scancode::KEY_RIGHTCONTROL;
            case SDL_SCANCODE_RSHIFT:       return Engine2D::Scancode::KEY_RIGHTSHIFT;
            case SDL_SCANCODE_RALT:         return Engine2D::Scancode::KEY_RIGHTALT;
            case SDL_SCANCODE_RGUI:         return Engine2D::Scancode::KEY_RIGHTMETA;

            default:                        return Engine2D::Scancode::KEY_UNKNOWN;
        }
    }

    Engine2D::MouseButton SDLMouseButtonToEngine2D(uint8_t mousebutton) {
        switch(mousebutton) {
            case SDL_BUTTON_LEFT:           return Engine2D::MouseButton::MOUSE_BUTTON_LEFT;
            case SDL_BUTTON_MIDDLE:         return Engine2D::MouseButton::MOUSE_BUTTON_MIDDLE;
            case SDL_BUTTON_RIGHT:          return Engine2D::MouseButton::MOUSE_BUTTON_RIGHT;
            case SDL_BUTTON_X1:             return Engine2D::MouseButton::MOUSE_BUTTON_X1;
            case SDL_BUTTON_X2:             return Engine2D::MouseButton::MOUSE_BUTTON_X2;

            default:                        return Engine2D::MouseButton::MOUSE_BUTTON_UNKNOWN;
        }
    }

    Engine2D::Window* m_Window;
    bool m_ShouldClose;
    bool m_CurrentState[512];
    bool m_PreviousState[512];
    bool m_CurrentMouseState[6];
    bool m_PreviousMouseState[6];
    float m_CurrentMouseX = 0, m_CurrentMouseY = 0;
    float m_PreviousMouseX = 0, m_PreviousMouseY = 0;
};

// Implementation of IInput::Init
std::unique_ptr<Engine2D::Input> Engine2D::Input::Create(Window* window) {
    return std::make_unique<SDL3Input>(window);
}