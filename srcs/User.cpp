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

bool User::getRegistered() const {
	return _IsRegistered;
}

void User::setReplyMessage(std::string const & Msg) {
	_ReplyMessage += Msg + "\r\n";
}

std::string const User::getReplyMessage() {
	std::string ret(_ReplyMessage);
	_ReplyMessage.clear();
	return ret;
}
