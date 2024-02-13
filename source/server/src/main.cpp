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

int main(int argc, char** argv)
{
    int server_fd;
    int new_socket;
    int valread;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

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
    // -----

    // std::cout << hello << std::endl;


    // Creating socket file descriptor
    if((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("In socket");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(config::PORT);

    memset(address.sin_zero, '\0', sizeof(address.sin_zero));

    // Reuse socket if socket is still in use in kernel. Avoids "Address already in use" error message
    int yes = 1;
    if(setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)) == -1)
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    std::cout << address.sin_addr.s_addr << std::endl;

    if(bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0)
    {
        perror("In bind");
        exit(EXIT_FAILURE);
    }

    if(listen(server_fd, 10) < 0)
    {
        perror("In listen");
        exit(EXIT_FAILURE);
    }

    while(1)
    {
        printf("\n+++++ Waiting for a new connection +++++\n\n");

        if((new_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen)) < 0)
        {
            perror("In accept");
            exit(EXIT_FAILURE);
        }

        char buffer[30000] = {0};
        valread = read(new_socket, buffer, 30000);
        printf("%s\n", buffer);

        write(new_socket, hello.c_str(), hello.length());
        printf("-----Hello message sent-----\n");
        close(new_socket);
    }
}