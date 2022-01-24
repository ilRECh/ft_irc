#include "ACommand.hpp"

class SomeCmds : public ACommand {
private:
    SomeCmds();
    SomeCmds(SomeCmds const &that);
    SomeCmds& operator=(SomeCmds const &that);
public:
    SomeCmds(Server &Server) : Acommand("SomeCmds", Server) {}
    virtual ~SomeCmds() {}
    virtual int run(){
        if (_Argument.empty()) {
            return _Initiator->setReplyMessage(ERR_NEEDMOREPARAMS(_Name));
            
        }
        //code
    }
};/*
        Parameters: Text to be sent to all operators currently online

        Sends  a  message  to  all   operators   currently   online.    After
        implementing  WALLOPS  as  a user command it was found that it was
        often and commonly abused as a means of sending a message to a lot
        of  people (much  similar to WALL).  Due to this it is recommended
        that the current implementation of  WALLOPS  be  used  as  an
        example  by  allowing  and recognising only servers as the senders of
        WALLOPS.

        Numeric Replies:

        ERR_NEEDMOREPARAMS

        Examples:

        :csd.bu.edu WALLOPS :Connect '*.uiuc.edu 6667' from Joshua
                    ; WALLOPS message from csd.bu.edu announcing a
                    CONNECT message it received and acted upon from Joshua.

*/