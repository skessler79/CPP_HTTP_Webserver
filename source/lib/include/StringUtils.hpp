#pragma once

#include <string_view>
#include <vector>

namespace utils
{
    std::vector<std::string_view> splitStringView(std::string_view strView, char delimiter);
    std::vector<std::string_view> splitStringView(std::string_view strView, std::string_view delimiter);
}