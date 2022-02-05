#pragma once
#include "Client.hpp"
#include "Channel.hpp"
#include "ACommand.hpp"

class NAMES : public ACommand {
private:
    NAMES();
    NAMES(NAMES const &that);
    NAMES& operator=(NAMES const &that);

	std::set<const Channel *> findChannel()
	{
		typedef std::vector<std::string> vec;
		typedef vec::iterator			ivec;

		ivec start = _Arguments.begin();
		ivec finish = _Arguments.end();
		std::set<const Channel *> channels;

		for(;start != finish; ++start)
		{
			std::set<Channel *> tmp = _Server.getChannelsByChannelName(*start);
			for(std::set<Channel *>::iterator i = tmp.begin(); i != tmp.end(); ++i)
				channels.insert(*i);
		}
		return channels;
	}

	std::string getNames(std::set<const Channel *> &channels)
	{
		std::stringstream			result;
		std::set<const Client *>	clients;

		for(std::set<const Channel *>::iterator i = channels.begin(); i != channels.end(); ++i)
			for(std::set<Client *>::iterator j = (*i)->_Clients.begin() ;j != (**i)._Clients.end(); ++j)
				if (!(*i)->getModeIsExist((*j), "s") && !(*i)->getModeIsExist((*j), "p"))
					clients.insert(*j);
		result << "+=================================================+" << "\r\n";
		for(std::set<const Client *>::iterator i = clients.begin(); i != clients.end(); ++i){
			_Initiator->updateReplyMessage("aaaaaaaaaaaaaaaaaaaaa");
			// result << (*i)->_NickName << ", ";
		}
		result << "+=================================================+" << "\r\n";
		return result.str();
	}
public:
    NAMES(Server &Server) : ACommand("NAMES", Server) {}
    virtual ~NAMES() {}
    virtual int run(){
		std::set<Channel *>::iterator channel_begin = _Server.getChannels().begin();
		std::set<Client *>::iterator client_begin, client_end;
	
        if (_Arguments.empty())
		{
			if (channel_begin != _Server.getChannels().end())
			{
				for(;channel_begin != _Server.getChannels().end(); ++channel_begin)
				{
					const Channel *channel = *channel_begin;
					if (!channel->getModeIsExist(*channel_begin, 'p') && !channel->getModeIsExist(*channel_begin, 's'))
					{
						_Initiator->updateReplyMessage(RPL_NAMREPLY(std::string("#") + channel->_ChannelName));
						client_begin = channel->_Clients.begin();
						for(; client_begin != channel->_Clients.end(); ++client_begin)
							_Initiator->updateReplyMessage(RPL_NAMREPLY((*client_begin)->_NickName));
					}
				}
				_Initiator->updateReplyMessage(RPL_ENDOFNAMES("#",(*(--_Server.getChannels().end()))->getChannelName()));
			}
        }
		else
		{
			for(uint i = 0; i < _Arguments.size(); ++i)
			{
				std::set<Channel *> channels = _Server.getChannelsByChannelName(_Arguments[i]);
				channel_begin = channels.begin();
				if (channel_begin != channels.end())
				{
					for(;channel_begin != channels.end(); ++channel_begin)
					{
						Channel * channel = *channel_begin;
						_Initiator->updateReplyMessage(RPL_NAMREPLY(std::string("#") + channel->_ChannelName));
						client_begin = channel->_Clients.begin();
						for(; client_begin != channel->_Clients.end(); ++client_begin)
							_Initiator->updateReplyMessage(RPL_NAMREPLY((*client_begin)->_NickName));

					}
					_Initiator->updateReplyMessage(RPL_ENDOFNAMES("#", (*(--channel_begin))->_ChannelName));
				}
			}
		}
		return 0;
    }
};/*
   Parameters: [<channel>{,<channel>}]

   By using the NAMES command, a user can list all nicknames that are
   visible to them on any channel that they can see.  Channel names
   which they can see are those which aren't private (+p) or secret (+s)
   or those which they are actually on.  The <channel> parameter
   specifies which channel(s) to return information about if valid.
   There is no error reply for bad channel names.

   If no <channel> parameter is given, a list of all channels and their
   occupants is returned.  At the end of this list, a list of users who
   are visible but either not on any channel or not on a visible channel
   are listed as being on `channel' "*".

   Numerics:

           RPL_NAMREPLY                    RPL_ENDOFNAMES

   Examples:

   NAMES #twilight_zone,#42        ; list visible users on #twilight_zone
                                   and #42 if the channels are visible to
                                   you.

   NAMES                           ; list all visible channels and users

*/
