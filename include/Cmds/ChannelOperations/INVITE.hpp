#pragma once
#include "ACommand.hpp"

class INVITE : public ACommand {
private:
	INVITE();
	INVITE(INVITE const &that);
	INVITE& operator=(INVITE const &that);
public:
	INVITE(Server &Server) : ACommand("INVITE", Server) {}
	virtual ~INVITE() {}
	virtual int run(){
		if (_Arguments.size() < 2) {
			return _Initiator->updateReplyMessage(ERR_NEEDMOREPARAMS(_Name));
		}
		ft::deleteSpaces(_Arguments[0], SPACE_SYMBOLS);
		ft::deleteSpaces(_Arguments[1], SPACE_SYMBOLS);
		Client * client = _Server.getUserByNickName(_Arguments[0]);
		Channel * channel = _Server.getChannelByChannelName(_Arguments[1]);
		if (!client)
			return _Initiator->updateReplyMessage(ERR_NOSUCHNICK(_Arguments[0]));
		if (!channel)
			return _Initiator->updateReplyMessage(ERR_NOSUCHCHANNEL (_Arguments[1]));
		if (channel->isOnChannel(client))
			return _Initiator->updateReplyMessage(ERR_USERONCHANNEL(client->_NickName, channel->getChannelName()));
		if (!channel->isOnChannel(_Initiator))
			return _Initiator->updateReplyMessage(ERR_NOTONCHANNEL(channel->getChannelName()));
		if (!channel->getModeIsExist(_Initiator, 'o'))
			return _Initiator->updateReplyMessage(ERR_CHANOPRIVSNEEDED(channel->getChannelName()));
		_Initiator->updateReplyMessage(RPL_INVITING(_Arguments[1], client->_NickName));
		client->updateReplyMessage(" INVITE " + client->_NickName + " :" + channel->getChannelName(), _Initiator->getFull());
        if (channel->getModeIsExist(channel, 'i'))
		    channel->_InviteClients.insert(client);
		return 0;
	}
};/*м
   Parameters: <nickname> <channel>

   The INVITE message is used to invite users to a channel.  The
   parameter <nickname> is the nickname of the person to be invited to
   the target channel <channel>.  There is no requirement that the
   channel the target user is being invited to must exist or be a valid
   channel.  To invite a user to a channel which is invite only (MODE
   +i), the client sending the invite must be recognised as being a
   channel operator on the given channel.

   Numeric Replies:

		   ERR_NEEDMOREPARAMS              ERR_NOSUCHNICK
		   ERR_NOTONCHANNEL                ERR_USERONCHANNEL
		   ERR_CHANOPRIVSNEEDED
		   RPL_INVITING                    RPL_AWAY

   Examples:

   :Angel INVITE Wiz #Dust         ; User Angel inviting WiZ to channel
								   #Dust

   INVITE Wiz #Twilight_Zone       ; Command to invite WiZ to
								   #Twilight_zone

*/
