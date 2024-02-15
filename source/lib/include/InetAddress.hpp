#pragma once

#include <netinet/in.h>
#include <string>
#include <variant>

namespace utils
{
    class InetAddress
    {
    public:
        InetAddress(const uint16_t port, bool isIPv6 = false);
        InetAddress(const std::string& ip, const uint16_t port, bool isIPv6 = false);

        const sockaddr* getSockAddr() const;
        const socklen_t getSocklen() const;

    private:
        std::variant<struct sockaddr_in, struct sockaddr_in6>m_Addr;

        bool m_isIPv6 {false};
    };
}