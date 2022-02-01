#pragma once

#include "ft.hpp"
#include "Modes.hpp"

enum eChannelPrivateLevel {
	CHANNEL_PRIVATE,
	CHANNEL_PROTECTED,
	CHANNEL_PUBLIC
};

class Client;
class Server;

class Channel : public Modes {
private:
	friend class NAMES;
	std::string _ChannelName;
	std::string _Key;
	std::string _Topic;
	std::set<Client *> _Clients;
    int                _Limit;
	Server *_Server;
	//! typePrivateLevel
	//* CHANNEL_PRIVATE могут приглашать только админы;
	//* CHANNEL_PROTECTED могут приглашать только админы и участники;
	//* CHANNEL_PUBLIC могут все добавляться;
	eChannelPrivateLevel _ePrivateLevel;
	void	addUser(Client const & whom);
public:
	Channel(
		std::string const & nameChannel,
		Client *userAdmin,
		Server *Server,
		eChannelPrivateLevel const ePrivateLevel = CHANNEL_PUBLIC);
	~Channel() {}
	
	std::string const &getTopic() const;
	void setTopic(std::string const & Topic);
	std::string const &getChannelName() const { return _ChannelName; }
	void	addClient(Client *whom, Client *who = NULL);
	void	removeClient(Client *whom);//, Client & whom);
	// void	removeClient(Client const & who, Client & whom);
	bool	isOnChannel(Client *whom) const;
	void	setLevelPrivate(
		Client *who,
		eChannelPrivateLevel const ePrivateLevel);
	void	setChannelName(
		Client *who,
		std::string const & newNameChannel);
    int getLimit() { return _Limit; }
    void setLimit(int limit) { _Limit = limit; }
    void setKey(std::string const & Key) { _Key = Key; }
    std::string &getKey() { return _Key; }
};
