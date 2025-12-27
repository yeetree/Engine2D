#ifndef INCLUDE_ENGINE2D_CORE_ASSETMANAGER
#define INCLUDE_ENGINE2D_CORE_ASSETMANAGER

#include <unordered_map>
#include <memory>
#include "Engine2D/Renderer/Shader.h"
#include "Engine2D/Renderer/Texture.h"
#include "Engine2D/Core/Image.h"

namespace Engine2D {
    class AssetManager {
    public:
        static AssetManager& Get();

        std::shared_ptr<Shader> LoadShader(const std::string& name, const std::string& vertPath, const std::string& fragPath);
        
        std::shared_ptr<Image> LoadImage(const std::string& path);
        
        std::shared_ptr<Texture> LoadTextureFromImage(const std::string& path);

    private:
        AssetManager() = default;

        std::unordered_map<std::string, std::shared_ptr<Shader>> m_Shaders;
        std::unordered_map<std::string, std::shared_ptr<Image>> m_Images;
        std::unordered_map<std::string, std::shared_ptr<Texture>> m_Textures;
    };
}

#endif // INCLUDE_ENGINE2D_CORE_ASSETMANAGER
