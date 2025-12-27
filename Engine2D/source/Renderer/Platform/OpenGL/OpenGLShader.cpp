#include "Engine2D/Renderer/Shader.h"
#include "Engine2D/Core/Log.h"
#include <glad/gl.h>
#include <glm/gtc/type_ptr.hpp>

class OpenGLShader : public Engine2D::Shader {
public:
    OpenGLShader(const char* vert, const char* frag) {
        // Vertex shader
        unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vert, NULL);
        glCompileShader(vertexShader);

        // Check for shader compile errors
        int success;
        char infoLog[512];
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
            LOG("Vertex shader compilation failed! OpenGL: " << infoLog);
        }

        // Fragment shader
        unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &frag, NULL);
        glCompileShader(fragmentShader);

        // Check for shader compile errors
        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
            LOG("Fragment shader compilation failed! OpenGL: " << infoLog);
        }

        // Link shaders
        m_Shader = glCreateProgram();
        glAttachShader(m_Shader, vertexShader);
        glAttachShader(m_Shader, fragmentShader);
        glLinkProgram(m_Shader);

        // Check for linking errors
        glGetProgramiv(m_Shader, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(m_Shader, 512, NULL, infoLog);
            LOG("Shader linking failed! OpenGL: " << infoLog);
        }

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    }

    ~OpenGLShader() {
        glDeleteProgram(m_Shader);
    }

    void Use() const override {
        glUseProgram(m_Shader);
    };

    void Unuse() const override {
        glUseProgram(0);
    };

    void SetBool(const char* name, bool value) const override
    {         
        glUniform1i(glGetUniformLocation(m_Shader, name), (int)value); 
    }

    void SetInt(const char* name, int value) const override
    { 
        glUniform1i(glGetUniformLocation(m_Shader, name), value); 
    }

    void SetFloat(const char* name, float value) const override
    { 
        glUniform1f(glGetUniformLocation(m_Shader, name), value); 
    }

    void SetVec2(const char* name, float x, float y) const override
    { 
        glUniform2f(glGetUniformLocation(m_Shader, name), x, y); 
    }

    void SetVec2(const char* name, glm::vec2 value) const override
    { 
        glUniform2f(glGetUniformLocation(m_Shader, name), value.x, value.y); 
    }

    void SetVec3(const char* name, float x, float y, float z) const override
    { 
        glUniform3f(glGetUniformLocation(m_Shader, name), x, y, z); 
    }

    void SetVec3(const char* name, glm::vec3 value) const override
    { 
        glUniform3f(glGetUniformLocation(m_Shader, name), value.x, value.y, value.z); 
    }

    void SetVec4(const char* name, float x, float y, float z, float w) const override
    { 
        glUniform4f(glGetUniformLocation(m_Shader, name), x, y, z, w); 
    }

    void SetVec4(const char* name, glm::vec4 value) const override
    { 
        glUniform4f(glGetUniformLocation(m_Shader, name), value.x, value.y, value.z, value.w); 
    }

    void SetMat2(const char* name, glm::mat2 value) const override {
        glUniformMatrix2fv(glGetUniformLocation(m_Shader, name), 1, GL_FALSE, glm::value_ptr(value));
    }

    void SetMat3(const char* name, glm::mat3 value) const override {
        glUniformMatrix3fv(glGetUniformLocation(m_Shader, name), 1, GL_FALSE, glm::value_ptr(value));
    }

    void SetMat4(const char* name, glm::mat4 value) const override {
        glUniformMatrix4fv(glGetUniformLocation(m_Shader, name), 1, GL_FALSE, glm::value_ptr(value));
    }

private:
    unsigned int m_Shader;
};

std::shared_ptr<Engine2D::Shader> Engine2D::Shader::Create(const char* vert, const char* frag) {
    return std::make_shared<OpenGLShader>(vert, frag);
}