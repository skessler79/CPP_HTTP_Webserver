#pragma once

#include "lib/include/Socket.hpp"

namespace server
{
    class HttpServer
    {
    public:
        HttpServer(const utils::InetAddress& inetAddress);

        void start();
        // TODO : stop

        // TODO : Handle sigkill, sigterm etc?

    private:
        utils::InetAddress m_InetAddress;
        utils::Socket m_Socket;
    };
}