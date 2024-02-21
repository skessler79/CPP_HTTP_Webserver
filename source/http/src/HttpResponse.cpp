#include <fstream>
#include <sstream>

#include "http/include/HttpResponse.hpp"
#include "server/include/FileRouter.hpp"

namespace utils
{

HttpResponse::HttpResponse()
    : m_FileRouter(server::FileRouter::getInstance())
{
}

// HttpResponse::HttpResponse(const std::string& path)
//     : m_HttpResponseHeader(HttpResponseHeader()),
//       m_FileRouter(server::FileRouter::getInstance())
// {
// }


void HttpResponse::setHttpResponseBody(const std::string& httpResponseBody)
{
    m_HttpResponseBody = httpResponseBody;
}

std::string HttpResponse::makeFullResponse()
{
    std::string res = generateHeaderString();
    res += m_FileRouter.getFileContentFromPath("site/index.html");
    return res;
}

std::string HttpResponse::generateHeaderString()
{
    std::string res = "HTTP/";

    // TODO : Temporary
    m_HttpVersion = HVersion_Http11;
    m_StatusCode = HStat_OK;

    // HTTP Version
    switch(m_HttpVersion)
    {
    case HVersion_None:
        break;
    
    case HVersion_Http10:
        res += "1.0 ";
        break;
    
    case HVersion_Http11:
        res += "1.1 ";
        break;

    case HVersion_Http20:
        res += "2 ";
        break;
    }

    // HTTP status codes
    switch(m_StatusCode)
    {
    case HStat_OK:
        res += "200 OK\n";
        break;
    }

    res += "\n";
    return res;
}

} // namespace utils