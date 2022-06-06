#include <iostream>
#include "GameServer.h"
#include "ParseTools.h"

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        std::cerr << "Usage: " << argv[0] << " <address> <port>\n";
        return 1;
    }

    // Check address format
    if (!ParseTool::is_address(argv[1]))
    {
        std::cerr << "Invalid address format.\n";
        return 1;
    }

    // Check port format
    uint32_t port = ParseTool::is_number(argv[2]) ? std::stoi(argv[2]) : -1;

    if (port < 0 || port > 65535)
    {
        std::cerr << "Invalid port number.\n";
        return 1;
    }

    std::cout << "Server Init" << std::endl;
    GameServer server(argv[1], argv[2]);
    server.run();
    return 0;
}