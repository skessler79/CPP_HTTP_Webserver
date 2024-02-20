#include <fstream>
#include <unistd.h>
#include <sstream>

#include "Config.hpp"
#include "server/include/HttpServer.hpp"
#include "lib/include/Socket.hpp"
#include "http/include/HttpResponse.hpp"
#include "http/include/HttpRequest.hpp"
#include "http/include/HttpRequestParser.hpp"
#include "http/include/HttpTypes.hpp"

#include <iostream>

server::HttpServer::HttpServer(const utils::InetAddress& inetAddress)
    : m_InetAddress(inetAddress),
      m_Socket(utils::Socket(AF_INET))
{
    m_Socket.setReuseAddr(true);
    m_Socket.bindAddress(inetAddress);
}

void server::HttpServer::start()
{
    m_Socket.listen();

    while(true)
    {
        printf("\n+++++ Waiting for a new connection +++++\n\n");

        // Create new socket and read from it
        utils::Socket newSock = m_Socket.accept();
        std::string readBuffer = newSock.read();

        // TODO : Parse HTTP request here...
        std::cout << readBuffer << std::endl;
        // std::cout << readBuffer.length() << std::endl;

        utils::HttpRequest httpRequest = utils::HttpRequestParser::parseRequest(readBuffer);

        // Generate HTTP response
        utils::HttpResponse httpResponse;
        std::string hello = httpResponse.makeFullResponse();

        // Write HTTP response to socket
        newSock.write(hello);

        printf("-----Hello message sent-----\n");
    }
}
