#include "Commands.hpp"

PASS::PASS(Server const *Server)
    :   ACommand("PASS", Server) {}

PASS::~PASS() {}

int PASS::run() {
    if (_Argument.empty()) {
        std::string arr[] = { _Name };
        return reply(ERR_NEEDMOREPARAMS, _User->_Fd, _User->getName(), L(arr));
    } else if (_User->getRegistered() == true) {
        return reply(ERR_ALREADYREGISTRED, _User->_Fd, _User->getName());
    }
    _User->setPassword(_Argument);
    std::string arr[] = { ":", _User->getName(), " ", _Name, _Argument };
    return reply(_User->_Fd, _User->getName(), L(arr));
}
