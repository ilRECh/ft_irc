#include "User.hpp"

User::User( 
	string const & Name,
	// Channel const & BaseChannel,
	int const Fd,
	sockaddr_in const AddrUser,
	socklen_t const Socklen)
	:	_Name(Name),
		_Fd(Fd),
		_AddrUser(AddrUser),
		_Socklen(Socklen) {
	string::const_iterator it_begin = Name.begin();
	string::const_iterator it_end = Name.end();

	while(it_begin != it_end)
		if (!std::isalnum(*(it_begin++)))
			throw std::runtime_error("Name " + Name + " is not valid, use A-Z, a-z, 0-9");
	//this->inviteToChannel(BaseChannel);
}

User::~User() {}

User::User(User& that)
	:	_Channels(that._Channels),
		_Name(that._Name),
		_Fd(that._Fd),
		_AddrUser(that._AddrUser),
		_Socklen(that._Socklen)
{}

User& User::operator=(User& that) {
	if (&that == this) {
		return *this;
	}
	return *this;
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

void User::setName(string const & name) {
	string::const_iterator it_begin = name.begin();
	string::const_iterator it_end = name.end();

	while(it_begin != it_end)
		if (!std::isalnum(*(it_begin++)))
			throw std::runtime_error("Name " + name + " is not valid, use A-Z, a-z, 0-9");
	_Name = name;
}

string const & User::getName( void ) const {
	return _Name;
}

string const & User::getNickName( void ) const {
	return _NickName;
}

void User::setPassword(std::string const & Password) {
	_Password = Password;
}

std::string const & User::getPassword() const {
	return _Password;
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

void User::setChannel(Channel const * channel){
	std::vector<Channel *>::iterator first, last;

	if (std::find(_Channels.begin(), _Channels.end(), channel) != _Channels.end())
		_Channels.push_back(channel);
}

std::vector<Channel const *> const &
User::getChannels() const{
	return _Channels;
}
