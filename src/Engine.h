#pragma once

#include "Program.h"
#include "Buffer.h"
#include "VertexLayout.h"
#include "Texture.h"

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
    std::unique_ptr<Program>        _program;
    std::unique_ptr<VertexLayout>   _vertexLayout;
    std::unique_ptr<Buffer>         _vertexBuffer;
    std::unique_ptr<Buffer>         _indexBuffer;
    std::unique_ptr<Texture>        _texture;
    std::unique_ptr<Texture>        _texture2;
};
