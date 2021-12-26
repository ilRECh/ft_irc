#pragma once
#include <string>
#include <vector>
#include <stdlib.h>
#include "User.hpp"
#include "ExceptionUni.hpp"

using std::string;
using std::vector;
using std::find;

enum eChannelPrivateLevel {
	CHANNEL_PRIVATE,
	CHANNEL_PROTECTED,
	CHANNEL_PUBLIC
};

class User;

class Channel
{
private:
	//! typePrivateLevel
	//* CHANNEL_PRIVATE могут приглашать только админы;
	//* CHANNEL_PROTECTED могут приглашать только админы и участники;
	//* CHANNEL_PUBLIC могут все добавляться;
	eChannelPrivateLevel			_ePrivateLevel;
	//*				имя канала
	string			_NameChannel;
	//*				Список админов
	vector<User const *>	_Admins;
	vector<User const *>	_Users;
	void	addAdmin(User const & whom);
	void	addUser(User const & whom);
public:
	Channel(string const & nameChannel, User const & userAdmin);
	Channel(string const & nameChannel, User const & userAdmin, eChannelPrivateLevel const ePrivateLevel);
	~Channel();
	void	addAdmin		(User const & who, User const & whom);
	void	addUser			(User const & who, User const & whom);
	void	removeUser		(User const & who, User const & whom);
	void	removeAdmin		(User const & who, User const & whom);
	const	vector<User const *>& getAdmins();
	bool	checkAdminPermist	(User const & whom) const;
	bool	checkOwnerPermist	(User const & whom) const;
	void	setLevelPrivate		(User const & who, eChannelPrivateLevel const ePrivateLevel);
	void	setNameChannel		(User const & who, string const & newNameChannel);
};