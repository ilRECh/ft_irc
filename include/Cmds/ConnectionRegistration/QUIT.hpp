#pragma once
#include "ACommand.hpp"

class QUIT : public ACommand {
private:
    QUIT();
    QUIT(QUIT const &that);
    QUIT& operator=(QUIT const &that);
    bool _ToInitiator;
    bool _ToInitiatorOnly;
public:
    QUIT(Server &Server)
        :   ACommand("QUIT", Server),
            _ToInitiator(false),
            _ToInitiatorOnly(false) {}
    virtual ~QUIT() {}
    virtual int run(){
        if (_Argument.find(':') != _Argument.npos and _Argument[_Argument.find(':') + 1]) {
            _Argument = _Argument.substr(_Argument.find(':') + 1);
        } else {
            _Argument = _Initiator->_NickName;
        }
        if (not _ToInitiatorOnly){
            for (std::set<Client *>::iterator ClientOnServer = _Server._Clients.begin();
                ClientOnServer != _Server._Clients.end(); ++ClientOnServer) {
                if ((*ClientOnServer != _Initiator and not _Server.getModeIsExist(*ClientOnServer, 'i')) or
                    (*ClientOnServer == _Initiator and _ToInitiator)) {
                    (*ClientOnServer)->updateReplyMessage(_Initiator->_NickName + " QUIT " +
                        (*ClientOnServer)->_NickName + " :" + _Argument);
                }
            }
        } else {
            _Initiator->updateReplyMessage(_Initiator->_NickName + " QUIT " + _Initiator->_NickName + " :" + _Argument);
        }
        _Server.pushBackErase(_Initiator);
        return 0;
    }
    void isNeedToBeSentToInitiator() {
        _ToInitiator = true;
    }
    void isNeedToBeSentToInitiatorOnly() {
        _ToInitiatorOnly = true;
    }
    void setQuitInitiator(Client *Initiator) {
        _Initiator = Initiator;
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
