#pragma once

#include "Image.h"

class Texture
{
private:
    Texture() = default;
    void CreateTexture();
    void SetTextureFromImage(const Image* image);

public:
    ~Texture();
    static std::unique_ptr<Texture> CreateTextureFromImage(const Image* image);

public:
    uint32_t GetTextureID() const { return _textureID; }
    void Bind();
    void SetFilter(uint32_t min, uint32_t mag);
    void SetWrap(uint32_t s, uint32_t t);

private:
    uint32_t _textureID = 0;
};
