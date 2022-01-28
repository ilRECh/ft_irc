#pragma once
#include "ACommand.hpp"

class WHOIS : public ACommand {
private:
	WHOIS();
	WHOIS(WHOIS const &that);
	WHOIS& operator=(WHOIS const &that);
	bool	isHaveCommonChannels(Client const *user_another)
	{
		std::vector<Channel const *> two = user_another->getChannels();
		std::vector<Channel const *> one = _Initiator->getChannels();

		for (size_t i = 0; i < one.size(); i++)
			for (size_t j = 0; j < two.size(); j++)
				if (one[i] == two[j])
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

	std::string getResult(std::vector<Client *> & usersToShow){
		std::vector<Client *>::iterator start = usersToShow.begin();
		std::vector<Client *>::iterator finish = usersToShow.end();
		std::string::size_type posStar;
		std::stringstream result;

		if (_Arguments.size() > 1 && std::tolower(_Arguments[1][0]) == 'o')
		{			
			posStar = _Arguments[0].find('*');
			result << "+============================================+" << "\r\n";
			if (posStar ==_Arguments[0].find_last_of('*'))
				for (;start != finish; ++start)
					result << "(" << shortByStar((*start)->getName(), posStar) << ")" << ", ";
			else
				for (;start != finish; ++start)
					result << (*start)->getName() << ", ";
		}
		else
		{
			for (;start != finish; ++start)
			{
				result << "+============================================+" << "\r\n";
				result << "Name: " << (*start)->getName() << "\r\n";
				result << "Nick name: " << (*start)->getNickName() << "\r\n";
				result << "Real name: " << (*start)->getRealName() << "\r\n";
				result << "IP: " << (*start)->getAddresIP() << "\r\n";
				result << "Last activity: " << (*start)->getLastActivity().getTimeStrStarted() << "\r\n";
			}
		}
		result << "+============================================+" << "\r\n";
		return result.str();
	}

public:
	WHOIS(Server &Server) : ACommand("WHOIS", Server) {setArguments(_Argument);}
	virtual ~WHOIS() {}
	virtual int run(){
		std::vector<Client *> usersToShow;
		std::vector<Client *> _Clients;
		std::stringstream result;

		if (_Arguments.empty() || !isRespondRequireTreeAlpha())
		{
			_Clients = _Arguments.empty() ? _Server.getUsersByName("*") : _Server.getUsersByName(_Arguments[0]);
			for (size_t i = 0; i < _Clients.size(); i++)
				if (isHaveCommonChannels(_Clients[i]) && !_Clients[i]->getModeIsExist('i'))
					usersToShow.push_back(_Clients[i]);
		}
		else
		{
			usersToShow = _Server.getUsersByName(_Arguments[0]);
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