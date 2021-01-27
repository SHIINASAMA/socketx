#include "socket.hpp"

#ifdef _WIN32
int Socket::count = 0;

int Socket::startup()
{
    WSADATA wsaData;
    return WSAStartup(MAKEWORD(2, 2), &wsaData);
}

Socket::Socket()
{
}

Socket::Socket(SocketMode mode, char *ipaddr, ushort port,TransferProtocol protocol = TransferProtocol::TCP)
{
    if (Socket::count == 0 && Socket::startup() != 0)
    {
        return;
    }
    Socket::count++;

    this->sock = ::socket(AF_INET, SOCK_STREAM, (int)protocol);
    this->addr.sin_family = AF_INET;
    this->addr.sin_addr.s_addr = inet_addr(ipaddr);
    this->addr.sin_port = htons(port);

    if (mode == SocketMode::Server)
    {
        bind(this->sock, (SOCKADDR *)&this->addr, sizeof(SOCKADDR));
        listen(this->sock, 20);
    }
}

Socket::~Socket()
{
    if (Socket::count == 0)
    {
        WSACleanup();
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

int Socket::Connect()
{
    return connect(this->sock, (SOCKADDR *)&this->addr, sizeof(SOCKADDR));
}

int Socket::Shutdown(ShutdownMode mode)
{
    return shutdown(this->sock, (int)mode);
}

void Socket::Close()
{
    closesocket(this->sock);
    Socket::count--;
}
#elif __linux__
Socket::Socket()
{
}

Socket::Socket(SocketMode mode, char *ipaddr, ushort port)
{
    this->sock = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    this->addr.sin_family = AF_INET;
    this->addr.sin_addr.s_addr = inet_addr(ipaddr);
    this->addr.sin_port = htons(port);

    if (mode == SocketMode::Server)
    {
        bind(this->sock, (sockaddr *)&this->addr, sizeof(sockaddr));
        listen(sock, 20);
    }
}

Socket Socket::Accept()
{
    Socket res;
    socklen_t len = sizeof(sockaddr);
    res.sock = accept(this->sock, (sockaddr *)&res.addr, &len);
    return res;
}

int Socket::Connect()
{
    return connect(this->sock, (sockaddr *)&this->addr, sizeof(sockaddr));
}

int Socket::Read(char *buffer, int size)
{
    return read(this->sock, buffer, size);
}

int Socket::Write(char *buffer, int size)
{
    return write(this->sock, buffer, size);
}

int Socket::Shutdown(ShutdownMode mode)
{
    return shutdown(this->sock,(int)mode);
}

void Socket::Close()
{
    close(this->sock);
}
#endif