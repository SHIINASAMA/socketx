#include "socket.hpp"

bool Socket::isStartup = false;

void Socket::startup()
{
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);
}

Socket::Socket()
{
}

Socket::Socket(SocketMode mode, char *ipaddr, ushort port)
{
    if (!isStartup)
    {
        startup();
    }

    this->sock = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    this->addr.sin_family = AF_INET;
    this->addr.sin_addr.s_addr = inet_addr(ipaddr);
    this->addr.sin_port = htons(port);

    if (mode == SocketMode::Server)
    {
        bind(this->sock, (SOCKADDR *)&this->addr, sizeof(SOCKADDR));
        listen(this->sock, 20);
    }
    else
    {
        //mode is SocketMode::Client
        connect(this->sock, (SOCKADDR *)&this->addr, sizeof(SOCKADDR));
    }
}

int Socket::Read(char *buffer, int size)
{
    return recv(this->sock, buffer, size, NULL);
}

int Socket::Write(char *buffer, int size)
{
    return send(this->sock, buffer, size, NULL);
}

Socket Socket::Accept()
{
    Socket res;
    int len = sizeof(SOCKADDR);
    res.sock = accept(this->sock, (SOCKADDR *)&res.addr, &len);
    return res;
}