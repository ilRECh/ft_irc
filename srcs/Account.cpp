#include "Account.hpp"

Account::Account( void ){nickName.clear(); password.clear();}
Account::Account(const string & nickName, const string & password)
    :nickName(nickName), password(password){}
Account::Account(const Account & othAccount)
    :nickName(othAccount.getName()), password(othAccount.getPassword()){}
string  Account::getName( void ) const {return nickName;}
string  Account::getPassword( void ) const {return password;}
void    Account::setName(const string & newNick){nickName = newNick;}
void    Account::setPassword(const string & newPassword){password = newPassword;}
Account::~Account( void ){};
