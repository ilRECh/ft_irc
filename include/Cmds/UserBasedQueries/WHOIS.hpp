#pragma once
#include "ACommand.hpp"

class WHOIS : public ACommand {
	typedef std::set<Client *>		setClient;
	typedef std::set<Channel *>	setChannel;
	typedef setClient::iterator	IsetClient;
	typedef setChannel::iterator	IsetChannel;
	
	typedef std::set<const Client *>	csetClient;
	typedef std::set<const Channel *>	csetChannel;
	typedef csetClient::iterator		IcsetClient;
	typedef csetChannel::iterator		IcsetChannel;
private:
	WHOIS();
	WHOIS(WHOIS const &that);
	WHOIS& operator=(WHOIS const &that);
	bool	isAcceptToShowClient(Client *user_another)
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

	bool isAccenpToShowChannel(Channel * channel){
		 return not channel->getModeIsExist(channel, 'p') or channel->isOnChannel(_Initiator);
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
		IsetClient beg_clnt = usersToShow.begin();
		IsetClient end_clnt = usersToShow.end();
		IcsetChannel beg_chan;
		IcsetChannel end_chan;
		std::stringstream result;
		if (beg_clnt != end_clnt)
		{
			for (;beg_clnt != end_clnt; ++beg_clnt)
			{
				result << RPL_WHOISUSER
				(
					(*beg_clnt)->_UserName, 
					(*beg_clnt)->_HostName, 
					(*beg_clnt)->_RealName
				) << "\r\n";
				if (not (*beg_clnt)->getChannels().empty())
				{
					beg_chan = (*beg_clnt)->getChannels().begin();
					end_chan = (*beg_clnt)->getChannels().end();
					for(;beg_chan != end_chan; ++beg_chan)
					{
						char status_in_channel = (*beg_chan)->getModeIsExist((*beg_clnt), 'o') ? '@' : '+';
						result << RPL_WHOISCHANNELS
						(
							(*beg_clnt)->_NickName, 
							status_in_channel, 
							(*beg_chan)->getChannelName()
						);
					}
				}
			}
			result << RPL_ENDOFWHOIS((*(--beg_clnt))->_NickName);
		}
		else
			result << RPL_ENDOFWHOIS(" ");

		// if (_Arguments.size() > 1 && std::tolower(_Arguments[1][0]) == 'o')
		// {
		// 	posStar = _Arguments[0].find('*');
		// 	bool is_one_star_in_arg = posStar == _Arguments[0].find_last_of('*');
		// 	if (is_one_star_in_arg)
		// 		for (;beg_client != end_client; ++beg_client)
		// 			result << "(" << shortByStar((*beg_client)->_NickName, posStar) << ")" << ", ";
		// 	else
		// 		for (;beg_client != end_client; ++beg_client)
		// 			result << (*beg_client)->_NickName << ", ";
		// }
		// else
		// {
		// }
		return result.str();
	}

public:
	WHOIS(Server &Server) : ACommand("WHOIS", Server) {setArguments(_Argument);}
	virtual ~WHOIS() {}
	virtual int run(){
		setClient	clients;
		setClient	users_to_show;
		setChannel	channels;

		if (_Arguments.empty() || !isRespondRequireTreeAlpha())
		{
			clients = _Arguments.empty() ? _Server.getClientsByName("*") : _Server.getClientsByName(_Arguments[0]);
			channels = _Arguments.empty() ? _Server.getChannelsByName("*") : _Server.getChannelsByName(_Arguments[0]);
			for (IsetClient i = clients.begin(); i != clients.end(); ++i)
				if (isAcceptToShowClient(*i))
					users_to_show.insert(*i);
		}
		else
		{
			users_to_show = _Server.getClientsByName(_Arguments[0]);
		}
		_Initiator->updateReplyMessage(getResult(users_to_show));
		return 0;
	}
};
/*

4.5.2 Whois-запрос

	Команда: WHOIS
  Параметры: [<server>] <nickmask>[,<nickmask>[,...]]

  Это сообщение используется для запроса информации об отдельном
  пользователе. Сервер будет отвечать на это сообщением различными
  числовыми сообщениями, указывая разность положений каждого пользователя,
  который попал под маску (если вы указали ее). Если в <nickmask> не
  указана никакая информация о том, какой никнейм опросить, вы получите
  информацию о всех доступных никнеймах. Запятая разделяет список
  никнеймов.

  Предыдущая версия отправляла запрос на указанный сервер. Это полезно,
  если хотите знать как долго опрашиваемый пользователь будет
  бездействовать , как только локальный сервер (т.е, пользователь
  напрямую соединен с сервером) узнает эту информацию.

  Числовые ответы:
	ERR_NOSUCHSERVER
		"<server name> :No such server"
?	ERR_NONICKNAMEGIVEN
*		":No nickname given"
?	RPL_WHOISUSER
*		"<nick> <user> <host> * :<real name>"
! here
?	RPL_WHOISCHANNELS
*		"<nick> :{[@|+]<channel><space>}"
	RPL_WHOISSERVER
		"<nick> <server> :<server info>"
?	RPL_AWAY
*		"<nick> :<away message>"
?	RPL_WHOISOPERATOR
*		"<nick> :is an IRC operator"
?	RPL_WHOISIDLE
*		"<nick> <integer> :seconds idle"
?	ERR_NOSUCHNICK
*		"<nickname> :No such nick/channel"
?	RPL_ENDOFWHOIS
*		"<nick> :End of /WHOIS list"

*/
