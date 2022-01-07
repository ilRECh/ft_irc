#include "Mandatory.hpp"
#include "Password.hpp"

// * mode: true for encrypt, false for decrypt
string Password::cryptor(string const & dataPass, bool mode){
	std::string buf(dataPass);
	size_t len = dataPass.length();
	size_t i = 0;

	if (mode){
		srand(time(NULL));
		_Rand = rand();
		for (; i < len; i++)
			buf[i] = dataPass[i] + ((_Rand * (i + 1)) & 0xff);
	}else
		for (; i < len; i++)
			buf[i] = dataPass[i] - ((_Rand * (i + 1)) & 0xff);
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
