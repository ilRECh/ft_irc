#pragma once
#include "ACommand.hpp"

class WHO : public ACommand {
	typedef std::set<Client *>		setClient;
	typedef std::set<Channel *>	setChannel;
	typedef setClient::iterator	IsetClient;
	typedef setChannel::iterator	IsetChannel;

	typedef std::set<const Client *>	csetClient;
	typedef std::set<const Channel *>	csetChannel;
	typedef csetClient::iterator		IcsetClient;
	typedef csetChannel::iterator		IcsetChannel;
private:
	WHO();
	WHO(WHO const &that);
	WHO& operator=(WHO const &that);
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
		std::stringstream result;

		for (IsetClient	start = usersToShow.begin(); start != usersToShow.end(); ++start)
		{
			result << "+============================================+" << "\r\n";
			result << "Name: " << (*start)->_NickName << ", ";
		}
		result << "+============================================+" << "\r\n";
		return result.str();
	}

public:
	WHO(Server & Server) : ACommand("WHO", Server) {}
	virtual ~WHO() {}
	virtual int run(){
		setClient clients = _Server.getClientsByName("*");
		setClient users_To_Show;

		if (_Arguments.empty() || !isRespondRequireTreeAlpha())
		{
			clients = _Arguments.empty() ? _Server.getClientsByName("*") : _Server.getClientsByName(_Arguments[0]);
			for (IsetClient i = clients.begin(); i != clients.end(); ++i)
				if (isAcceptToShow(*i))
					users_To_Show.insert(*i);
		}
		else
		{
			users_To_Show = _Server.getClientsByName(_Arguments[0]);
		}
		_Initiator->updateReplyMessage(getResult(users_To_Show));
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
