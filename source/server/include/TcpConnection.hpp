#pragma once

#include "http/include/HttpTypes.hpp"
#include "http/include/HttpRequest.hpp"
#include "http/include/HttpResponse.hpp"
#include "http/include/HttpRequestParser.hpp"
#include "lib/include/Socket.hpp"

namespace server
{
    class TcpConnection
    {
    public:
        enum class ConnectionState
        {
            Conn_ReadRequest = 0,
            Conn_ParseRequest,
            Conn_MakeResponse,
            Conn_WriteResponse,
            Conn_EndConnection
        };

        TcpConnection(utils::Socket&& socket);

        void handleConnection();

        void setHttpRequest(utils::HttpRequest&& httpRequest);

    private:
        void handleReadRequest();
        void handleParseRequest();
        void handleMakeResponse();
        void handleWriteResponse();

        utils::Socket m_Socket;
        ConnectionState m_ConnectionState;
        std::string m_ReadBuffer;
        std::string m_WriteBuffer;
        utils::HttpRequest m_HttpRequest;
        utils::HttpResponse m_HttpResponse;
        utils::HttpRequestParser m_RequestParser;
        utils::HttpStatusCode m_CurrentStatus;
    };
}