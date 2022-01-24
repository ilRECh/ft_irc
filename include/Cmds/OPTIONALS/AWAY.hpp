#include "ACommand.hpp"

class AWAY : public ACommand {
private:
    AWAY();
    AWAY(AWAY const &that);
    AWAY& operator=(AWAY const &that);
public:
    AWAY(Server &Server):   ACommand("AWAY", Server) {}
    virtual ~AWAY() {}
    virtual int run(){
        if (_Argument.empty()) {
            _Initiator->setReplyMessage(ERR_NEEDMOREPARAMS(_Name));
            return ;
        }
        //code
    }
};/*
        Parameters: [message]

        With the AWAY message, clients can set an automatic reply string for
        any PRIVMSG commands directed at them (not to a channel they are on).
        The automatic reply is sent by the server to client sending the
        PRIVMSG command.  The only replying server is the one to which the
        sending client is connected to.

        The AWAY message is used either with one parameter (to set an AWAY
        message) or with no parameters (to remove the AWAY message).

        Numeric Replies:

        RPL_UNAWAY                      RPL_NOWAWAY

        Examples:

        AWAY :Gone to lunch.  Back in 5 ;   set away message to "Gone to lunch.
                                            Back in 5".

        :WiZ AWAY                       ;   unmark WiZ as being away.

*/
