#include "ft.hpp"
#include "Server.hpp"
#include "Client.hpp"

#include "Password.hpp"
#include "TimeStamp.hpp"

#include <iostream>
using std::cout;
using std::endl;

void usage() {
	std::cout << "\n\tUsage: ./ircserv [host:port_network:password_network] <port> <password>\n" << std::endl;
}

void	tester(std::string needle, std::string haystack){
	std::cout << "  needle = |" << needle << "|" << std::endl;
	std::cout << "haystack = |" << haystack << "|" << std::endl;
	if (ft::compareSimpleWildcard(needle, haystack))
		cout << "true" << endl;
	else
		cout << "false" << endl;
	cout << "__________________________________________" << endl;
}

int main(int argc, char **argv) {

	tester("* bro *", "blabla bro blabla bro");	//true
	tester("* bro", "blabla bro blaaabla bro");	//true
	tester("*_bro", "blabla bro blaaabla bro");	//false
	tester("bro", "blabla bro blaaaaabla bro");	//false
	tester(  "a", "a aa aaa aaaa");	//false
	tester("*a*", "a aa aaa aaaa");	//true
	tester("*ab*", "a aa aaa aaaa");	//true
	tester("*ba*", "a aa aaa aaaa");	//true
	tester( "*a", "a aa aaa aaaa");	//true
	tester( "a*a", "ba aa aaa aaaa");	//true
	tester( "a*", "a aa aaa aaaa");	//true
	exit(0);


	// if (argc != HOST_PORTNETWORK_PASSWORDNETWORK_PORT_PASSWORD
	// 	|| argc != PORT_PASSWORD) {
	// 	usage();
	// 	return 1;
	// }
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
