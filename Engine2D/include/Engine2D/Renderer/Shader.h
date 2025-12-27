#ifndef INCLUDE_ENGINE2D_RENDERER_SHADER
#define INCLUDE_ENGINE2D_RENDERER_SHADER

#include <memory>
#include <glm/glm.hpp>

namespace Engine2D
{
    class Shader {
    public:
        virtual ~Shader() = default;

        virtual void Use() const = 0;
        virtual void Unuse() const = 0;

        virtual void SetBool(const char* name, bool value) const = 0;
        virtual void SetInt(const char* name, int value) const = 0;
        virtual void SetFloat(const char* name, float value) const = 0;
        virtual void SetVec2(const char* name, float x, float y) const = 0;
        virtual void SetVec2(const char* name, glm::vec2 value) const = 0;
        virtual void SetVec3(const char* name, float x, float y, float z) const = 0;
        virtual void SetVec3(const char* name, glm::vec3 value) const = 0;
        virtual void SetVec4(const char* name, float x, float y, float z, float w) const = 0;
        virtual void SetVec4(const char* name, glm::vec4 value) const = 0;
        virtual void SetMat2(const char* name, glm::mat2 value) const = 0;
        virtual void SetMat3(const char* name, glm::mat3 value) const = 0;
        virtual void SetMat4(const char* name, glm::mat4 value) const = 0;

        static std::shared_ptr<Shader> Create(const char * vert, const char * frag);
    };
} // namespace Engine2D

#endif // INCLUDE_ENGINE2D_RENDERER_SHADER
