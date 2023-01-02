#include "Common.h"
#include <fstream>
#include <sstream>

std::optional<std::string> LoadTextFromFile(const std::string& fileName)
{
    std::ifstream file(fileName);
    if(file.is_open() == false)
    {
        SPDLOG_ERROR("Failed to open file: {}", fileName);
        return {};
    }

    std::stringstream text;
    text << file.rdbuf();
    return text.str();
}