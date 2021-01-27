#include "socket.hpp"
#include <stdio.h>

int main()
{
    Socket *socket = new Socket(SocketMode::Server, "0.0.0.0", 9977);
    Socket client = socket->Accept();

    char buffer[128] = {"Hello,This is server!"};
    int len = client.Write(buffer, sizeof(buffer));
    client.Close();
    socket->Close();
    delete socket;

    printf("Message sended!%d\n", len);
    return 0;
}