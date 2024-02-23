#pragma once

#include "http/include/HttpTypes.hpp"
#include "http/include/HttpResponse.hpp"
#include "http/include/HttpRequest.hpp"

namespace utils
{
    class HttpResponseGenerator
    {
    public:
        enum class GenerateState
        {
            GenerateStatusLine,
            GenerateHeaders,
            GenerateBody,
            GenerateComplete
        };

        HttpResponseGenerator(const HttpRequest& request);

        HttpResponse generateResponse();

    private:
        void generateStatusLine();
        void generateResponseHeaders();
        void generateResponseBody();

        HttpRequest m_HttpRequest;
        HttpResponse m_HttpResponse;
        utils::HttpStatusCode m_CurrentStatus;
    };
}