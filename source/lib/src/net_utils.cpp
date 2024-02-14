#include <string>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "net_utils.hpp"

std::string utils::getAddressString(const sockaddr* sockAddr)
{
    // TODO : Use string over char array
    // TODO : Try to remove the use of reinterpret_cast
    // TODO : Try to use smart pointers instead of raw pointers

    char ipstr[INET6_ADDRSTRLEN];

    if(sockAddr->sa_family == AF_INET)
    {
        // IPv4
        const sockaddr_in* addr_in = reinterpret_cast<const sockaddr_in*>(sockAddr);
        inet_ntop(AF_INET, &(addr_in->sin_addr), ipstr, sizeof(ipstr));
    }
    else
    {
        // IPv6
        const sockaddr_in6* addr_in6 = reinterpret_cast<const sockaddr_in6*>(sockAddr);
        inet_ntop(AF_INET6, &(addr_in6->sin6_addr), ipstr, sizeof(ipstr));
    }

    return std::string(ipstr);
}
