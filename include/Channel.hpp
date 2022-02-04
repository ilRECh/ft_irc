#pragma once

#include "ft.hpp"
#include "Modes.hpp"

class Client;
class Server;

class Channel : public Modes {
private:
	friend class NAMES;
	friend class JOIN;
	uint _maxUserLimit;
	std::string _ChannelName;
	std::string _Key;
	std::string _Topic;
	std::set<Client *> _Clients;
	std::set<Client *> _BanList;
	Server *_Server;
public:
	Channel(
		std::string const & nameChannel,
		Client *userAdmin,
		Server *Server,
		uint maxUserLimit = 1024);
	~Channel() {}
	
	std::string const &getTopic() const;
	void setTopic(std::string const & Topic);
	std::string const &getChannelName() const { return _ChannelName; }
	int		addClient(Client *whom, Client *who = NULL);
	void	removeClient(Client *whom);//, Client & whom);
	bool	isOnChannel(Client *whom) const;
	void	setChannelName(
		Client *who,
		std::string const & newNameChannel);
	void replyToAllMembers(std::string msg, Client * sender = NULL);
	//* Ban!!
	void addToBan(Client * toBanUser);
	void removeFromBan(Client * unBanUser);
	bool isBanned(Client * isBannedUser);
	//* limit Users
    uint getLimit() { return _maxUserLimit; }
    void setLimit(int limit) { _maxUserLimit = limit; }
    void setKey(std::string const & Key) { _Key = Key; }
    std::string &getKey() { return _Key; }
};
