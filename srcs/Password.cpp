#include "Password.hpp"

// * mode: true for encrypt, false for decrypt
string Password::cryptor(string const & dataPass, bool mode){
	char		buf[dataPass.length() + 1];
	char const	*cDataPass = dataPass.c_str();
	size_t len = dataPass.length();
	size_t i = 0;

	if (mode){
		srand(time(NULL));
		_Rand = rand();
		for (; i < len; i++)
			buf[i] = cDataPass[i] + ((_Rand * (i + 1)) & 0b11111111);
	}else
		for (; i < len; i++)
			buf[i] = cDataPass[i] - ((_Rand * (i + 1)) & 0b11111111);
	buf[len] = 0;
	return (buf);
}

Password::Password( void ){}
Password::~Password( void ){}

Password::Password(Password const & oth)
: _Password(oth._Password), _Rand(oth._Rand){}

int	Password::setPassword(string const & oldPass, string const & newPass){
	if (oldPass != cryptor(_Password, false))
		return -1;
	_Password = cryptor(newPass, true);
	return 0;
}

//* if equal, returned 0
int	Password::comparePassword(string const & forCompare){
	if (cryptor(_Password, false) != forCompare)
		return -1;
	return 0;
}
