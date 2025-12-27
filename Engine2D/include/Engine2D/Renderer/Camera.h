#ifndef INCLUDE_ENGINE2D_RENDERER_CAMERA2D
#define INCLUDE_ENGINE2D_RENDERER_CAMERA2D

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Engine2D {
    class Camera {
    public:
        Camera(float width = 0, float height = 0);

        void SetSize(float screenWidth, float screenHeight);

        void SetPosition(const glm::vec2& position);
        void SetRotation(float rotation);
        void SetZoom(float zoom);

        glm::vec2 GetPosition() const;
        float GetRotation() const;
        float GetZoom() const;

        glm::vec2 ScreenToWorld(glm::vec2 screenPos) const;
        glm::vec2 ScreenToWorldDelta(const glm::vec2& screenDelta) const;
        glm::vec2 WorldToScreen(glm::vec2 screenPos) const;

        const glm::mat4& GetViewProjectionMatrix();

    private:
        void UpdateProjectionMatrix();
        void UpdateViewProjectionMatrix();

        glm::mat4 m_ProjectionMatrix;
        glm::mat4 m_ViewProjectionMatrix;

        glm::vec2 m_Position;
        float m_Rotation, m_Zoom;

        float m_ScreenWidth, m_ScreenHeight, m_AspectRatio;

        bool m_Dirty;
    };
}

#endif // INCLUDE_ENGINE2D_RENDERER_CAMERA2D
