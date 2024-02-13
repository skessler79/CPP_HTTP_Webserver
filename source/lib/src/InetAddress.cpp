#include <cstring>
#include <arpa/inet.h>

#include <InetAddress.hpp>

utils::InetAddress::InetAddress(const uint16_t port, bool ipv6 = false)
    : isIPv6(ipv6)
{
    if(ipv6)
    {
        // IPv6
        std::memset(&m_Addr6, 0, sizeof(m_Addr6));
        m_Addr6.sin6_family = AF_INET6;
        m_Addr6.sin6_addr = in6addr_any;            // TODO : Can maybe adjust this to use loopback also
        m_Addr6.sin6_port = htons(port);
    }
    else
    {
        // IPv4
        std::memset(&m_Addr, 0, sizeof(m_Addr));
        m_Addr.sin_family = AF_INET;
        m_Addr.sin_addr.s_addr = INADDR_ANY;        // TODO : Can maybe adjust this to use loopback also
        m_Addr.sin_port = htons(port);
    }
}

utils::InetAddress::InetAddress(const std::string& ip, const uint16_t port, bool ipv6 = false)
    : isIPv6(ipv6)
{
    if(ipv6)
    {
        // IPv6
        std::memset(&m_Addr6, 0, sizeof(m_Addr6));
        m_Addr.sin_family = AF_INET6;
        m_Addr.sin_port = htons(port);
        inet_pton(AF_INET6, ip.c_str(), &m_Addr6.sin6_addr);
    }
    else
    {
        // IPv4
        std::memset(&m_Addr, 0, sizeof(m_Addr));
        m_Addr.sin_family = AF_INET;
        m_Addr.sin_port = htons(port);
        inet_pton(AF_INET, ip.c_str(), &m_Addr.sin_addr);
    }
}