#pragma once

#include <cstdint>

namespace config
{
    // Port number
    constexpr uint16_t SK_PORT = 8080;

    // Http request buffer size in bytes
    constexpr uint32_t SK_HTTP_REQUEST_BUFFER_SIZE = 4096;

    // File cache capacity
    constexpr uint32_t SK_FILE_CACHE_CAPACITY = 20;

    // Maximum connection requests on socket listening queue
    constexpr int SK_SOCK_MAX_QUEUE = 1024;
}