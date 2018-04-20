#include "Client.hpp"

TcpClient::TcpClient (int Port) {
	m_Port = Port;
	avail_bytes = 0;
}

TcpClient::~TcpClient() {

}

void TcpClient::Start() {
	struct sockaddr_in my_addr;
	string str;
	char buf[1024];

	hsock = socket(AF_INET, SOCK_STREAM, 0);
	if (hsock == -1) {
		cerr << "Error initializing TCP client socket" << endl;
	}

	memset(&my_addr, 0, sizeof(my_addr));
	my_addr.sin_family = AF_INET;
	my_addr.sin_port = htons(m_Port);
	my_addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

	if (connect(hsock, (sockaddr*)&my_addr, sizeof(my_addr)) == -1) {
		cerr << "Error connecting to TCP server socket" << endl;
	}

	while(true) {
		cin >> str;
		if (str.length() > 65536) {
			cerr << "Error. Packet is over 64kb" << endl;
		}
		else {
			send(hsock, str.c_str(), str.length(), 0);
			avail_bytes = recv(hsock, buf, 1024, 0);
			string s(buf, avail_bytes);
			cout << s << endl;
		}
	}

	shutdown(hsock, SHUT_RDWR);
	close(hsock);
}
