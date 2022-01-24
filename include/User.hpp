#pragma once

#include "ft.hpp"
#include "AUser.hpp"

// #include "Password.hpp"

using std::string;
using std::vector;

class Channel;
class TimeStamp;

class User : public AUser {
private:
	TimeStamp _time;
	std::set<char> _mode_set;
	std::string _Password;
	User(User& that);
	User& operator=(User& that);
	vector<Channel const *> _Channels;
	std::string _NickName;
	std::string _RealName;
	std::pair<bool, TimeStamp> Registration;
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

	// NickName
	void setNickName(std::string const & NickName);
	string const & getNickName( void ) const;

	//	* get|set mode
	bool	getModeIsExist(char) const;
	void	setMode(char);
	void	unsetMode(char);
	
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
	void updateActivity();

	// ReplyMessage
	status setReplyMessage(std::string const & Msg);
	std::string const getReplyMessage();
};
