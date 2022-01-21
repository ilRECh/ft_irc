#include "User.hpp"
#include "Server.hpp"
#include "Channel.hpp"

User::User(string const & Name, int const Fd)
	:	AUser(Name),
		_Fd(Fd) {
	
	//this->inviteToChannel(BaseChannel);
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

string const & User::getNickName( void ) const {
	return _NickName;
}

void User::registeredIs(bool const Condition) {
	_IsRegistered = Condition;
}

bool User::getRegistered() const {
	return _IsRegistered;
}
