#include "ACommand.hpp"

class NOTICE : public ACommand {
private:
    NOTICE();
    NOTICE(NOTICE const &that);
    NOTICE& operator=(NOTICE const &that);
public:
    NOTICE(Server &Server) : Acommand("NOTICE", Server) {}
    virtual ~NOTICE() {}
    virtual int run(){
        if (_Argument.empty()) {
            return _Initiator->setReplyMessage(ERR_NEEDMOREPARAMS(_Name));
            
        }
        //code
    }
};/*
        Parameters: <nickname> <text>

        The NOTICE message is used similarly to PRIVMSG.  The difference
        between NOTICE and PRIVMSG is that automatic replies must never be
        sent in response to a NOTICE message.  This rule applies to servers
        too - they must not send any error reply back to the client on
        receipt of a notice.  The object of this rule is to avoid loops
        between a client automatically sending something in response to
        something it received.  This is typically used by automatons (clients
        with either an AI or other interactive program controlling their
        actions) which are always seen to be replying lest they end up in a
        loop with another automaton.

        See PRIVMSG for more details on replies and examples.

*/