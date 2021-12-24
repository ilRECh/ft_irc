#include "ExceptionUni.hpp"

ExceptionUni::ExceptionUni(std::string const reason):reason(reason){}
ExceptionUni::~ExceptionUni( void ) throw(){}
const char * ExceptionUni::what( void ) const throw(){return reason.c_str();}