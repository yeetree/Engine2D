#ifndef INCLUDE_ENGINE2D_RENDERER_MESH
#define INCLUDE_ENGINE2D_RENDERER_MESH

#include <vector>
#include <memory>

namespace Engine2D
{
    enum class BufferUsage {
        STATIC,
        DYNAMIC,
        STREAM
    };

    class Mesh {
    public:
        virtual ~Mesh() = default;

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        virtual unsigned int GetIndexCount() const = 0;

        virtual void SetVertices(const std::vector<float>& data, BufferUsage usage) = 0;
        virtual void SetIndices(const std::vector<unsigned int>& data, BufferUsage usage) = 0;

        static std::shared_ptr<Mesh> Create();
        static std::shared_ptr<Mesh> Create(const std::vector<float> &vertices, const std::vector<unsigned int> &indices, BufferUsage vertexUsage, BufferUsage indexUsage);
    };
} // namespace Engine2D



#endif // INCLUDE_ENGINE2D_RENDERER_MESH
