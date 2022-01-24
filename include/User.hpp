#pragma once

#include "ft.hpp"
#include "AUser.hpp"

// #include "Password.hpp"

using std::string;
using std::vector;

class Channel;

class User : public AUser {
private:
	User(User& that);
	User& operator=(User& that);
	vector<Channel const *> _Channels;
	std::string _NickName;
	std::string _RealName;
	bool _IsRegistered;
    std::string _ReplyMessage;
public:
	User(std::string const & Name, int const Fd);
	virtual ~User() {}
	
	bool operator!=(const User& that) const;
	bool operator==(const User& that) const;

	std::string _Msg;
	int const _Fd;
	void inviteToChannel(Channel const & channel);
	void setNickName(std::string const & NickName);
	string const & getNickName( void ) const;
	void registeredIs(bool const Condition);
	bool getRegistered() const;
	void setChannels(std::vector<Channel const *> & Channels);
	std::vector<Channel const *> const getChannels() const;
	void setReplyMessage(std::string const & Msg);
	std::string const getReplyMessage();
};
