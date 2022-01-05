#include "Mandatory.hpp"
#include "Server.hpp"
#include "User.hpp"
#include "Password.hpp"

using std::cout;
using std::endl;

void usage() {
	std::cout << "\n\tUsage: ./ircserv [host:port_network:password_network] <port> <password>\n\n" << std::endl;
}

int main(int argc, char **argv) {
	if (argc != HOST_PORTNETWORK_PASSWORDNETWORK_PORT_PASSWORD || argc != PORT_PASSWORD) {
		usage();
		return 1;
	}
	try {
		std::vector<std::string> settings(argv + 1 /*skipping name*/, argv + argc /*past-the-last argument*/);
		Server server(settings);

	    server.run();
	} catch(std::exception& e) {
	    cout << e.what() << endl;
	} catch(...) {
		cout << "Unexpected error" << endl;
	}
	return 0;
}
