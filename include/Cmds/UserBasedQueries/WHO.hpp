#pragma once
#include "ACommand.hpp"

class WHOIS : public ACommand {
private:
	WHOIS();
	WHOIS(WHOIS const &that);
	WHOIS& operator=(WHOIS const &that);
	bool	isHaveCommonChannels(Client const *user_another)
	{
		std::set<Channel const *> two = user_another->getChannels();
		std::set<Channel const *> one = _Initiator->getChannels();

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
		for (;start != finish; ++start)
		{
			result << "+============================================+" << "\r\n";
			result << "Name: " << (*start)->getName() << ", ";
		}
		result << "+============================================+" << "\r\n";
		return result.str();
	}

public:
	WHO(Server const & Server) : ACommand("WHO", Server) {}
	virtual ~WHO() {}
	virtual int run(std::string name = std::string()){
		std::set<Client const *> const & _Clients = _Server->getUsers();
		std::set<Client const *> users_To_Show;
		
		if (_Argument.empty()) {
			//std::string arr[] = { _Name }; // ? чей этот _Name ?
			//return reply(ERR_NEEDMOREPARAMS, _User->_Fd, _User->getName(), L(arr));
			std::set<Channel const *> const & channels = _User->getChannels();

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
