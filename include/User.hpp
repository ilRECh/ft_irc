#pragma once

#include "Server.hpp"
#include "Password.hpp"
#include "Channel.hpp"

using std::string;
using std::vector;

class Channel;

class User : public Password {
private:
	User();

	std::string _Name;
	std::string _Password;
	struct sockaddr_in _SaddrUser;
	vector<Channel const *> _Channels;
public:
	User(
		std::string const & Name,
		Channel const & BaseChannel,
		int const Fd,
		socklen_t const Socklen);
	User(User& that);
	~User();
	User& operator=(User& that);
	bool operator!=(const User& that) const;
	bool operator==(const User& that) const;

	int const _Fd;
	socklen_t const _Socklen;
	void inviteToChannel(Channel const & channel);
	void setName(string const & name);
	string const & getName( void ) const;
	void setPassword(std::string const & Password);
	std::string const & getPassword() const;
	void setAddrUser(struct sockaddr_in & _SaddrUser);
	struct sockaddr_in const getAddrUser() const;
	//void setSocklen(socklen_t & Socklen);
	//socklen_t const getSocklen() const;
	void setChannels(std::vector<Channel const *> & Channels);
	std::vector<Channel const *> const getChannels() const;
};
