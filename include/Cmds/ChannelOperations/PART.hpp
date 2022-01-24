#include "ACommand.hpp"

class PART : public ACommand {
private:
    PART();
    PART(PART const &that);
    PART& operator=(PART const &that);
public:
    PART(Server &Server):   ACommand("PART", Server) {}
    virtual ~PART() {}
    virtual int run(){
        if (_Argument.empty()) {
            _Initiator->setReplyMessage(ERR_NEEDMOREPARAMS(_Name));
            return ;
        }
        //code
    }
};/*
   Parameters: <channel>{,<channel>}

   The PART message causes the client sending the message to be removed
   from the list of active users for all given channels listed in the
   parameter string.

   Numeric Replies:

           ERR_NEEDMOREPARAMS              ERR_NOSUCHCHANNEL
           ERR_NOTONCHANNEL

   Examples:

   PART #twilight_zone             ; leave channel "#twilight_zone"

   PART #oz-ops,&group5            ; leave both channels "&group5" and
                                   "#oz-ops".

*/