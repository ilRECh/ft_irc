#include "User.hpp"

User::User(string const & name, Channel const & baseChannel){
	string::const_iterator it_begin = name.begin();
	string::const_iterator it_end = name.end();

	while(it_begin != it_end)
		if (!std::isalnum(*(it_begin++)))
			throw std::runtime_error("Name " + name + " is not valid, use A-Z, a-z, 0-9");
	this->inviteToChannel(baseChannel);
	this->_Name = name;
}
User::~User(){}
User::User(User& that): _Name(that._Name), _Channels(that._Channels){}
User& User::operator=(User& that){this->_Name = that._Name; return *this;}

bool User::operator==(const User& that) const {return this->_Name == that._Name;}
bool User::operator!=(const User& that) const {return this->_Name != that._Name;}

void User::inviteToChannel(Channel const & channel){_Channels.push_back(&channel);}
void User::setName(string const & name){
	string::const_iterator it_begin = name.begin();
	string::const_iterator it_end = name.end();

	while(it_begin != it_end)
		if (!std::isalnum(*(it_begin++)))
			throw std::runtime_error("Name " + name + " is not valid, use A-Z, a-z, 0-9");
	_Name = name;
}

string const & User::getName( void ) const {return _Name; }

