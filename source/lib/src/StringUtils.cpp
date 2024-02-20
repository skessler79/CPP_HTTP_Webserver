

#include "lib/include/StringUtils.hpp"

namespace utils
{

std::vector<std::string_view> splitStringView(std::string_view strView, char delimiter)
{
    std::vector<std::string_view> results;

    size_t start = 0;
    size_t end;

    // Loop until end of string
    while((end = strView.find(delimiter, start)) != std::string_view::npos)
    {
        results.push_back(strView.substr(start, end - start));
        start = end + 1;
    }

    results.push_back(strView.substr(start));
    return results;
}

std::vector<std::string_view> splitStringView(std::string_view strView, std::string_view delimiter)
{
    std::vector<std::string_view> results;

    size_t start = 0;
    size_t end;
    size_t delimLen = delimiter.length();

    // Loop until end of string
    while((end = strView.find(delimiter, start)) != std::string_view::npos)
    {
        results.push_back(strView.substr(start, end - start));
        start = end + delimLen;
    }

    results.push_back(strView.substr(start));
    return results;
}

} // namespace utils