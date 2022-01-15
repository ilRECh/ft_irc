#include "Commands.hpp"

PASS::PASS(Server const *Server)
    :   ACommand("PASS", Server) {}

PASS::~PASS() {}

int PASS::run() {
    for (std::vector<std::string>::iterator it = _Tokens.begin(); it != _Tokens.end(); ++it) {
        std::cout << '|' << *it << '|' << '\n';
    }
    if (_Tokens.size() < 2 || _Tokens[2].empty()) {
        std::string arr[] = {"PASS"};
        return reply(ERR_NEEDMOREPARAMS, _User->_Fd, _User->getName(), L(arr));
    } else if (not _User->getPassword().empty()) {
        return reply(ERR_ALREADYREGISTRED, _User->_Fd, _User->getName());
    }
    _User->setPassword(_Tokens[1]);
    std::string arr[] = { ":", _User->getName(), " PASS ", _Tokens[1] };
    return reply(_User->_Fd, _User->getName(), L(arr));
}
