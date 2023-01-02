#include "Engine.h"

void OnFrameBufferSizeChange(GLFWwindow* window, int width, int height)
{
    SPDLOG_INFO("Framebuffer size changed: ({} - {})", width, height);
    glViewport(0, 0, width, height);
}

void OnKeyEvent(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    SPDLOG_INFO("key: {}, scancode: {}, action: {}, mods: {}{}{}",
        key, scancode,
        action == GLFW_PRESS ? "Pressed" :
        action == GLFW_RELEASE ? "Released" :
        action == GLFW_REPEAT ? "Repeat" : "Unknown",
        mods & GLFW_MOD_CONTROL ? "C" : "-",
        mods & GLFW_MOD_SHIFT ? "S" : "-",
        mods & GLFW_MOD_ALT ? "A" : "-");
    
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
      ::glfwSetWindowShouldClose(window, true);
}

int main(int argc, const char** argv)
{
    SPDLOG_INFO("GLFW LIB START");

    if(::glfwInit() == false)
    {
        const char* description = nullptr;
        ::glfwGetError(&description);
        SPDLOG_ERROR("Failed to initailize GLFW: {}", description);
        return -1;
    }

    ::glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    ::glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    ::glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // glfw 윈도우 생성, 실패하면 에러 출력후 종료
    SPDLOG_INFO("Create glfw window");
    auto window = ::glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_NAME,
      nullptr, nullptr);
    if (window == nullptr) {
        SPDLOG_ERROR("failed to create glfw window");
        ::glfwTerminate();
        return -1;
    }

    ::glfwMakeContextCurrent(window);

    // glad를 활용한 OpenGL 함수 로딩
    if (::gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) == false) {
        SPDLOG_ERROR("failed to Initialize glad");
        ::glfwTerminate();
        return -1;
    }

    const auto* glVersion = reinterpret_cast<const char*>(glGetString(GL_VERSION));
    SPDLOG_INFO("OpenGL Context Version: {}", glVersion);

    auto engine = Engine::CreateEngine();
    if (engine == nullptr) 
    {
        SPDLOG_ERROR("Failed to Create Engine");
        ::glfwTerminate();
        return -1;
    }

    ::OnFrameBufferSizeChange(window, WINDOW_WIDTH, WINDOW_HEIGHT);
    ::glfwSetFramebufferSizeCallback(window, OnFrameBufferSizeChange);
    ::glfwSetKeyCallback(window, OnKeyEvent);

      // glfw 루프 실행, 윈도우 close 버튼을 누르면 정상 종료
    SPDLOG_INFO("Start main loop");
    while (::glfwWindowShouldClose(window) == false) {
        ::glfwPollEvents();
        engine->Render();
        ::glfwSwapBuffers(window);
    }

    engine.reset();
    
    ::glfwTerminate();
    return 0;
}