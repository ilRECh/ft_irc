#pragma once
#include "ACommand.hpp"

class WHO : public ACommand {
private:
	WHO();
	WHO(WHO const &that);
	WHO& operator=(WHO const &that);
	bool	isAcceptToShow(Client *user_another)
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

	void getResult(std::set<std::pair< Channel *, Client *> > & usersToShow){
		std::set<std::pair< Channel *, Client *> >::iterator start = usersToShow.begin();
		std::set<std::pair< Channel *, Client *> >::iterator finish = usersToShow.end();

		std::string channelName = "*";
		for(;start != finish; ++start)
		{
			std::string serverName = "127.0.0.1";// _Server.getServerAddrInfo().substr(0, _Server.getServerAddrInfo().find(':'));
			char H_G = start->second->_Away.empty() ? 'H' : 'G';
			std::string isAminInLastJoin = "+";
			if (start->first)
			{
				channelName = start->first->getChannelName();
				if (start->first->getModeIsExist(start->second, 'o'))
					isAminInLastJoin = "@";
			} else if (start->second->_lastJoin) {
				channelName = start->second->_lastJoin->getChannelName();
				if (start->second->_lastJoin->getModeIsExist(start->second, 'o'))
					isAminInLastJoin = "@";
			}
			_Initiator->updateReplyMessage(RPL_WHOREPLY
			(
				channelName, 
				start->second->_UserName,
				"127.0.0.1",//start->second->_HostName, 
				"irc.WIP.ru", //serverName,
				start->second->_NickName,
				H_G,
				"*",
				isAminInLastJoin,
				"0",
				start->second->_RealName
			));
		}
		_Initiator->updateReplyMessage(RPL_ENDOFWHO(channelName));
	}

public:
	WHO(Server & Server) : ACommand("WHO", Server) {}
	virtual ~WHO() {}
	virtual int run(){
		std::set<Client *> clients;
		std::set<std::pair< Channel *, Client *> > users_set_pair;
		std::pair< Channel *, Client *>				user_pair_el;
		std::set<Client *>::iterator begin_client, end_client;

		if (_Arguments.empty() || !isRespondRequireTreeAlpha())
		{
			clients = _Arguments.empty() ? _Server.getClientsByName("*") : _Server.getClientsByName(_Arguments[0]);
			for (std::set<Client *>::iterator i = clients.begin(); i != clients.end(); ++i){
				if (isAcceptToShow(*i)){
					user_pair_el.first = NULL;
					user_pair_el.second = *i;
					users_set_pair.insert(user_pair_el);
				}
			}
		}
		else
		{
			for(uint i = 0; i < _Arguments.size(); ++i)
			{
				ft::deleteSpaces(_Arguments[i], SPACE_SYMBOLS);
				if (_Arguments[i].empty())
					continue ;
				if (_Arguments[i].find_first_of(std::string("#&")) != _Arguments[i].npos)
				{
					std::string nameChanNoSharp = _Arguments[i];
					ft::deleteSpaces(nameChanNoSharp, std::string() + SPACE_SYMBOLS);
					Channel * chan =_Server.getChannelByChannelName(nameChanNoSharp);
					if (!chan)
					{
						_Initiator->updateReplyMessage(ERR_NOSUCHCHANNEL(_Arguments[i]));
						continue ;
					}
					clients = chan->_Clients;
					begin_client = clients.begin();
					end_client = clients.end();
					for(;begin_client != end_client; ++begin_client)
					{
						user_pair_el.first = chan;
						user_pair_el.second = *begin_client;
						users_set_pair.insert(user_pair_el);
					}
				}
				else
				{
					clients = _Server.getClientsByName(_Arguments[i]);
					begin_client = clients.begin();
					end_client = clients.end();
					for(;begin_client != end_client; ++begin_client)
					{
						user_pair_el.first = NULL;
						user_pair_el.second = *begin_client;
						users_set_pair.insert(user_pair_el);
					}
				}
			}
		}
		getResult(users_set_pair);
		return 0;
	}
};
/**
*		Parameters: [<name> [<o>]]
*
*		Команда WHO используется клиентом для создания запроса, который возвращает
*		list с информацией, которая 'совпадает' с параметром <name> полученный
*		от клиента.
*		При отсутствие параметра <name>, все видимые пользователи будут в list'е.
*   	?(пользователи, которые не невидимы (user mode +i)
*		?и у кого нет общего канала с запрашивающим клиентом)
*		Тот же результыт будет если в <name> буде "0" or any wildcard which
*
*		в конечном итоге совпадает с каждой возможной записью.
*
*		The <name> passed to WHO is matched against users' host, server, real
*		name and nickname if the channel <name> cannot be found.
*
*		If the "o" parameter is passed only operators are returned according
*		to the name mask supplied.
*
*		Numeric Replies:
*
*				   ERR_NOSUCHSERVER
*				   RPL_WHOREPLY					RPL_ENDOFWHO
*
*		Examples:
*		
*		WHO *.fi						; List all users who match against
*										"*.fi".
*
*		WHO jto* o					  ; List all users with a match against
*										"jto*" if they are an operator.
*/
