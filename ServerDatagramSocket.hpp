#include "DatagramSocket.hpp"

class ServerDatagramSocket : public DatagramSocket
{
public:
    ServerDatagramSocket(unsigned short port);
};