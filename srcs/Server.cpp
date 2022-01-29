#include "Server.hpp"
#include "Client.hpp"

#include "Channel.hpp"

// Commands
#include "PASS.hpp"
#include "NICK.hpp"
#include "USER.hpp"
#include "QUIT.hpp"
#include "PING.hpp"
#include "PONG.hpp"
#include "UNKNOWNCOMMAND.hpp"

//* Domain can be AF_INET
Server::Server(string const & Port, string const & Password)
    :   _Ip("127.0.0.1"),
        _Port(Port),
        _Password(Password),
        _LoopListen(true),
        _Sockfd(-1),
        _ServInfo(NULL),
        _Socklen(0),
        _FdsSet(),
        _MaxFd(0) {
    _Commands.push_back(new PASS(*this));
    _Commands.push_back(new NICK(*this));
    _Commands.push_back(new USER(*this));
    _Commands.push_back(new QUIT(*this));
    _Commands.push_back(new PING(*this));
    _Commands.push_back(new PONG(*this));
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
    _Sockfd = socket(AF_INET, SOCK_STREAM/* | SOCK_NONBLOCK*/, 0);
    if (_Sockfd < 0)
        throw std::runtime_error(string("Socket: ") + strerror(errno));
    int    retFcntl = fcntl(_Sockfd, F_GETFL, 0);
    if (retFcntl < 0 || fcntl(_Sockfd, F_SETFL, retFcntl | O_NONBLOCK) < 0)
        throw std::runtime_error(string("fcntl: ") + strerror(errno));
    _Socklen = sizeof(sockaddr);
    if (bind(_Sockfd, _ServInfo->ai_addr, _Socklen))
        throw std::runtime_error(string("bind: ") + strerror(errno));
    if (listen(_Sockfd, 1)) // *! Возможно второй аргумент придется увеличить
        throw std::runtime_error(string("listen: ") + strerror(errno));
    // FD_ZERO(&_FdsSet);
}

Server::~Server(void)
{
    freeaddrinfo(_ServInfo);
    close(_Sockfd);
    for (std::set<Client *>::iterator it = _Clients.begin();
         it != _Clients.end(); ++it) {
        close((*it)->_Fd);
        delete *it;
    }
    for (std::vector<ACommand *>::iterator it = _Commands.begin();
         it != _Commands.end(); ++it) {
        delete *it;
    }
}

void Server::run()
{
    timeval tm = {0, 10000};

    std::cout << "Waiting for a connection..." << '\n';
    while (_LoopListen)
    {

        //GetConnectionPart
        int const UserFd = accept(_Sockfd, _ServInfo->ai_addr, &_Socklen);
        if (UserFd >= 0) {
            if (UserFd > _MaxFd) {
                _MaxFd = UserFd;
            }
            fcntl(UserFd, F_SETFD, fcntl(UserFd, F_GETFD) | O_NONBLOCK);
            FD_SET(UserFd, &_FdsSet);
            send(UserFd, "=> Server connected!\n", 22, 0);
#ifdef __linux__
    sockaddr_in AddrUser = {0,0,{0},{0}};
#elif __APPLE__
    sockaddr_in AddrUser = {0,0,0,{0},{0}};
#endif
            socklen_t Socklen = sizeof(AddrUser);
            std::cout << "status: " << getpeername(UserFd, (sockaddr *) &AddrUser, &Socklen) << '\n'; //* Выяняем кто подключился
            std::cout << "<<<<<<< " << inet_ntoa(AddrUser.sin_addr) << '\n'; // Left for testing, remove if Release
            _Clients.insert(new Client(UserFd));
        } else if (UserFd < 0 && errno != EAGAIN) {
            throw std::runtime_error("Fatal. Accepting the " + ft::to_string(UserFd) + " failed.\n" + strerror(errno));
        }

        //ReadPart
        int retSelect = 1;
		fd_set fdsCopy = _FdsSet;
        while (retSelect && _MaxFd)
        {
            retSelect = select(_MaxFd + 1, &fdsCopy, NULL, NULL, &tm);
            if (retSelect > 0) {
                readerClient(fdsCopy);
            } else if (retSelect < 0) {
                throw std::runtime_error("Error: Select");
            }
        }

        //Reply part
        for (std::set<Client *>::iterator User = _Clients.begin(); User != _Clients.end(); ++User) {
            if ((*User)->ServerNeedToPING()) {
                PING ping(*this);
                ping.setTarget(*User);
                ping.run();
            }
            std::string ReplyMessage = (*User)->getReplyMessage();
            if (not ReplyMessage.empty()) {
                send((*User)->_Fd, ReplyMessage.c_str(), ReplyMessage.length(), 0);
            } else {
                QUIT q(*this);
                q.setTarget(*User);
                if ((*User)->inactiveShouldDie()) {
                    q.setArgument("QUIT: Smells Like Thees Spirit. B-gone, ghost.");
                    q.run();
                } else if ((*User)->unregisteredShouldDie()) {
                    q.setArgument("QUIT: Are not as fast, are ya? Bye then, champ.");
                    q.run();
                }
            }
        }

        //Erase part
        while (not _UsersToBeErased.empty()) {
            std::set<Client *>::iterator ToBeErased = _Clients.find(_UsersToBeErased.front());
            FD_CLR((*ToBeErased)->_Fd, &_FdsSet);
            close((*ToBeErased)->_Fd);
            delete(*ToBeErased);
            _Clients.erase(ToBeErased);
            _UsersToBeErased.pop_front();
        }
    }
}

