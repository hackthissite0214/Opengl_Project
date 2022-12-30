#include <spdlog/spdlog.h>
#include <GLFW/glfw3.h>

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

    // glfw 윈도우 생성, 실패하면 에러 출력후 종료
    SPDLOG_INFO("Create glfw window");
    auto window = ::glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_NAME,
      nullptr, nullptr);
    if (window == nullptr) {
        SPDLOG_ERROR("failed to create glfw window");
        ::glfwTerminate();
        return -1;
    }

      // glfw 루프 실행, 윈도우 close 버튼을 누르면 정상 종료
    SPDLOG_INFO("Start main loop");
    while (::glfwWindowShouldClose(window) == false) {
        ::glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}