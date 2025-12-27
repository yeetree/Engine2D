#include "Engine2D/Renderer/Mesh.h"
#include <glad/gl.h>

class OpenGLMesh : public Engine2D::Mesh {
private:
    GLenum GetBufferUsage(Engine2D::BufferUsage usage) {
        switch(usage) {
            case Engine2D::BufferUsage::STATIC:
                return GL_STATIC_DRAW;
                break;
            case Engine2D::BufferUsage::DYNAMIC:
                return GL_DYNAMIC_DRAW;
                break;
            case Engine2D::BufferUsage::STREAM:
                return GL_STREAM_DRAW;
                break;
            default:
                return GL_STATIC_DRAW;
                break;
        }
    }

public:
    OpenGLMesh() {
        glGenVertexArrays(1, &m_VertexArray);
        glGenBuffers(1, &m_VertexBuffer);
        glGenBuffers(1, &m_ElementBuffer);
        glBindVertexArray(m_VertexArray);
        glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ElementBuffer);

        // Attributes
        // 0: Position (Vec2 float)
        // 1: UV       (Vec2 float)
        // 2: Color    (Vec4 float)
        int stride = 8 * sizeof(float);
        glVertexAttribPointer(0, 2, GL_FLOAT, false, stride, (void*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 2, GL_FLOAT, false, stride, (void*)(2 * sizeof(float)));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(2, 4, GL_FLOAT, false, stride, (void*)(4 * sizeof(float)));
        glEnableVertexAttribArray(2);

        glBindVertexArray(0);
    }

    OpenGLMesh(const std::vector<float> &vertices, const std::vector<unsigned int> &indices, Engine2D::BufferUsage vertexUsage, Engine2D::BufferUsage indexUsage) : OpenGLMesh() {
        SetVertices(vertices, vertexUsage);
        SetIndices(indices, indexUsage);
    }

    ~OpenGLMesh() {
        if (m_VertexArray > 0) {
            glDeleteVertexArrays(1, &m_VertexArray);
        }
        if (m_VertexBuffer > 0) {
            glDeleteBuffers(1, &m_VertexBuffer);
        }
        if (m_ElementBuffer > 0) {
            glDeleteBuffers(1, &m_ElementBuffer);
        }
    }

    void Bind() const override {
        glBindVertexArray(m_VertexArray);
    };

    void Unbind() const override {
        glBindVertexArray(0);
    };

    unsigned int GetIndexCount() const override {
        return m_IndexCount;
    };
    
    void SetVertices(const std::vector<float> &data, Engine2D::BufferUsage usage) override {
        glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);
        glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), data.data(), GetBufferUsage(usage));
    }

    void SetIndices(const std::vector<unsigned int> &data, Engine2D::BufferUsage usage) override {
        m_IndexCount = (unsigned int)data.size();
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ElementBuffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, data.size() * sizeof(unsigned int), data.data(), GetBufferUsage(usage));
    }

private:
    unsigned int m_VertexArray, m_VertexBuffer, m_ElementBuffer, m_IndexCount;
};

std::shared_ptr<Engine2D::Mesh> Engine2D::Mesh::Create() {
    return std::make_shared<OpenGLMesh>();
}

std::shared_ptr<Engine2D::Mesh> Engine2D::Mesh::Create(const std::vector<float> &vertices, const std::vector<unsigned int> &indices, BufferUsage vertexUsage, BufferUsage indexUsage) {
    return std::make_shared<OpenGLMesh>(vertices, indices, vertexUsage, indexUsage);
}