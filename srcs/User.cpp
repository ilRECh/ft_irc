#include "Client.hpp"

#include "Server.hpp"
#include "Channel.hpp"

Client::Client(int const Fd)
	:	AUser(""),
		_Fd(Fd) {
}

bool Client::operator==(const Client& that) const {
	return _Name == that._Name;
}

bool Client::operator!=(const Client& that) const {
	return _Name != that._Name;
}

void Client::inviteToChannel(Channel const & channel) {
	_Channels.push_back(&channel);
}

void Client::setNickName(std::string const & NickName) {
	_NickName = NickName;
}

string const & Client::getNickName( void ) const {
	return _NickName;
}

// Registration
void Client::setRegistered(bool const Condition) {
	_Registration.IsRegistered = Condition;
}

bool Client::isRegistered() const {
	return _Registration.IsRegistered;
}

bool Client::unregisteredShouldDie() const {
	if (_Registration.Time.hasTimePassed(30)) {
		std::cout << _Name << " is unregistered. Died." << '\n';
		return true;
	}
	return false;
}

// Last activity
bool Client::inactiveShouldDie() const {
	if (_LastResponse.hasTimePassed(60)) {
		std::cout << _Name << " is inactive. Died." << '\n';
		return true;
	}
	return false;
}

void Client::updateActivity() {
	_LastResponse.updateBaseTime();
}

bool Client::isReadyForPing() const {
	if (_LastResponse.hasTimePassed(30) and not _LastResponse.hasTimePassed(60)) {
		return true;
	}
	return false;
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
	std::vector<Channel *>::iterator first, last;

	if (std::find(_Channels.begin(), _Channels.end(), channel) != _Channels.end())
		_Channels.push_back(channel);
}

std::vector<Channel const *> const & Client::getChannels() const {
	return _Channels;
}

status Client::setReplyMessage(std::string const & Msg) {
	_ReplyMessage += Msg + "\r\n";
	return 0;
}

std::string const Client::getReplyMessage() {
	std::string ret(_ReplyMessage);
	_ReplyMessage.clear();
	return ret;
}
