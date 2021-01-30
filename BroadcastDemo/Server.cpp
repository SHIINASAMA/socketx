#include "../Broadcast.hpp"
#include <stdio.h>

int main()
{
    auto server = new Broadcast(SocketMode::Server, 9977);
    while (1)
    {
        int len = server->Write("Hello,this is server.", 128);
        printf("size of sended bytes:%d\n\n",len);
        Sleep(2000);
    }
    delete server;
    return 0;
}