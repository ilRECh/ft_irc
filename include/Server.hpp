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
	// Parameters
	std::string _Ip;
	std::string _Port;
	std::string _Password;

	// Networking
    bool _LoopListen;
    int _Sockfd;
	addrinfo *_ServInfo;
	socklen_t _Socklen;
	fd_set _FdsSet;
	int _MaxFd;

	// Top level logic
	std::vector<ACommand *> _Commands;
	std::set<Client *> _Users;
	std::set<Channel *> _Channels;

	// Insights
	void readerClient(fd_set & fdsCpy);
	void processCmd(Client *User);
	std::pair<std::string, std::string> parseCmd(std::string &Cmd);
	void proceedCmd(std::pair<std::string, std::string> Cmd, Client *User);
	std::string timeStamp() { return "A long time ago"; }
    void serverLog(Client *that, std::string const & ReceivedMessage);
    void sendMsg(Client *From, Client *To);
	std::set<Client *> const &getUsers();

public:
	Server(string const & Port, std::string const & Password);
	~Server();

	void run();
	std::string getServerAddrInfo() const { return _Ip + ":" + _Port; }
	Client *getUserByNickName(std::string const & NickName);
	Client *getUserByName(std::string const & NickName);
	Channel *getChannelByName(std::string const & NameChannel);
	void sendMsg(Client *To);
	void removeUserByNickName(std::string const & NickName);
};
