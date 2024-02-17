#include <fstream>
#include <unistd.h>
#include <sstream>

#include "Config.hpp"
#include "server/include/HttpServer.hpp"
#include "lib/include/Socket.hpp"
#include "http/include/HttpResponse.hpp"

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

        utils::Socket newSock = m_Socket.accept();

        char buffer[30000] = {0};
        ::read(newSock.getSockFd(), buffer, 30000);

        // TODO : Parse HTTP request here...
        // printf("%s\n", buffer);

        // Generate HTTP response
        utils::HttpResponse httpResponse;
        std::string hello = httpResponse.makeFullResponse();

        ::write(newSock.getSockFd(), hello.c_str(), hello.length());

        printf("-----Hello message sent-----\n");
    }
}
