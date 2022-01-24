#include "ACommand.hpp"

class QUIT : public ACommand {
private:
    QUIT();
    QUIT(QUIT const &that);
    QUIT& operator=(QUIT const &that);
public:
    QUIT(Server &Server):   ACommand("QUIT", Server) {}
    virtual ~QUIT() {}
    virtual int run(){
        if (_Argument.empty()) {
            _Argument = _Initiator->getNickName();
        }
        _Initiator->setReplyMessage(_Argument);
        _Server.sendMsg(_Initiator);
        _Server.removeUserByNickName(_Initiator->getNickName());
    }
};/*
   Parameters: [<Quit message>]

   A client session is ended with a quit message.  The server must close
   the connection to a client which sends a QUIT message. If a "Quit
   Message" is given, this will be sent instead of the default message,
   the nickname.

   When netsplits (disconnecting of two servers) occur, the quit message

   is composed of the names of two servers involved, separated by a
   space.  The first name is that of the server which is still connected
   and the second name is that of the server that has become
   disconnected.

   If, for some other reason, a client connection is closed without  the
   client  issuing  a  QUIT  command  (e.g.  client  dies and EOF occurs
   on socket), the server is required to fill in the quit  message  with
   some sort  of  message  reflecting the nature of the event which
   caused it to happen.

   Numeric Replies:

           None.

   Examples:

   QUIT :Gone to have lunch        ; Preferred message format.

*/