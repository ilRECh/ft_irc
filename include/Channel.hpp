#pragma once

#include "ft.hpp"
#include "AUser.hpp"

using std::string;
using std::vector;
using std::find;

enum eChannelPrivateLevel {
	CHANNEL_PRIVATE,
	CHANNEL_PROTECTED,
	CHANNEL_PUBLIC
};

class Client;
class Server;

class Channel : public AUser {
private:
	//! typePrivateLevel
	//* CHANNEL_PRIVATE могут приглашать только админы;
	//* CHANNEL_PROTECTED могут приглашать только админы и участники;
	//* CHANNEL_PUBLIC могут все добавляться;
	eChannelPrivateLevel			_ePrivateLevel;
	//*				имя канала
	//*				Список админов
	vector<Client const *>	_Admins;
	vector<Client const *>	_Clients;
	void	addAdmin(Client const & whom);
	void	addUser(Client const & whom);
	using AUser::setName;
public:
	Channel(string const & nameChannel, Client const & userAdmin);
	Channel(string const & nameChannel, Client const & userAdmin, eChannelPrivateLevel const ePrivateLevel);
	~Channel();
	void	addAdmin		(Client & who, Client & whom);
	void	addUser			(Client & who, Client & whom);
	void	removeUser		(Client & who, Client & whom);
	void	removeAdmin		(Client & who, Client & whom);
	const	vector<Client const *>& getAdmins();
	bool	isAdmin (Client const & whom) const;
	bool	isOwner (Client const & whom) const;
	void	setLevelPrivate	(Client & who, eChannelPrivateLevel const ePrivateLevel);
	void	setName(Client & who, string const & newNameChannel);
};
