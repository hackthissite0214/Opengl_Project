#include "VertexLayout.h"

VertexLayout::~VertexLayout()
{
    if(_vertexArrayObject)
    {
        glDeleteVertexArrays(1, &_vertexArrayObject);
        _vertexArrayObject = 0;
    }
}

void VertexLayout::Initialize()
{
    glGenVertexArrays(1, &_vertexArrayObject);
    Bind();
}

std::unique_ptr<VertexLayout> VertexLayout::CreateVertexLayout()
{
    auto vertexLayout = std::unique_ptr<VertexLayout>(new VertexLayout());
    vertexLayout->Initialize();
    return std::move(vertexLayout);
}

void VertexLayout::Bind()
{
    glBindVertexArray(_vertexArrayObject);
}

void VertexLayout::SetAttribute(uint32_t attributeIndex, int count, uint32_t type, bool normalized, size_t stride, uint64_t offset)
{
    glEnableVertexAttribArray(attributeIndex);
    glVertexAttribPointer(attributeIndex, count, type, normalized, stride, reinterpret_cast<const void*>(offset));
}

void VertexLayout::RemoveAttribute(int attributeIndex)
{
    glDisableVertexArrayAttrib(_vertexArrayObject, attributeIndex);
}