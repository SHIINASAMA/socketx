#include "ServerSocket.hpp"

ServerSocket::ServerSocket(unsigned short port, int backlog)
    : Socket(SocketMode::Server, "0.0.0.0", port)
{
    this->Listen(backlog);
}