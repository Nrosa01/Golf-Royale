#include <iostream>
#include "GameServer.h"

int main(int argc, char **argv)
{
    if(argc != 3)
    {
        std::cerr << "Usage: " << argv[0] << " <address> <port>\n";
        return 1;
    }
    
    std::cout << "Server Init" << std::endl;
    GameServer server(argv[1], argv[2]);
    server.run();
    return 0;
}