#pragma once
#include <iostream>
#include <vector>
#include <iostream>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "Client.hpp"

using	std::string;
using	std::vector;
using   std::cout;
using   std::endl;

class Server
{
private:
	int		port;
	int		domain;
	string	ip_addres;
	vector<int>			fd_servs;
	vector<Client>  	clients;		
	//struct sockaddr_in	soketaddr;
public:
	Server(const string & ip_addres, const int port, const int domain);
	~Server();
	void    addClient( void );
	bool    binding( void );
	class sExcept: public std::exception{
		string  reason;
	public:
		sExcept(const string reason);
		~sExcept( void );
		const char * what( void ) const throw();
	};
};
