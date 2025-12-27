#include "Engine2D/Core/FileSystem.h"
#include "Engine2D/Core/Log.h"
#include <fstream>
#include <sstream>
#include <filesystem>

std::filesystem::path Engine2D::FileSystem::s_RootPath = "";

void Engine2D::FileSystem::Init(const char* argv0) {
    // Gets the absolute path of the executable
    std::filesystem::path exePath = std::filesystem::absolute(argv0).parent_path();
    s_RootPath = exePath;
}

std::string Engine2D::FileSystem::ReadFile(const std::string &path)
{
    std::ifstream file(path);
    if (!file.is_open()) {
        LOG("Could not open file: " << path);
        return "";
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

bool Engine2D::FileSystem::Exists(const std::string &path) {
    return std::filesystem::exists(path);
}

std::string Engine2D::FileSystem::GetAbsolutePath(const std::string& relativePath) {
    return (s_RootPath / relativePath).string();
}