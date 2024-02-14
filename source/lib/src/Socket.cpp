#include <unistd.h>

#include "config.hpp"
#include "Socket.hpp"


utils::Socket::Socket(int family)
    : m_SockFd(::socket(family, SOCK_STREAM, IPPROTO_IP))
{
    if(m_SockFd == 0)
    {
        perror("In socket");
        exit(EXIT_FAILURE);
    }
}

utils::Socket::Socket(int family, int socktype, int protocol)
    : m_SockFd(::socket(family, socktype, protocol))
{
    if(m_SockFd == 0)
    {
        perror("In socket");
        exit(EXIT_FAILURE);
    }
}

utils::Socket::~Socket()
{
    // if(m_SockFd >= 0)
    //     ::close(m_SockFd);
}

utils::Socket utils::Socket::SocketFromSockFd(int sockFd)
{
    utils::Socket newSock;
    newSock.setSockFd(sockFd);
    return newSock;
}

int utils::Socket::getSockFd()
{
    return m_SockFd;
}

void utils::Socket::setSockFd(int sockFd)
{
    this->m_SockFd = sockFd;
}

void utils::Socket::listen()
{
    int ret = ::listen(m_SockFd, config::SK_SOCK_MAX_QUEUE);

    if(ret < 0)
    {
        perror("In listen");
        exit(EXIT_FAILURE);
    }
}

void utils::Socket::bindAddress(const utils::InetAddress& inetAddress)
{
    int ret = ::bind(m_SockFd, inetAddress.getSockAddr(), inetAddress.getSocklen());

    if(ret < 0)
    {
        perror("In bind");
        exit(EXIT_FAILURE);
    }
}

void utils::Socket::setReuseAddr(bool reuse)
{
    int yes = reuse ? 1 : 0;

    int ret = setsockopt(m_SockFd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes));

    if(ret < 0)
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
}

utils::Socket utils::Socket::accept()
{
    struct sockaddr_storage theirAddr;
    socklen_t len = sizeof(theirAddr);
    int newSockFd = ::accept(m_SockFd, reinterpret_cast<struct sockaddr*>(&theirAddr), &len);

    if(newSockFd < 0)
    {
        perror("In accept");
        exit(EXIT_FAILURE);
    }

    utils::Socket newSock;
    newSock.setSockFd(newSockFd);

    return newSock;
}

// utils::Socket utils::Socket::accept(utils::InetAddress inetAddress)
// {
//     struct sockaddr_storage their_addr;
//     socklen_t len = sizeof(their_addr);
//     int new_socket = ::accept(m_SockFd, reinterpret_cast<struct sockaddr*>(&their_addr), &len);

//     if(new_socket < 0)
//     {
//         perror("In accept");
//         exit(EXIT_FAILURE);
//     }

//     return Socket(new_socket);
// }

