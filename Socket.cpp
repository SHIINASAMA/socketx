#include "Socket.hpp"

#ifdef _WIN32
int Socket::count = 0;

int Socket::startup()
{
    WSADATA wsaData;
    return WSAStartup(MAKEWORD(2, 2), &wsaData);
}

Socket::Socket()
{
    if (Socket::count == 0 && Socket::startup() != 0)
    {
        return;
    }
    Socket::count++;
}

Socket::Socket(SocketMode mode, char *ipaddr, unsigned short port)
{
    if (Socket::count == 0 && Socket::startup() != 0)
    {
        return;
    }
    Socket::count++;

    this->sock = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    this->sin.sin_family = AF_INET;
    this->sin.sin_addr.s_addr = inet_addr(ipaddr);
    this->sin.sin_port = htons(port);

    if (mode == SocketMode::Server)
    {
        bind(this->sock, (SOCKADDR *)&this->sin, sizeof(SOCKADDR));
    }
}

int Socket::Listen(int backlog)
{
    return listen(this->sock, backlog);
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
    res.sock = accept(this->sock, (SOCKADDR *)&res.sin, &len);
    return res;
}

int Socket::Connect()
{
    return connect(this->sock, (SOCKADDR *)&this->sin, sizeof(SOCKADDR));
}

int Socket::Shutdown(ShutdownMode mode)
{
    return shutdown(this->sock, (int)mode);
}

int Socket::Close()
{
    Socket::count--;
    return closesocket(this->sock);
}
#endif

#ifdef __linux__
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
    }
}

Socket Socket::Accept()
{
    Socket res;
    socklen_t len = sizeof(sockaddr);
    res.sock = accept(this->sock, (sockaddr *)&res.sin, &len);
    return res;
}

int Socket::Listen(int backlog)
{
    return listen(this->sock, backlog);
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
    return shutdown(this->sock, (int)mode);
}

int Socket::Close()
{
    return close(this->sock);
}
#endif