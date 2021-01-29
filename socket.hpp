enum class SocketMode
{
    Server,
    Client
};

enum class ShutdownMode
{
    Read,
    Write,
    Both
};

#ifdef _WIN32
#include <WinSock2.h>
#pragma comment(lib, "ws2_32.lib")
class Socket
{
private:
    static int count;
    static int startup();

protected:
    SOCKET sock;
    SOCKADDR_IN sin;

public:
    Socket();
    Socket(SocketMode mode, char *ipaddr, unsigned short port);
    ~Socket();
    Socket Accept();
    int Listen(int backlog);
    int Connect();
    int Write(char *buffer, int size);
    int Read(char *buffer, int size);
    int Shutdown(ShutdownMode mode);
    int Close();
};
#endif

#ifdef __linux__
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
    Socket(SocketMode mode, char *ipaddr, unsigned short port);
    Socket Accept();
    int Connect();
    int Read(char *buffer, int size);
    int Write(char *buffer, int size);
    int Shutdown(ShutdownMode mode);
    void Close();
};
#endif