#include "Server.hpp"
#include "Client.hpp"

#include "Channel.hpp"

// Commands
#include "PASS.hpp"
#include "NICK.hpp"
#include "USER.hpp"

Server::Server(std::vector<std::string> &argv)
        : _Commands(),
          ip(0),
          port(0),
          _LoopListen(true)
{
    _Commands.push_back(new PASS(*this));
    std::vector<std::string>::reverse_iterator r_it = argv.rbegin();
    _Password = *r_it--;
    _Port = *r_it--;
    if (1024 > std::atoi(_Port.c_str()) || std::atoi(_Port.c_str()) > 65535)
    {
        throw std::runtime_error("Port is out of range");
    }
    if (r_it != argv.rend())
    {
        std::vector<std::string> ExistingNetwork = ft::split(*r_it--, ":");
        _Host = ExistingNetwork[HOST];
        _PortNetwork = ExistingNetwork[PORT_NETWORK];
        if (1024 > std::atoi(_PortNetwork.c_str()) ||
            std::atoi(_PortNetwork.c_str()) > 65535)
        {
            throw std::runtime_error("Port is out of range");
        }
        _PasswordNetwork = ExistingNetwork[PASSWORD_NETWORK];
    }
}

//* Domain can be AF_INET
Server::Server(string const &ip, string const &port)
        : ip(ip),
          port(port),
          _LoopListen(true)
{
    _Commands.push_back(new PASS(*this));
    _Commands.push_back(new NICK(*this));
    _Commands.push_back(new USER(*this));
    addrinfo hints;

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;


    if (getaddrinfo(ip.c_str(), port.c_str(), &hints, &servinfo))
        throw std::runtime_error(
                string("getaddrinfo error: ") + gai_strerror(errno));
    if (1024 > std::atoi(port.c_str()) || std::atoi(port.c_str()) > 49151)
        throw std::runtime_error("wrong port! min 1024, max 49151,");


    std::cout << "Server will be bound to port: " << port << '\n';
    _Sockfd = socket(AF_INET, SOCK_STREAM/* | SOCK_NONBLOCK*/, 0);
    if (_Sockfd < 0)
        throw std::runtime_error(string("Socket: ") + strerror(errno));
    int    retFcntl = fcntl(_Sockfd, F_GETFL, 0);
    if (retFcntl < 0 || fcntl(_Sockfd, F_SETFL, retFcntl | O_NONBLOCK) < 0)
        throw std::runtime_error(string("fcntl: ") + strerror(errno));
    _Socklen = sizeof(sockaddr);
    if (bind(_Sockfd, servinfo->ai_addr, _Socklen))
        throw std::runtime_error(string("bind: ") + strerror(errno));
    if (listen(_Sockfd, 1)) // *! Возможно второй аргумент придется увеличить
        throw std::runtime_error(string("listen: ") + strerror(errno));
    FD_ZERO(&_Fds_set);
    maxFd = 0;
}

Server::~Server(void)
{
    freeaddrinfo(servinfo);
    close(_Sockfd);
    for (std::vector<Client *>::iterator it = _Users.begin();
         it != _Users.end(); ++it)
    {
        close((*it)->_Fd);
        delete *it;
    }
    for (std::vector<ACommand *>::iterator it = _Commands.begin();
         it != _Commands.end(); ++it)
    {
        delete *it;
    }
}

void Server::run()
{
    timeval tm = {0, 10000};

    std::cout << "Waiting for a connection..." << '\n';
    while (_LoopListen)
    {
        int const UserFd = accept(_Sockfd, servinfo->ai_addr, &_Socklen);
        if (UserFd >= 0) {
            if (UserFd > maxFd) {
                maxFd = UserFd;
            }
            fcntl(UserFd, F_SETFD, fcntl(UserFd, F_GETFD) | O_NONBLOCK);
            FD_SET(UserFd, &_Fds_set);
            send(UserFd, "=> Server connected!\n", 22, 0);
#ifdef __linux__
            sockaddr_in AddrUser = {0, 0, {0}, {0}};
#elif __APPLE__
            sockaddr_in AddrUser = {0, 0, 0, {0}, {0}};
#endif
            socklen_t Socklen = sizeof(AddrUser);
            std::cout << "status: " << getpeername(UserFd, (sockaddr *) &AddrUser, &Socklen) << '\n'; //* Выяняем кто подключился
            std::cout << "<<<<<<< " << inet_ntoa(AddrUser.sin_addr) << '\n'; // Left for testing, remove if Release
            _Users.push_back(new Client(UserFd));
        } else if (UserFd < 0 && errno != EAGAIN) {
            throw std::runtime_error("Fatal. Accepting the " + ft::to_string(UserFd) + " failed.\n" + strerror(errno));
        }
        int retSelect = 1;
		fd_set fdsCopy = _Fds_set;
        while (retSelect && maxFd)
        {
            retSelect = select(maxFd + 1, &fdsCopy, NULL, NULL, &tm);
            if (retSelect > 0) {
                readerClient(fdsCopy);
            } else if (retSelect < 0) {
                throw std::runtime_error("Error: Select");
            }
        }
		for (std::vector<Client *>::iterator User = _Users.begin(); User != _Users.end(); ++User) {
			std::string ReplyMessage = (*User)->getReplyMessage();
            if ((*User)->isReadyForPing()) {
                //PING(*User);
            }
			if (not ReplyMessage.empty()) {
				send((*User)->_Fd, ReplyMessage.c_str(), ReplyMessage.length(), 0);
			} else {
				if ((*User)->unregisteredShouldDie() || (*User)->inactiveShouldDie()) {
					FD_CLR((*User)->_Fd, &_Fds_set);
            		if ((User = _Users.erase(User)) == _Users.end()) {
						break ;
					}
				}
			}
		}
    }
}

