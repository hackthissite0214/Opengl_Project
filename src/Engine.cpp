#include "Engine.h"
#include "Shader.h"
#include "Image.h"

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

    //  Texture Binary Data -> CPU
    auto image = Image::LoadImg("./image/container.jpg");
    if(image == nullptr)
        return false;

    SPDLOG_INFO("Image : {}x{}, {} channels", image->GetWidth(), image->GetHeight(), image->GetChannel());


    //  GPU
    //  Texture Object Generate
    glGenTextures(1, &_textureID);

    //  Bind 2D Texture Target -> _textureID
    glBindTexture(GL_TEXTURE_2D, _textureID);

    //  축소 or 확대 Linear
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    //  Textrue 좌표계 : S -> X , T -> Y 
    //  X or Y 축의 Texture 좌표가 0보다작거나 1보다 클 경우
    //  -> 제일 모서리의 컬러를 사용하는 Clamp
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    //  Texture Size 2의 지수 효율

    //  Texture CPU -> GPU
    //  Target -> GL_TEXTURE_2D -> _textureID
    glTexImage2D(GL_TEXTURE_2D,
        //  GPU Info
        //  level -> Default Image Size
        //  RGB -> Channel 변환 가능 어떤 채널을 사용할지 GPU에서의 Texture Channel Format
        //  Image Size
        //  Border Size
     0, GL_RGB, image->GetWidth(), image->GetHeight(), 0, 
        // CPU Info
        // RGB -> 3 Channel Image
        // Data -> Channel Type -> unsinged byte
        // image Binary Data 
     GL_RGB, GL_UNSIGNED_BYTE, image->GetData());
    
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
