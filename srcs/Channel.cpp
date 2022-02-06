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
	else
	{
		if (_Clients.size() >= _maxUserLimit)
		{
			whom->updateReplyMessage(ERR_CHANNELISFULL(this->getChannelName()));
			return 1;
		}
	}
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
		eraseClientFromModes(*i);
		_Clients.erase(i);
	}
	if (_Clients.empty()) {
		ToRemove = true;
		_Server->pushBackErase(this);
	}
	replyToAllMembers("leaved", whom);
}

void Channel::replyToAllMembers(std::string msg, Client * sender) {
	std::string Reply = msg;//_ChannelName +  " :" + msg;
	if (sender != NULL) {
		for (std::set<Client *>::iterator i = _Clients.begin(); i != _Clients.end(); ++i) {
			if (*i != sender) {
				if ((*i)->updateReplyMessage(Reply)) {
					(*i)->updateReplyMessage(" 301 " + sender->getNickName() + " AWAY " + (*i)->getNickName() + " :" + (*i)->getAwayMessage());
				}
			}
		}
	} else {
		for (std::set<Client *>::iterator i = _Clients.begin(); i != _Clients.end(); ++i) {
			(*i)->updateReplyMessage(Reply);
		}
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
