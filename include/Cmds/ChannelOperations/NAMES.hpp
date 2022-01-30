#pragma once
#include "Client.hpp"
#include "Channel.hpp"
#include "ACommand.hpp"

class NAMES : public ACommand {
	typedef std::set<const Channel *>	csChannel;
	typedef csChannel::iterator			icsChannel;
	typedef std::set<Channel *>			sChannel;
	typedef sChannel::iterator			isChannel;

	typedef std::set<const Client *>	csClient;
	typedef csClient::iterator			icsCLient;
	typedef std::set<Client *>			sClient;
	typedef sClient::iterator			isCLient;
private:
    NAMES();
    NAMES(NAMES const &that);
    NAMES& operator=(NAMES const &that);

	csChannel findChannel(){
		typedef std::vector<std::string> vec;
		typedef vec::iterator			ivec;

		ivec start = _Arguments.begin();
		ivec finish = _Arguments.end();
		csChannel channels;

		for(;start != finish; ++start)
		{
			sChannel tmp = _Server.getChannelsByName(*start);
			for(isChannel i = tmp.begin(); i != tmp.end(); ++i)
				channels.insert(*i);
		}
		return channels;
	}

	std::string getNames(csChannel &channels){
		std::stringstream	result;
		csClient			clients;

		for(icsChannel i = channels.begin(); i != channels.end(); ++i)
			for(icsCLient j = (**i)._Clients.begin() ;j != (**i)._Clients.end(); ++j)
				if (!(*j)->getModeIsExist("ps"))
					clients.insert(*j);
		result << "+=================================================+" << "\r\n";
		for(icsCLient i = clients.begin(); i != clients.end(); ++i){
			result << (*i)->getName() << ", ";
		}
		result << "+=================================================+" << "\r\n";
		return result.str();
	}
public:
    NAMES(Server &Server) : ACommand("NAMES", Server) {}
    virtual ~NAMES() {}
    virtual int run(){
		csChannel channels;
		std::string reply;
		
        if (_Arguments.empty()) {
            //return _Initiator->updateReplyMessage(ERR_NEEDMOREPARAMS(_Name));
			channels = _Initiator->_Channels;
        } else {
			channels = findChannel();
		}
		reply = getNames(channels);
		_Initiator->updateReplyMessage(reply);
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