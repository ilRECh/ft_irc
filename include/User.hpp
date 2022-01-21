#pragma once

#include "Mandatory.hpp"
#include "Server.hpp"
#include "Password.hpp"
#include "Channel.hpp"

using std::string;
using std::vector;

class Channel;

class User {//: public Password {
private:
	TimeStamp _time;
	std::set<char> _mode_set;
	std::string _Password;
	vector<Channel const *> _Channels;
	std::string _Name;
	std::string _NickName;
	std::string _RealName;
	bool _IsRegistered;
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

	std::string _Msg;
	int const _Fd;
	sockaddr_in const _AddrUser;
	socklen_t const _Socklen;
	void inviteToChannel(Channel const & channel);
	void setName(string const & name);
	string const & getName( void ) const;
	string const & getNickName( void ) const;
	void setPassword(std::string const & Password);
	std::string const & getPassword() const;
	void registeredIs(bool const Condition);

	//	* get|set mode
	bool	getModeIsExist(char) const;
	void	setMode(char);
	void	unsetMode(char);
	
	// * get time
	TimeStamp const & getTime() const;
	
	//	* get|set addrUser
	sockaddr_in const getAddrUser() const;
	void setAddrUser(struct sockaddr_in & _SaddrUser);
	//void setSocklen(socklen_t & Socklen);
	//socklen_t const getSocklen() const;

	//	* get|set Channels
	void setChannel(Channel const * Channel);
	std::vector<Channel const *> const &getChannels() const;

	//	* get Registered
	bool getRegistered() const;
};
