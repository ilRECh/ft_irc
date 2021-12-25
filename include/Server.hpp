#pragma once

#include <stdlib.h>
#include <string.h>
#include "default.hpp"
#include <sys/select.h>
#include <sys/time.h>
#include <netdb.h>
#include "ExceptionUni.hpp"

struct	s_account {
	std::string	_Name;
	std::string	_Password;
    struct sockaddr_in _SaddrClient;
    socklen_t _Socklen;
	int	_Fd;
};

class Server {
private:
	std::string	ip;
	std::string	port;
    bool	_LoopListen;
    std::vector<s_account> _Accounts;
	struct addrinfo *servinfo;
    // struct sockaddr_in _Saddr;
    socklen_t _Socklen;
    int _Sockfd;
    char _Buf[SIZE];

	fd_set	fds;
	int		maxFd;

	void readerClient(fd_set);
public:
	Server(std::string const & ip, std::string const & port);
	~Server();
	void run();
};
