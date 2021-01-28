#include "Socketx.hpp"

#ifdef _WIN32
int Socketx::count = 0;

int Socketx::startup()
{
    WSADATA wsaData;
    return WSAStartup(MAKEWORD(2, 2), &wsaData);
}

Socketx::Socketx()
{
}

Socketx::Socketx(SocketMode mode, char *ipaddr, ushort port)
{
    if (Socketx::count == 0 && Socketx::startup() != 0)
    {
        return;
    }
    Socketx::count++;

    this->sock = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    this->sin.sin_family = AF_INET;
    this->sin.sin_addr.s_addr = inet_addr(ipaddr);
    this->sin.sin_port = htons(port);

    if (mode == SocketMode::Server)
    {
        bind(this->sock, (SOCKADDR *)&this->sin, sizeof(SOCKADDR));
        listen(this->sock, 20);
    }
}

Socketx::~Socketx()
{
    if (Socketx::count == 0)
    {
        WSACleanup();
    }
}

int Socketx::Read(char *buffer, int size)
{
    return recv(this->sock, buffer, size, NULL);
}

int Socketx::Write(char *buffer, int size)
{
    return send(this->sock, buffer, size, NULL);
}

Socketx Socketx::Accept()
{
    Socketx res;
    int len = sizeof(SOCKADDR);
    res.sock = accept(this->sock, (SOCKADDR *)&res.sin, &len);
    return res;
}

int Socketx::Connect()
{
    return connect(this->sock, (SOCKADDR *)&this->sin, sizeof(SOCKADDR));
}

int Socketx::Shutdown(ShutdownMode mode)
{
    return shutdown(this->sock, (int)mode);
}

int Socketx::Close()
{
    Socketx::count--;
    return closesocket(this->sock);
}
#elif __linux__
Socket::Socket()
{
}

Socket::Socket(SocketMode mode, char *ipaddr, ushort port)
{
    this->sock = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    this->sin.sin_family = AF_INET;
    this->sin.sin_addr.s_addr = inet_addr(ipaddr);
    this->sin.sin_port = htons(port);

    if (mode == SocketMode::Server)
    {
        bind(this->sock, (sockaddr *)&this->sin, sizeof(sockaddr));
        listen(sock, 20);
    }
}

Socket Socket::Accept()
{
    Socket res;
    socklen_t len = sizeof(sockaddr);
    res.sock = accept(this->sock, (sockaddr *)&res.sin, &len);
    return res;
}

int Socket::Connect()
{
    return connect(this->sock, (sockaddr *)&this->sin, sizeof(sockaddr));
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