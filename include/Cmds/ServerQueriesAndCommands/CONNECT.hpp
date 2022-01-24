#include "ACommand.hpp"

class CONNECT : public ACommand {
private:
    CONNECT();
    CONNECT(CONNECT const &that);
    CONNECT& operator=(CONNECT const &that);
public:
    CONNECT(Server &Server) : ACommand("CONNECT", Server) {}
    virtual ~CONNECT() {}
    virtual int run(){
        if (_Argument.empty()) {
            return _Initiator->setReplyMessage(ERR_NEEDMOREPARAMS(_Name));
            
        }
        //code
    }
};/*   Parameters: <target server> [<port> [<remote server>]]

   The CONNECT command can be used to force a server to try to establish
   a new connection to another server immediately.  CONNECT is a
   privileged command and is to be available only to IRC Operators.  If
   a remote server is given then the CONNECT attempt is made by that
   server to <target server> and <port>.

   Numeric Replies:

           ERR_NOSUCHSERVER                ERR_NOPRIVILEGES
           ERR_NEEDMOREPARAMS

   Examples:

   CONNECT tolsun.oulu.fi          ; Attempt to connect a server to
                                   tolsun.oulu.fi

   :WiZ CONNECT eff.org 6667 csd.bu.edu
                                   ; CONNECT attempt by WiZ to get servers
                                   eff.org and csd.bu.edu connected on port
                                   6667.

*/