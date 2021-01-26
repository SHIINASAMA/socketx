#include "socket.hpp"
#include "stdio.h"

int main(){
    Socket* client = new Socket(SocketMode::Client,"127.0.0.1",9977);
    
    char buffer[128];
    client->Read(buffer,sizeof(buffer));
    printf("recv message:%s\n",buffer);
    return 0;
}