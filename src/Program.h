#pragma once

#include "Common.h"
class Shader;
class Program
{
private:
    Program() = default;
    bool Link(const std::vector<std::shared_ptr<Shader>>& shaders);

public:
    ~Program();
    static std::unique_ptr<Program> CreateProgram(const std::vector<std::shared_ptr<Shader>>& shaders);
    void Use();
    
public:
    uint32_t GetProgramID() const { return _programID; }

private:
    uint32_t _programID = {0};
};