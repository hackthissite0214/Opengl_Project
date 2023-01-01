#pragma once

#include <memory>
#include <string>
#include <optional>
#include <spdlog/spdlog.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

std::optional<std::string> LoadTextFromFile(const std::string& fileName);