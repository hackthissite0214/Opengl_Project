#include "Engine.h"
#include "Shader.h"
#include "Program.h"

bool Engine::Initialize()
{
    std::shared_ptr<Shader> vertexShader = Shader::CreateFromFile("./shader/simple.vs", GL_VERTEX_SHADER);
    std::shared_ptr<Shader> fragmentShader = Shader::CreateFromFile("./shader/simple.fs", GL_FRAGMENT_SHADER);
    
    if(vertexShader == nullptr || fragmentShader == nullptr)
        return false;

    SPDLOG_INFO("Vertext Shader Id : {}", vertexShader->GetShaderID());
    SPDLOG_INFO("Fragment Shader Id : {}", fragmentShader->GetShaderID());

    _programID = Program::CreateProgram({vertexShader, fragmentShader});

    if(_programID == nullptr)
        return false;

    SPDLOG_INFO("Program Id : {}", _programID->GetProgramID());

    glClearColor(0.1f, 0.2f, 0.3f, 0.f);

    //  TEMP : ?
    uint32_t vao = 0;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    return true;
}

std::unique_ptr<Engine> Engine::CreateEngine()
{
    auto engine = std::unique_ptr<Engine>(new Engine());
    if(engine->Initialize() == false)
        return nullptr;

    return std::move(engine);
}

void Engine::Render()
{
    glClear(GL_COLOR_BUFFER_BIT);

    //  TEMP : ?
    glUseProgram(_programID->GetProgramID());
    glDrawArrays(GL_POINTS, 0, 1);
}
