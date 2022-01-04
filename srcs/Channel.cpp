#include "Channel.hpp"

//! 	enum ePrivateLevel
//* 	0 == CHANNEL_PRIVATE,
//* 	1 == CHANNEL_PROTECTED,
//* 	2 == CHANNEL_PUBLIC
Channel::Channel(string const & nameChannel, User const & userAdmin, eChannelPrivateLevel const ePrivateLevel){
	string::const_iterator beg = nameChannel.cbegin();
	string::const_iterator end = nameChannel.cend();

	while(beg != end)
		if (!std::isalnum(*(beg++)))
			throw std::runtime_error("Name channel " + nameChannel + " is not valid, use A-Z, a-z, 0-9");
	_ePrivateLevel = ePrivateLevel;
	_NameChannel = nameChannel;
	addAdmin(userAdmin);
}

Channel::Channel(string const & nameChannel, User const & userAdmin){
	string::const_iterator beg = nameChannel.cbegin();
	string::const_iterator end = nameChannel.cend();

	while(beg != end)
		if (!std::isalnum(*(beg++)))
			throw std::runtime_error("Name channel " + nameChannel + " is not valid, use A-Z, a-z, 0-9");
	_ePrivateLevel = CHANNEL_PUBLIC;
	_NameChannel = nameChannel;
	addAdmin(userAdmin);
}

Channel::~Channel(){}

void	Channel::setLevelPrivate(User const & who, eChannelPrivateLevel const ePrivateLevel){
	if (!checkAdminPermist(who))
		throw std::runtime_error(who.getName() + " is not Admin\n" + who.getName() + " cannot change private level");
	_ePrivateLevel = ePrivateLevel;
}
void	Channel::setNameChannel(User const & who, string const & newNameChannel){
	string::const_iterator beg = newNameChannel.cbegin();
	string::const_iterator end = newNameChannel.cend();

	if (!checkAdminPermist(who))
		throw std::runtime_error(who.getName() + " is not Admin\n" + who.getName() + " cannot change name channel");
	while(beg != end)
		if (!std::isalnum(*(beg++)))
			throw std::runtime_error("Name channel " + newNameChannel + " is not valid, use A-Z, a-z, 0-9");
	_NameChannel = newNameChannel;
}

bool Channel::checkAdminPermist(User const & whom) const{
	vector<User const *>::const_iterator beg = _Admins.cbegin();
	vector<User const *>::const_iterator end = _Admins.cend();

	while(beg != end)
		if (whom == **(beg++))
			return true;
	return false;
}

bool Channel::checkOwnerPermist(User const & whom) const{
	vector<User const *>::const_iterator beg = _Users.cbegin();
	vector<User const *>::const_iterator end = _Users.cend();

	while(beg != end)
		if (whom == **(beg++))
			return true;
	return false;
}

const vector<User const *>& Channel::getAdmins(){ return _Admins;}

void	Channel::addUser(User const & who, User const & whom){
	vector<User const *>::iterator it;
	bool	isAdmin;
	bool	isPrivateOwner;

	isAdmin = checkAdminPermist(who);
	isPrivateOwner = checkOwnerPermist(who) | isAdmin;

	if (_ePrivateLevel == CHANNEL_PRIVATE)
		if (!isAdmin)
			throw std::runtime_error(who.getName() + " is not Admin\n" + who.getName() + " cannot add new User");
	if (_ePrivateLevel == CHANNEL_PROTECTED)
		if (!isPrivateOwner)
			throw std::runtime_error(who.getName() + " is not Owner or Admin\n" + who.getName() + " cannot add new User");
	it = find(_Users.begin(), _Users.end(), &whom);
	if (it == _Users.end())
		_Users.push_back(&whom);
}

void	Channel::addUser(User const & whom){
	vector<User const *>::iterator it;

	it = find(_Users.begin(), _Users.end(), &whom);
	if (it == _Users.end())
		_Users.push_back(&whom);
}

void	Channel::removeUser(User const & who, User const & whom){
	vector<User const *>::iterator it;
	bool	isPrivateOwner;
	bool	isAdmin;

	isAdmin = checkAdminPermist(who);
	isPrivateOwner = checkOwnerPermist(who) | isAdmin;

	if (who != whom){
		if (_ePrivateLevel == CHANNEL_PRIVATE)
			if (!isAdmin)
				throw std::runtime_error(who.getName() + " is not Admin\n" + who.getName() + " cannot delete User");
		if (_ePrivateLevel == CHANNEL_PROTECTED)
			if (!isPrivateOwner)
				throw std::runtime_error(who.getName() + " is not Owner or Admin\n" + who.getName() + " cannot delete User");
	}
	it = find(_Admins.begin(), _Admins.end(), &whom);
	if (it != _Admins.end())
		removeAdmin(who, whom);
	it = find(_Users.begin(), _Users.end(), &whom);
	if (it == _Users.end())
		throw std::runtime_error(whom.getName() + "isn't member of this channel");
	_Users.erase(it);
}

void	Channel::addAdmin(User const & who, User const & whom){
	vector<User const *>::iterator beg = _Admins.begin();
	vector<User const *>::iterator end = _Admins.end();

	if (!checkAdminPermist(who))
		throw std::runtime_error(who.getName() + " is not Admin\n" + who.getName() + " cannot add new Admin");
	while(beg != end)
		if (**beg == whom)
			return ;
	_Admins.push_back(&whom);
	addUser(whom);
}

void	Channel::addAdmin(User const & whom){
	vector<User const *>::iterator beg = _Admins.begin();
	vector<User const *>::iterator end = _Admins.end();

	while(beg != end)
		if (**beg == whom)
			return ;
	_Admins.push_back(&whom);
}

void	Channel::removeAdmin(User const & who, User const & whom){
	vector<User const *>::iterator it;

	if (!checkAdminPermist(who))
		throw std::runtime_error(who.getName() + " is not Admin\n" + who.getName() + " cannot add new Admin");
	if (_Admins.size() == 1){
		if (_Users.size() > 0)
			throw std::runtime_error(
				"A group with users cannot be without an admin, \
				assign a new Admin, or delete all users to delete \
				the group");
		delete this;
	}
	it = find(_Admins.begin(), _Admins.end(), &whom);
	if (it == _Admins.end())
		throw std::runtime_error(whom.getName() + "isn't member of Admins, of this channel");
	_Admins.erase(it);
}