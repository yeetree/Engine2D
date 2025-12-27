#ifndef INCLUDE_ENGINE2D_CORE_IMAGE
#define INCLUDE_ENGINE2D_CORE_IMAGE

namespace Engine2D
{
    struct Image {
        unsigned char* Data = nullptr;
        int Width = 0;
        int Height = 0;
        int Channels = 0;

        // Helper to check if loading actually worked
        bool IsValid() const { return Data != nullptr; }
    };
} // namespace Engine2D

#endif // INCLUDE_ENGINE2D_CORE_IMAGE
