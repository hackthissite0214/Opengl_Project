#include "Engine.h"
#include "Shader.h"

bool Engine::Initialize()
{
    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f, 0.5f, 0.0f,
    };

    float vertices2[] = {
        0.5f, 0.5f, 0.f,
        0.5f, -0.5f, 0.f,
        -0.5f, 0.5f, 0.f,

        0.5f, -0.5f, 0.f,
        -0.5f, -0.5f, 0.f,
        -0.5f, 0.5f, 0.f
    };

    float vertices3[] = {
        0.5f, 0.5f, 0.f,
        0.5f, -0.5f, 0.f,
        -0.5f, -0.5f, 0.f,
        -0.5f, 0.5f, 0.f
    };

    uint32_t indices[] = {
        0, 1, 3,
        1, 2, 3
    };

    _vertexArrayObject = VertexLayout::CreateVertexLayout();
 
    _vertexBuffer = Buffer::CreateBuffer(GL_ARRAY_BUFFER, GL_STATIC_DRAW, vertices3, sizeof(vertices3));

    //  simple.vs -> layout (location = 0) in vec3 aPos; -> location 0 = VAO attribute 0 
     _vertexArrayObject->SetAttribute(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);
     
    _indexBuffer = Buffer::CreateBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW, indices, sizeof(indices));

    std::shared_ptr<Shader> vertexShader = Shader::CreateFromFile("./shader/simple.vs", GL_VERTEX_SHADER);
    std::shared_ptr<Shader> fragmentShader = Shader::CreateFromFile("./shader/simple.fs", GL_FRAGMENT_SHADER);
    
    if(vertexShader == nullptr || fragmentShader == nullptr)
        return false;

    SPDLOG_INFO("Vertext Shader Id : {}", vertexShader->GetShaderID());
    SPDLOG_INFO("Fragment Shader Id : {}", fragmentShader->GetShaderID());

    _program = Program::CreateProgram({vertexShader, fragmentShader});

    if(_program == nullptr)
        return false;

    SPDLOG_INFO("Program Id : {}", _program->GetProgramID());

    glClearColor(0.1f, 0.2f, 0.3f, 0.f);

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

    _program->Use();

    // glDrawArrays(GL_POINTS, 0, 1);
    // glDrawArrays(GL_TRIANGLES, 0, 6);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
