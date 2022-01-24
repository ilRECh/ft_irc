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

class User;
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
	vector<User const *>	_Admins;
	vector<User const *>	_Users;
	void	addAdmin(User const & whom);
	void	addUser(User const & whom);
	using AUser::setName;
public:
	Channel(string const & nameChannel, User const & userAdmin);
	Channel(string const & nameChannel, User const & userAdmin, eChannelPrivateLevel const ePrivateLevel);
	~Channel();
	void	addAdmin		(User & who, User & whom);
	void	addUser			(User & who, User & whom);
	void	removeUser		(User & who, User & whom);
	void	removeAdmin		(User & who, User & whom);
	const	vector<User const *>& getAdmins();
	bool	isAdmin (User const & whom) const;
	bool	isOwner (User const & whom) const;
	void	setLevelPrivate	(User & who, eChannelPrivateLevel const ePrivateLevel);
	void	setName(User & who, string const & newNameChannel);
};
