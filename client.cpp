#include "socket.hpp"
#include "stdio.h"

int main()
{
    char buffer[128];
    int len;
    {
        Socket *client = new Socket(SocketMode::Client, "127.0.0.1", 9977);
        client->Connect();
        len = client->Read(buffer, sizeof(buffer));
        client->Close();
    }
    printf("recv message%d:%s\n", len, buffer);
    return 0;
}