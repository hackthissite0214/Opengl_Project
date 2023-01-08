#include "Image.h"
//  IMG LIB
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

Image::~Image()
{
    if(_data)
    {
        ::stbi_image_free(_data);
        _data = nullptr;
    }
}

bool Image::LoadFromStb(const std::string& filePath)
{
    //  본래 이미지 좌표 기준 좌상단 원점
    //  OpenGl은 좌하단 원점
    //  -> Image Loading 시 상하 반전 
    ::stbi_set_flip_vertically_on_load(true);
    _data = ::stbi_load(filePath.c_str(), &_width, &_height, &_channel, 0);
    if(_data == nullptr)
    {
        SPDLOG_ERROR("Failed to Load Image : {}", filePath);
        return false;
    }

    return true;
}

bool Image::Allocate(int width, int height, int channel)
{
    _width = width;
    _height = height;
    _channel = channel;

    _data = reinterpret_cast<uint8_t*>(::malloc(_width * _height* _channel));

    return _data ? true : false;
}

std::unique_ptr<Image> Image::LoadImg(const std::string &filePath)
{
    auto image = std::unique_ptr<Image>(new Image());
    if(image->LoadFromStb(filePath) == false)
        return nullptr;

    return std::move(image);
}

std::unique_ptr<Image> Image::CreateImage(int width, int height, int channel)
{
    auto image = std::unique_ptr<Image>(new Image());
    if(image->Allocate(width, height, channel) == false)
        return nullptr;

    return std::move(image);
}

void Image::SetCheckImage(int gridX, int gridY)
{
    int pos = 0;
    bool even = false;
    uint8_t value = 0;

    for(int y = 0; y < _height; y++)
    {
        for(int x = 0; x < _width; x++)
        {
            pos = (y * _width + x) * _channel; 
            even = ((x / gridX) + (y / gridY)) % 2 == 0;
            value = even ? 255 : 0;

            for(int pixel = 0; pixel < _channel; pixel++)
                _data[pos + pixel] = value;

            // RGBA -> Alpha
            if(_channel > 3)
                _data[pos + 3] = 255;       
        }
    }
}