#include "Client.hpp"
#include "Server.hpp"

#include "Channel.hpp"

// Channel Operations
#include "INVITE.hpp"
#include "NAMES.hpp"
#include "PART.hpp"
#include "TOPIC.hpp"
#include "MODE.hpp"
#include "JOIN.hpp"
#include "LIST.hpp"
#include "KICK.hpp"

// Connection Registration
#include "PASS.hpp"
#include "NICK.hpp"
#include "USER.hpp"
#include "QUIT.hpp"
#include "OPER.hpp"
#include "SQUIT.hpp"

// Miscellaneous Messages
#include "PING.hpp"
#include "PONG.hpp"

// OPTIONALS
#include "AWAY.hpp"
#include "ISON.hpp"

// Sending Messages
#include "PRIVMSG.hpp"
#include "NOTICE.hpp"

// Server Queries And Commands
#include "ADMIN.hpp"

// UserBasedQueries
#include "WHO.hpp"
#include "WHOIS.hpp"
#include "WHOWAS.hpp"

operators_s Server::_Operators[] = { {"admin", "admin"} };

//* Domain can be AF_INET
Server::Server(string const & Port, string const & Password)
	:   Modes(),
		_Name(SERVER_NAME),
		_Ip("0"),
		_Port(Port),
		_Password(Password),
		_LoopListen(true),
		_Sockfd(-1),
		_ServInfo(NULL),
		_Socklen(0),
		_FdsSet(),
		_MaxFd(0){
	_Commands.push_back(new PASS(*this));
	_Commands.push_back(new NICK(*this));
	_Commands.push_back(new USER(*this));
	_Commands.push_back(new OPER(*this));
	_Commands.push_back(new QUIT(*this));
	_Commands.push_back(new SQUIT(*this));
	_Commands.push_back(new PING(*this));
	_Commands.push_back(new PONG(*this));
	_Commands.push_back(new PRIVMSG(*this));
	_Commands.push_back(new AWAY(*this));
	_Commands.push_back(new MODE(*this));
	_Commands.push_back(new WHO(*this));
	_Commands.push_back(new WHOIS(*this));
	_Commands.push_back(new WHOWAS(*this));
	_Commands.push_back(new PART(*this));
	_Commands.push_back(new ISON(*this));
	_Commands.push_back(new TOPIC(*this));
	_Commands.push_back(new JOIN(*this));
	_Commands.push_back(new NAMES(*this));
	_Commands.push_back(new ADMIN(*this));
	_Commands.push_back(new INVITE(*this));
	_Commands.push_back(new LIST(*this));
	_Commands.push_back(new KICK(*this));
	_Commands.push_back(new NOTICE(*this));
	addrinfo hints;
	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;
	if (getaddrinfo(_Ip.c_str(), _Port.c_str(), &hints, &_ServInfo))
		throw std::runtime_error(
				string("getaddrinfo error: ") + gai_strerror(errno));
	if (1024 > std::atoi(_Port.c_str()) || std::atoi(_Port.c_str()) > 49151)
		throw std::runtime_error("wrong _Port! min 1024, max 49151,");
	std::cout << "Server will be bound to _Port: " << _Port << '\n';
	_Sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (_Sockfd < 0)
		throw std::runtime_error(string("Socket: ") + strerror(errno));
	if (fcntl(_Sockfd, F_SETFL, O_NONBLOCK) < 0)
		throw std::runtime_error(string("fcntl: ") + strerror(errno));
	_Socklen = sizeof(sockaddr);
	if (bind(_Sockfd, _ServInfo->ai_addr, _Socklen))
		throw std::runtime_error(string("bind: ") + strerror(errno));
	if (listen(_Sockfd, SOMAXCONN))
		throw std::runtime_error(string("listen: ") + strerror(errno));
}

void Server::buryMe(std::string const & DyingMessage) {
	_DyingMessage = DyingMessage + "\r\n";
	_LoopListen = false;
}

