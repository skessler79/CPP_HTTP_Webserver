#pragma once

#include "http/include/HttpTypes.hpp"

namespace utils
{
    struct HttpResponseHeader
    {
        HttpVersion m_HttpVersion = HVersion_Http11;
        HttpStatusCode m_HttpStatusCode = HStat_OK;
        ContentType m_ContentType = CT_Text_HTML;
    };
}