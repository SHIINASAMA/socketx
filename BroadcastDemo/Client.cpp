#include "../Broadcast.hpp"
#include "stdio.h"

int main()
{
    auto client = new Broadcast(SocketMode::Client, 9977);
    char buffer[128];
    while (1)
    {
        int len = client->Read(buffer, 128);
        printf("size of recved bytes:%d\nmessage:%s\n\n",len,buffer);
    }
    delete client;
    return 0;
}