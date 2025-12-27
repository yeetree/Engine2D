#include "Engine2D/Renderer/Camera.h"

namespace Engine2D
{
    Camera::Camera(float width, float height) {
        m_ProjectionMatrix = glm::ortho(0.0f, width, height, 0.0f, -1.0f, 1.0f);
        m_ViewMatrix = glm::mat4(1.0f);
        m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
        m_Rotation = 0.0f;
        m_Position = glm::vec2(0.0f, 0.0f);
    }

    void Camera::SetSize(float width, float height) {
        m_ProjectionMatrix = glm::ortho(0.0f, width, height, 0.0f, -1.0f, 1.0f);
        m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
    }

    void Camera::SetPosition(const glm::vec2& position) { 
        m_Position = position; 
        RecalculateViewMatrix(); 
    }

    void Camera::SetRotation(float rotation) {
        m_Rotation = rotation;
        RecalculateViewMatrix();
    }

    const glm::mat4& Camera::GetViewProjectionMatrix() const { 
        return m_ViewProjectionMatrix;
    }

    void Camera::RecalculateViewMatrix() {
        // 1. Create the transform (Position and Rotation)
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(m_Position, 0.0f)) *
                            glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation), glm::vec3(0, 0, 1));
        
        // 2. The View Matrix is the inverse of the Camera's transform
        m_ViewMatrix = glm::inverse(transform);
        
        // 3. Update the combined matrix
        m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
    }
} // namespace Engine2D
