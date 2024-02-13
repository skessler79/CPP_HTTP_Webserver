#include <cstring>
#include <arpa/inet.h>

#include "InetAddress.hpp"

utils::InetAddress::InetAddress(const uint16_t port, bool isIPv6)
    : m_isIPv6(isIPv6)
{
    std::memset(&m_Addr, 0, sizeof(m_Addr));

    if(isIPv6)
    {
        // IPv6
        struct sockaddr_in6 addr6 {};
        addr6.sin6_family = AF_INET6;
        addr6.sin6_addr = in6addr_any;
        addr6.sin6_port = htons(port);
        m_Addr = addr6;
    }
    else
    {
        // IPv4
        struct sockaddr_in addr {};
        addr.sin_family = AF_INET;
        addr.sin_addr.s_addr = INADDR_ANY;
        addr.sin_port = htons(port);
        m_Addr = addr;
    }
}

// TODO : Finish this
utils::InetAddress::InetAddress(const std::string& ip, const uint16_t port, bool isIPv6)
    : m_isIPv6(isIPv6)
{

}

const sockaddr* utils::InetAddress::getSockAddr() const
{
    return std::visit([](auto&& arg) -> const sockaddr*
    {
        return reinterpret_cast<const sockaddr*>(&arg);
    }, m_Addr);
}

const socklen_t utils::InetAddress::getSocklen() const
{
    if(m_isIPv6)
        return sizeof(sockaddr_in6);
    return sizeof(sockaddr_in);
}