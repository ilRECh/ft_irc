#include "User.hpp"
#include "Server.hpp"
#include "Channel.hpp"

User::User(string const & Name, int const Fd)
	:	AUser(Name),
		_Fd(Fd) {
}

bool User::operator==(const User& that) const {
	return _Name == that._Name;
}

bool User::operator!=(const User& that) const {
	return _Name != that._Name;
}

void User::inviteToChannel(Channel const & channel) {
	_Channels.push_back(&channel);
}

void User::setNickName(std::string const & NickName) {
	_NickName = NickName;
}

string const & User::getNickName( void ) const {
	return _NickName;
}

void User::registeredIs(bool const Condition) {
	_IsRegistered = Condition;
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

bool User::getRegistered() const {
	return _IsRegistered;
}

<<<<<<< HEAD
void User::setChannel(Channel const * channel){
	std::vector<Channel *>::iterator first, last;

	if (std::find(_Channels.begin(), _Channels.end(), channel) != _Channels.end())
		_Channels.push_back(channel);
}

std::vector<Channel const *> const &
User::getChannels() const{
	return _Channels;
=======
void User::setReplyMessage(std::string const & Msg) {
	_ReplyMessage += Msg + "\r\n";
}

std::string const User::getReplyMessage() {
	std::string ret(_ReplyMessage);
	_ReplyMessage.clear();
	return ret;
>>>>>>> Ildar
}
