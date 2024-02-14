#pragma once

#include <string>
#include <netinet/in.h>
#include <arpa/inet.h>

namespace utils
{
    std::string getAddressString(const sockaddr* sockAddr);
} // namespace utils