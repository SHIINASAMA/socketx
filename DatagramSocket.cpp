#include "DatagramSocket.hpp"

DatagramSocket::DatagramSocket(SocketMode mode, char *ipaddr, unsigned short port)
    : Socket()
{
    this->sock = ::socket(AF_INET, SOCK_DGRAM, 0);
    this->sin.sin_family = AF_INET;
    this->sin.sin_addr.S_un.S_addr = inet_addr(ipaddr);
    this->sin.sin_port = htons(port);
    if (mode == SocketMode::Server)
    {
        bind(this->sock, (sockaddr *)&this->sin, sizeof(sockaddr));
    }
}

int DatagramSocket::Write(char *buffer, int size)
{
    return sendto(this->sock, buffer, size, 0, (sockaddr *)&this->sin, sizeof(sockaddr));
}

int DatagramSocket::Read(char *buffer, int size)
{
    int len = sizeof(sockaddr);
    return recvfrom(this->sock, buffer, size, 0, (sockaddr *)&this->sin, &len);
}

int DatagramSocket::Close()
{
    return closesocket(this->sock);
}