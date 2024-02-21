#pragma once

#include "http/include/HttpTypes.hpp"
#include "http/include/HttpResponse.hpp"
#include "http/include/HttpRequest.hpp"

namespace utils
{
    class HttpResponseGenerator
    {
    public:

        static HttpResponse generateResponse(const HttpRequest& request);

    private:
    };
}