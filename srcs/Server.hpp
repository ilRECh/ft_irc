#pragma once
#include <iostream>
#include <vector>
#include <iostream>
#include <fcntl.h>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

using	std::string;
using	std::vector;
using   std::cout;
using   std::endl;

typedef struct	s_account{
	string		_name;
	string		_password;
	int			_fd;
}	t_account;

class Server
{
private:
	string				_ip_addres;
	vector<t_account>	_accounts;
	struct sockaddr_in	_server_addres;
	socklen_t			socklen;
	bool	create_connect_to_client();
public:
	Server(const string & ip_addres, const int port, const int domain);
	~Server();
	void	run();
	class sExcept: public std::exception{
		string  reason;
	public:
		sExcept(const string reason);
		virtual ~sExcept( void ) throw();
		const char * what( void ) const throw();
	};
};
