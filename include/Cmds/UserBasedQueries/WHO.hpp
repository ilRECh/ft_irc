#pragma once
#include "ACommand.hpp"

class WHO : public ACommand {
private:
	WHO();
	WHO(WHO const &that);
	WHO& operator=(WHO const &that);
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
		std::vector<Client *>::iterator start;
		std::vector<Client *>::iterator finish;
		std::string::size_type posStar;
		std::stringstream result;
		bool isOneStar;

		start = usersToShow.begin();
		finish = usersToShow.end();
		if (_Arguments.size() > 1 && std::tolower(_Arguments[1][0]) == 'o')
		{			
			posStar = _Arguments[0].find('*');
			isOneStar = posStar ==_Arguments[0].find_last_of('*');
			result << "+============================================+" << "\r\n";
			if (isOneStar)
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
				result << "NickName: " << (*start)->getNickName() << "\r\n";
				result << "RealName: " << (*start)->getRealName() << "\r\n";
				result << "RealName: " << (*start)->getRealName() << "\r\n";
			}
		}
		result << "+============================================+" << "\r\n";
		return result.str();
	}

public:
	WHO(Server &Server) : ACommand("WHO", Server) {setArguments(_Argument);}
	virtual ~WHO() {}
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
