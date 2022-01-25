#pragma once
#include "ACommand.hpp"

class ISON : public ACommand {
private:
    ISON();
    ISON(ISON const &that);
    ISON& operator=(ISON const &that);
public:
    ISON(Server &Server) : ACommand("ISON", Server) {}
    virtual ~ISON() {}
    virtual int run(){
        if (_Argument.empty()) {
            return _Initiator->setReplyMessage(ERR_NEEDMOREPARAMS(_Name));
            
        }

        for (std::vector<Client *>::iterator it = _Users.begin();
             it != _Users.end(); ++it)
        {

        }
    }
};/*
        Parameters: <nickname>{<space><nickname>}

        The ISON command was implemented to provide  a  quick  and  efficient
        means  to get a response about whether a given nickname was currently
        on IRC. ISON only takes one (1) parameter: a space-separated list of
                nicks.  For  each  nickname in the list that is present, the server
        adds that to its reply string.  Thus the reply string may return
        empty (none  of  the given  nicks are present), an exact copy of the
                parameter string (all of them present) or as any other subset of the
        set of nicks  given  in  the parameter.  The only limit on the number
        of nicks that may be checked is that the combined length must not be
                too large as to cause the server to chop it off so it fits in 512
        characters.

        ISON is only be processed by the server local to the client sending
                the command and thus not passed onto other servers for further
                processing.

        Numeric Replies:

        RPL_ISON                ERR_NEEDMOREPARAMS

        Examples:

        ISON phone trillian WiZ jarlek Avalon Angel Monstah
                                            ; Sample ISON request for 7 nicks.
*/