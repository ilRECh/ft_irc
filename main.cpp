#include "default.hpp"
#include "Server.hpp"
#include "User.hpp"
#include "Password.hpp"
#include <iostream>
#include <string>

using std::cout;
using std::endl;

int main(int ac, char **av)
{
	(void)av;
	(void)ac;
	std::string ipAddres, sPort;

	if (ac > 1){
		sPort = av[2];
		ipAddres = av[1];
	}else{
		ipAddres = "127.0.0.1";
		sPort = "2224";
	}
	Server server(ipAddres, sPort);
	try{
	    server.run();
	}catch(std::exception & e){
	    cout << e.what() << endl;
	}
}