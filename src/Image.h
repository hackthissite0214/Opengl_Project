#pragma once

#include "Common.h"

class Image
{
private:
    Image() = default;
    bool LoadFromStb(const std::string& filePath);
    bool Allocate(int width, int height, int channel);

public:
    ~Image();
    static std::unique_ptr<Image> LoadImg(const std::string& filePath);
    static std::unique_ptr<Image> CreateImage(int width, int height, int channel = 4);

public:
    int32_t GetWidth() const { return _width; }
    int32_t GetHeight() const { return _height; }
    int32_t GetChannel() const { return _channel;}
    uint8_t* GetData() const { return _data; }

    void    SetCheckImage(int gridX, int gridY);

private:
    int32_t _width = 0;
    int32_t _height = 0;
    int32_t _channel = 0;

    uint8_t* _data = nullptr; 
};

