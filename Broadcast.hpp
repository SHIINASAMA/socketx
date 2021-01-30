#include "Socket.hpp"

class Broadcast :  Socket
{
public:
    Broadcast(SocketMode mode, unsigned short port);
    int Write(char *buffer, int size);
    int Read(char *buffer, int size);
    int Close();
};