#pragma once
#include "ACommand.hpp"

class VERSION : public ACommand {
private:
    VERSION();
    VERSION(VERSION const &that);
    VERSION& operator=(VERSION const &that);
public:
    VERSION(Server &Server) : ACommand("VERSION", Server) {}
    virtual ~VERSION() {}
    virtual int run(){
        if (_Arguments.empty()) {
            return _Initiator->updateReplyMessage(ERR_NEEDMOREPARAMS(_Name));
            
        }
        //code
    }
};/*
   Parameters: [<server>]

   The VERSION message is used  to  query  the  version  of  the  server
   program.  An optional parameter <server> is used to query the version
   of the server program which a client is not directly connected to.

   Numeric Replies:

           ERR_NOSUCHSERVER                RPL_VERSION

   Examples:

   :Wiz VERSION *.se               ; message from Wiz to check the version
                                   of a server matching "*.se"

   VERSION tolsun.oulu.fi          ; check the version of server
                                   "tolsun.oulu.fi".

*/