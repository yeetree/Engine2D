#include "Engine2D/Renderer/Texture.h"
#include <glad/gl.h>

class OpenGLTexture : public Engine2D::Texture {
private:
    unsigned int m_Texture, m_Width, m_Height;

public:
    OpenGLTexture(unsigned int width, unsigned int height) : m_Width(width), m_Height(height) {
        // Gen texture
        glGenTextures(1, &m_Texture);
        glBindTexture(GL_TEXTURE_2D, m_Texture);

        // set the texture wrapping/filtering options
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // Allocate memory
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

        glBindTexture(GL_TEXTURE_2D, 0);
    }

    ~OpenGLTexture() {
        glDeleteTextures(1, &m_Texture);
    }

    unsigned int GetWidth() const override {
        return m_Width;
    }

    unsigned int GetHeight() const override {
        return m_Height;
    }

    unsigned int GetRendererID() const override {
        return m_Texture;
    }

    void SetData(void* data) override {
        glBindTexture(GL_TEXTURE_2D, m_Texture);
        
        glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, m_Width, m_Height, GL_RGBA, GL_UNSIGNED_BYTE, data);
        
        // glGenerateMipmap(GL_TEXTURE_2D);
        
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void Bind(unsigned int slot) const override {
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D, m_Texture);
    }

    void Unbind(unsigned int slot) const override {
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

};

// Implementation of Texture::Init
std::shared_ptr<Engine2D::Texture> Engine2D::Texture::Create(unsigned int width, unsigned int height) {
    return std::make_shared<OpenGLTexture>(width, height);
}

std::shared_ptr<Engine2D::Texture> Engine2D::Texture::Create(const Image& image) {
    std::shared_ptr<Engine2D::Texture> texture = std::make_shared<OpenGLTexture>(image.Width, image.Height);
    texture->SetData(image.Data);
    return texture;
}