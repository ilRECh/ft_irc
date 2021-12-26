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
			throw ExceptionUni("Name channel " + nameChannel + " is not valid, use A-Z, a-z, 0-9");
	_ePrivateLevel = ePrivateLevel;
	_NameChannel = nameChannel;
	addAdmin(userAdmin);
}

Channel::Channel(string const & nameChannel, User const & userAdmin){
	string::const_iterator beg = nameChannel.cbegin();
	string::const_iterator end = nameChannel.cend();

	while(beg != end)
		if (!std::isalnum(*(beg++)))
			throw ExceptionUni("Name channel " + nameChannel + " is not valid, use A-Z, a-z, 0-9");
	_ePrivateLevel = CHANNEL_PUBLIC;
	_NameChannel = nameChannel;
	addAdmin(userAdmin);
}
Channel::~Channel(){}

void	Channel::setLevelPrivate(User const & who, eChannelPrivateLevel const ePrivateLevel){
	if (!checkAdminPermist(who))
		throw ExceptionUni(who.getName() + " is not Admin\n" + who.getName() + " cannot change private level");
	_ePrivateLevel = ePrivateLevel;
}
void	Channel::setNameChannel(User const & who, string const & newNameChannel){
	string::const_iterator beg = newNameChannel.cbegin();
	string::const_iterator end = newNameChannel.cend();

	if (!checkAdminPermist(who))
		throw ExceptionUni(who.getName() + " is not Admin\n" + who.getName() + " cannot change name channel");
	while(beg != end)
		if (!std::isalnum(*(beg++)))
			throw ExceptionUni("Name channel " + newNameChannel + " is not valid, use A-Z, a-z, 0-9");
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
	bool	isAdmin;
	bool	isPrivateOwner;

	isAdmin = checkAdminPermist(who);
	isPrivateOwner = checkOwnerPermist(who) | isAdmin;

	if (_ePrivateLevel == CHANNEL_PRIVATE)
		if (!isAdmin)
			throw ExceptionUni(who.getName() + " is not Admin\n" + who.getName() + " cannot add new User");
	if (_ePrivateLevel == CHANNEL_PROTECTED)
		if (!isPrivateOwner)
			throw ExceptionUni(who.getName() + " is not Owner or Admin\n" + who.getName() + " cannot add new User");
	_Users.push_back(&whom);
}

void	Channel::addAdmin(User const & who, User const & whom){
	vector<User const *>::iterator beg = _Admins.begin();
	vector<User const *>::iterator end = _Admins.end();

	if (!checkAdminPermist(who))
		throw ExceptionUni(who.getName() + " is not Admin\n" + who.getName() + " cannot add new Admin");
	while(beg != end)
		if (**beg == whom)
			return ;
	_Admins.push_back(&whom);
}

void	Channel::addAdmin(User const & whom){
	vector<User const *>::iterator beg = _Admins.begin();
	vector<User const *>::iterator end = _Admins.end();

	while(beg != end)
		if (**beg == whom)
			return ;
	_Admins.push_back(&whom);
}

void	Channel::dellAdmin(User const & who, User const & whom){
	vector<User const *>::iterator beg = _Admins.begin();
	vector<User const *>::iterator end = _Admins.end();

	if (!checkAdminPermist(who))
		throw ExceptionUni(who.getName() + " is not Admin\n" + who.getName() + " cannot add new Admin");
	while(beg != end)
		if (**beg == whom)
			_Admins.erase(beg);
}