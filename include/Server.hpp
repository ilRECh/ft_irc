#pragma once

#include "ft.hpp"
#include "Replies.hpp"
#include "Modes.hpp"

using std::vector;
using std::string;

class Client;
class ACommand;
class Channel;

enum OperatorStatus {
	YOUREOPER,
	NOOPERHOST,
	PASSWDMISMATCH
};
struct operators_s {
	std::string Name;
	std::string Password;
	bool operator==(std::string const & ThatName) const {
		return Name == ThatName;
	}
};

class Server : public Modes {
private:
	// Time since start
	TimeStamp _Age;

	// Parameters
	std::string _Ip;
	std::string _Port;
	std::string _Password;

	// On dying
	std::string _DyingMessage;

	// Networking
    bool _LoopListen;
    int _Sockfd;
	addrinfo *_ServInfo;
	socklen_t _Socklen;
	fd_set _FdsSet;
	int _MaxFd;

	// Top level logic
	std::vector<ACommand *> _Commands;
	std::set<Client *> _Clients;
	std::list<Client *> _ClientsToBeErased;
	std::set<Channel *> _Channels;
	std::list<Channel *> _ChannelsToBeErased;


	// Opers
	static operators_s _Operators[1];

	// Insights
	void readerClient(fd_set & fdsCpy);
	void processCmd(Client *User);
	std::pair<std::string, std::string> parseCmd(std::string &Cmd);
	void proceedCmd(std::pair<std::string, std::string> Cmd, Client *User);
    void serverLog(Client *that, std::string const & ReceivedMessage);
    void sendMsg(Client *From, Client *To);
	std::set<Client *> const &getUsers();

public:
	Server(string const & Port, std::string const & Password);
	~Server();

	void sendMsg(Client *To);
	void run();
	std::string getServerAddrInfo() const { return _Ip + ":" + _Port; }
	Client *getUserByNickName(std::string const & NickName);
	//* now it support find by wildcard
	std::set<Client *> getClientsByName(std::string Name);
	std::set<Client *> const &getClients();
	std::set<Channel *>getChannelsByName(std::string Name);
	Channel *getChannelByChannelName(std::string const & NameChannel);
	OperatorStatus canBeAutorized(
		std::string const & Name,
		std::string const & Password);
	void pushBackErase(Client *Client);
	void pushBackErase(Channel *Channel);
	void buryMe(std::string const & DyingMessage);
};
