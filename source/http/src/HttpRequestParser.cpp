#include <string_view>
#include <ranges>
#include <vector>

#include "http/include/HttpRequestParser.hpp"
#include "lib/include/StringUtils.hpp"

namespace utils
{

HttpRequestParser::HttpRequestParser()
    : m_HttpRequest(),
      m_ParseState(ParseState::ParseRequestLine),
      m_CurrentStatus(HStat_OK)
{
}

HttpStatusCode HttpRequestParser::getCurrentStatus()
{
    return m_CurrentStatus;
}

// TODO : Should probably return an error if there is one
HttpRequest HttpRequestParser::parseRequest(std::string& buffer)
{
    auto lines = utils::splitStringView(buffer, HTTP_LINE_END);

    while(true)
    {
        // An error occured while parsing
        if(m_CurrentStatus != HStat_OK)
            break;
        
        // Parsing complete
        if(m_ParseState == ParseState::ParseComplete)
            break;
        
        // Continue parsing
        switch(m_ParseState)
        {
        case ParseState::ParseRequestLine:
            parseRequestLine(lines[0]);
            break;
        
        case ParseState::ParseHeaders:
            parseRequestHeaders(lines);
            break;
        
        case ParseState::ParseBody:
            parseRequestBody(lines);
            break;
        }
    }

    return m_HttpRequest;
}

void HttpRequestParser::parseRequestLine(std::string_view requestLine)
{
    auto parts = utils::splitStringView(requestLine, ' ');

    if(parts.size() < 3)
    {
        // TODO : Should just end connection with error 400
        perror("Invalid request line");
        exit(EXIT_FAILURE);
    }

    // TODO : Handle error status codes and dont parse any further
    m_HttpRequest.setRequestMethod(parseMethod(parts[0]));
    m_HttpRequest.setPath(parsePath(parts[1]));
    m_HttpRequest.setHttpVersion(parseVersion(parts[2]));

    m_ParseState = ParseState::ParseHeaders;
}

void HttpRequestParser::parseRequestHeaders(const std::vector<std::string_view>& lines)
{

    // Loop from second line to empty line
    for(std::string_view line : std::ranges::drop_view{lines, 1})
    {
        if(line.empty())
            break;
        
        auto header = utils::splitStringView(line, ':');
        std::string key = std::string(header[0]);
        std::string value = std::string(header[1]);
        m_HttpRequest.addHeader(std::move(key), std::move(value));
    }
    
    m_ParseState = ParseState::ParseBody;
}

void HttpRequestParser::parseRequestBody(const std::vector<std::string_view>& lines)
{
    // Duplicated computation to find empty line but it's fine for now
    auto bodyStartItr = std::find_if(lines.begin(), lines.end(), [](std::string_view line)
    {
        return line.empty();
    });

    std::string body;
    if(bodyStartItr != lines.end())
    {
        // Skip current empty line
        std::advance(bodyStartItr, 1);

        // Loop until end of body
        while(bodyStartItr != lines.end())
        {
            if(!body.empty())
                body += '\n';
            
            body += std::string(*bodyStartItr);
            bodyStartItr++;
        }
    }
    
    m_HttpRequest.setBody(body);
    m_ParseState = ParseState::ParseComplete;
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