#include "..\DatagramSocket.hpp"
#include <stdio.h>

int main()
{
    auto client = new DatagramSocket(SocketMode::Client, "127.0.0.1", 9977);
    char buffer[128] = {"Hello,this is client."};
    int len = client->Write(buffer, sizeof(buffer));
    printf("size of sended byte:%d\n", len);
    len = client->Read(buffer, sizeof(buffer));
    printf("message %d:%s\n", len, buffer);
    client->Close();
    delete client;
    return 0;
}