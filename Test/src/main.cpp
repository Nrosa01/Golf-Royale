#include <iostream>
#include "Client.h"

int main(int argc, char **argv)
{
    if(argc != 3)
    {
        std::cerr << "Usage: " << argv[0] << " <address> <port>\n";
        return 1;
    }
    
    Client client(argv[1], argv[2]);
    //client.login();
    //client.logout();
    client.test();
    return 0;
}