#include "socket.hpp"
#include "stdio.h"

int main()
{
    Socket *client = new Socket(SocketMode::Client, "127.0.0.1", 9977);

    char buffer[128];
    int len = client->Read(buffer, sizeof(buffer));
    printf("recv message%d:%s\n", len, buffer);
    client->Close();
    return 0;
}