#include "Server.hpp"
#include <iostream>

void usage() {
	std::cout << "\n\tUsage: ./ircserv <port> <password>\n" << std::endl;
}

int main(int argc, char **argv) {
#ifndef GODMODE
	if (argc not_eq 3) {
		usage();
		return 1;
	}
#else
	(void)argc;
#endif
	try {
		Server server(argv[1] ? argv[1] : "6668", argv[2] ? argv[2] : "123");
		server.run();
	} catch(std::exception& e) {
		std::cout << e.what() << std::endl;
	} catch(...) {
		std::cout << "Unexpected error" << std::endl;
	}
	return 0;
}
