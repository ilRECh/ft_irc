#pragma once

#include "Mandatory.hpp"

using std::string;
using std::srand;
using std::rand;
using std::time;

class Password
{
private:
	string _Password;
	unsigned char   _Rand;
// * mode: true for encrypt, false for decrypt
	string cryptor(string const &, bool mode);
public:
	Password( void );
	Password(Password const & oth);
	virtual ~Password();
	int	setPassword(string const & oldPass, string const & newPass);
	//* if equal, returned 0
	int	comparePassword(string const & forCompare);
};
