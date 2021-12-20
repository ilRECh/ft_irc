#pragma once

#include "default.hpp"

struct	s_account {
	std::string	_Name;
	std::string	_Password;
	int	_Fd;
};

class Server {
private:
    bool _LoopListen;
    std::string _IpStr;
    std::vector<s_account> _Accounts;
    struct sockaddr_in _Saddr;
    socklen_t _Socklen;
    int _Sockfd;
    char _Buf[SIZE];

public:
	Server(const std::string & ip_addres, const int port);
	~Server();
	void run();
	class sExcept: public std::exception{
		std::string reason;
	public:
		sExcept(const std::string reason);
		virtual ~sExcept() throw();
		const char *what() const throw();
	};
};
