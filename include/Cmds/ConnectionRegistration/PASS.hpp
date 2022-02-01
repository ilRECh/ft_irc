#pragma once
#include "ACommand.hpp"

class PASS : public ACommand {
private:
    PASS();
    PASS(PASS const &that);
    PASS& operator=(PASS const &that);
public:
    PASS(Server & Server) : ACommand("PASS", Server) {}
    virtual ~PASS() {}
    virtual int run() {
        if (_Initiator->_Registration.IsRegistered == true) {
            return _Initiator->updateReplyMessage(ERR_ALREADYREGISTRED);
        } else if (_Arguments.empty()) {
            return _Initiator->updateReplyMessage(ERR_NEEDMOREPARAMS(_Name));
        } else if (not _Initiator->_RealName.empty()) {
            return 0;
        }
        _Initiator->_Password = ft::split(_Argument, " :").end()[-1];
        return 0;
    }
};/*
   Parameters: <password>

   The PASS command is used to set a 'connection password'.  The
   password can and must be set before any attempt to register the
   connection is made.  Currently this requires that clients send a PASS
   command before sending the NICK/USER combination and servers *must*
   send a PASS command before any SERVER command.  The password supplied
   must match the one contained in the C/N lines (for servers) or I
   lines (for clients).  It is possible to send multiple PASS commands
   before registering but only the last one sent is used for
   verification and it may not be changed once registered.  Numeric
   Replies:

           ERR_NEEDMOREPARAMS              ERR_ALREADYREGISTRED

   Example:

           PASS secretpasswordhere
*/
