
#include "..\Socketx.hpp"
#include <stdio.h>

int main()
{
    Socketx *client = new Socketx(SocketMode::Client, "127.0.0.1", 9977);
    client->Connect();

    char buffer[128];
    int len = client->Read(buffer, sizeof(buffer));
    client->Close();
    delete client;

    printf("recv message%d:%s\n", len, buffer);
    return 0;
}