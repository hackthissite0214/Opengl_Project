#include "Engine.h"
#include "Shader.h"
#include "Image.h"
#include "Texture.h"

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

    //  vertex coordinate
    //  -1,1         1,1
    //         0,0
    // -1,-1         1,-1 
    float vertices4[] = {
        0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // top right, red
        0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // bottom right, green
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, // bottom left, blue
        -0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, // top left, yellow
    };

    //  x, y, z, r, g, b, s, t
    //  s,t -> Texture coordinate (좌표)
    //  s -> x , t -> y
    float vertices5[] = {
    0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
    0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
    -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
    -0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
    };

    //  Texture coordinate 
    //  x,y
    //  0,1    1,1
    //  0,0    0,1
    uint32_t indices[] = {
        0, 1, 3,
        1, 2, 3
    };

    _vertexLayout = VertexLayout::CreateVertexLayout();
 
    _vertexBuffer = Buffer::CreateBuffer(GL_ARRAY_BUFFER, GL_STATIC_DRAW, vertices5, sizeof(vertices5));

    //  layout (location = 0) in vec3 aPos; -> location 0 = VAO attribute 0 
    _vertexLayout->SetAttribute(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, 0);
    //  layout (location = 1) in vec3 aColor -> location 1 = VAO attribute 1  
    _vertexLayout->SetAttribute(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, sizeof(float) * 3);
    //  layout (location = 2) in vec3 aTexCoord -> location 2 = VAO attribute 2  
    _vertexLayout->SetAttribute(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, sizeof(float) * 6);

    _indexBuffer = Buffer::CreateBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW, indices, sizeof(indices));

    std::shared_ptr<Shader> vertexShader = Shader::CreateFromFile("./shader/texture.vs", GL_VERTEX_SHADER);
    std::shared_ptr<Shader> fragmentShader = Shader::CreateFromFile("./shader/texture.fs", GL_FRAGMENT_SHADER);
    
    if(vertexShader == nullptr || fragmentShader == nullptr)
        return false;

    SPDLOG_INFO("Vertext Shader Id : {}", vertexShader->GetShaderID());
    SPDLOG_INFO("Fragment Shader Id : {}", fragmentShader->GetShaderID());

    _program = Program::CreateProgram({vertexShader, fragmentShader});

    if(_program == nullptr)
        return false;

    SPDLOG_INFO("Program Id : {}", _program->GetProgramID());

    //  fs -> uniform color
    // auto uniformLocation = glGetUniformLocation(_program->GetProgramID(), "color");
    // _program->Use();
    // glUniform4f(uniformLocation, 0.f, 1.0f, 0.f, 1.0f);

    glClearColor(0.1f, 0.2f, 0.3f, 0.f);


    // auto image = Image::CreateImage(512,512);
    // image->SetCheckImage(16,16);
    // if(image == nullptr)
    //     return false;

    // SPDLOG_INFO("Image : {}x{}, {} channels", image->GetWidth(), image->GetHeight(), image->GetChannel());

    // Image Binary Data -> CPU
    auto image = Image::LoadImg("./image/container.jpg");
    if(image == nullptr)
        return false;

    SPDLOG_INFO("Image : {}x{}, {} channels", image->GetWidth(), image->GetHeight(), image->GetChannel());

    _texture = Texture::CreateTextureFromImage(image.get());
    if(_texture == nullptr)
        return false;

    SPDLOG_INFO("Texture Id : {}", _texture->GetTextureID());

    auto image2 = Image::LoadImg("./image/awesomeface.png");
    if(image2 == nullptr)
        return false;

    SPDLOG_INFO("Image : {}x{}, {} channels", image2->GetWidth(), image2->GetHeight(), image2->GetChannel());

    _texture2 = Texture::CreateTextureFromImage(image2.get());
    if(_texture2 == nullptr)
        return false;

    SPDLOG_INFO("Texture Id : {}", _texture2->GetTextureID());

    //  Texture 0번 슬롯에 _texture Object Bind
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, _texture->GetTextureID());

    //  Texture 1번 슬롯에 _texture2 Object Bind
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, _texture2->GetTextureID());

    _program->Use();

    //  fs uniform sampler2D tex
    //  0번 슬롯 Texture Use
    glUniform1i(glGetUniformLocation(_program->GetProgramID(), "tex"), 0);
    //  fs uniform sampler2D tex2
    //  1번 슬롯 Texture Use
    glUniform1i(glGetUniformLocation(_program->GetProgramID(), "tex2"), 1);

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

    // static float tick = 0.f;
    // float value = ::sinf(tick) * 0.5f + 0.5f; // 0 ~ 1
    // auto uniformLocation = glGetUniformLocation(_program->GetProgramID(), "color");
    // _program->Use();
    // glUniform4f(uniformLocation, value * value, 2.0f * value * (1.0f - value), (1.0f - value) * (1.0f - value), 1.0f);
    // // glDrawArrays(GL_POINTS, 0, 1);
    // // glDrawArrays(GL_TRIANGLES, 0, 6);
    // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    // tick += 0.016f;

    _program->Use();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
