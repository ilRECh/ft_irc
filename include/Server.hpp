#pragma once

#include "Mandatory.hpp"
#include "Server.hpp"
#include "Commands.hpp"
#include "User.hpp"

using std::vector;
using std::string;

class User;

class Server {
private:
	std::string _Password;
	std::string _Port;
	std::string _Host;
	std::string _PortNetwork;
	std::string _PasswordNetwork;
	std::vector<ACommand *> _Commands;

	string	ip;
	string	port;
    bool	_LoopListen;
	std::vector<User *> _Users;
	addrinfo *servinfo;
    // struct sockaddr_in _Saddr;
    socklen_t _Socklen;
    int _Sockfd;
    char _Buf[SIZE];

	fd_set	fds;
	int		maxFd;

	void readerClient(fd_set);
public:
	Server(string const & ip, string const & port);
	Server(std::vector<std::string>& argv);
	~Server();
	void run();
	static std::vector<std::string> parseCmd(std::string Cmd);
};
