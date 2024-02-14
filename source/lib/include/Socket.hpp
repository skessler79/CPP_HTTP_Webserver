#pragma once

#include "InetAddress.hpp"

namespace utils
{
    class Socket
    {
    public:
        Socket() = default;
        Socket(int family);
        Socket(int family, int socktype, int protocol);
        ~Socket();

        static Socket SocketFromSockFd(int sockFd);

        int getSockFd();
        void setSockFd(int sockFd);

        void listen();
        void bindAddress(const InetAddress& inetAddress);
        void setReuseAddr(bool yes);
        // Socket accept(InetAddress inetAddress);
        Socket accept();

    private:
        int m_SockFd;
    };
}