Server::~Server(void)
{
	for (std::set<Client *>::iterator it = _Clients.begin();
		it not_eq _Clients.end(); ++it) {
		std::string Reply = ":" + _Name + " QUIT " + (*it)->getNickName() + " :" + _DyingMessage;
		send((*it)->_Fd, Reply.c_str(), Reply.length(), MSG_NOSIGNAL);
		close((*it)->_Fd);
		delete *it;
	}
	freeaddrinfo(_ServInfo);
	close(_Sockfd);
	for (std::vector<ACommand *>::iterator it = _Commands.begin();
		it not_eq _Commands.end(); ++it) {
		delete *it;
	}
	for (std::set<Channel *>::iterator it = _Channels.begin();
		it not_eq _Channels.end(); ++it) {
		delete *it;
	}
}

void Server::run()
{
	std::cout << "Waiting for a connection..." << '\n';
	while (_LoopListen)
	{
		//GetConnectionPart
		int const UserFd = accept(_Sockfd, _ServInfo->ai_addr, &_Socklen);
		if (UserFd >= 0) {
			if (UserFd > _MaxFd) {
				_MaxFd = UserFd;
			}
			fcntl(UserFd, F_SETFD, O_NONBLOCK);
			FD_SET(UserFd, &_FdsSet);
#ifdef __linux__
	sockaddr_in AddrUser = {0,0,{0},{0}};
#elif __APPLE__
	sockaddr_in AddrUser = {0,0,0,{0},{0}};
#endif
			socklen_t Socklen = sizeof(AddrUser);
			getpeername(UserFd, (sockaddr *) &AddrUser, &Socklen);
			std::cout << "+====================CONNECTED======================+" << '\n';
			std::cout << "<<<<<<< " << inet_ntoa(AddrUser.sin_addr) << '\n';
			std::cout << "+===================================================+" << std::endl;
			_Clients.insert(new Client(UserFd, inet_ntoa(AddrUser.sin_addr)));
		}

		//ReadPart
		readerClients();

		//Reply part
		replyToClients();

		//Erase dead clients
		eraseClientsAndChannels();
	}
}

void Server::readerClients()
{
	timeval tm = {0, 1000};
	fd_set fdsCopy = _FdsSet;
	if (select(_MaxFd + 1, &fdsCopy, NULL, NULL, &tm) < 0) {
		throw std::runtime_error(std::string("Error: Select") + strerror(errno));
	}
	for (std::set<Client *>::iterator Client = _Clients.begin();
		 Client not_eq _Clients.end(); ++Client)
	{
		if (FD_ISSET((*Client)->_Fd, &fdsCopy) > 0)
		{
			FD_CLR((*Client)->_Fd, &fdsCopy);
			char Buffer[SIZE] = { 0 };
			ssize_t ReadByte = 0;
			ReadByte = recv((*Client)->_Fd, Buffer, SIZE - 1, 0);
			if (ReadByte < 0) {
				continue ;
			}
			if (ReadByte == 0) {
				QUIT q(*this);
				q.setQuitInitiator(*Client);
				q.setArgument(std::string(":Is dead. Just dead. People die, ya know?"));
			} else {
				(*Client)->getIncomingBuffer() += Buffer;
				serverLog(*Client, (*Client)->getIncomingBuffer());
				processCmd(*Client);
			}
		}
	}
}

void Server::processCmd(Client *Client)
{
	if (Client->getIncomingBuffer().end()[-1] not_eq '\n') {
		return ;
	}
	if (Client->getIncomingBuffer().find_first_not_of("\r\n") == Client->getIncomingBuffer().npos) {
		Client->getIncomingBuffer().clear();
		return ;
	}
	std::vector<std::string> Cmds = ft::split(Client->getIncomingBuffer(), "\n");
	for (std::vector<std::string>::iterator i = Cmds.begin(); i != Cmds.end(); ++i) {
		ft::deleteSpaces(*i, "\r");
	}
	Client->getIncomingBuffer().clear();
	for (std::vector<std::string>::iterator it = Cmds.begin();
			it not_eq Cmds.end(); ++it) {
		std::pair<std::string, std::string> Cmd = parseCmd(*it);
		proceedCmd(Cmd, Client);
	}
}

