#pragma once
#include "ACommand.hpp"

class WHOIS : public ACommand {
	typedef typename std::set<Client *>		setClient;
	typedef typename std::set<Channel *>	setChannel;
	typedef typename setClient::iterator	IsetClient;
	typedef typename setChannel::iterator	IsetChannel;
	
	typedef typename std::set<const Client *>	csetClient;
	typedef typename std::set<const Channel *>	csetChannel;
	typedef typename csetClient::iterator		IcsetClient;
	typedef typename csetChannel::iterator		IcsetChannel;
private:
	WHOIS();
	WHOIS(WHOIS const &that);
	WHOIS& operator=(WHOIS const &that);
	bool	isAcceptToShow(Client *user_another)
	{
		csetChannel &two = user_another->_Channels;
		csetChannel &one = _Initiator->_Channels;
		csetChannel common;

		if (std::find_first_of(one.begin(), one.end(), two.begin(), two.end()) == one.end())
			return false;
		for(IcsetChannel i = one.begin(); i != one.end(); ++i)
			for(IcsetChannel j = two.begin(); j != two.end(); ++j)
				if (*i == *j)
					common.insert(*i);
		for(IcsetChannel i = common.begin(); i != common.end(); ++i)
			if (!(*i)->getModeIsExist(user_another, 'i'))
				return true;
		return false;
	}

	bool	isRespondRequireTreeAlpha(){
		uint const	minAlpha = 3;
		uint		countAlpha = 0;

		for(size_t i = 0; i < _Arguments[0].size(); ++i)
			_Arguments[0][i] != '*' && ++countAlpha;
		return countAlpha >= minAlpha;
	}


	std::string shortByStar(std::string const &some, std::string::size_type posStar){
		if (posStar)
			return std::string("..") + some.substr(some.find_last_of(_Arguments[0].substr(0, posStar)));
		return some.substr(0, some.find(_Arguments[0].substr(1))) + "..";
	}

	std::string getResult(setClient & usersToShow){
		IsetClient start = usersToShow.begin();
		IsetClient finish = usersToShow.end();
		std::string::size_type posStar;
		std::stringstream result;

		if (_Arguments.size() > 1 && std::tolower(_Arguments[1][0]) == 'o')
		{			
			posStar = _Arguments[0].find('*');
			if (posStar ==_Arguments[0].find_last_of('*'))
				for (;start != finish; ++start)
					result << "(" << shortByStar((*start)->_NickName, posStar) << ")" << ", ";
			else
				for (;start != finish; ++start)
					result << (*start)->_NickName << ", ";
		}
		else
		{
			for (;start != finish; ++start)
			{
				result << "Nick name: " << (*start)->_NickName << "\r\n";
				result << "Real name: " << (*start)->_RealName << "\r\n";
				result << "IP: " << (*start)->getAddresIP() << "\r\n";
				result << "Last activity: " << (*start)->getLastActivity().getTimeStrStarted() << "\r\n";
			}
		}
		return result.str();
	}

public:
	WHOIS(Server &Server) : ACommand("WHOIS", Server) {setArguments(_Argument);}
	virtual ~WHOIS() {}
	virtual int run(){
		setClient usersToShow;
		setClient _Clients;
		std::stringstream result;

		if (_Arguments.empty() || !isRespondRequireTreeAlpha())
		{
			_Clients = _Arguments.empty() ? _Server.getClientsByName("*") : _Server.getClientsByName(_Arguments[0]);
			for (IsetClient i = _Clients.begin(); i != _Clients.end(); ++i)
				if (isAcceptToShow(*i))
					usersToShow.insert(*i);
		}
		else
		{
			usersToShow = _Server.getClientsByName(_Arguments[0]);
		}
		_Initiator->updateReplyMessage(getResult(usersToShow));
		return 0;
	}
};
/*

		WHOIS
		Синтаксис:

		WHOIS [<сервер>] <имена пользователей>
		Возвращает информацию о пользователях,
		определённых в разделенном запятыми списке 
		<имена пользователей>.
		[51] Если определен параметр <сервер>, команда передается ему для обработки.

		Определена в RFC 1459


        Parameters: [<server>] <nickmask>[,<nickmask>[,...]]

        Это сообщение используется для запроса информации о конкретном пользователе.
		The server will answer this message with several numeric messages
        indicating different statuses of each user which matches the nickmask
        (if you are entitled to see them).  If no wildcard is present in the
        <nickmask>, any information about that nick which you are allowed to
        see is presented.  A comma (',') separated list of nicknames may be
        given.

        The latter version sends the query to a specific server.  It is
        useful if you want to know how long the user in question has been
        idle as only local server (ie. the server the user is directly
        connected to) knows that information, while everything else is
        globally known.

        Numeric Replies:

           ERR_NOSUCHSERVER                ERR_NONICKNAMEGIVEN
           RPL_WHOISUSER                   RPL_WHOISCHANNELS
           RPL_WHOISCHANNELS               RPL_WHOISSERVER
           RPL_AWAY                        RPL_WHOISOPERATOR
           RPL_WHOISIDLE                   ERR_NOSUCHNICK
           RPL_ENDOFWHOIS

        Examples:

        WHOIS wiz                       ; return available user information
                                        about nick WiZ

        WHOIS eff.org trillian          ; ask server eff.org for user
                                        information about trillian

*/