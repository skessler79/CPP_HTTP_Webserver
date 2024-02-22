#pragma once

#include <vector>

#include "http/include/HttpRequest.hpp"
#include "http/include/HttpTypes.hpp"

namespace utils
{
    class HttpRequestParser
    {
    public:
        enum class ParseState
        {
            ParseRequestLine,
            ParseHeaders,
            ParseBody,
            ParseComplete
        };

        HttpRequestParser();

        utils::HttpStatusCode getCurrentStatus();

        HttpRequest parseRequest(std::string& buffer);
    
    private:
        void parseRequestLine(std::string_view requestLine);
        void parseRequestHeaders(const std::vector<std::string_view>& lines);
        void parseRequestBody(const std::vector<std::string_view>& lines);
        HttpRequestMethod parseMethod(std::string_view methodStr);
        std::string parsePath(std::string_view path);
        HttpVersion parseVersion(std::string_view versionStr);

        HttpRequest m_HttpRequest;
        ParseState m_ParseState;
        utils::HttpStatusCode m_CurrentStatus;
    };
}