void Server::proceedCmd(std::pair<std::string, std::string> Cmd, Client *_Initiator) {
    try {
        for (std::vector<ACommand *>::iterator command = _Commands.begin();
            command not_eq _Commands.end(); ++command) {
            if (Cmd.first == (*command)->_Name) {
                    (*command)->setArgument(Cmd.second);
                    (*command)->setInitiator(_Initiator);
                    (*command)->run();
                return ;
            }
        }
        _Initiator->updateReplyMessage(ERR_UNKNOWNCOMMAND(_Initiator->getNickName(), Cmd.first));
    } catch (std::exception&) {
        throw;
    } catch (...) {}
}

std::pair<std::string, std::string> Server::parseCmd(std::string &Cmd)
{
	if (Cmd.end()[-1] == '\n') {
		Cmd.erase(Cmd.end()-1);
	}
	char const *Empty = "\010\011\012\013\014\015 ";
	size_t pos_WordStart = Cmd.find_first_not_of(Empty);
	size_t pos_WordEnd = (pos_WordStart not_eq Cmd.npos) ? Cmd.find_first_of(Empty, pos_WordStart) : Cmd.npos;
	std::string pair_First;
	if (pos_WordStart not_eq Cmd.npos && pos_WordEnd not_eq Cmd.npos) {
		pair_First = Cmd.substr(pos_WordStart, pos_WordEnd - pos_WordStart);
	} else {
		pair_First = Cmd;
	}
	std::string pair_Second;
	if (pos_WordEnd not_eq Cmd.npos) {
		pair_Second = Cmd.substr(pos_WordEnd);
	}
	std::pair<std::string, std::string> Value(pair_First, pair_Second);
    std::transform(Value.first.begin(), Value.first.end(), Value.first.begin(), toupper);
	return Value;
}

void Server::replyToClients() {
	for (std::set<Client *>::iterator User = _Clients.begin(); User not_eq _Clients.end(); ++User) {
		if ((*User)->ServerNeedToPING()) {
			PING ping(*this);
			ping.setTarget(*User);
			ping.run();
		}
		std::string ReplyMessage = (*User)->getReplyMessage();
		if (ReplyMessage.empty()) {
			QUIT q(*this);
			q.setQuitInitiator(*User);
			if ((*User)->inactiveShouldDie()) {
				q.setArgument(":Smells Like He's Spirit. B-gone, ghost.");
				q.run();
			} else if ((*User)->unregisteredShouldDie()) {
				q.isNeedToBeSentToInitiatorOnly();
				q.setArgument(":Are not as fast, are ya? Bye then, champ.");
				q.run();
			}
			ReplyMessage = (*User)->getReplyMessage();
		}
		if (not ReplyMessage.empty()) {
			std::cout << "+=======================out=========================+" << std::endl;
			std::cout << ReplyMessage;
			std::cout << "+===================================================+" << std::endl;
			send((*User)->_Fd, ReplyMessage.c_str(), ReplyMessage.length(), MSG_NOSIGNAL);
		}
	}
}

void Server::eraseClientsAndChannels() {
	while (not _ClientsToBeErased.empty()) {
		std::set<Client *>::iterator ToBeErased = _Clients.find(_ClientsToBeErased.front());
		FD_CLR((*ToBeErased)->_Fd, &_FdsSet);
		close((*ToBeErased)->_Fd);
		delete (*ToBeErased);
		eraseClientFromModes(*ToBeErased);
		_Clients.erase(ToBeErased);
		_ClientsToBeErased.pop_front();
	}

	while (not _ChannelsToBeErased.empty()) {
		std::set<Channel *>::iterator ToBeErased = _Channels.find(_ChannelsToBeErased.front());
		delete (*ToBeErased);
		_Channels.erase(ToBeErased);
		_ChannelsToBeErased.pop_front();
	}
}

