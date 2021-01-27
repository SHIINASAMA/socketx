#include "socket.hpp"

int main(){
    Socket* socket = new Socket(SocketMode::Server,"0.0.0.0",9977);
    Socket client = socket->Accept();

    char buffer[128] = {"Hello,This is server!"};
    int len = client.Write(buffer,sizeof(buffer));
    printf("Message sended!%d\n",len);
    socket->Close();
    return 0;
}