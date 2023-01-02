#include "Program.h"
#include "Shader.h"
Program::~Program()
{
    if(_programID)
    {
        glDeleteProgram(_programID);
        _programID = 0;
    }
}

bool Program::Link(const std::vector<std::shared_ptr<Shader>> &shaders)
{
    _programID = glCreateProgram();

    for(auto& shader : shaders)
        glAttachShader(_programID, shader->GetShaderID());

    glLinkProgram(_programID);

    int success = 0;
    glGetProgramiv(_programID, GL_LINK_STATUS, &success);
    if(success == 0)
    {
        char log[1024];
        glGetProgramInfoLog(_programID, 1024, nullptr, log);
        SPDLOG_ERROR("Failed to link program: {}", log);
        return false;
    }

    return true;
}

std::unique_ptr<Program> Program::CreateProgram(const std::vector<std::shared_ptr<Shader>>& shaders)
{
    auto program = std::unique_ptr<Program>(new Program());
    if(program->Link(shaders) == false)
        return nullptr;

    return std::move(program);
}
