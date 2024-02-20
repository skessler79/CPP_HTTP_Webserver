#include <string_view>
#include <ranges>
#include <vector>

#include "http/include/HttpRequestParser.hpp"
#include "lib/include/StringUtils.hpp"

namespace utils
{

// TODO : Should probably return an error if there is one
HttpRequest HttpRequestParser::parseRequest(std::string& buffer)
{
    auto lines = utils::splitStringView(buffer, HTTP_LINE_END);

    // Parse request line
    auto [requestMethod, path, httpVersion] = parseRequestLine(lines[0]);

    // Parse headers
    auto headers = parseRequestHeaders(lines);

    // Parse body
    std::string body = parseRequestBody(lines);

    return HttpRequest{requestMethod, path, httpVersion, headers, body};
}

std::tuple<HttpRequestMethod, std::string, HttpVersion> HttpRequestParser::parseRequestLine(std::string_view requestLine)
{
    auto parts = utils::splitStringView(requestLine, ' ');

    if(parts.size() < 3)
    {
        // TODO : Should just end connection with error 400
        perror("Invalid request line");
        exit(EXIT_FAILURE);
    }

    HttpRequestMethod method = parseMethod(parts[0]);
    std::string path = parsePath(parts[1]);
    HttpVersion version = parseVersion(parts[2]);

    return {method, path, version};
}

std::unordered_map<std::string, std::string> HttpRequestParser::parseRequestHeaders(const std::vector<std::string_view>& lines)
{
    std::unordered_map<std::string, std::string> headers;

    // Loop from second line to empty line
    for(std::string_view line : std::ranges::drop_view{lines, 1})
    {
        if(line.empty())
            break;
        
        auto header = utils::splitStringView(line, ':');
        std::string key = std::string(header[0]);
        std::string value = std::string(header[1]);
        headers[std::move(key)] = std::move(value);
    }
    return headers;
}

std::string HttpRequestParser::parseRequestBody(const std::vector<std::string_view>& lines)
{
    // Duplicated computation to find empty line but it's fine for now
    auto bodyStartItr = std::find_if(lines.begin(), lines.end(), [](std::string_view line)
    {
        return line.empty();
    });

    std::string body;
    if(bodyStartItr != lines.end())
    {
        std::advance(bodyStartItr, 1); // Move to start of body

        while(bodyStartItr != lines.end())
        {
            if(!body.empty())
                body += '\n';
            
            body += std::string(*bodyStartItr);
            bodyStartItr++;
        }
    }
    return body;
}

// TODO : Implement these properly
HttpRequestMethod HttpRequestParser::parseMethod(std::string_view methodStr)
{
    return HMethod_GET;
}

std::string HttpRequestParser::parsePath(std::string_view path)
{
    return "site/index.html";
}

HttpVersion HttpRequestParser::parseVersion(std::string_view versionStr)
{
    return HVersion_Http11;
}

} // namespace utils