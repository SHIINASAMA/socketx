#include "../ServerDatagramSocket.hpp"
#include <stdio.h>

int main()
{
    auto server = new ServerDatagramSocket(9977);
    char buffer[128];
    int len;
    while (1)
    {
        len = server->Read(buffer, sizeof(buffer));
        if (len != -1)
        {   
            printf("message %d:%s\n", len, buffer);
            int len = server->Write("Hello,this is server.",128);
            printf("size of sended byte:%d\n",len);
            break;
        }
    }
    server->Close();
    delete server;
    return 0;
}