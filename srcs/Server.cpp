#include "Server.hpp"

Server::Server(std::vector<std::string> &argv)
        : _Commands(),
          ip(0),
          port(0),
          _LoopListen(true)
{
    _Commands.push_back(new PASS(this));
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
    _Commands.push_back(new PASS(this));
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
    if (listen(_Sockfd, 1))
        throw std::runtime_error(string("listen: ") + strerror(errno));
    FD_ZERO(&fds);
    maxFd = 0;
}

Server::~Server(void)
{
    freeaddrinfo(servinfo);
    close(_Sockfd);
    for (std::vector<User *>::iterator it = _Users.begin();
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

void Server::readerClient(fd_set fdsCpy)
{
    for (std::vector<User *>::iterator it = _Users.begin();
         it != _Users.end(); ++it)
    {
        if (FD_ISSET((*it)->_Fd, &fdsCpy) > 0)
        {
            (*it)->_Msg = recvReader((*it)->_Fd);
            processCmd(*it);
            serverLog(*it);
        }
    }
}

void Server::run()
{
    timeval tm = {5, 0};
    fd_set fdsCpy = {{0}}; // Why? ... for FD_SET() & FD_ISSET()
    int retSelect = 0;

    std::cout << "Waiting for a connection..." << '\n';
    while (_LoopListen)
    {
        int const UserFd = accept(_Sockfd, servinfo->ai_addr, &_Socklen);
        if (UserFd >= 0)
        {
            if (UserFd > maxFd)
            {
                maxFd = UserFd;
            }
            fcntl(UserFd, F_SETFD, fcntl(UserFd, F_GETFD) | O_NONBLOCK);
            FD_SET(UserFd, &fds);
            send(UserFd, "=> Server connected!\n", 22, 0);
            sockaddr_in AddrUser;// = {0, 0, {0}, {0}};
            socklen_t Socklen = sizeof(AddrUser);
            //* Выяняем кто подключился
            std::cout << "status: "
                      << getpeername(UserFd, (sockaddr *) &AddrUser, &Socklen)
                      << '\n';
            // Left for testing, remove if Release
            std::cout << "<<<<<<< " << inet_ntoa(AddrUser.sin_addr)
                      << '\n';
            User *NewUser = new User("Name", UserFd, AddrUser, Socklen);
            _Users.push_back(NewUser);
        } else if (UserFd < 0 && errno != EAGAIN) {
            throw std::runtime_error("Fatal. Accepting the " + ft::to_string(UserFd) + " failed.\n" + strerror(errno));
        }
        retSelect = 1;
        while (retSelect && maxFd)
        {
            fdsCpy = fds;
            retSelect = select(maxFd + 1, &fdsCpy, NULL, NULL, &tm);
            if (retSelect > 0)
            {
                readerClient(fdsCpy);
            } else if (retSelect < 0)
            {
                throw std::runtime_error("Error: Select");
            }
        }
    }
}

int Server::processCmd(User *That)
{
    std::vector<std::string> Value = ft::splitByCmds(That->_Msg, "\r\n");

    // That->_Msg.clear();
    for (std::vector<std::string>::iterator it = Value.begin();
         it != Value.end(); ++it)
    {
        parseCmd(*it, That);
        // proceeding command here instead of parseCmd
    }
    return 0; // compiler error
}

int Server::parseCmd(std::string &Cmd, User *User)
{
    std::vector<std::string> Value = ft::split(Cmd, " \t\n");


    for (std::vector<std::string>::iterator it = Value.begin(); it != Value.end(); ++it) {
        std::cout << '|' << *it << '|' << '\n';
    }
    // User->_Msg.clear();
    for (std::vector<ACommand *>::iterator it = _Commands.begin(); it != _Commands.end(); ++it) {
        if (Value[0] == (*it)->_Name) {
            (*it)->setTokens(Value);
            (*it)->setUser(User);
            (*it)->run();
            return 0; // reply() <- command successful ?
        }
    }
    std::string arr[] = { Value[0] };
    return reply(ERR_UNKNOWNCOMMAND, User->_Fd, User->getName(), L(arr));
}

std::string Server::recvReader(int Fd)
{
    char Buffer[SIZE];
    ssize_t ReadByte = 0;
    std::string ReturnValue;

    memset(Buffer, 0, SIZE);
    ReadByte = recv(Fd, Buffer, SIZE, 0);
    if (ReadByte < 0)
    {
        ;// Error expt
    }
    ReturnValue += Buffer;
    return (ReturnValue);
}

void Server::sendMsg(User *From, User *To)
{
    std::string ReturnValue;

    ReturnValue += timeStamp() + " " + From->getName() + " " + From->_Msg;
    send(To->_Fd , ReturnValue.c_str(), ReturnValue.size(), 0);
    From->_Msg.clear();
}

void Server::serverLog(User *That)
{
    std::cout << That->getName() << ": "<< That->_Msg << std::endl;
}
