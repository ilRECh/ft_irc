#include "ACommand.hpp"

class PASS : public ACommand {
private:
    PASS();
    PASS(PASS const &that);
    PASS& operator=(PASS const &that);
public:
    PASS(Server const *Server) : ACommand("PASS", Server) {}
    virtual ~PASS() {}
    virtual int run(){
        if (_Argument.empty()) {
            std::string arr[] = { _Name };
            return reply(ERR_NEEDMOREPARAMS, _User->_Fd, _User->getName(), L(arr));
        } else if (_User->getRegistered() == true) {
            return reply(ERR_ALREADYREGISTRED, _User->_Fd, _User->getName());
        }
        _User->setPassword(_Argument);
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
