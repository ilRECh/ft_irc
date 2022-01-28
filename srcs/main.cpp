#include "ft.hpp"
#include "Server.hpp"
#include "Client.hpp"

#include "Password.hpp"
#include "TimeStamp.hpp"

#include <iostream>
using std::cout;
using std::endl;

void usage() {
	std::cout << "\n\tUsage: ./ircserv <port> <password>\n" << std::endl;
}

int main(int argc, char **argv) {
	(void)argc;
	// if (argc != 3) {
	// 	usage();
	// 	return 1;
	// }
	try {
		Server server(argv[1] ? argv[1] : "2224", argv[2] ? argv[2] : "123");
		server.run();
	} catch(std::exception& e) {
		cout << e.what() << endl;
	} catch(...) {
		cout << "Unexpected error" << endl;
	}
	return 0;
}
