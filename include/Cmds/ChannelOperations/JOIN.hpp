#pragma once
#include "ACommand.hpp"
#define MAX_NUMBER_OF_CHANNELS 10

class JOIN : public ACommand {
private:
    JOIN();
    JOIN(JOIN const &that);
    JOIN& operator=(JOIN const &that);
	std::list<std::string> _NoSuchChannel;
	std::list<std::string> _BadChannelMask;
	std::list<std::string> _BadChannelKey;
	std::list<std::string> _BannedFromChannel;
	std::list<std::string> _InviteOnlyChannel;
	std::list<std::string> _ChannelIsFull;
	std::list<std::string> _TooManyChannels;
	std::list< std::pair<std::string, std::string> > _NamesWithKeys;
	
	void join(std::string & nameChannel, std::string & key){
		Channel * chan = _Server.getChannelByChannelName(nameChannel);
		if (not chan) {
			chan = new Channel(nameChannel, _Initiator, &_Server);
			_Server.pushBack(chan);
ClientJoined:
			// chan->addClient(_Initiator);
			_Initiator->_Channels.insert(chan);
			chan->_Clients.insert(_Initiator);
			_Initiator->updateReplyMessage(" JOIN :" + chan->getChannelName(), _Initiator->_NickName);
			_Initiator->updateReplyMessage(RPL_NAMREPLY(chan->getChannelName()) + " :" + _Initiator->_RealName);
			_Initiator->updateReplyMessage(RPL_ENDOFNAMES(" ", chan->getChannelName()));
		} else if (chan->getModeIsExist(chan, 'p') or chan->getModeIsExist(chan, 's')) {
			_NoSuchChannel.push_back(nameChannel);
		} else if (chan->_Clients.size() >= chan->_maxUserLimit) {
			_ChannelIsFull.push_back(nameChannel);
		} else if (chan->getModeIsExist(chan, 'i')) {
			_InviteOnlyChannel.push_back(nameChannel);
		} else if (not key.empty() and chan->_Key != key) {
			_BadChannelKey.push_back(nameChannel);
		} else if (chan->isBanned(_Initiator)) {
			_BannedFromChannel.push_back(nameChannel);
		} else {
			goto ClientJoined;
		}
	}
public:
    JOIN(Server &Server) : ACommand("JOIN", Server) {}
    virtual ~JOIN() {}
    virtual int run(){
        if (_Argument.empty() or _Argument.find_first_not_of(SPACE_SYMBOLS) == _Argument.npos) {
            return _Initiator->updateReplyMessage(ERR_NEEDMOREPARAMS(_Name));
		}
		std::vector<std::string> InputNamesAndKeys = ft::split(_Argument, " ");
		std::vector<std::string> Names = ft::split(InputNamesAndKeys[0], ",");
		std::vector<std::string> Keys;
		if (InputNamesAndKeys.size() == 2) {
			Keys = ft::split(InputNamesAndKeys[1], ",");
		}
		std::vector<std::string>::iterator Name = Names.begin();
		std::vector<std::string>::iterator Key = Keys.begin();
		for(; Name != Names.end(); ++Name) {
			if ((*Name)[0] != '#') {
				_BadChannelMask.push_back(*Name);
				continue ;
			} else if ((*Name).length() > 200 or
				Name->find_first_of("\007 ,") != Name->npos) {
				_NoSuchChannel.push_back(*Name);
				continue ;
			}
			_NamesWithKeys.push_back(std::pair<std::string, std::string>(*Name, Key != Keys.end() ? *Key++ : ""));
		}
		for (std::list< std::pair<std::string, std::string> >::iterator i = _NamesWithKeys.begin();
			i != _NamesWithKeys.end(); ++i) {
			if (_Initiator->_Channels.size() < MAX_NUMBER_OF_CHANNELS) {
				join(i->first, i->second);
			} else {
				_TooManyChannels.push_back(i->first);
			}
		}
		std::list<std::string>::iterator ErrorNames = _NoSuchChannel.begin();
		while (ErrorNames != _NoSuchChannel.end()) {
			_Initiator->updateReplyMessage(ERR_NOSUCHCHANNEL(*ErrorNames));
			++ErrorNames;
		}
		ErrorNames = _BadChannelMask.begin();
		while (ErrorNames != _BadChannelMask.end()) {
			_Initiator->updateReplyMessage(ERR_BADCHANMASK(*ErrorNames));
			++ErrorNames;
		}
		ErrorNames = _BadChannelKey.begin();
		while (ErrorNames != _BadChannelKey.end()) {
			_Initiator->updateReplyMessage(ERR_BADCHANNELKEY(*ErrorNames));
			++ErrorNames;
		}
		ErrorNames = _BannedFromChannel.begin();
		while (ErrorNames != _BannedFromChannel.end()) {
			_Initiator->updateReplyMessage(ERR_BANNEDFROMCHAN(*ErrorNames));
			++ErrorNames;
		}
		ErrorNames = _InviteOnlyChannel.begin();
		while (ErrorNames != _InviteOnlyChannel.end()) {
			_Initiator->updateReplyMessage(ERR_INVITEONLYCHAN(*ErrorNames));
			++ErrorNames;
		}
		ErrorNames = _ChannelIsFull.begin();
		while (ErrorNames != _ChannelIsFull.end()) {
			_Initiator->updateReplyMessage(ERR_CHANNELISFULL(*ErrorNames));
			++ErrorNames;
		}
		ErrorNames = _TooManyChannels.begin();
		while (ErrorNames != _TooManyChannels.end()) {
			_Initiator->updateReplyMessage(ERR_TOOMANYCHANNELS(*ErrorNames));
			++ErrorNames;
		}
		_NoSuchChannel.clear();
		_BadChannelMask.clear();
		_BadChannelKey.clear();
		_BannedFromChannel.clear();
		_InviteOnlyChannel.clear();
		_ChannelIsFull.clear();
		_TooManyChannels.clear();
		_NamesWithKeys.clear();
		return 0;
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
