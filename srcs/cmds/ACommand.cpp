#include "Mandatory.hpp"
#include "Commands.hpp"

ACommand::ACommand(std::string Name, Server const *Server)
    :   _User(NULL),
        _Name(Name),
        _Server(Server) {
    
}

ACommand::~ACommand() {}

// void ACommand::setTokens(std::vector<std::string> const & Tokens) {
//     _Tokens = Tokens;
// }

void ACommand::setArgument(std::string const & Argument) {
    _Argument = Argument;
}

void ACommand::setUser(User *User) {
    _User = User;
}
