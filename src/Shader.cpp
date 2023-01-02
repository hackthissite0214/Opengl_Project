#include "Shader.h"

bool Shader::LoadFromFile(const std::string &fileName, GLenum shaderType)
{
    auto ret = LoadTextFromFile(fileName);
    if(ret.has_value() == false)
        return false;

    auto& text = ret.value();
    const auto textPtr = text.c_str();
    int32_t textLen = static_cast<int32_t>(text.length());

    _shaderID = glCreateShader(shaderType);
    glShaderSource(_shaderID, 1, &textPtr, &textLen);
    glCompileShader(_shaderID);

    int success = 0;
    glGetShaderiv(_shaderID, GL_COMPILE_STATUS, &success);
    
    if(success == 0)
    {
        char log[1024];
        glGetShaderInfoLog(_shaderID, sizeof(log), nullptr, log);
        SPDLOG_ERROR("Failed to Complie Shader : \"{}\"", fileName);
        SPDLOG_ERROR("Reason : {}", log);
        return false;
    }

    return true;   
}

std::unique_ptr<Shader> Shader::CreateFromFile(const std::string &fileName, GLenum shaderType)
{
    auto shader = std::unique_ptr<Shader>(new Shader());
    if(shader->LoadFromFile(fileName, shaderType) == false)
        return nullptr;

    return std::move(shader);
}

Shader::~Shader()
{
    if(_shaderID)
    {        
        glDeleteShader(_shaderID);
        _shaderID = 0;
    }
}
