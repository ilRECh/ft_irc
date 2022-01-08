#pragma once

#include "Mandatory.hpp"
#include "Server.hpp"
#include "Password.hpp"
#include "Channel.hpp"

using std::string;
using std::vector;

class Channel;

class User : public Password {
private:
	User();
	std::string _Password;
	vector<Channel const *> _Channels;
	std::string _Name;
public:
	User(
		std::string const & Name,
		//Channel const & BaseChannel, // Do we need it on acception?
		int const Fd,
		sockaddr_in AddrUser,
		socklen_t const Socklen);
	User(User& that);
	~User();
	User& operator=(User& that);
	bool operator!=(const User& that) const;
	bool operator==(const User& that) const;

	int const _Fd;
	sockaddr_in const _AddrUser;
	socklen_t const _Socklen;
	void inviteToChannel(Channel const & channel);
	void setName(string const & name);
	string const & getName( void ) const;
	void setPassword(std::string const & Password);
	std::string const & getPassword() const;
	void setAddrUser(struct sockaddr_in & _SaddrUser);
	sockaddr_in const getAddrUser() const;
	//void setSocklen(socklen_t & Socklen);
	//socklen_t const getSocklen() const;
	void setChannels(std::vector<Channel const *> & Channels);
	std::vector<Channel const *> const getChannels() const;
};
