#include "Engine2D/Core/AssetManager.h"
#include "Engine2D/Core/FileSystem.h"
#include "Engine2D/Core/Log.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

Engine2D::AssetManager& Engine2D::AssetManager::Get()
{
    static AssetManager instance;
    return instance;
}

std::shared_ptr<Engine2D::Shader> Engine2D::AssetManager::LoadShader(const std::string& name, const std::string& vertPath, const std::string& fragPath)
{
    // If shader is already loaded, return existing one
    if (m_Shaders.find(name) != m_Shaders.end()) {
        return m_Shaders[name];
    }

    // Else, create shader
    std::string vertSource = FileSystem::ReadFile(FileSystem::GetAbsolutePath(vertPath));
    std::string fragSource = FileSystem::ReadFile(FileSystem::GetAbsolutePath(fragPath));
    std::shared_ptr<Shader> shader = Shader::Create(vertSource.c_str(), fragSource.c_str());
    
    // Cache and return shader
    m_Shaders[name] = shader;
    return shader;
}

std::shared_ptr<Engine2D::Image> Engine2D::AssetManager::LoadImage(const std::string& path) {
    // If image is already loaded, return existing one
    if (m_Images.find(path) != m_Images.end()) {
        return m_Images[path];
    }

    // Else, load image
    std::shared_ptr<Image> image = std::make_shared<Image>();
    stbi_set_flip_vertically_on_load(1);
    image->Data = stbi_load(FileSystem::GetAbsolutePath(path).c_str(), &image->Width, &image->Height, nullptr, 4);

    if(image->Data == nullptr)
    {
        LOG("Couldn't load image: " << FileSystem::GetAbsolutePath(path));
    }

    // Cache and return imahe
    m_Images[path] = image;
    return image;
}
        
std::shared_ptr<Engine2D::Texture> Engine2D::AssetManager::LoadTextureFromImage(const std::string& path) {
    // If texture is already loaded, return existing one
    if (m_Textures.find(path) != m_Textures.end()) {
        return m_Textures[path];
    }

    // Else, load texture
    std::shared_ptr<Texture> texture = Texture::Create(*LoadImage(path));

    // Cache and return texture
    m_Textures[path] = texture;
    return texture;
}