void Server::readerClient(fd_set & fdsCpy)
{
    for (std::vector<Client *>::iterator it = _Users.begin();
         it != _Users.end(); ++it)
    {
        if (FD_ISSET((*it)->_Fd, &fdsCpy) > 0)
        {
			FD_CLR((*it)->_Fd, &fdsCpy);
			char Buffer[SIZE] = { 0 };
			ssize_t ReadByte = 0;
			ReadByte = recv((*it)->_Fd, Buffer, SIZE, 0);
			if (ReadByte < 0 && errno != EAGAIN) {
				throw std::runtime_error(std::string("recv: ") + strerror(errno));
			} else if (ReadByte == 0) {
				FD_CLR((*it)->_Fd, &_Fds_set);
				return ;
			}
			std::string ReceivedMessage(Buffer);
            processCmd(*it, ReceivedMessage);
            serverLog(*it, ReceivedMessage);
        }
    }
}

void Server::processCmd(Client *User, std::string const & ReceivedMessage)
{
    std::vector<std::string> Cmds = ft::splitByCmds(ReceivedMessage, "\r\n");

    for (std::vector<std::string>::iterator it = Cmds.begin();
            it != Cmds.end(); ++it) {
        std::pair<std::string, std::string> Cmd = parseCmd(*it);
        proceedCmd(Cmd, User);
    }
}

void Server::proceedCmd(std::pair<std::string, std::string> Cmd, Client *User) {
	for (std::vector<ACommand *>::iterator command = _Commands.begin();
			command != _Commands.end(); ++command) {
		if (Cmd.first == (*command)->_Name) {
			std::cout << (*command)->_Name << std::endl;
			(*command)->setArgument(Cmd.second);
			(*command)->setInitiator(User);
			(*command)->run();
			return ;
		}
	}
	User->setReplyMessage(ERR_UNKNOWNCOMMAND(Cmd.first));
}

std::pair<std::string, std::string> Server::parseCmd(std::string &Cmd)
{
    if (Cmd.end()[-1] == '\n') {
        Cmd.erase(Cmd.end()-1);
    }
    char const *Empty = "\010\011\012\013\014\015 ";
    size_t pos_WordStart = Cmd.find_first_not_of(Empty);
    size_t pos_WordEnd = (pos_WordStart != Cmd.npos) ? Cmd.find_first_of(Empty, pos_WordStart) : Cmd.npos;
    std::string pair_First;
    if (pos_WordStart != Cmd.npos && pos_WordEnd != Cmd.npos) {
        pair_First = Cmd.substr(pos_WordStart, pos_WordEnd - pos_WordStart);
    } else {
        pair_First = Cmd;
    }
    std::string pair_Second;
    if (pos_WordEnd != Cmd.npos) {
        pair_Second = Cmd.substr(pos_WordEnd);
    }
    std::pair<std::string, std::string> Value(pair_First, pair_Second);
    std::cout << '|' << Value.first << '|' << Value.second << '|' << '\n';
    return Value;
}

void Server::sendMsg(Client *From, Client *To)
{
    std::string ReturnValue;

    ReturnValue += timeStamp() + " " + From->getName() + " " + From->getReplyMessage();
    send(To->_Fd , ReturnValue.c_str(), ReturnValue.size(), 0);
}

void Server::sendMsg(Client *To) {
    std::string ReturnValue;

    ReturnValue += timeStamp() + " " + To->getName() + " " + To->getReplyMessage();
    send(To->_Fd , ReturnValue.c_str(), ReturnValue.size(), 0);
}

void Server::serverLog(Client *That, std::string const & ReceivedMessage)
{
    std::cout << That->getName() << ": "<< ReceivedMessage;
}

std::vector<Client *> const &Server::getUsers(){
	return _Users;
}

Client *Server::getUserByNickName(std::string const & NickName){
	std::vector<Client *>::iterator first, last;
	first = _Users.begin();
	last = _Users.end();

	for (;first != last; ++first)
		if ((*first)->getNickName() == NickName)
			return *first;
	return NULL;
}

Client *Server::getUserByName(std::string const & Name){
	std::vector<Client *>::iterator first, last;
	first = _Users.begin();
	last = _Users.end();

	for (;first != last; ++first)
		if ((*first)->getName() == Name)
			return *first;
	return NULL;
}

Channel *Server::getChannelByName(std::string const & NameChannel){
	std::vector<Channel *>::iterator first, last;

	first = _Channels.begin();
	last = _Channels.end();
	for(;first != last; ++first)
		if ((*first)->getName() == NameChannel)
			return *first;
	return NULL;
}

void Server::removeUserByNickName(std::string const & NickName) {
    for (std::vector<Client *>::iterator i = _Users.begin(); i != _Users.end(); ++i) {
        if ((*i)->getNickName() == NickName) {
            FD_CLR((*i)->_Fd, &_Fds_set);
            _Users.erase(i);
        }
    }
}
