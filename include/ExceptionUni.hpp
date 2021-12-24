#include <exception>
#include <string>

class ExceptionUni: public std::exception{
	std::string	reason;
public:
	ExceptionUni(std::string const reason);
	virtual ~ExceptionUni( void ) throw();
	const char * what( void ) const throw();
};