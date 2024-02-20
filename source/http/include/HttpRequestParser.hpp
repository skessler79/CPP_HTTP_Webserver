#pragma once

#include <vector>

#include "http/include/HttpRequest.hpp"
#include "http/include/HttpTypes.hpp"

namespace utils
{
    class HttpRequestParser
    {
    public:
        HttpRequestParser() = delete;

        static HttpRequest parseRequest(std::string& buffer);
    
    private:
        static std::tuple<HttpRequestMethod, std::string, HttpVersion> parseRequestLine(std::string_view requestLine);
        static std::unordered_map<std::string, std::string> parseRequestHeaders(const std::vector<std::string_view>& lines);
        static std::string parseRequestBody(const std::vector<std::string_view>& lines);
        static HttpRequestMethod parseMethod(std::string_view methodStr);
        static std::string parsePath(std::string_view path);
        static HttpVersion parseVersion(std::string_view versionStr);
    };
}