#pragma once

#include "ft.hpp"
#include "AUser.hpp"

#define MAY_BE_UNREGISTERED_seconds 100
#define MAY_BE_INACTIVE_seconds 30

using std::string;
using std::vector;

class Channel;
class TimeStamp;

class User : public AUser {
private:
	TimeStamp _time;
	std::set<char> _mode_set;
	User(User& that);
	User& operator=(User& that);
	vector<Channel const *> _Channels;
	std::string _NickName;
	std::string _RealName;
	std::string _HostName;
	std::string _ServerName;
	struct {
		bool IsRegistered;
		TimeStamp Time;
	} _Registration;
	TimeStamp _LastResponse;
    std::string _ReplyMessage;
public:
	User(int const Fd);
	virtual ~User() {}
	
	bool operator!=(const User& that) const;
	bool operator==(const User& that) const;

	int const _Fd;

	// Names get|set
	void setNickName(std::string const & NickName);
	string const & getNickName() const;
	void setRealName(std::string const & RealName);
	string const & getRealName() const;
	void setHostName(std::string const & HostName);
	string const & getHostName() const;
	void setServerName(std::string const & ServerName);
	string const & getServerName() const;

	//	* get|set mode
	bool	getModeIsExist(char c) const;
	void	setMode(char c);
	void	unsetMode(char c);
	
	// * get time
	TimeStamp const & getTime() const;

	//	* get|set Channels
	void inviteToChannel(Channel const & channel);
	void setChannel(Channel const * Channel);
	std::vector<Channel const *> const &getChannels() const;

	//	* get Registered
	bool isRegistered() const;
	void setRegistered(bool const Condition);
	bool unregisteredShouldDie() const;

	// Last Activity
	bool inactiveShouldDie() const;
	bool isReadyForPing() const;
	void updateActivity();

	// ReplyMessage
	status updateReplyMessage(std::string const & Msg);
	std::string const getReplyMessage();
};
