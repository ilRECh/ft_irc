#pragma once

#include "ft.hpp"
#include "Replies.hpp"

// Commands
#include "ConnectionRegistration/PASS.hpp"

using std::vector;
using std::string;

class User;
class ACommand;
class Channel;

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
	std::vector<Channel *> _Channels;
    int _Sockfd;

	fd_set	fds;
	int		maxFd;

	void readerClient(fd_set);
public:
	Server(string const & ip, string const & port);
	Server(std::vector<std::string>& argv);
	~Server();
	void run();

	int processCmd(User *That);
	std::pair<std::string, std::string> parseCmd(std::string &Cmd);
	void proceedCmd(std::pair<std::string, std::string> Cmd, User *User);
	std::string timeStamp() { return "A long time ago"; }

    std::string recvReader(int fd);
    void serverLog(User *that);
    void sendMsg(User *From, User *To);
	void sendMsg(User *To);

	std::vector<User *> const &getUsers();

	User *getUserByNickName(std::string const & NickName);
	User *getUserByName(std::string const & NickName);
	Channel *getChannelByName(std::string const & NameChannel);
	void removeUserByNickName(std::string const & NickName);
};
