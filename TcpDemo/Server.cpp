#include "../ServerSocket.hpp"
#include <stdio.h>

int main()
{
    auto server = new ServerSocket(9977, 10);
    auto client = server->Accept();
    char buffer[128] = {"Hello,this is server."};
    int len = client.Write(buffer, sizeof(buffer));
    client.Close();
    server->Close();
    delete server;
    printf("size of sended bytes:%d\n", len);
    return 0;
}