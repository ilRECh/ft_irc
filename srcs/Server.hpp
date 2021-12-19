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
#include <thread>
#include <mutex>

using	std::string;
using	std::vector;
using   std::cout;
using   std::endl;
using	std::thread;
using	std::mutex;


#define SIZE 256
typedef struct	s_account{
	string		_name;
	string		_password;
	int			_fd;
}	t_account;

class Server
{
private:
	bool				loop_listen;
    thread              thread_listener;
	mutex				mutex_vector;
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
