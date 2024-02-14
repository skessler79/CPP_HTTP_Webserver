#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <memory>
#include <string.h>
#include <unistd.h>
#include <fstream>
#include <sstream>

#include "net_utils.hpp"
#include "config.hpp"
#include "InetAddress.hpp"
#include "Socket.hpp"

int main(int argc, char** argv)
{
    int server_fd;
    int new_socket;
    int valread;
    // struct sockaddr_in address;
    // int addrlen = sizeof(address);

    // char* hello = "HTTP/1.1 200 OK\n\nHello World!";
    std::string hello = "HTTP/1.1 200 OK\n\n";
    // char* header = "HTTP/1.1 200 OK\n\n";

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

    // // Creating socket file descriptor
    // if((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    // {
    //     perror("In socket");
    //     exit(EXIT_FAILURE);
    // }

    // // Reuse socket if socket is still in use in kernel. Avoids "Address already in use" error message
    // int yes = 1;
    // if(setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)) == -1)
    // {
    //     perror("setsockopt");
    //     exit(EXIT_FAILURE);
    // }

    // if(bind(server_fd, inetAddress.getSockAddr(), inetAddress.getSocklen()) < 0)
    // {
    //     perror("In bind");
    //     exit(EXIT_FAILURE);
    // }

    // if(listen(server_fd, 10) < 0)
    // {
    //     perror("In listen");
    //     exit(EXIT_FAILURE);
    // }

    while(1)
    {
        printf("\n+++++ Waiting for a new connection +++++\n\n");

        struct sockaddr_storage their_addr;
        socklen_t addr_size = sizeof(their_addr);
        if((new_socket = accept(serverSock.getSockFd(), (struct sockaddr*)&their_addr, &addr_size)) < 0)
        {
            perror("In accept");
            exit(EXIT_FAILURE);
        }
        // utils::Socket newSock = serverSock.accept();

        // std::cout << "new_socket == " << new_socket << std::endl;
        // std::cout << "newSock == " << newSock.getSockFd() << std::endl;


        char buffer[30000] = {0};
        valread = read(new_socket, buffer, 30000);
        // valread = read(newSock.getSockFd(), buffer, 30000);

        // printf("%s\n", buffer);
        

        write(new_socket, hello.c_str(), hello.length());
        // write(newSock.getSockFd(), hello.c_str(), hello.length());
        
        printf("-----Hello message sent-----\n");
        close(new_socket);
        // close(newSock.getSockFd());
    }
}