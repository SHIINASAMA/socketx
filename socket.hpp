#include "typedef.hpp"
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")

enum class SocketMode
{
    Client = 0,
    Server = 1
};

class Socket
{
    static bool isStartup;
    static void startup();

    SOCKET sock;
    sockaddr_in addr;

public:
    Socket();
    Socket(SocketMode mode, char *ipaddr, ushort port);
    Socket Accept();
    int Read(char *buffer, int size);
    int Write(char *buffer, int size);
};