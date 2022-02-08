#pragma once
#include "Client.hpp"
#include "Channel.hpp"
#include "ACommand.hpp"

class NAMES : public ACommand {
private:
    NAMES();
    NAMES(NAMES const &that);
    NAMES& operator=(NAMES const &that);

	int sendResult(std::list<std::set<Channel *> > channels)
	{
		std::stringstream result;
		std::list<std::set<Channel *> >::iterator begin_chan_list, end_chan_list;
		std::set<Client *>::iterator begin_client, end_client;
		std::set<Channel *>::iterator begin_chan, end_chan;
		begin_chan_list = channels.begin();
		end_chan_list = channels.end();
		std::string LastChannel = "*";

		if (begin_chan_list == end_chan_list)
		{
			_Initiator->updateReplyMessage(RPL_ENDOFNAMES(""));
			return 1;
		}
		while (begin_chan_list != end_chan_list)
		{
			end_chan = begin_chan_list->end();
			begin_chan = begin_chan_list->begin();
			while (begin_chan != end_chan)
			{
				if (not (*begin_chan)->getModeIsExist(*begin_chan, 'p') 
					and not (*begin_chan)->getModeIsExist(*begin_chan, 's'))
				{
					end_client = (*begin_chan)->_Clients.end();
					begin_client = (*begin_chan)->_Clients.begin();
					if (begin_client != end_client)
					{
						LastChannel = (*begin_chan)->_ChannelName;
						result << RPL_NAMREPLY((*begin_chan)->_ChannelName) << " :";
						while (true)
						{
							result << ((*begin_chan)->getModeIsExist((*begin_client), 'o') ? "@" : "");
							result << (*begin_client)->_NickName;
							++begin_client;
							if (begin_client != end_client)
								result << " ";
							else
								break ;
						}
						_Initiator->updateReplyMessage(result.str());
						result.str("");
						result.clear();
					}
				}
				++begin_chan;
			}
			++begin_chan_list;
		}
		_Initiator->updateReplyMessage(RPL_ENDOFNAMES(LastChannel));
		return 0;

	}

public:
    NAMES(Server &Server) : ACommand("NAMES", Server) {}
    virtual ~NAMES() {}
    virtual int run(){
		std::list<std::set<Channel *> > channels_from_arg;
		std::set<Channel *>::iterator channel_begin;
	
        if (_Arguments.empty())
			channels_from_arg.push_back(_Server._Channels);
		else
			for(uint i = 0; i < _Arguments.size(); ++i)
				channels_from_arg.push_back(_Server.getChannelsByChannelName(_Arguments[i]));
		return sendResult(channels_from_arg);
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
