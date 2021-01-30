#include "../Broadcast.hpp"
#include <stdio.h>

int main()
{
    auto server = new Broadcast(SocketMode::Server, 9977);
    while (1)
    {
        int len = server->Write("Hello,this is server.", 128);
        printf("size of sended bytes:%d\n\n",len);
        #ifdef _WIN32
        Sleep(2000);
        #elif __linux__
        sleep(2);
        #endif
    }
    delete server;
    return 0;
}