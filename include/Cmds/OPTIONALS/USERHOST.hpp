#pragma once
#include "ACommand.hpp"

class SomeCmds : public ACommand {
private:
    SomeCmds();
    SomeCmds(SomeCmds const &that);
    SomeCmds& operator=(SomeCmds const &that);
public:
    SomeCmds(Server &Server) : ACommand("SomeCmds", Server) {}
    virtual ~SomeCmds() {}
    virtual int run(){
        if (_Arguments.empty()) {
            return _Initiator->updateReplyMessage(ERR_NEEDMOREPARAMS(_Name));
            
        }
        //code
    }
};/*
        Parameters: <nickname>{<space><nickname>}

        The USERHOST command takes a list of up to 5 nicknames, each
        separated by a space character and returns a list of information
        about each nickname that it found.  The returned list has each reply
        separated by a space.

        Numeric Replies:

        RPL_USERHOST                    ERR_NEEDMOREPARAMS

        Examples:

        USERHOST Wiz Michael Marty p    ;USERHOST request for information on
                                        nicks "Wiz", "Michael", "Marty" and "p"

*/