#pragma once

#include "ft.hpp"

#ifndef GODMODE
#define MAY_BE_UNREGISTERED_seconds 40
#define MAY_BE_INACTIVE_seconds 100
#else
#define MAY_BE_UNREGISTERED_seconds 100000
#define MAY_BE_INACTIVE_seconds 100000
#endif

using std::string;
using std::vector;

class Channel;
class TimeStamp;

class Client {
private:
	TimeStamp _time;
	Client(Client& that);
	Client& operator=(Client& that);
	Channel *	_lastJoin;
	std::set<Channel *> _Channels;
	bool _PasswordCorrect;
	std::string _UserName;
	std::string _NickName;
	std::string _RealName;
    std::string _Away;
	std::string _HostName;
	std::string _ServerName;
	struct registration_s {
		registration_s()
			:	IsRegistered(false) {}
		bool IsRegistered;
		TimeStamp Time;
	} _Registration;
	struct activity_s {
		activity_s()
			:	WaitingForPONG(false) {} 
		bool WaitingForPONG;
		TimeStamp LastResponse;
		TimeStamp LastPING;
	} _Activity;
    std::string _ReplyMessage;
	std::string _IncomingBuffer;
	std::string getFull() { return _NickName + "!" + _UserName + "@" + _HostName; }
public:
	Client(int const Fd, std::string HostName);
	~Client() {}
	
	bool operator!=(const Client& that) const;
	bool operator==(const Client& that) const;

	int const _Fd;

	// Names get|set
	string const & getNickName() const { return _NickName; }
	
	// * get activity
	TimeStamp const & getLastActivity() const;

	//	* get|set  invite Channels
	bool isOnChannel(Channel * channel);

	//	* get Registered
	bool unregisteredShouldDie() const;

	// Last Activity
	bool inactiveShouldDie() const;
	bool ServerNeedToPING() const;
	void updateActivity();

	// ReplyMessage
	bool updateReplyMessage(
		std::string const & Msg,
		std::string const & From = std::string("irc.WIP.ru"));
	std::string const getReplyMessage();

	// Incoming buffer
	std::string& getIncomingBuffer();
private:
	friend class ACommand;
	friend class INVITE;
	friend class JOIN;
	friend class KICK;
	friend class LIST;
	friend class MODE;
	friend class NAMES;
	friend class PART;
	friend class TOPIC;
	friend class NICK;
	friend class OPER;
	friend class PASS;
	friend class QUIT;
	friend class SERVER;
	friend class Server;
	friend class SQUIT;
	friend class USER;
	friend class ERROR;
	friend class KILL;
	friend class PING;
	friend class PONG;
	friend class AWAY;
	friend class ISON;
	friend class REHASH;
	friend class RESTART;
	friend class SUMMON;
	friend class USERHOST;
	friend class USERS;
	friend class WALLOPS;
	friend class NOTICE;
	friend class PRIVMSG;
	friend class ADMIN;
	friend class CONNECT;
	friend class INFO;
	friend class LINKS;
	friend class STATS;
	friend class TIME;
	friend class TRACE;
	friend class VERSIONS;
	friend class WHO;
	friend class WHOIS;
	friend class WHOWAS;
	friend class Channel;
};
