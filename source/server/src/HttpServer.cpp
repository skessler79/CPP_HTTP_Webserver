#include <fstream>
#include <unistd.h>
#include <sstream>

#include "Config.hpp"
#include "server/include/HttpServer.hpp"
#include "lib/include/Socket.hpp"

server::HttpServer::HttpServer(const utils::InetAddress& inetAddress)
    : m_InetAddress(utils::InetAddress(config::SK_PORT, false)),
      m_Socket(utils::Socket(AF_INET))
{
    m_Socket.setReuseAddr(true);
    m_Socket.bindAddress(inetAddress);
}

void server::HttpServer::start()
{
    // -----
    // TODO : Move this to something to manage response...
    std::string hello = "HTTP/1.1 200 OK\n\n";
    std::ifstream inFile;
    inFile.open("index.html");
    std::stringstream ss;
    ss << inFile.rdbuf();
    hello += ss.str();
    // std::cout << hello << std::endl;
    // -----

    m_Socket.listen();

    while(true)
    {
        printf("\n+++++ Waiting for a new connection +++++\n\n");

        utils::Socket newSock = m_Socket.accept();

        char buffer[30000] = {0};
        ::read(newSock.getSockFd(), buffer, 30000);

        // TODO : Parse request here...
        // printf("%s\n", buffer);

        ::write(newSock.getSockFd(), hello.c_str(), hello.length());

        printf("-----Hello message sent-----\n");
    }
}
