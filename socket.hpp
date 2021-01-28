#include "typedef.hpp"
#ifdef _WIN32
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")
typedef SOCKET sock;
#elif __linux__
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
typedef int sock;
#endif

class Socket
{
protected:
    sock sock;
    sockaddr_in sin;

public:
    virtual int Read(char *buffer, int size) = 0;
    virtual int Write(char *buffer, int size) = 0;
    virtual int Close() = 0;
};