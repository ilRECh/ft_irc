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
	Server server("127.0.0.1", 1112);
	try
	{
	    server.run();
	}
	catch(std::exception & e)
	{
	    cout << e.what() << endl;
	}
}