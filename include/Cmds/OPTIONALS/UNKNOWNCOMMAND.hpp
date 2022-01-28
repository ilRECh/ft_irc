#pragma once
#include "ACommand.hpp"

class UNKNOWNCOMMAND : public ACommand {
private:
    UNKNOWNCOMMAND();
    UNKNOWNCOMMAND(UNKNOWNCOMMAND const &that);
    UNKNOWNCOMMAND& operator=(UNKNOWNCOMMAND const &that);
public:
    UNKNOWNCOMMAND(Server &Server) : ACommand("UNKNOWNCOMMAND", Server) {}
    virtual ~UNKNOWNCOMMAND() {}
    virtual int run(){
        if (not _Argument.empty()) {
            return _Initiator->updateReplyMessage(ERR_UNKNOWNCOMMAND(_Argument));
        }
        return 0;
    }
};
