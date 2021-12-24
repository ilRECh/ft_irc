#pragma once

#include "default.hpp"
#include <sys/select.h>
#include <sys/time.h>
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
    bool	_LoopListen;
    std::string _IpStr;
    std::vector<s_account> _Accounts;
    struct sockaddr_in _Saddr;
    socklen_t _Socklen;
    int _Sockfd;
    char _Buf[SIZE];

	fd_set	fds;
	int		maxFd;

	void readerClient(fd_set);
public:
	Server(const std::string & ip_addres, const int port);
	~Server();
	void run();
};
