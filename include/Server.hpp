#pragma once

#include "ft.hpp"
#include "Replies.hpp"

using std::vector;
using std::string;

class Client;
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
	std::vector<Client *> _Users;
	std::vector<Channel *> _Channels;
    int _Sockfd;

	addrinfo *servinfo;
	socklen_t _Socklen;

	fd_set	_Fds_set;
	int		maxFd;

	void readerClient(fd_set & fdsCpy);
	void processCmd(Client *User, std::string const & ReceivedMessage);
	std::pair<std::string, std::string> parseCmd(std::string &Cmd);
	void proceedCmd(std::pair<std::string, std::string> Cmd, Client *User);
	std::string timeStamp() { return "A long time ago"; }

    void serverLog(Client *that, std::string const & ReceivedMessage);
    void sendMsg(Client *From, Client *To);
	void sendMsg(Client *To);

	std::vector<Client *> const &getUsers();


public:
	Server(string const & ip, string const & port);
	Server(std::vector<std::string>& argv);
	~Server();
	std::string getServerAddrInfo() const;

	void removeUserByNickName(std::string const & NickName);
	Client *getUserByNickName(std::string const & NickName);
	Client *getUserByName(std::string const & NickName);
	Channel *getChannelByName(std::string const & NameChannel);
	void run();
};
