#pragma once
#include "ACommand.hpp"

class QUIT : public ACommand {
private:
    QUIT();
    QUIT(QUIT const &that);
    QUIT& operator=(QUIT const &that);
    Client *_Target;
public:
    QUIT(Server &Server) : ACommand("QUIT", Server) {}
    virtual ~QUIT() {}
    virtual int run(){
        Client *ClientToErase = _Initiator != NULL ? _Initiator : _Target;
        std::string Reply = _Argument.empty() ? ClientToErase->_NickName : _Argument;
        ClientToErase->updateReplyMessage(Reply);
        _Server.pushBackErase(ClientToErase);
        return 0;
    }
    void setTarget(Client *Target) {
        _Target = Target;
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
