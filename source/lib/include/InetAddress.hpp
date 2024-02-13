#include <netinet/in.h>
#include <string>

namespace utils
{
    class InetAddress
    {
    public:

        InetAddress(const uint16_t port, bool ipv6 = false);
        InetAddress(const std::string& ip, const uint16_t port, bool ipv6 = false);

    private:
        union
        {
            struct sockaddr_in m_Addr;
            struct sockaddr_in6 m_Addr6;
        };

        bool isIPv6 {false};
    };
}