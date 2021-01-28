#include "Socket.hpp"

enum class SocketMode
{
    Client = 0,
    Server = 1
};

enum class ShutdownMode{
    Read = 0,
    Write = 1,
    WriteAndRead = 2
};

#ifdef _WIN32
class Socketx : public Socket
{
private:
    static int count;
    static int startup();
    SOCKET sock;
    sockaddr_in addr;

public:
    Socketx();
    Socketx(SocketMode mode, char *ipaddr, ushort port);
    ~Socketx();
    Socketx Accept();
    int Connect();
    int Read(char *buffer, int size);
    int Write(char *buffer, int size);
    int Shutdown(ShutdownMode mode);
    int Close();
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
    int Connect();
    int Read(char *buffer, int size);
    int Write(char *buffer, int size);
    int Shutdown(ShutdownMode mode);
    void Close();
};
#endif