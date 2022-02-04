#include "ft.hpp"
#include "Channel.hpp"
#include "Replies.hpp"
#include "Client.hpp"
#include "Server.hpp"

Channel::Channel(
	string const & nameChannel,
	Client * userAdmin,
	Server *Server,
	uint maxUserLimit)
	:	Modes(this),
		_maxUserLimit(maxUserLimit),
		_ChannelName(nameChannel),
		_Server(Server){
	_Clients.insert(userAdmin);
	setMode(userAdmin, 'o');

}

bool Channel::isOnChannel(Client *whom) const {
	return _Clients.find(whom) != _Clients.end();
}

int	Channel::addClient(Client *whom, Client *_Initiator) {
	if (std::find(_Clients.begin(), _Clients.end(), whom) != _Clients.end())
		return 0;
	if (std::find(_BanList.begin(), _BanList.end(), whom) != _BanList.end())
	{
		(_Initiator ? _Initiator : whom)->updateReplyMessage(ERR_BANNEDFROMCHAN(_ChannelName));
		return 1;
	}
	if (_Initiator != NULL)
	{
		if (_Clients.size() >= _maxUserLimit)
		{
			_Initiator->updateReplyMessage(ERR_CHANNELISFULL(this->getChannelName()));
			return 1;
		}
		if (getModeIsExist(this, 'i') && not getModeIsExist(_Initiator, 'o')) {
			_Initiator->updateReplyMessage(ERR_CHANOPRIVSNEEDED(_ChannelName));
			return 1;
		}
	}
	replyToAllMembers("joined", whom);
	_Clients.insert(whom);
	return 0;
}

std::string const &Channel::getTopic() const {
	return _Topic;
}

void Channel::setTopic(std::string const & Topic) {
	_Topic = Topic;
}

void Channel::removeClient(Client *whom) {
	//? Если был удален последний Админ, то передать полномочия другому юзеру
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
	replyToAllMembers("leaved", whom);
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
