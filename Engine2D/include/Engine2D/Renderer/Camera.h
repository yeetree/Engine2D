#ifndef INCLUDE_ENGINE2D_RENDERER_CAMERA2D
#define INCLUDE_ENGINE2D_RENDERER_CAMERA2D

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Engine2D {
    class Camera {
    public:
        Camera(float width = 0, float height = 0);

        void SetSize(float width, float height);
        void SetPosition(const glm::vec2& position);
        void SetRotation(float rotation);

        const glm::mat4& GetViewProjectionMatrix() const;

    private:
        void RecalculateViewMatrix();

        glm::mat4 m_ProjectionMatrix;
        glm::mat4 m_ViewMatrix;
        glm::mat4 m_ViewProjectionMatrix;
        glm::vec2 m_Position;
        float m_Rotation;
    };
}

#endif // INCLUDE_ENGINE2D_RENDERER_CAMERA2D
