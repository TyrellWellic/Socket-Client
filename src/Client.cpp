#include "Client.hpp"

#define tcp_port 5555
#define udp_port 5556

bool tcp = false;
bool udp = false;

void printHelp (void) {
	cout << __DATE__ << " " << __TIME__ <<
			"\n-h: print this help and exit"
			"\n-t: TCP protocol"
			"\n-u: UDP protocol"
			<< endl;
}

int ParseCmdLine(int argc, char **argv) {
	const char *cArgList = "htu";
	int c;

	if (argc < 2) {
		printHelp();
		return -1;
	}
	while ((c = getopt(argc, argv, cArgList)) != -1) {
		switch(c) {
		case 'h':
			printHelp();
			return -1;
		case 't':
			tcp = true;
			break;
		case 'u':
			udp = true;
			break;
		}
	}
	if (tcp && udp) {
		cout << "Bad arguments" << endl;
		printHelp();
		return -1;
	}

	return 0;
}

int main(int argc, char *argv[]) {
	if (ParseCmdLine(argc, argv) < 0) {
		return 0;
	}
	if (tcp) {
		TcpClient tcp_client(tcp_port);
		tcp_client.Start();
	}
	else {
		UdpClient udp_client(udp_port);
		udp_client.Start();
	}

	return 0;
}
