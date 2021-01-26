#include "typedef.hpp"

enum class SocketMode
{
    Client = 0,
    Server = 1
};

#ifdef _WIN32
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")

class Socket
{
private:
    static int count;
    static int startup();
    SOCKET sock;
    sockaddr_in addr;

public:
    Socket();
    Socket(SocketMode mode, char *ipaddr, ushort port);
    Socket Accept();
    int Read(char *buffer, int size);
    int Write(char *buffer, int size);
    void Close();
};

#elif __linux__
#include "typedef.hpp"
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
class Socket
{
private:
    int sock;
    sockaddr_in addr{0};

public:
    Socket();
    Socket(SocketMode mode, char *ipaddr, ushort port);
    Socket Accept();
    int Read(char *buffer, int size);
    int Write(char *buffer, int size);
    void Close();
};
#endif