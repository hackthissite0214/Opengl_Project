#pragma once

#include "Program.h"
#include "Buffer.h"
#include "VertexLayout.h"

class Engine
{
private:
    Engine() = default;

private:
    bool Initialize();

public:
    static std::unique_ptr<Engine> CreateEngine();
    void Render();

private:
    std::unique_ptr<Program> _program;
    std::unique_ptr<VertexLayout> _vertexArrayObject;
    std::unique_ptr<Buffer> _vertexBuffer;
    std::unique_ptr<Buffer> _indexBuffer;
};
