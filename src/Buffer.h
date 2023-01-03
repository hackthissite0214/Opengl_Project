#pragma once
#include "Common.h"

class Buffer
{
private:
    Buffer() = default;
    bool Initialize(uint32_t bufferType, uint32_t usage, const void* data, size_t dataSize);
    
public:
    ~Buffer();
    static std::unique_ptr<Buffer> CreateBuffer(uint32_t bufferType, uint32_t usage, const void* data, size_t dataSize);
    void Bind();

public:
    uint32_t GetBuffer() const { return _buffer; }

private:
    uint32_t _buffer = {0};
    uint32_t _bufferType = {0};
    uint32_t _usage = {0};
};

