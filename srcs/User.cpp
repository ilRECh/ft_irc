#include "User.hpp"

User::User(string const & name){
	string::const_iterator it_begin = name.cbegin();
	string::const_iterator it_end = name.cend();

	while(it_begin != it_end)
		if (!std::isalnum(*(it_begin++)))
			throw ExceptionUni("Name " + name + " is not valid, use A-Z, a-z, 0-9");
	_Name = name;
}
User::~User(){}
User::User(User& that): _Name(that._Name){}
User& User::operator=(User& that){this->_Name = that._Name; return *this;}

bool User::operator==(const User& that) const {return this->_Name == that._Name;}
bool User::operator!=(const User& that) const {return this->_Name != that._Name;}

void User::setName(string const & name){
	string::const_iterator it_begin = name.cbegin();
	string::const_iterator it_end = name.cend();

	while(it_begin != it_end)
		if (!std::isalnum(*(it_begin++)))
			throw ExceptionUni("Name " + name + " is not valid, use A-Z, a-z, 0-9");
	_Name = name;
}

