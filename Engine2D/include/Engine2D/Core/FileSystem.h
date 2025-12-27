#ifndef SOURCE_CORE_FILESYSTEM
#define SOURCE_CORE_FILESYSTEM

#include <filesystem>
#include <string>

namespace Engine2D
{
    class FileSystem {
    public:
        static void Init(const char* argv0);
        static std::string ReadFile(const std::string &path);
        static bool Exists(const std::string &path);
        static std::string GetAbsolutePath(const std::string& relativePath);
    private:
        static std::filesystem::path s_RootPath;
    };
} // namespace Engine2D

#endif // SOURCE_CORE_FILESYSTEM
