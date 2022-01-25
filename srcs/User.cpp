#include "User.hpp"
#include "Server.hpp"
#include "Channel.hpp"

User::User(int const Fd)
	:	AUser(""),
		_Fd(Fd) {}

bool User::operator==(const User& that) const {
	return _Name == that._Name;
}

bool User::operator!=(const User& that) const {
	return _Name != that._Name;
}

void User::inviteToChannel(Channel const & channel) {
	_Channels.push_back(&channel);
}

// Names get|set
void User::setNickName(std::string const & NickName) { _NickName = NickName; }
string const & User::getNickName() const { return _NickName; }

void User::setRealName(std::string const & RealName) { _RealName = RealName; }
string const & User::getRealName() const { return _RealName; }

void User::setHostName(std::string const & HostName) { _HostName = HostName; }
string const & User::getHostName() const { return _HostName; }

void User::setServerName(std::string const & ServerName) { _ServerName = ServerName; }
string const & User::getServerName() const { return _ServerName; }

// Registration
void User::setRegistered(bool const Condition) {
	_Registration.IsRegistered = Condition;
}

bool User::isRegistered() const {
	return _Registration.IsRegistered;
}

bool User::unregisteredShouldDie() const {
	if (not _Registration.IsRegistered
		and _Registration.Time.hasTimePassed(MAY_BE_UNREGISTERED_seconds)) {
		return true;
	}
	return false;
}

// Last activity
bool User::inactiveShouldDie() const {
	if (_LastResponse.hasTimePassed(MAY_BE_INACTIVE_seconds)) {
		return true;
	}
	return false;
}

void User::updateActivity() {
	_LastResponse.updateBaseTime();
}

bool User::isReadyForPing() const {
	if (_LastResponse.hasTimePassed(MAY_BE_INACTIVE_seconds / 2)
		and not _LastResponse.hasTimePassed(MAY_BE_INACTIVE_seconds)) {
		return true;
	}
	return false;
}

//	* get|set mode
bool User::getModeIsExist(char c) const {
	return _mode_set.find(c) != _mode_set.end();
}
void	User::setMode(char c){
	_mode_set.insert(c);
}
void	User::unsetMode(char c){
	_mode_set.erase(c);
}

TimeStamp const & User::getTime() const{
	return _time;
}

void User::setChannel(Channel const * channel){
	std::vector<Channel *>::iterator first, last;

	if (std::find(_Channels.begin(), _Channels.end(), channel) != _Channels.end())
		_Channels.push_back(channel);
}

std::vector<Channel const *> const & User::getChannels() const {
	return _Channels;
}

status User::updateReplyMessage(std::string const & Msg) {
	_ReplyMessage += Msg + "\r\n";
	return 0;
}

std::string const User::getReplyMessage() {
	std::string ret(_ReplyMessage);
	_ReplyMessage.clear();
	return ret;
}
