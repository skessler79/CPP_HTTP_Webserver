#include <iostream>
#include <unistd.h>
#include <fstream>
#include <sstream>

#include "Config.hpp"
#include "lib/include/InetAddress.hpp"
#include "lib/include/Socket.hpp"

int main(int argc, char** argv)
{
    // char* hello = "HTTP/1.1 200 OK\n\nHello World!";
    std::string hello = "HTTP/1.1 200 OK\n\n";

    // -----
    // TODO : Concatenate HTML
    std::ifstream inFile;
    inFile.open("index.html");
    std::stringstream ss;
    ss << inFile.rdbuf();
    hello += ss.str();
    // std::cout << hello << std::endl;
    // -----

    utils::InetAddress inetAddress(config::SK_PORT, false);

    utils::Socket serverSock(AF_INET);
    serverSock.setReuseAddr(true);
    serverSock.bindAddress(inetAddress);
    serverSock.listen();

    while (1)
    {
        printf("\n+++++ Waiting for a new connection +++++\n\n");

        utils::Socket newSock = serverSock.accept();

        char buffer[30000] = {0};
        read(newSock.getSockFd(), buffer, 30000);
        // printf("%s\n", buffer);
        write(newSock.getSockFd(), hello.c_str(), hello.length());

        printf("-----Hello message sent-----\n");
    }
}
