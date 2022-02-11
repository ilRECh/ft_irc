#pragma once
#include "ACommand.hpp"

class KICK : public ACommand {
private:
    KICK();
    KICK(KICK const &that);
    KICK& operator=(KICK const &that);
public:
    KICK(Server &Server) : ACommand("KICK", Server) {}
    virtual ~KICK() {}
    virtual int run(){
        if (_Arguments.size() < 2) {
            return _Initiator->updateReplyMessage(ERR_NEEDMOREPARAMS(_Name));
        }
        ft::deleteSpaces(_Arguments[0], SPACE_SYMBOLS);
        ft::deleteSpaces(_Arguments[1], SPACE_SYMBOLS);
        if (_Arguments[0].find_first_of("&#"))  // Если в начале нет (# or &)
            return _Initiator->updateReplyMessage(ERR_BADCHANMASK(_Arguments[0]));
        Channel * chan = _Server.getChannelByChannelName(_Arguments[0]);
        if (not chan)
            return _Initiator->updateReplyMessage(ERR_NOSUCHCHANNEL(_Arguments[0]));
        if (not chan->getModeIsExist(_Initiator, 'o'))
            return _Initiator->updateReplyMessage(ERR_CHANOPRIVSNEEDED(_Arguments[0]));
        Client * client = chan->getClient(_Arguments[1]);
        if (not client)
            return _Initiator->updateReplyMessage(ERR_NOTONCHANNEL(chan->getChannelName()));
        if (_Arguments.size() > 2)
            chan->replyToAllMembers(_Initiator->getFull() + chan->getChannelName() + client->_NickName + " :" + _Arguments[3]);
        else
            chan->replyToAllMembers(_Initiator->getFull() + chan->getChannelName() + client->_NickName + " :" + client->_NickName);
        client->_Channels.erase(chan);
        chan->removeClient(client);
        return 0;
    }
};/*
   Parameters: <channel> <user> [<comment>]

   The KICK command can be  used  to  forcibly  remove  a  user  from  a
   channel.   It  'kicks  them  out'  of the channel (forced PART).

   Only a channel operator may kick another user out of a  channel.
   Each  server that  receives  a KICK message checks that it is valid
   (ie the sender is actually a  channel  operator)  before  removing
   the  victim  from  the channel.

   Numeric Replies:

           ERR_NEEDMOREPARAMS              ERR_NOSUCHCHANNEL
           ERR_BADCHANMASK                 ERR_CHANOPRIVSNEEDED
           ERR_NOTONCHANNEL

   Examples:

KICK &Melbourne Matthew         ; Kick Matthew from &Melbourne

KICK #Finnish John :Speaking English
                                ; Kick John from #Finnish using
                                "Speaking English" as the reason
                                (comment).

:WiZ KICK #Finnish John         ; KICK message from WiZ to remove John
                                from channel #Finnish

NOTE:
     It is possible to extend the KICK command parameters to the
following:

<channel>{,<channel>} <user>{,<user>} [<comment>]

*/
