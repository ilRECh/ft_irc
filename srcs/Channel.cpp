#include "ft.hpp"
#include "Channel.hpp"
#include "Replies.hpp"
#include "User.hpp"

//! 	enum ePrivateLevel
//* 	0 == CHANNEL_PRIVATE,
//* 	1 == CHANNEL_PROTECTED,
//* 	2 == CHANNEL_PUBLIC
Channel::Channel(
	string const & nameChannel, User const & userAdmin,
	eChannelPrivateLevel const ePrivateLevel)
	:	AUser(nameChannel) {
	_ePrivateLevel = ePrivateLevel;
	addAdmin(userAdmin);
}

Channel::Channel(
	string const & nameChannel,
	User const & userAdmin)
	:	AUser(nameChannel) {
	addAdmin(userAdmin);
}

Channel::~Channel(){}

void	Channel::setLevelPrivate(User & who, eChannelPrivateLevel const ePrivateLevel){
	if (not isAdmin(who)) {
		who.setReplyMessage(ERR_CHANOPRIVSNEEDED(_Name));
		return ;
	}
	_ePrivateLevel = ePrivateLevel;
}

void	Channel::setName(User & who, string const & newNameChannel) {
	if (not isAdmin(who)) {
		who.setReplyMessage(ERR_CHANOPRIVSNEEDED(_Name));
		return ;
	}
	if (setName(newNameChannel)) {
		who.setReplyMessage(ERR_ERRONEUSNICKNAME(newNameChannel));
		return ;
	}
}

bool Channel::isAdmin(User const & whom) const {
	vector<User const *>::const_iterator beg = _Admins.begin();
	vector<User const *>::const_iterator end = _Admins.end();

	while(beg != end)
		if (whom == **(beg++))
			return true;
	return false;
}

bool Channel::isOwner(User const & whom) const {
	vector<User const *>::const_iterator beg = _Users.begin();
	vector<User const *>::const_iterator end = _Users.end();

	while(beg != end)
		if (whom == **(beg++))
			return true;
	return false;
}

const vector<User const *>& Channel::getAdmins(){ return _Admins;}

void	Channel::addUser(User & who, User & whom){
	if (_ePrivateLevel == CHANNEL_PRIVATE || _ePrivateLevel == CHANNEL_PROTECTED) {
		if (not isAdmin(who) && not isOwner(who)) {
			who.setReplyMessage(ERR_CHANOPRIVSNEEDED(_Name));
			return ;
		}
	}
	vector<User const *>::iterator it = find(_Users.begin(), _Users.end(), &whom);
	if (it == _Users.end())
		_Users.push_back(&whom);
}

void	Channel::addUser(User const & whom){
	vector<User const *>::iterator it;

	it = find(_Users.begin(), _Users.end(), &whom);
	if (it == _Users.end())
		_Users.push_back(&whom);
}

void	Channel::removeUser(User & who, User & whom){
	if (_ePrivateLevel == CHANNEL_PRIVATE || _ePrivateLevel == CHANNEL_PROTECTED) {
		if (not isAdmin(who) && not isOwner(who)) {
			who.setReplyMessage(ERR_CHANOPRIVSNEEDED(_Name));
			return ;
		}
	}
	vector<User const *>::iterator it = find(_Admins.begin(), _Admins.end(), &whom);
	if (it != _Admins.end())
		removeAdmin(who, whom);
	it = find(_Users.begin(), _Users.end(), &whom);
	if (it == _Users.end()) {
		who.setReplyMessage(ERR_NOSUCHNICK(whom.getNickName()));
		return ;
	}
	_Users.erase(it);
}

void	Channel::addAdmin(User & who, User & whom){
	vector<User const *>::iterator beg = _Admins.begin();
	vector<User const *>::iterator end = _Admins.end();

	if (not isAdmin(who)) {
		who.setReplyMessage(ERR_CHANOPRIVSNEEDED(_Name));
		return ;
	}
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

void	Channel::removeAdmin(User & who, User & whom){

	if (not isAdmin(who)) {
		who.setReplyMessage(ERR_CHANOPRIVSNEEDED(_Name));
		return ;
	}
	if (_Admins.size() == 1){
		if (_Users.size() > 0) {
			who.setReplyMessage(ft::to_string(__LINE__) + " in Channel is need to set appropriate message");
			return ;
		}
		delete this; //Is it appropriate here?
	}
	vector<User const *>::iterator it = find(_Admins.begin(), _Admins.end(), &whom);
	if (it == _Admins.end()) {
		who.setReplyMessage(ERR_NOSUCHNICK(whom.getNickName()));
		return ;
	}
	_Admins.erase(it);
}
