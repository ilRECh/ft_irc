#pragma once

#include "default.hpp"

#define SIZE 256
struct	s_account{
	std::string	_Name;
	std::string	_Password;
	int			_fd;
};

class Server
{
private:
	bool				loop_listen;
	string				ip_str;
	vector<t_account>	accounts;
	struct sockaddr_in	saddr;
	socklen_t			socklen;
    int                 sockfd;
    char                buf[SIZE];
    //int                 port;
public:
	Server(const string & ip_addres, const int port);
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
