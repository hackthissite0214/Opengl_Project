#pragma once
#include "common.h"

class Shader
{
private:
    Shader() = default;
    bool LoadFromFile(const std::string& fileName, GLenum shaderType);

public:
    static std::unique_ptr<Shader> CreateFromFile(const std::string& fileName, GLenum shaderType);
    ~Shader();

public:
    uint32_t GetShaderID() const { return _shaderID; }

private:
    Shader(const Shader&) = delete;
    Shader& operator=(const Shader&) = delete;
    
    //  Shader Object ID
    uint32_t _shaderID = {0};
};
