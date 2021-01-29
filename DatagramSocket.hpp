#include "Socket.hpp"

class DatagramSocket : Socket
{
public:
    DatagramSocket(SocketMode mode, char *ipaddr, unsigned short port);
    int Write(char *buffer, int size);
    int Read(char *buffer, int size);
    int Close();
};