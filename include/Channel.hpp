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
	std::string _Password;
	std::string _Topic;
	std::set<Client *> _Clients;
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
		eChannelPrivateLevel const ePrivateLevel = CHANNEL_PUBLIC);
	~Channel() {}
	
	std::string const &getTopic() const;
	void setTopic(std::string const & Topic);
	std::string const &getChannelName() const { return _ChannelName; }
	void	addClient(Client *whom, Client *who = NULL);
	void	removeClient(Client const & who, Client & whom);
	bool	isOnChannel(Client *whom) const;
	void	setLevelPrivate(
		Client *who,
		eChannelPrivateLevel const ePrivateLevel);
	void	setChannelName(
		Client *who,
		std::string const & newNameChannel);
};