void Server::readerClient(fd_set & fdsCpy)
{
    for (std::set<Client *>::iterator Client = _Clients.begin();
         Client != _Clients.end(); ++Client)
    {
        if (FD_ISSET((*Client)->_Fd, &fdsCpy) > 0)
        {
			FD_CLR((*Client)->_Fd, &fdsCpy);
			char Buffer[SIZE] = { 0 };
			ssize_t ReadByte = 0;
			ReadByte = recv((*Client)->_Fd, Buffer, SIZE, 0);
			if (ReadByte < 0 && errno != EAGAIN) {
				throw std::runtime_error(std::string("recv: ") + strerror(errno));
			} else if (ReadByte == 0) {
				FD_CLR((*Client)->_Fd, &_FdsSet);
                _Clients.erase(Client);
				return ;
			}
            (*Client)->getIncomingBuffer() += Buffer;
            serverLog(*Client, (*Client)->getIncomingBuffer());
            processCmd(*Client);
        }
    }
}

void Server::processCmd(Client *Client)
{
    if (Client->getIncomingBuffer().end()[-1] != '\n') {
        return ;
    }
    std::vector<std::string> Cmds = ft::splitByCmds(Client->getIncomingBuffer(), "\r\n");
    Client->getIncomingBuffer().clear();
    for (std::vector<std::string>::iterator it = Cmds.begin();
            it != Cmds.end(); ++it) {
        std::pair<std::string, std::string> Cmd = parseCmd(*it);
        proceedCmd(Cmd, Client);
    }
}

void Server::proceedCmd(std::pair<std::string, std::string> Cmd, Client *User) {
    try {
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
        UNKNOWNCOMMAND uc(*this);
        uc.setInitiator(User);
        uc.setArgument(Cmd.first);
        uc.run();
    } catch (...) {}
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

    ReturnValue += _Age.getTimeStrCurrent() + " " + From->getNickName() + " " + From->getReplyMessage();
    send(To->_Fd , ReturnValue.c_str(), ReturnValue.size(), 0);
}

void Server::sendMsg(Client *To) {
    std::string ReturnValue;

    ReturnValue += _Age.getTimeStrCurrent() + " " + To->getNickName() + " " + To->getReplyMessage();
    send(To->_Fd , ReturnValue.c_str(), ReturnValue.size(), 0);
}

void Server::serverLog(Client *That, std::string const & ReceivedMessage)
{
    std::cout << That->getNickName() << ": "<< ReceivedMessage << std::endl;
}

std::set<Client *> const &Server::getUsers(){
	return _Clients;
}

Client *Server::getUserByNickName(std::string const & NickName){
	std::set<Client *>::iterator first, last;
	first = _Clients.begin();
	last = _Clients.end();

	for (;first != last; ++first)
		if ((*first)->getNickName() == NickName)
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
		if (Name[--i] != '*')
			break;
		if (!i)
			return _Clients;
	}

	if (Name.find('*') == std::string::npos)
	{
		for(;istart != ifinish; ++istart)
			if (ft::wildcard(Name, (*istart)->getName()))
				result.insert(*istart);
	}
	else
	{
		for(;istart != ifinish; ++istart)
			if ((*istart)->getName() == Name)
				result.insert(*istart);
	}
	return result;
}

Channel *Server::getChannelByName(std::string const & NameChannel){
	std::set<Channel *>::iterator first, last;

	first = _Channels.begin();
	last = _Channels.end();
	for(;first != last; ++first)
		if ((*first)->getName() == NameChannel)
			return *first;
	return NULL;
}

void Server::pushBackErase(Client *Client) {
    _UsersToBeErased.push_front(Client);
}
