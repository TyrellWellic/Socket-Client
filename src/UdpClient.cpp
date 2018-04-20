#include "Client.hpp"

UdpClient::UdpClient (int Port) {
	m_Port = Port;
	avail_bytes = 0;
}

UdpClient::~UdpClient() {

}

void UdpClient::Start() {
	struct sockaddr_in my_addr;
	string str;
	char buf[1024];

	hsock = socket(AF_INET, SOCK_DGRAM, 0);
	if (hsock == -1) {
		cerr << "Error initializing UDP client socket" << endl;
		exit(1);
	}

	memset(&my_addr, 0, sizeof(my_addr));
	my_addr.sin_family = AF_INET;
	my_addr.sin_port = htons(m_Port);
	my_addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

	while(true) {
		cin >> str;
		if (str.length() > 65536) {
			cerr << "Error. Packet is over 64kb" << endl;
		}
		else {
			sendto(hsock, str.c_str(), str.length(), 0, (struct sockaddr*)&my_addr, sizeof(my_addr));
			avail_bytes = recvfrom(hsock, buf, 1024, 0, NULL, NULL);
			string s(buf, avail_bytes);
			cout << s << endl;
		}
	}

	shutdown(hsock, SHUT_RDWR);
	close(hsock);
}

