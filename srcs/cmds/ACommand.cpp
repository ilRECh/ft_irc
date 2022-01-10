#include "Mandatory.hpp"
#include "Commands.hpp"

ACommand::ACommand(std::string Name)
    :   _User(NULL),
        _Server(NULL),
        _Name(Name) {
    
}

ACommand::~ACommand() {}

ACommand::ACommand(ACommand const & that)
    :   _User(that._User),
        _Server(that._Server),
        _Name(that._Name)
{}

ACommand& ACommand::operator=(ACommand const & that) {
    if (&that == this) {
        return *this;
    }
    return *this;
}

std::string ACommand::assembleMsg() {
    std::string msg;
    for (std::vector<std::string>::iterator it = _Tokens.begin(); it != _Tokens.end() ; ++it) {
        msg += *it;
    }
    return msg;
}
