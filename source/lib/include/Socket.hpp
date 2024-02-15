#pragma once

#include "lib/include/InetAddress.hpp"

namespace utils
{
    class Socket
    {
    public:
        Socket() = default;
        Socket(int family);
        Socket(int family, int socktype, int protocol);
        Socket(const Socket&) = delete;
        Socket(Socket&& other) noexcept;
        Socket& operator=(Socket&& other) noexcept;
        ~Socket() noexcept;

        static Socket SocketFromSockFd(int sockFd);

        int getSockFd();
        void setSockFd(int sockFd);

        void listen();
        void bindAddress(const InetAddress& inetAddress);
        void setReuseAddr(bool yes);
        Socket accept();

    private:
    // TODO : Wrap `m_SockFd` with unique_ptr with custom `close` deleter
        int m_SockFd;
    };
}