#include "http/include/HttpRequest.hpp"

namespace utils
{

HttpRequest::HttpRequest()
    : m_RequestMethod(HMethod_Invalid),
      m_HttpVersion(HVersion_None)
{
}

HttpRequest::HttpRequest(HttpRequestMethod requestMethod, std::string path, HttpVersion httpVersion,
                    std::unordered_map<std::string, std::string> headers, std::string body)
    : m_RequestMethod(requestMethod),
      m_Path(std::move(path)),
      m_HttpVersion(httpVersion),
      m_RequestHeaders(std::move(headers)),
      m_RequestBody(std::move(body))
{
}

const HttpRequestMethod& HttpRequest::getRequestMethod() const
{
    return m_RequestMethod;
}

void HttpRequest::setRequestMethod(HttpRequestMethod requestMethod)
{
    m_RequestMethod = requestMethod;
}

const std::string& HttpRequest::getPath() const
{
    return m_Path;
}

void HttpRequest::setPath(const std::string& path)
{
    m_Path = path;
}

void HttpRequest::setPath(std::string&& path)
{
    m_Path = std::move(path);
}

const HttpVersion& HttpRequest::getHttpVersion() const
{
    return m_HttpVersion;
}

void HttpRequest::setHttpVersion(HttpVersion httpVersion)
{
    m_HttpVersion = httpVersion;
}

const std::unordered_map<std::string, std::string>& HttpRequest::getHeaders() const
{
    return m_RequestHeaders;
}

const std::string& HttpRequest::getBody() const
{
    return m_RequestBody;
}

void HttpRequest::setBody(const std::string& body)
{
    m_RequestBody = body;
}

const std::string& HttpRequest::getHeaderBy(const std::string& key) const
{
    static const std::string emptyStr;
    auto result = m_RequestHeaders.find(key);
    if(result == m_RequestHeaders.end())
        return emptyStr;
    return result->second;
}

void HttpRequest::addHeader(const std::string& key, const std::string& value)
{
    m_RequestHeaders[key] = value;
}

void HttpRequest::removeHeaderBy(const std::string& key)
{
    m_RequestHeaders.erase(key);
}

} // namespace utils