void Server::serverLog(Client *That, std::string const & ReceivedMessage)
{
	std::cout << "+========================in========================+" << std::endl;
	std::cout << That->getNickName() << ": "<< ReceivedMessage;
	std::cout << "+==================================================+" << std::endl;
}

Client *Server::getUserByNickName(std::string const & NickName){
	std::set<Client *>::iterator first, last;
	first = _Clients.begin();
	last = _Clients.end();

	for (;first not_eq last; ++first)
		if (ft::tolowerString((*first)->getNickName()) == ft::tolowerString(NickName))
			return *first;
	return NULL;
}

//* now it support find by wildcard
std::set<Client *> Server::getClientsByName(std::string Name){
	std::set<Client *>::iterator istart = _Clients.begin();
	std::set<Client *>::iterator ifinish = _Clients.end();
	std::set<Client *> result;

	for(uint i = Name.size(); true;)
	{
		if (Name[--i] not_eq '*')
			break;
		if (!i)
			return _Clients;
	}

	if (Name.find('*') not_eq std::string::npos)
	{
		for(;istart not_eq ifinish; ++istart)
		{
			if (ft::wildcard(ft::tolowerString(Name), ft::tolowerString((*istart)->_NickName)))
				result.insert(*istart);
		}
	}
	else
	{
		for(;istart not_eq ifinish; ++istart)
			if (ft::tolowerString((*istart)->getNickName()) == ft::tolowerString(Name))
				result.insert(*istart);
	}
	return result;
}

std::set<Channel *> Server::getChannelsByChannelName(std::string ChannelName, bool enableWildcard){
	std::set<Channel *>::iterator istart = _Channels.begin();
	std::set<Channel *>::iterator ifinish = _Channels.end();
	std::set<Channel *> result;

	for(uint i = ChannelName.size(); enableWildcard;)
	{
		if (ChannelName[--i] not_eq '*')
			break;
		if (!i)
			return _Channels;
	}

	if (ChannelName.find('*') == std::string::npos && enableWildcard)
	{
		for(;istart not_eq ifinish; ++istart)
			if (ft::wildcard(ChannelName, (*istart)->getChannelName()))
				result.insert(*istart);
	}
	else
	{
		for(;istart not_eq ifinish; ++istart)
			if ((*istart)->getChannelName() == ChannelName)
				result.insert(*istart);
	}
	return result;
}

Channel *Server::getChannelByChannelName(std::string const & NameChannel){
	std::set<Channel *>::iterator first, last;

	first = _Channels.begin();
	last = _Channels.end();
	for(;first not_eq last; ++first)
		if (ft::tolowerString((*first)->getChannelName()) == ft::tolowerString(NameChannel))
			return *first;
	return NULL;
}

OperatorStatus Server::canBeAutorized(
	std::string const & Name,
	std::string const & Password) {
	operators_s *_Operators_end = _Operators + sizeof(_Operators) / sizeof(operators_s);
	operators_s *oper = std::find(_Operators, _Operators_end, Name);
	if (oper == _Operators_end) {
		return NOOPERHOST;
	} else if (oper->Password not_eq Password) {
		return PASSWDMISMATCH;
	}
	return YOUREOPER;
}

bool Server::pushBack(Channel *Channel){
	return _Channels.insert(Channel).second;
}

void Server::pushBackErase(Client *Client) {
	_ClientsToBeErased.push_front(Client);
}

void Server::pushBackErase(Channel *Channel) {
	_ChannelsToBeErased.push_front(Channel);
}
