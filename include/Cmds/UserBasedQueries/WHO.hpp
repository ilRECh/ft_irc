#pragma once
#include "ACommand.hpp"

class WHO : public ACommand {
private:
	WHO();
	WHO(WHO const &that);
	WHO& operator=(WHO const &that);
	bool	isHaveCommonChannels(Client const *user_another)
	{
		std::set<Channel const *> two = user_another->getChannels();
		std::set<Channel const *> one = _User->getChannels();

		for (size_t i = 0; i < one.size(); i++)
			for (size_t j = 0; j < two.size(); j++)
				if (one[i] == two[j])
					return true;
		return false;
	}
public:
	WHO(Server const *Server) : ACommand("WHO", Server) {}
	virtual ~WHO() {}
	virtual int run(std::string name = std::string()){
		std::set<Client const *> const & _Users = _Server->getUsers();
		std::set<Client const *> users_To_Show;
		
		if (_Argument.empty()) {
			//std::string arr[] = { _Name }; // ? чей этот _Name ?
			//return reply(ERR_NEEDMOREPARAMS, _User->_Fd, _User->getName(), L(arr));
			std::set<Channel const *> const & channels = _User->getChannels();

			for (size_t i = 0; i < _Users.size(); i++)
				if (isHaveCommonChannels(_Users[i]) && !_Users[i]->getModeIsExist('i'))
					users_To_Show.push_back(_Users[i]);
		} else {
			for (size_t i = 0; i < _Users.size(); i++)
				if (_Users[i]->getName() == name)
					users_To_Show.push_back(_Users[i]);
		}
		// ! Куда послать этот лист юзеров "users_To_Show"
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