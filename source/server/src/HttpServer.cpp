#include <fstream>
#include <unistd.h>
#include <sstream>
#include <thread>

#include "Config.hpp"
#include "server/include/HttpServer.hpp"
#include "lib/include/Socket.hpp"
#include "http/include/HttpResponse.hpp"
#include "http/include/HttpRequest.hpp"
#include "http/include/HttpRequestParser.hpp"
#include "http/include/HttpTypes.hpp"
#include "server/include/TcpConnection.hpp"

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

        server::TcpConnection connection(std::move(newSock));

        // Run handleConnection on it's own thread
        std::thread([connection = std::move(connection)]() mutable
        {
            connection.handleConnection();
            printf("-----Hello message sent-----\n");
        }).detach(); // Detach thread to allow it to run independently
    }
}
