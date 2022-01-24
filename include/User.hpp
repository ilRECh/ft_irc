#pragma once

#include "ft.hpp"
#include "AUser.hpp"

// #include "Password.hpp"

using std::string;
using std::vector;

class Channel;

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
	bool _IsRegistered;
    std::string _ReplyMessage;
public:
	User(std::string const Name, int const Fd);
	virtual ~User() {}
	
	bool operator!=(const User& that) const;
	bool operator==(const User& that) const;

	std::string _Msg;
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
	bool getRegistered() const;
	void registeredIs(bool const Condition);

	// ReplyMessage
	status setReplyMessage(std::string const & Msg);
	std::string const getReplyMessage();
};
