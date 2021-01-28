#include "Socket.hpp"

class ServerSocket : public Socket
{
public:
    ServerSocket(unsigned short port, int backlog);
};