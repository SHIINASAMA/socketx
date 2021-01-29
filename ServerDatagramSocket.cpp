#include "ServerDatagramSocket.hpp"

ServerDatagramSocket::ServerDatagramSocket(unsigned short port)
    : DatagramSocket(SocketMode::Server, "0.0.0.0", port)
{
}