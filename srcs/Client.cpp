#include "Client.hpp"
#include "Server.hpp"
#include "Channel.hpp"

Client::Client(int const Fd)
	:	AUser(""),
		_Fd(Fd) {}

bool Client::operator==(const Client& that) const {
	return _Name == that._Name;
}

bool Client::operator!=(const Client& that) const {
	return _Name != that._Name;
}

void Client::inviteToChannel(Channel const & channel) {
	_Channels.insert(&channel);
}

string const & Client::getNickName() const { return _NickName; }

bool Client::unregisteredShouldDie() const {
	if (not _Registration.IsRegistered
		and _Registration.Time.hasTimePassed(MAY_BE_UNREGISTERED_seconds)) {
		return true;
	}
	return false;
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

// void Client::PINGisSent() {
// 	_Activity.WaitingForPONG = true;
// }

bool Client::isWaitingForPONG() const {
	return _Activity.WaitingForPONG;
}

//	* get|set mode
bool Client::getModeIsExist(char c) const {
	return _mode_set.find(c) != _mode_set.end();
}
void	Client::setMode(char c){
	_mode_set.insert(c);
}
void	Client::unsetMode(char c){
	_mode_set.erase(c);
}

TimeStamp const & Client::getTime() const{
	return _time;
}

void Client::setChannel(Channel const * channel){
	std::set<Channel *>::iterator first, last;

	if (std::find(_Channels.begin(), _Channels.end(), channel) != _Channels.end())
		_Channels.insert(channel);
}

std::set<Channel const *> const & Client::getChannels() const {
	return _Channels;
}

status Client::updateReplyMessage(std::string const & Msg) {
	_ReplyMessage += _time.getTimeStrCurrent() + " " + Msg + "\r\n";
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
