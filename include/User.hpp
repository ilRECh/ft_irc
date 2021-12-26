#pragma once

#include "Server.hpp"
#include "Password.hpp"
#include "Channel.hpp"

using std::string;
using std::vector;

class Channel;

class User: public Password {
private:
	string                  _Name;
	vector<Channel const *> _Channels;
public:
	User(string const & name, Channel const & baseChannel);
	User(User& that);
	~User();
	void inviteToChannel(Channel const & channel);
	void setName(string const & name);
	string const & getName( void ) const;
	User& operator=(User& that);
	bool operator==(const User& that) const;
	bool operator!=(const User& that) const;
};
