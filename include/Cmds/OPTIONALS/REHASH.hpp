#include "ACommand.hpp"

class REHASH : public ACommand {
private:
    REHASH();
    REHASH(REHASH const &that);
    REHASH& operator=(REHASH const &that);
public:
    REHASH(Server const *Server):   ACommand("REHASH", Server) {}
    virtual ~REHASH() {}
    virtual int run(){
        if (_Argument.empty()) {
            std::string arr[] = { _Name };
            return reply(ERR_NEEDMOREPARAMS, _User->_Fd, _User->getName(), L(arr));
        }
        //code
    }
};/*
        Parameters: None

        The rehash message can be used by the operator to force the server to
        re-read and process its configuration file.

        Numeric Replies:

        RPL_REHASHING                   ERR_NOPRIVILEGES

        Examples:

        REHASH                          ;   message from client with operator
                                            status to server asking it to reread its
                                            configuration file.

*/