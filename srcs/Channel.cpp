#include "ft.hpp"
#include "Channel.hpp"
#include "Replies.hpp"
#include "Client.hpp"
#include "Server.hpp"

#include "NAMES.hpp"

Channel::Channel(
	string const & nameChannel,
	string const & key,
	Client * userAdmin,
	Server *Server,
	uint maxUserLimit)
	:	Modes(this),
		_maxUserLimit(maxUserLimit),
		_ChannelName(nameChannel),
		_Key(key),
		_Server(Server),
		_ToRemove(false) {
	_Clients.insert(userAdmin);
	setMode(userAdmin, 'o');
}

std::string const &Channel::getTopic() const{
	return _Topic;
}

bool Channel::isOnChannel(Client *whom) const {
	return _Clients.find(whom) not_eq _Clients.end();
}

std::set<Client *>::size_type Channel::getCountClients(){
	return _Clients.size();
}

void Channel::removeClient(Client *whom) {	
	int countUserO = 0;

	if (_ToRemove) {
		return ;
	}
	std::set<Client *>::iterator i = find(_Clients.begin(), _Clients.end(), whom);
	if (i not_eq _Clients.end()) {
		eraseClientFromModes(*i);
		_Clients.erase(i);
	}
	if (_Clients.empty()) {
		_ToRemove = true;
		_Server->pushBackErase(this);
	}
	else
	{	
		if (countUserO == 0)
			for(std::set<Client *>::iterator first = _Clients.begin();first != _Clients.end(); ++first)
				if (getModeIsExist(*first, 'o'))
					++countUserO;
		if (countUserO == 0 and ++countUserO)
			setMode(*_Clients.begin(), 'o');
		replyToAllMembers(whom->getFull() + " PART " + _ChannelName);
		NAMES n(*_Server);
		n.setArgument(_ChannelName);
		for(std::set<Client *>::iterator EachClient = _Clients.begin();EachClient != _Clients.end(); ++EachClient) {
			n.setInitiator(*EachClient);
			n.run();
		}
	}
}

void Channel::replyToAllMembers(std::string msg, Client * sender) {
	std::string Reply = msg;//_ChannelName +  " :" + msg;
	if (sender not_eq NULL) {
		for (std::set<Client *>::iterator i = _Clients.begin(); i not_eq _Clients.end(); ++i) {
			if (*i not_eq sender) {
				(*i)->updateReplyMessage(Reply, "");
			}
		}
	} else {
		for (std::set<Client *>::iterator i = _Clients.begin(); i not_eq _Clients.end(); ++i) {
			(*i)->updateReplyMessage(Reply, "");
		}
	}
}

void Channel::addToBan(std::string BanMask)
{
	if (BanMask.empty())
		return ;
	std::string str;
	if (BanMask.find("!@") != BanMask.npos)
		BanMask.insert(BanMask.find("!@") + 1, "*");
	if (BanMask[0] == '!')
		BanMask.insert(0, "*");
	while(BanMask.find("**") != BanMask.npos)
		BanMask.replace(BanMask.find("**"), 2, "*");
	std::vector<std::string> vec = ft::split(BanMask, "@!");
	switch (vec.size())
	{
		case 0: str = "*!*@*"; break;
		case 1: str = vec[0] + "!*@*"; break;
		case 2: str = vec[0] + "!" + vec[1] + "@*"; break;
		default:
		for (uint i = 0; i < vec.size(); i++)
		{
			str += vec[i];
			switch (i)
			{
				case 0: str += '!';	break;
				case 1: str += '@';	break;
			}
		}
		break;
	}
	_BanList.insert(str);
}
void Channel::removeFromBan(std::string const &BanMask)
{
SearchAgain:
	std::set<std::string>::iterator EachBanMaskInBanList = _BanList.begin();
	while (EachBanMaskInBanList not_eq _BanList.end()) {
		if (ft::wildcard(*EachBanMaskInBanList, BanMask)) {
			_BanList.erase(EachBanMaskInBanList);
			goto SearchAgain;
		}
		++EachBanMaskInBanList;
	}
}
bool Channel::isBanned(std::string const &NickName)
{
	for (std::set<std::string>::iterator EachBanMask = _BanList.begin();
		EachBanMask not_eq _BanList.end();
		++EachBanMask) {
		if (ft::wildcard(*EachBanMask, NickName)) {
			return true;
		}
	}
	return false;
}

Client * Channel::getClient(std::string nickName){
	std::set<Client *>::iterator beginClient = _Clients.begin();
	std::set<Client *>::iterator endClient = _Clients.end();

	nickName = ft::tolowerString(nickName);
	while(beginClient not_eq endClient)
	{
		if (nickName == ft::tolowerString((*beginClient)->_NickName))
			return *beginClient;
		++beginClient;
	}
	return NULL;
}

bool Channel::isInvited(Client *client){
    if (_InviteClients.find(client) != _InviteClients.end()){
        _InviteClients.erase(client);
        return true;
    }
    return false;
}
