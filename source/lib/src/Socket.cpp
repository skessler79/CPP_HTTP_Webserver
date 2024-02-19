#include <unistd.h>
#include <vector>

#include "Config.hpp"
#include "lib/include/Socket.hpp"

namespace utils
{

Socket::Socket(int family)
    : m_SockFd(::socket(family, SOCK_STREAM, IPPROTO_IP))
{
    if (m_SockFd == 0)
    {
        perror("In socket");
        exit(EXIT_FAILURE);
    }
}

Socket::Socket(int family, int socktype, int protocol)
    : m_SockFd(::socket(family, socktype, protocol))
{
    if (m_SockFd == 0)
    {
        perror("In socket");
        exit(EXIT_FAILURE);
    }
}

Socket::Socket(Socket&& other) noexcept
    : m_SockFd(other.m_SockFd)
{
    other.m_SockFd = -1;
}

Socket& Socket::operator=(Socket&& other) noexcept
{
    if(this != &other)
    {
        if(m_SockFd >= 0)
            ::close(m_SockFd);
        
        m_SockFd = other.m_SockFd;
        other.m_SockFd = -1;
    }

    return *this;
}

Socket::~Socket() noexcept
{
    if (m_SockFd >= 0)
        ::close(m_SockFd);
}

Socket Socket::SocketFromSockFd(int sockFd)
{
    Socket newSock;
    newSock.setSockFd(sockFd);
    return newSock;
}

int Socket::getSockFd()
{
    return m_SockFd;
}

void Socket::setSockFd(int sockFd)
{
    this->m_SockFd = sockFd;
}

void Socket::listen()
{
    int ret = ::listen(m_SockFd, config::SK_SOCK_MAX_QUEUE);

    if (ret < 0)
    {
        perror("In listen");
        exit(EXIT_FAILURE);
    }
}

void Socket::bindAddress(const InetAddress& inetAddress)
{
    int ret = ::bind(m_SockFd, inetAddress.getSockAddr(), inetAddress.getSocklen());

    if (ret < 0)
    {
        perror("In bind");
        exit(EXIT_FAILURE);
    }
}

void Socket::setReuseAddr(bool reuse)
{
    int yes = reuse ? 1 : 0;
    int ret = setsockopt(m_SockFd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes));

    if (ret < 0)
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
}

Socket Socket::accept()
{
    struct sockaddr_storage theirAddr;
    socklen_t len = sizeof(theirAddr);
    int newSockFd = ::accept(m_SockFd,
                             reinterpret_cast<struct sockaddr*>(&theirAddr),
                             &len);

    if (newSockFd < 0)
    {
        perror("In accept");
        exit(EXIT_FAILURE);
    }

    Socket newSock;
    newSock.setSockFd(newSockFd);

    return newSock;
}

std::string Socket::read()
{
    std::vector<char> buffer(config::SK_HTTP_REQUEST_BUFFER_SIZE);
    std::string result;

    // Loop until no more data
    uint32_t bytesReceived = 0;
    do
    {
        bytesReceived = ::read(m_SockFd, &buffer[0], config::SK_HTTP_REQUEST_BUFFER_SIZE);

        // Appends buffer to result
        if(bytesReceived < 0)
        {
            perror("In read");
            exit(EXIT_FAILURE);
        }
        else
        {
            result.append(buffer.cbegin(), buffer.cend());
        }
    }
    while (bytesReceived == config::SK_HTTP_REQUEST_BUFFER_SIZE);

    return result;
}

void Socket::write(std::string_view str)
{
    int ret = ::write(m_SockFd, str.data(), str.length());

    if(ret < 0)
    {
        perror("In write");
        exit(EXIT_FAILURE);
    }
}

} // namespace utils
