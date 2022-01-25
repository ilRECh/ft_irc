#include "ACommand.hpp"

class INFO : public ACommand {
private:
    INFO();
    INFO(INFO const &that);
    INFO& operator=(INFO const &that);
public:
    INFO(Server &Server) : ACommand("INFO", Server) {}
    virtual ~INFO() {}
    virtual int run(){
        if (_Arguments.empty()) {
            return _Initiator->updateReplyMessage(ERR_NEEDMOREPARAMS(_Name));
            
        }
        //code
    }
};/*
   Parameters: [<server>]

   The INFO command is required to return information which describes
   the server: its version, when it was compiled, the patchlevel, when
   it was started, and any other miscellaneous information which may be
   considered to be relevant.

   Numeric Replies:

           ERR_NOSUCHSERVER
           RPL_INFO                        RPL_ENDOFINFO

   Examples:

   INFO csd.bu.edu                 ; request an INFO reply from
   csd.bu.edu

   :Avalon INFO *.fi               ; INFO request from Avalon for first
                                   server found to match *.fi.

   INFO Angel                      ; request info from the server that
                                   Angel is connected to.

*/