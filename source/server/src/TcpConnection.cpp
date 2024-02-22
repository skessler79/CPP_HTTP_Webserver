
#include "http/include/HttpRequestParser.hpp"
#include "server/include/TcpConnection.hpp"

#include <iostream>

namespace server
{

TcpConnection::TcpConnection(utils::Socket&& socket)
    : m_Socket(std::move(socket)),
      m_ConnectionState(ConnectionState::Conn_ReadRequest),
      m_RequestParser(),
      m_CurrentStatus(utils::HStat_OK)
{
}

void TcpConnection::handleConnection()
{
    while(true)
    {
        if(m_CurrentStatus != utils::HStat_OK)
            break;

        if(m_ConnectionState == ConnectionState::Conn_EndConnection)
            break;

        switch(m_ConnectionState)
        {
        case ConnectionState::Conn_ReadRequest:
            handleReadRequest();
            break;
        
        case ConnectionState::Conn_ParseRequest:
            handleParseRequest();
            break;
        
        case ConnectionState::Conn_MakeResponse:
            handleMakeResponse();
            break;
        
        case ConnectionState::Conn_WriteResponse:
            handleWriteResponse();
            break;
        }
    }
}

void TcpConnection::setHttpRequest(utils::HttpRequest&& httpRequest)
{
    m_HttpRequest = std::move(httpRequest);
}

void TcpConnection::handleReadRequest()
{
    m_ReadBuffer = m_Socket.read();

    // TODO : Handle empty buffer error
    m_ConnectionState = ConnectionState::Conn_ParseRequest;
}

void TcpConnection::handleParseRequest()
{
    m_HttpRequest = m_RequestParser.parseRequest(m_ReadBuffer);
    m_CurrentStatus = m_RequestParser.getCurrentStatus();

    // TODO : Handle parsing failed error (malformed request)
    m_ConnectionState = ConnectionState::Conn_MakeResponse;
}

void TcpConnection::handleMakeResponse()
{
    m_WriteBuffer = m_HttpResponse.makeFullResponse();

    // TODO : Handle making response failed (not found or other errors)
    m_ConnectionState = ConnectionState::Conn_WriteResponse;
}

void TcpConnection::handleWriteResponse()
{
    m_Socket.write(m_WriteBuffer);

    // TODO : Handle error?
    m_ConnectionState = ConnectionState::Conn_EndConnection;
}

} // namespace server