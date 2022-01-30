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
	Client * userAdmin,
	eChannelPrivateLevel const ePrivateLevel)
	:	Modes(),
	_ChannelName(nameChannel) {
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
		if (not getModeIsExist(who, 'o')) {
			who->updateReplyMessage(ERR_CHANOPRIVSNEEDED(_ChannelName));
			return ;
		}
	}
	_Clients.insert(whom);
}

std::string const &Channel::getTopic() const {
	return _Topic;
}

void Channel::setTopic(std::string const & Topic) {
	_Topic = Topic;
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
