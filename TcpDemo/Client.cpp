#include "../Socket.hpp"
#include <stdio.h>

int main()
{
    auto client = new Socket(SocketMode::Client,"127.0.0.1",9977);
    client->Connect();
    char buffer[128];
    int len = client->Read(buffer,sizeof(buffer));
    client->Close();
    delete client;
    printf("size of revced bytes:%d\nmessage:%s\n",len,buffer);
    return 0;
}