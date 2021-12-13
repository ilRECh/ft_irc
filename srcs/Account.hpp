#pragma once
#include <string>

using   std::string;
class Account
{
private:
    string nickName;
    string password;
public:
    Account( void );
    Account(const string & nickName, const string & password);
    Account(const Account & othAccount);
    string  getName( void ) const;
    string  getPassword( void ) const;
    void    setName(const string & newName);
    void    setPassword(const string & newPassword);
    virtual ~Account( void );
};
