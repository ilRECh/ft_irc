#pragma once
#include "ACommand.hpp"

class PART : public ACommand {
private:
    PART();
    PART(PART const &that);
    PART& operator=(PART const &that);
public:
    PART(Server &Server) : ACommand("PART", Server) {}
    virtual ~PART() {}
    virtual int run(){
        if (_Argument.empty()) {
            return _Initiator->updateReplyMessage(ERR_NEEDMOREPARAMS(_Name));
        }
        _Arguments = ft::split(_Argument, " ,");
        std::string Reply;
        for (std::vector<std::string>::iterator i = _Arguments.begin(); i not_eq _Arguments.end(); ++i) {
            std::string ChannelName(*i);
            Channel *FoundChannel = _Server.getChannelByChannelName(ChannelName);
            if (not FoundChannel) {
                Reply += ERR_NOSUCHCHANNEL(ChannelName);
            } else if (not FoundChannel->isOnChannel(_Initiator)) {
                Reply += ERR_NOTONCHANNEL(ChannelName);
            } else {
                FoundChannel->removeClient(_Initiator);
            }
            if (not Reply.empty() and i + 1 not_eq _Arguments.end()) {
                Reply += "\r\n";
            }
        }
        if (not Reply.empty()) {
            return _Initiator->updateReplyMessage(Reply);
        }
        return 0;
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
