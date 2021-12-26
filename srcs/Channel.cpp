#include "Channel.hpp"

Channel::Channel(string const & nameChannel, User const & userAdmin){
	string::const_iterator beg = nameChannel.cbegin();
	string::const_iterator end = nameChannel.cend();

	while(beg != end)
		if (!std::isalnum(*(beg++)))
			throw ExceptionUni("Name channel " + nameChannel + " is not valid, use A-Z, a-z, 0-9");
	_Admins.push_back(userAdmin);
	_NameChannel = nameChannel;
}
Channel::~Channel(){}

void	Channel::setNameChannel(string const & newNameChannel){
	string::const_iterator beg = newNameChannel.cbegin();
	string::const_iterator end = newNameChannel.cend();

	while(beg != end)
		if (!std::isalnum(*(beg++)))
			throw ExceptionUni("Name channel " + newNameChannel + " is not valid, use A-Z, a-z, 0-9");
	_NameChannel = newNameChannel;
}

bool Channel::checkAdminPermist(User const & adminName) const{
	vector<User>::const_iterator beg = _Admins.cbegin();
	vector<User>::const_iterator end = _Admins.cend();

	while(beg != end)
		if (adminName == *(beg++))
			return true;
	return false;
}

const vector<User>& Channel::getAdmins(){ return _Admins;}

void	Channel::addAdmin(User const & name){
	vector<User>::iterator beg = _Admins.begin();
	vector<User>::iterator end = _Admins.end();

	while(beg != end)
		if (*beg == name)
			return ;
	_Admins.push_back(name);
}

void	Channel::dellAdmin(User const & name){
	vector<User>::iterator beg = _Admins.begin();
	vector<User>::iterator end = _Admins.end();

	while(beg != end)
		if (*beg == name)
			_Admins.erase(beg);
}