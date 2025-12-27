#include "Engine2D/Renderer/Camera.h"

constexpr float k_CameraSize = 10.0f;

namespace Engine2D
{
    Camera::Camera(float width, float height) : m_ScreenWidth(width), m_ScreenHeight(height),
    m_Position(0.0f, 0.0f), m_Rotation(0.0f), m_Zoom(1.0f) {
        UpdateProjectionMatrix();
    }

    void Camera::SetSize(float width, float height) {
        m_ScreenWidth = width;
        m_ScreenHeight = height;
        UpdateProjectionMatrix();
    }

    void Camera::SetPosition(const glm::vec2& position) { 
        m_Position = position; 
        m_Dirty = true;
    }

    void Camera::SetRotation(float rotation) {
        m_Rotation = rotation;
        m_Dirty = true;
    }

    void Camera::SetZoom(float zoom) {
        m_Zoom = zoom;
        UpdateProjectionMatrix();
        m_Dirty = true;
    }

    glm::vec2 Camera::GetPosition() const {
        return m_Position;
    }

    float Camera::GetRotation() const {
        return m_Rotation;
    }

    float Camera::GetZoom() const {
        return m_Zoom;
    }

    glm::vec2 Camera::ScreenToWorld(glm::vec2 screenPos) const {
        // Screen to NDC
        float x = (2.0f * screenPos.x) / m_ScreenWidth - 1.0f;
        float y = 1.0f - (2.0f * screenPos.y) / m_ScreenHeight;

        // Create a vec4 in NDC space
        glm::vec4 rayClip = glm::vec4(x, y, 0.0f, 1.0f);

        // Multiply by inverse View-Projection matrix
        glm::mat4 invVP = glm::inverse(m_ViewProjectionMatrix);
        glm::vec4 worldPos = invVP * rayClip;

        return glm::vec2(worldPos.x, worldPos.y);
    }

    glm::vec2 Camera::ScreenToWorldDelta(const glm::vec2& screenDelta) const {
        float unitsPerPixel = (2.0f * k_CameraSize * m_Zoom) / m_ScreenHeight;
        return screenDelta * unitsPerPixel;
    }

    glm::vec2 Camera::WorldToScreen(glm::vec2 worldPos) const {
        // World to NDC
        glm::vec4 clipSpacePos = m_ViewProjectionMatrix * glm::vec4(worldPos, 0.0f, 1.0f);
        
        // Perspective divide
        glm::vec3 ndc = glm::vec3(clipSpacePos) / clipSpacePos.w;

        // NDC to Screen Pixels
        float x = (ndc.x + 1.0f) * 0.5f * m_ScreenWidth;
        float y = (1.0f - ndc.y) * 0.5f * m_ScreenHeight;

        return glm::vec2(x, y);
    }

    const glm::mat4& Camera::GetViewProjectionMatrix() { 
        if(m_Dirty)
        {
            UpdateViewProjectionMatrix();
        }
        return m_ViewProjectionMatrix;
    }

    void Camera::UpdateProjectionMatrix() {
        m_AspectRatio = m_ScreenWidth / m_ScreenHeight;
        
        float orthoSize = k_CameraSize * m_Zoom; 

        float left   = -orthoSize * m_AspectRatio;
        float right  =  orthoSize * m_AspectRatio;
        float bottom =  orthoSize;
        float top    = -orthoSize;

        m_ProjectionMatrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
        m_Dirty = true;
    }


    void Camera::UpdateViewProjectionMatrix() {
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(m_Position, 0.0f)) *
                            glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation), glm::vec3(0, 0, 1));
        
        m_ViewProjectionMatrix = m_ProjectionMatrix * glm::inverse(transform);;
        m_Dirty = false;
    }
} // namespace Engine2D
