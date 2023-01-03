#include "Buffer.h"

Buffer::~Buffer()
{   
    if(_buffer)
    {
        glDeleteBuffers(1, &_buffer);
        _buffer = 0;
    }
}

bool Buffer::Initialize(uint32_t bufferType, uint32_t usage, const void* data, size_t dataSize)
{
    _bufferType = bufferType;
    _usage = usage;

    glGenBuffers(1, &_buffer);
    Bind();
    
    glBufferData(_bufferType, dataSize, data, usage);
    return true;
}

std::unique_ptr<Buffer> Buffer::CreateBuffer(uint32_t bufferType, uint32_t usage, const void* data, size_t dataSize)
{
    auto buffer = std::unique_ptr<Buffer>(new Buffer());
    if(buffer->Initialize(bufferType, usage, data, dataSize) == false)
        return nullptr;
    
    return std::move(buffer);
}

void Buffer::Bind()
{
    glBindBuffer(_bufferType, _buffer);
}