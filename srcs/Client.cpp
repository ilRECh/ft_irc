#include "Client.hpp"
#include "Server.hpp"
#include "Channel.hpp"

Client::Client(int const Fd, std::string HostName)
	:	_lastJoin(NULL),
		_HostName(HostName),
		_Fd(Fd) {}

bool Client::operator==(const Client& that) const {
	return _UserName == that._UserName;
}

bool Client::operator!=(const Client& that) const {
	return _UserName != that._UserName;
}

string const & Client::getNickName() const { return _NickName; }

bool Client::unregisteredShouldDie() const {
	if (not _Registration.IsRegistered
		and _Registration.Time.hasTimePassed(MAY_BE_UNREGISTERED_seconds)) {
		return true;
	}
	return false;
}

// get IP address
std::string Client::getAddresIP() const{
#ifdef __linux__
    sockaddr_in AddrUser = {0,0,{0},{0}};
#elif __APPLE__
    sockaddr_in AddrUser = {0,0,0,{0},{0}};
#endif
	socklen_t Socklen = sizeof(AddrUser);
	getpeername(this->_Fd, (sockaddr *) &AddrUser, &Socklen);
	return inet_ntoa(AddrUser.sin_addr);
}

// Last activity
bool Client::inactiveShouldDie() const {
	if (_Activity.WaitingForPONG and
		_Activity.LastResponse.hasTimePassed(MAY_BE_INACTIVE_seconds)) {
		return true;
	}
	return false;
}

void Client::updateActivity() {
	_Activity.LastResponse.updateBaseTime();
	_Activity.LastPING.updateBaseTime();
	_Activity.WaitingForPONG = false;
}

bool Client::ServerNeedToPING() const {
	if (not _Activity.WaitingForPONG and
		_Activity.LastPING.hasTimePassed(MAY_BE_INACTIVE_seconds / 2)) {
		return true;
	}
	return false;
}

bool Client::isWaitingForPONG() const {
	return _Activity.WaitingForPONG;
}

TimeStamp const & Client::getTime() const{
	return _time;
}

TimeStamp const & Client::getLastActivity() const{
	return std::max(_Activity.LastResponse, _Activity.LastPING);
}

// void Client::inviteToChannel(Channel * channel, Client * Iniciator){
// 	std::set<Channel *>::iterator first, last;

// 	if (channel->addClient(this, Iniciator ? Iniciator : this))
// 		return ;
// 	_lastJoin = channel;
// 	if (std::find(_Channels.begin(), _Channels.end(), channel) != _Channels.end())
// 		_Channels.insert(channel);
// }

void Client::leaveFromChannel(Channel * channel)
{
	channel->removeClient(this);
	_Channels.erase(channel);
}

std::set<Channel *> const & Client::getChannels() const {
	return _Channels;
}

bool Client::isOnChannel(Channel * channel){
	return _Channels.find(channel) != _Channels.end();
}

bool Client::updateReplyMessage(std::string const & Msg, std::string const & From) {
	_ReplyMessage += ":" + From + Msg + "\r\n";
    if (!_Away.empty()){
        return 1;
	}
	return 0;
}

std::string const Client::getReplyMessage() {
	std::string ret(_ReplyMessage);
	_ReplyMessage.clear();
	return ret;
}

std::string& Client::getIncomingBuffer() {
	return _IncomingBuffer;
}
