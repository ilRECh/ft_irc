#pragma once
#include "ACommand.hpp"

class JOIN : public ACommand {
	typedef std::string				str;
	typedef str::iterator			istr;
	typedef str::reverse_iterator	ristr;
	typedef std::pair<str, str>		pStrStr;
	typedef std::vector<str>		vecStr;
	typedef vecStr::iterator		ivecStr;
	typedef std::vector<pStrStr>	vpStrStr;
	typedef vpStrStr::iterator		ivpStrStr;
private:
    JOIN();
    JOIN(JOIN const &that);
    JOIN& operator=(JOIN const &that);
	
	vpStrStr smartSplit(){
		vpStrStr result;
		_Arguments = ft::split(_Argument, ",");
		for (ivecStr i = _Arguments.begin(); i != _Arguments.end(); ++i)
		{
			*i = ft::strTrim(*i, SPACE_SYMBOLS);
			if (i->empty())
				continue ;
			else if ((*i)[0] == '#')
			{
				str s = ft::strTrim(*i, std::string(SPACE_SYMBOLS) + "#");
				if (s.empty())
					continue ;
				result.push_back(pStrStr(*i, str()));
			}
			else if ((*i)[0] == '&')
			{
				str s1 = ft::strTrim(*i, std::string(SPACE_SYMBOLS) + "&");
				if (s1.empty())
					continue ;
				vecStr vstr = ft::split(*i, SPACE_SYMBOLS);
				if (vstr.size() != 2)
					return vpStrStr();
				result.push_back(pStrStr(vstr.front(), vstr.back()));
			}
			else
				return vpStrStr();
		}
	}
	
	int join(str nameChannel){
		//!code
	}
	int join(str nameChannel, str password){
		//!code
	}

	void	distributor(){
		vpStrStr args = smartSplit();
		ivpStrStr first, last;

		first = args.begin();
		last = args.end();

		while(first != last)
		{
			//!code
			++first;
		}
	}
public:
    JOIN(Server &Server) : ACommand("JOIN", Server) {}
    virtual ~JOIN() {}
    virtual int run(){
        if (_Arguments.empty()) {
            return _Initiator->updateReplyMessage(ERR_NEEDMOREPARAMS(_Name));
        }
        //code
    }
};/*
   4.2.1 Join-сообщение

    Команда: JOIN
  Параметры: <channel>{,<channel>} [<key>{,<key>}]

  Команда JOIN используется клиентом для входа на канал. Так или иначе,
  клиенту позволительно войти на канал, проверенным только сервером, к
  которому подсоединен; все остальные серверы автоматически добавляют
  пользователя на канал, когда получают уведомление от других серверов.
  Условия выполнения все того, ниже:

          1.  Пользователь может быть приглашен, если канал invite-only;

          2.  Никнейм/имя пользователя/имя хоста не должны быть
              забанеными;

          3.  Если установлен пароль, но должен быть верным.

  Это обсуждается в разделе MODE-команды более подробно (см. 4.2.3).
  Когда пользователи заходят на канал, они получат уведомление о всех
  командах их сервера. Оно вмещает в себе MODE, KICK, PART, QUIT и,
  конечно же, PRIVMSG/NOTICE. Команда JOIN требуется для сообщения всем
  серверам, чтобы каждый сервер знал, где искать пользователей, которые
  находятся на канале. Это позволяет оптимальную передачу сообщений
  PRIVMSG/NOTICE в канал.

  Если JOIN прошла хорошо, пользователь получает топик канала
  (используя RPL_TOPIC) и список пользователей, которые находятся на канале
  (используя RPL_NAMREPLY).

  Числовые ответы:

          ERR_NEEDMOREPARAMS              ERR_BANNEDFROMCHAN
          ERR_INVITEONLYCHAN              ERR_BADCHANNELKEY
          ERR_CHANNELISFULL               ERR_BADCHANMASK
          ERR_NOSUCHCHANNEL               ERR_TOOMANYCHANNELS
          RPL_TOPIC

  Примеры:

  JOIN #foobar                    ; вход на канал #foobar.

  JOIN &foo fubar                 ; вход на канал &foo, используя ключ "fubar".

  JOIN #foo,&bar fubar            ; вход на канал #foo, используя ключ "fubar"
                                  и на канал &bar без использования ключа.

  JOIN #foo,#bar fubar,foobar     ; вход на канал #foo, используя ключ "fubar".
                                  и на канал #bar, используя ключ "foobar".

  JOIN #foo,#bar                  ; вход на каналы #foo и #bar.

  :WiZ JOIN #Twilight_zone        ; JOIN-сообщение от WiZ


*/