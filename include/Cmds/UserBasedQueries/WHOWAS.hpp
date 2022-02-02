#pragma once
#include "ACommand.hpp"

class WHOWAS : public ACommand {
	typedef typename std::set<Client *>			setClient;
	typedef typename std::set<Channel *>		setChannel;
	typedef typename setClient::iterator		IsetClient;
	typedef typename setChannel::iterator		IsetChannel;
private:
    WHOWAS();
    WHOWAS(WHOWAS const &that);
    WHOWAS& operator=(WHOWAS const &that);

	std::string getResult(std::vector<setClient> clientsToShow){
		std::vector<Client *> toSortVec;
		std::stringstream result;

		for (size_t i = 0; i < clientsToShow.size(); i++)
			for (IsetClient j = clientsToShow[i].begin(); j != clientsToShow[i].end(); ++j)
				if ((*j)->getLastActivity().hasTimePassed(MAY_BE_INACTIVE_seconds))
					toSortVec.push_back(*j);
		for (size_t i = 0; i < toSortVec.size(); i++)
			result << "Nick: " << toSortVec[i]->_NickName << " last activity: " << toSortVec[i]->getLastActivity().getTimeStrStarted() << "\r\n";
		return result.str();		
	}
public:
    WHOWAS(Server &Server) : ACommand("WHOWAS", Server) {}
    virtual ~WHOWAS() {}
    virtual int run(){
		std::vector<setClient> clientsToShow;
        if (_Arguments.empty()) {
			clientsToShow.push_back(_Server.getClientsByName("*"));
        } else {
			for (size_t i = 0; i < _Arguments.size(); i++)
			{
				clientsToShow.push_back(_Server.getClientsByName(_Arguments[i]));
			}
		}
		std::string result = getResult(clientsToShow);
		_Initiator->updateReplyMessage(result);
    }
};/*
        Parameters: <nickname> [<count> [<server>]]

        Whowas asks for information about a nickname which no longer exists.
        This may either be due to a nickname change or the user leaving IRC.
        In response to this query, the server searches through its nickname
        history, looking for any nicks which are lexically the same (no wild
        card matching here).  The history is searched backward, returning the
        most recent entry first.  If there are multiple entries, up to
        <count> replies will be returned (or all of them if no <count>
        parameter is given).  If a non-positive number is passed as being
        <count>, then a full search is done.

        Numeric Replies:

        ERR_NONICKNAMEGIVEN             ERR_WASNOSUCHNICK
        RPL_WHOWASUSER                  RPL_WHOISSERVER
        RPL_ENDOFWHOWAS

        Examples:

        WHOWAS Wiz                      ; return all information in the nick
                                        history about nick "WiZ";

        WHOWAS Mermaid 9                ; return at most, the 9 most recent
                                        entries in the nick history for
                                        "Mermaid";

        WHOWAS Trillian 1 *.edu         ; return the most recent history for
                                        "Trillian" from the first server found
                                        to match "*.edu".
*/