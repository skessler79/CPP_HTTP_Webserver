#pragma once

#include <cstdint>

namespace config
{
    // Port number
    constexpr uint16_t SK_PORT = 8080;

    // File cache capacity
    constexpr uint32_t SK_FILE_CACHE_CAPACITY = 20;

    // Maximum connection requests on socket listening queue
    constexpr int SK_SOCK_MAX_QUEUE = 1024;
}