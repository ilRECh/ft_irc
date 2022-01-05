#include "Mandatory.hpp"
#include "Commands.hpp"

ACommand::ACommand(std::string Name)
    :   _Name(Name),
        _User(NULL),
        _Server(NULL) {
    
}

ACommand::~ACommand() {}

ACommand::ACommand(ACommand& that) {}

ACommand& ACommand::operator=(ACommand& that) {
    return *this;
}

std::string ACommand::assembleMsg() {
    std::string msg;
    for (std::vector<std::string>::iterator it = _Tokens.begin(); it != _Tokens.end() ; ++it) {
        msg += *it;
    }
    return msg;
}
