#include "Common.h"

class VertexLayout
{
private:
    VertexLayout() = default;
    void Initialize();

public:
    ~VertexLayout();
    static std::unique_ptr<VertexLayout> CreateVertexLayout();
    void Bind();

public:
    uint32_t    GetVertexArray() const { return _vertexArrayObject; }
    void        SetAttribute(uint32_t attributeIndex, int count, uint32_t type, bool normalized, size_t stride, uint64_t offset);
    void        RemoveAttribute(int attributeIndex);

private:
    uint32_t _vertexArrayObject = {0};
};
