#pragma once

#include "Program.h"
class Engine
{
private:
    Engine() = default;

private:
    bool Initialize();

public:
    static std::unique_ptr<Engine>  CreateEngine();
    void                            Render();

private:
    std::unique_ptr<Program> _programID;
};
