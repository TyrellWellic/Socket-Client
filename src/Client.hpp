#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdint>
#include <cctype>

#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <getopt.h>

using namespace std;

class TcpClient {
public:
	TcpClient(int Port);
	~TcpClient();
	void Start();
private:
	int m_Port;
	int hsock;
	uint16_t avail_bytes;
};

class UdpClient {
public:
	UdpClient(int Port);
	~UdpClient();
	void Start();
private:
	int m_Port;
	int hsock;
	uint16_t avail_bytes;
};
