#include "Texture.h"

Texture::~Texture()
{
    if(_textureID)
    {
        glDeleteTextures(1, &_textureID);
        _textureID = 0;
    }
}

void Texture::CreateTexture()
{
    //  GPU
    //  Texture Object Generate
    glGenTextures(1, &_textureID);
    Bind();

    // SetFilter(GL_LINEAR, GL_LINEAR);

    //  MINMAP 적용 -> 축소에 대비하여 Level에 따른 절반 크기에 대한 이미지 미리 만들어놓음 ( 메모리 1/3 비용 추가 )
    //  본래의 사이즈 보다 더 작게 랜더링되는 텍스쳐 일 경우 MINMAP에서 작은 이미지의 사이즈를 가져와서 랜더링
    SetFilter(GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    SetWrap(GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE);
}

void Texture::SetTextureFromImage(const Image* image)
{
    GLenum format = GL_RGBA;

    switch (image->GetChannel())
    {
    case 1:
        format = GL_RED;
        break;
    case 2:
        format = GL_RG;
        break;
    case 3:
        format = GL_RGB;
        break;
    default:
        break;
    }

    //  Texture CPU -> GPU
    //  Target -> GL_TEXTURE_2D -> _textureID
    glTexImage2D(GL_TEXTURE_2D,
        //  GPU Info
        //  level -> Default Image Size
        //  RGB -> Channel 변환 가능 어떤 채널을 사용할지 GPU에서의 Texture Channel Format
        //  Image Size
        //  Border Size
     0, GL_RGBA, image->GetWidth(), image->GetHeight(), 0, 
        // CPU Info
        // RGB -> 3 Channel Image
        // Data -> Channel Type -> unsinged byte
        // image Binary Data 
     format, GL_UNSIGNED_BYTE, image->GetData());
    
    glGenerateMipmap(GL_TEXTURE_2D);
}

std::unique_ptr<Texture> Texture::CreateTextureFromImage(const Image* image)
{
    auto texture = std::unique_ptr<Texture>(new Texture());
    texture->CreateTexture();
    texture->SetTextureFromImage(image);
    return std::move(texture);
}

void Texture::Bind()
{
    //  Bind 2D Texture Target -> _textureID
    glBindTexture(GL_TEXTURE_2D, _textureID);
}

void Texture::SetFilter(uint32_t min, uint32_t mag)
{
    //  축소 or 확대 Linear
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, min);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mag);

}

void Texture::SetWrap(uint32_t s, uint32_t t)
{
    //  Textrue 좌표계 : S -> X , T -> Y 
    //  X or Y 축의 Texture 좌표가 0보다작거나 1보다 클 경우
    //  -> 제일 모서리의 컬러를 사용하는 Clamp
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, s);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, t);

}