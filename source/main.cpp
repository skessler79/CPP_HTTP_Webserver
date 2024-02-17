#include "Config.hpp"
#include "lib/include/InetAddress.hpp"
#include "server/include/HttpServer.hpp"

int main(int argc, char** argv)
{
    utils::InetAddress inetAddress(config::SK_PORT, false);
    server::HttpServer httpServer(inetAddress);
    httpServer.start();
}
