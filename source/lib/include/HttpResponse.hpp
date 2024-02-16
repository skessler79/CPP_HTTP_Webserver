#pragma once

#include <string>

#include "lib/include/HttpTypes.hpp"
#include "lib/include/HttpResponseHeader.hpp"

namespace utils
{
    class HttpResponse
    {
    public:
        HttpResponse();

        void setHttpResponseBody(const std::string& httpResponseBody);
        std::string makeFullResponse();
        std::string generateHeaderString();

    private:
        HttpResponseHeader m_HttpResponseHeader;
        std::string m_HttpResponseBody;     // TODO : Might need more than a string?
    };
}