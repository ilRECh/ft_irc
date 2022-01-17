#include "Mandatory.hpp"
#include "Server.hpp"
#include "User.hpp"
#include "Password.hpp"
#include "TimeStamp.hpp"

using std::cout;
using std::endl;

void usage() {
	std::cout << "\n\tUsage: ./ircserv [host:port_network:password_network] <port> <password>\n" << std::endl;
}

int main(int argc, char **argv) {
	// if (argc != HOST_PORTNETWORK_PASSWORDNETWORK_PORT_PASSWORD && argc != PORT_PASSWORD) {
	// 	usage();
	// 	return 1;
	// }
	{
		// test TimeStamp
		(void) argc;
		(void) argv;
		TimeStamp time;
		#include <unistd.h>
		while (!time.hasTimePassed(3)) {
			std::cout << time.getTimeStrCurrent() << std::endl;
			sleep(1);
		}
		exit(0);
	}
	try {
		std::vector<std::string> settings(argv + 1 /*skipping name*/, argv + argc /*past-the-last argument*/);
		// Server server(settings);
		Server server("127.0.0.1", argv[1] ? argv[1] : "2224");

	    server.run();
	} catch(std::exception& e) {
	    cout << e.what() << endl;
	} catch(...) {
		cout << "Unexpected error" << endl;
	}
	return 0;
}
