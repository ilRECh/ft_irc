#include "ACommand.hpp"

class SomeCmds : public ACommand {
private:
    SomeCmds();
    SomeCmds(SomeCmds const &that);
    SomeCmds& operator=(SomeCmds const &that);
public:
    SomeCmds(Server &Server):   ACommand("SomeCmds", Server) {}
    virtual ~SomeCmds() {}
    virtual int run(){
        if (_Argument.empty()) {
            _Initiator->setReplyMessage(ERR_NEEDMOREPARAMS(_Name));
            return ;
        }
        //code
    }
};/*
        Parameters: [<server>]

        The USERS command returns a list of users logged into the server in a
        similar  format  to  who(1),  rusers(1)  and finger(1).  Some people
        may disable this command on their server for security related
        reasons.   If disabled, the correct numeric must be returned to
        indicate this.

        Numeric Replies:

        ERR_NOSUCHSERVER                ERR_FILEERROR
        RPL_USERSSTART                  RPL_USERS
        RPL_NOUSERS                     RPL_ENDOFUSERS
        ERR_USERSDISABLED

        Disabled Reply:

        ERR_USERSDISABLED

        Examples:

        USERS eff.org                   ; request a list of users logged in on
                                        server eff.org

        :John USERS tolsun.oulu.fi      ; request from John for a list of users
                                        logged in on server tolsun.oulu.fi

*/
