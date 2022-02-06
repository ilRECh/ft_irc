#pragma once
#include "ACommand.hpp"

class WHOIS : public ACommand {
private:
	WHOIS();
	WHOIS(WHOIS const &that);
	WHOIS& operator=(WHOIS const &that);
	bool	isAcceptToShowClient(Client *user_another)
	{
		std::set<Channel *> &two = user_another->_Channels;
		std::set<Channel *> &one = _Initiator->_Channels;
		std::set<Channel *> common;

		if (std::find_first_of(one.begin(), one.end(), two.begin(), two.end()) == one.end())
			return false;
		for(std::set<Channel *>::iterator i = one.begin(); i != one.end(); ++i)
			for(std::set<Channel *>::iterator j = two.begin(); j != two.end(); ++j)
				if (*i == *j)
					common.insert(*i);
		for(std::set<Channel *>::iterator i = common.begin(); i != common.end(); ++i)
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

	void getResult(std::set<Client *> & usersToShow){
		std::set<Client *>::iterator beg_clnt = usersToShow.begin();
		std::set<Client *>::iterator end_clnt = usersToShow.end();
		std::set<Channel *>::iterator beg_chan;
		std::set<Channel *>::iterator end_chan;
		if (beg_clnt != end_clnt)
		{
			for (;beg_clnt != end_clnt; ++beg_clnt)
			{
				_Initiator->updateReplyMessage(RPL_WHOISUSER
				(
					(*beg_clnt)->_NickName, 
					(*beg_clnt)->_UserName, 
					(*beg_clnt)->_HostName, 
					(*beg_clnt)->_RealName
				));
				if (not (*beg_clnt)->getChannels().empty())
				{
					beg_chan = (*beg_clnt)->getChannels().begin();
					end_chan = (*beg_clnt)->getChannels().end();
					for(;beg_chan != end_chan; ++beg_chan)
					{
						char status_in_channel = (*beg_chan)->getModeIsExist((*beg_clnt), 'o') ? '@' : '+';
						_Initiator->updateReplyMessage(RPL_WHOISCHANNELS(
							(*beg_clnt)->_NickName, 
							status_in_channel, 
							(*beg_chan)->getChannelName()));
					}
				}
				_Initiator->updateReplyMessage(RPL_ENDOFWHOIS((*beg_clnt)->_NickName));
			}
		}
		else
		{
			for(uint i = 0; i < _Arguments.size(); ++i)
			{
				_Initiator->updateReplyMessage(ERR_NOSUCHNICK(_Arguments[i]));
				_Initiator->updateReplyMessage(RPL_ENDOFWHOIS(_Arguments[i]));
			}
		}
	}

public:
	WHOIS(Server &Server) : ACommand("WHOIS", Server) {setArguments(_Argument);}
	virtual ~WHOIS() {}
	virtual int run(){
		std::set<Client *>	clients;
		std::set<Client *>	users_to_show;
		std::set<Channel *>	channels;

		if (_Arguments.empty() || !isRespondRequireTreeAlpha())
		{
			clients = _Arguments.empty() ? _Server.getClientsByName("*") : _Server.getClientsByName(_Arguments[0]);
			channels = _Arguments.empty() ? _Server.getChannelsByChannelName("*") : _Server.getChannelsByChannelName(_Arguments[0]);
			for (std::set<Client *>::iterator i = clients.begin(); i != clients.end(); ++i)
				if (isAcceptToShowClient(*i))
					users_to_show.insert(*i);
		}
		else
		{
			users_to_show = _Server.getClientsByName(_Arguments[0]);
		}
		getResult(users_to_show);
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
