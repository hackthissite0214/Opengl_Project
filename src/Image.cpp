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

std::unique_ptr<Image> Image::LoadImg(const std::string &filePath)
{
    auto image = std::unique_ptr<Image>(new Image());
    if(image->LoadFromStb(filePath) == false)
        return nullptr;

    return std::move(image);
}

bool Image::LoadFromStb(const std::string& filePath)
{
    _data = ::stbi_load(filePath.c_str(), &_width, &_height, &_channel, 0);
    if(_data == nullptr)
    {
        SPDLOG_ERROR("Failed to Load Image : {}", filePath);
        return false;
    }

    return true;
}