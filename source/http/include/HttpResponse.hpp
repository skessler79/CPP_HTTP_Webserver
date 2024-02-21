#pragma once

#include <string>

#include "http/include/HttpTypes.hpp"
#include "server/include/FileRouter.hpp"

namespace utils
{
    class HttpResponse
    {
    public:
        HttpResponse();

        void setHttpResponseBody(const std::string& httpResponseBody);
        std::string makeFullResponse();     // TODO : Should take in parameter of request
        std::string generateHeaderString();     

    private:
        HttpVersion m_HttpVersion;
        HttpStatusCode m_StatusCode;
        std::unordered_map<std::string, std::string> m_ResponseHeaders;
        std::string m_HttpResponseBody;     // TODO : Might need more than a string?
        server::FileRouter& m_FileRouter;
    };
}