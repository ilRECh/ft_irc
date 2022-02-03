#include "ft.hpp"
#include "Channel.hpp"
#include "Replies.hpp"
#include "Client.hpp"
#include "Server.hpp"


//! 	enum ePrivateLevel
//* 	0 == CHANNEL_PRIVATE,
//* 	1 == CHANNEL_PROTECTED,
//* 	2 == CHANNEL_PUBLIC
Channel::Channel(
	string const & nameChannel,
	Client * userAdmin,
	Server *Server,
	eChannelPrivateLevel const ePrivateLevel,
	uint maxUserLimit)
	:	Modes(this),
		_maxUserLimit(maxUserLimit),
		_ChannelName(nameChannel),
		_Server(Server){
	_ePrivateLevel = ePrivateLevel;
	_Clients.insert(userAdmin);
}

void	Channel::setLevelPrivate(
	Client *who,
	eChannelPrivateLevel const ePrivateLevel){
	if (not getModeIsExist(who, 'o')) {
		who->updateReplyMessage(ERR_CHANOPRIVSNEEDED(_ChannelName));
		return ;
	}
	_ePrivateLevel = ePrivateLevel;
}

void Channel::setChannelName(
	Client *who,
	std::string const &newNameChannel) {
	if (not getModeIsExist(who, 'o')) {
		who->updateReplyMessage(ERR_CHANOPRIVSNEEDED(_ChannelName));
		return ;
	}
	_ChannelName = newNameChannel;
}

bool Channel::isOnChannel(Client *whom) const {
	return _Clients.find(whom) != _Clients.end();
}

void	Channel::addClient(Client *whom, Client *who) {
	if (who != NULL and
		(_ePrivateLevel == CHANNEL_PRIVATE or _ePrivateLevel == CHANNEL_PROTECTED)) {
		if (_Clients.size() >= _maxUserLimit)
		{
			who->updateReplyMessage(ERR_CHANNELISFULL(this->getChannelName()));
			return ;
		}
		if (not getModeIsExist(who, 'o')) {
			who->updateReplyMessage(ERR_CHANOPRIVSNEEDED(_ChannelName));
			return ;
		}
	}
	replyToAllMembers("joined", whom);
	_Clients.insert(whom);
}

std::string const &Channel::getTopic() const {
	return _Topic;
}

void Channel::setTopic(std::string const & Topic) {
	_Topic = Topic;
}

void Channel::removeClient(Client *whom) {
	static bool ToRemove = false;
	if (ToRemove) {
		return ;
	}
	std::set<Client *>::iterator i = find(_Clients.begin(), _Clients.end(), whom);
	if (i != _Clients.end()) {
		_Clients.erase(i);
		eraseClientFromModes(*i);
	}
	if (_Clients.empty()) {
		ToRemove = true;
		_Server->pushBackErase(this);
	}
}

void Channel::replyToAllMembers(std::string msg, Client * sender) {
	std::string Reply = this->getChannelName() +  " :" + msg;
	if (sender != NULL) {
		Reply = sender->_NickName + " " + Reply;
		for (std::set<Client *>::iterator i = _Clients.begin(); i != _Clients.end(); ++i) {
			if (*i != sender) {
				(*i)->updateReplyMessage(Reply);
			}
		}
	}
	for (std::set<Client *>::iterator i = _Clients.begin(); i != _Clients.end(); ++i) {
		(*i)->updateReplyMessage(Reply);
	}
}

void Channel::addToBan(Client * toBanUser)
{
	if (!isBanned(toBanUser))
	{
		_BanList.insert(toBanUser);
		replyToAllMembers("banned!", toBanUser);
	}
}
void Channel::removeFromBan(Client * unBanUser)
{
	if (isBanned(unBanUser))
	{
		_BanList.erase(unBanUser);
		replyToAllMembers("unbanned", unBanUser);
	}
}
bool Channel::isBanned(Client * isBannedUser)
{
	std::set<Client *>::iterator first, last;

	first = _BanList.begin();
	last = _BanList.end();
	while(first != last)
	{
		if (*first == isBannedUser)
			return true;
		++first;
	}
	return false;
}


// void	Channel::removeUser(Client & who, Client & whom){
// 	if (_ePrivateLevel == CHANNEL_PRIVATE || _ePrivateLevel == CHANNEL_PROTECTED) {
// 		if (not isAdmin(who) && not isOwner(who)) {
// 			who.updateReplyMessage(ERR_CHANOPRIVSNEEDED(_ChannelName));
// 			return ;
// 		}
// 	}
// 	std::set<Client const *>::iterator it = find(_Admins.begin(), _Admins.end(), &whom);
// 	if (it != _Admins.end())
// 		removeAdmin(who, whom);
// 	it = find(_Clients.begin(), _Clients.end(), &whom);
// 	if (it == _Clients.end()) {
// 		who.updateReplyMessage(ERR_NOSUCHNICK(whom.getNickName()));
// 		return ;
// 	}
// 	_Clients.erase(it);
// }

// void	Channel::addAdmin(Client const & whom){
// 	std::set<Client const *>::iterator beg = _Admins.begin();
// 	std::set<Client const *>::iterator end = _Admins.end();

// 	while(beg != end)
// 		if (**beg == whom)
// 			return ;
// 	_Admins.insert(&whom);
// }

// void	Channel::removeAdmin(Client & who, Client & whom){

// 	if (not isAdmin(who)) {
// 		who.updateReplyMessage(ERR_CHANOPRIVSNEEDED(_ChannelName));
// 		return ;
// 	}
// 	if (_Admins.size() == 1){
// 		if (_Clients.size() > 0) {
// 			who.updateReplyMessage(ft::to_string(__LINE__) + " in Channel is need to set appropriate message");
// 			return ;
// 		}
// 		delete this; //Is it appropriate here?
// 	}
// 	std::set<Client const *>::iterator it = find(_Admins.begin(), _Admins.end(), &whom);
// 	if (it == _Admins.end()) {
// 		who.updateReplyMessage(ERR_NOSUCHNICK(whom.getNickName()));
// 		return ;
// 	}
// 	_Admins.erase(it);
// }
