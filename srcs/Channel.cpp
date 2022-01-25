#include "ft.hpp"
#include "Channel.hpp"
#include "Replies.hpp"
#include "Client.hpp"


//! 	enum ePrivateLevel
//* 	0 == CHANNEL_PRIVATE,
//* 	1 == CHANNEL_PROTECTED,
//* 	2 == CHANNEL_PUBLIC
Channel::Channel(
	string const & nameChannel,
	Client const & userAdmin,
	eChannelPrivateLevel const ePrivateLevel)
	:	AUser(nameChannel) {
	_ePrivateLevel = ePrivateLevel;
	addAdmin(userAdmin);
}

Channel::Channel(
	string const & nameChannel,
	Client const & userAdmin)
	:	AUser(nameChannel) {
	addAdmin(userAdmin);
}

Channel::~Channel(){}

void	Channel::setLevelPrivate(Client & who, eChannelPrivateLevel const ePrivateLevel){
	if (not isAdmin(who)) {
		who.updateReplyMessage(ERR_CHANOPRIVSNEEDED(_Name));
		return ;
	}
	_ePrivateLevel = ePrivateLevel;
}

void	Channel::setName(Client & who, string const & newNameChannel) {
	if (not isAdmin(who)) {
		who.updateReplyMessage(ERR_CHANOPRIVSNEEDED(_Name));
		return ;
	}
	setName(newNameChannel);
}

bool Channel::isAdmin(Client const & whom) const {
	vector<Client const *>::const_iterator beg = _Admins.begin();
	vector<Client const *>::const_iterator end = _Admins.end();

	while(beg != end)
		if (whom == **(beg++))
			return true;
	return false;
}

bool Channel::isOwner(Client const & whom) const {
	vector<Client const *>::const_iterator beg = _Users.begin();
	vector<Client const *>::const_iterator end = _Users.end();

	while(beg != end)
		if (whom == **(beg++))
			return true;
	return false;
}

const vector<Client const *>& Channel::getAdmins(){ return _Admins;}

void	Channel::addUser(Client & who, Client & whom){
	if (_ePrivateLevel == CHANNEL_PRIVATE || _ePrivateLevel == CHANNEL_PROTECTED) {
		if (not isAdmin(who) && not isOwner(who)) {
			who.updateReplyMessage(ERR_CHANOPRIVSNEEDED(_Name));
			return ;
		}
	}
	vector<Client const *>::iterator it = find(_Users.begin(), _Users.end(), &whom);
	if (it == _Users.end())
		_Users.push_back(&whom);
}

void	Channel::addUser(Client const & whom){
	vector<Client const *>::iterator it;

	it = find(_Users.begin(), _Users.end(), &whom);
	if (it == _Users.end())
		_Users.push_back(&whom);
}

void	Channel::removeUser(Client & who, Client & whom){
	if (_ePrivateLevel == CHANNEL_PRIVATE || _ePrivateLevel == CHANNEL_PROTECTED) {
		if (not isAdmin(who) && not isOwner(who)) {
			who.updateReplyMessage(ERR_CHANOPRIVSNEEDED(_Name));
			return ;
		}
	}
	vector<Client const *>::iterator it = find(_Admins.begin(), _Admins.end(), &whom);
	if (it != _Admins.end())
		removeAdmin(who, whom);
	it = find(_Users.begin(), _Users.end(), &whom);
	if (it == _Users.end()) {
		who.updateReplyMessage(ERR_NOSUCHNICK(whom.getNickName()));
		return ;
	}
	_Users.erase(it);
}

void	Channel::addAdmin(Client & who, Client & whom){
	vector<Client const *>::iterator beg = _Admins.begin();
	vector<Client const *>::iterator end = _Admins.end();

	if (not isAdmin(who)) {
		who.updateReplyMessage(ERR_CHANOPRIVSNEEDED(_Name));
		return ;
	}
	while(beg != end)
		if (**beg == whom)
			return ;
	_Admins.push_back(&whom);
	addUser(whom);
}

void	Channel::addAdmin(Client const & whom){
	vector<Client const *>::iterator beg = _Admins.begin();
	vector<Client const *>::iterator end = _Admins.end();

	while(beg != end)
		if (**beg == whom)
			return ;
	_Admins.push_back(&whom);
}

void	Channel::removeAdmin(Client & who, Client & whom){

	if (not isAdmin(who)) {
		who.updateReplyMessage(ERR_CHANOPRIVSNEEDED(_Name));
		return ;
	}
	if (_Admins.size() == 1){
		if (_Users.size() > 0) {
			who.updateReplyMessage(ft::to_string(__LINE__) + " in Channel is need to set appropriate message");
			return ;
		}
		delete this; //Is it appropriate here?
	}
	vector<Client const *>::iterator it = find(_Admins.begin(), _Admins.end(), &whom);
	if (it == _Admins.end()) {
		who.updateReplyMessage(ERR_NOSUCHNICK(whom.getNickName()));
		return ;
	}
	_Admins.erase(it);
}
