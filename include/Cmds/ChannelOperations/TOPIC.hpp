#pragma once
#include "ACommand.hpp"

class TOPIC : public ACommand {
private:
    TOPIC();
    TOPIC(TOPIC const &that);
    TOPIC& operator=(TOPIC const &that);
public:
    TOPIC(Server &Server) : ACommand("TOPIC", Server) {}
    virtual ~TOPIC() {}
    virtual int run(){
        if (_Arguments.empty() or (_Arguments[0][0] != '#' and _Arguments[0][0] != '&')) {
            return _Initiator->updateReplyMessage(ERR_NEEDMOREPARAMS(_Name));
        }
        std::string ChannelName = _Arguments[0];
        Channel *FoundChannel = _Server.getChannelByChannelName(ChannelName);
        if (FoundChannel and not FoundChannel->isOnChannel(_Initiator)) {
            return _Initiator->updateReplyMessage(ERR_NOTONCHANNEL(ChannelName));
        } else {
            return _Initiator->updateReplyMessage(ERR_NOSUCHCHANNEL(ChannelName));
        }
        std::vector<std::string> Topic = ft::split(_Argument, ":");
        if (Topic.size() != 2) {
            if (FoundChannel->getTopic().empty()) {
                return _Initiator->updateReplyMessage(RPL_NOTOPIC(ChannelName));
            }
            return _Initiator->updateReplyMessage(RPL_TOPIC(ChannelName, FoundChannel->getTopic()));
        } else {
            if (not FoundChannel->getModeIsExist(_Initiator, '0')) {
                return _Initiator->updateReplyMessage(ERR_CHANOPRIVSNEEDED(ChannelName));
            }
            FoundChannel->setTopic(Topic[1]);
        }
        return 0;
    }
};/*
   Parameters: <channel> [<topic>]

   The TOPIC message is used to change or view the topic of a channel.
   The topic for channel <channel> is returned if there is no <topic>
   given.  If the <topic> parameter is present, the topic for that
   channel will be changed, if the channel modes permit this action.

   Numeric Replies:

           ERR_NEEDMOREPARAMS              ERR_NOTONCHANNEL
           RPL_NOTOPIC                     RPL_TOPIC
           ERR_CHANOPRIVSNEEDED

   Examples:

   :Wiz TOPIC #test :New topic     ;User Wiz setting the topic.

   TOPIC #test :another topic      ;set the topic on #test to "another
                                   topic".

   TOPIC #test                     ; check the topic for #test.

*/
