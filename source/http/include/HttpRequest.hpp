#pragma once

#include <string>
#include <unordered_map>

#include "http/include/HttpTypes.hpp"

namespace utils
{
    class HttpRequest
    {
    public:
        HttpRequest();

        const HttpRequestMethod& getRequestMethod() const;
        void setRequestMethod(HttpRequestMethod requestMethod);
        const std::string& getPath() const;
        void setPath(const std::string& path);
        void setPath(std::string&& path);
        const HttpVersion& getHttpVersion() const;
        void setHttpVersion(HttpVersion httpVersion);
        const std::unordered_map<std::string, std::string>& getHeaders() const;
        const std::string& getBody() const;
        void setBody(const std::string& body);

        const std::string& getHeaderBy(const std::string& key) const;
        void addHeader(const std::string& key, const std::string& value);
        void removeHeaderBy(const std::string& key);

    private:
        HttpRequestMethod m_RequestMethod;
        std::string m_Path;
        HttpVersion m_HttpVersion;
        std::unordered_map<std::string, std::string> m_RequestHeaders;
        std::string m_RequestBody;
    };
}