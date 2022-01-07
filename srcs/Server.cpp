#include "Server.hpp"

Server::Server(std::vector<std::string>& argv)
    :   ip(0),
        port(0),
        _LoopListen(true) {
    std::vector<std::string>::reverse_iterator r_it = argv.rbegin();
	_Password = *r_it--;
	_Port = *r_it--;
	if (1024 > std::atoi(_Port.c_str()) || std::atoi(_Port.c_str()) > 65535) {
		throw std::runtime_error("Port is out of range");
	}
	if (r_it != argv.rend()) {
		std::vector<std::string> ExistingNetwork = damn_basic_stuff::split(*r_it--, ":");
		_Host = ExistingNetwork[HOST];
		_PortNetwork = ExistingNetwork[PORT_NETWORK];
		if (1024 > std::atoi(_PortNetwork.c_str()) || std::atoi(_PortNetwork.c_str()) > 65535) {
			throw std::runtime_error("Port is out of range");
		}
		_PasswordNetwork = ExistingNetwork[PASSWORD_NETWORK];
	}
}

//* Domain can be AF_INET
Server::Server(string const & ip, string const & port)
    :    ip(ip),
        port(port),
        _LoopListen(true) {
    struct addrinfo hints;

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;


    if (getaddrinfo(ip.c_str(), port.c_str(), &hints, &servinfo))
        throw std::runtime_error(string("getaddrinfo error: ") + gai_strerror(errno));
    if (1024 > std::atoi(port.c_str()) || std::atoi(port.c_str()) > 49151)
        throw std::runtime_error("wrong port!");


    std::cout << "Server will be bound to port: " << port << std::endl;
    _Sockfd = socket(AF_INET, SOCK_STREAM/* | SOCK_NONBLOCK*/, 0);
    if (_Sockfd < 0)
        throw std::runtime_error("Fatal. What to do now ?");
    int    retFcntl = fcntl(_Sockfd, F_GETFL, 0);
    if (retFcntl < 0 || fcntl(_Sockfd, F_SETFL, retFcntl | O_NONBLOCK) < 0)
        throw std::runtime_error("error: fcntl");
    _Socklen = sizeof(struct sockaddr);
    if (bind(_Sockfd, servinfo->ai_addr, _Socklen))
        throw std::runtime_error("Fatality! bind");
    if (listen(_Sockfd, 1))
        throw std::runtime_error("Listen error");
    FD_ZERO(&fds);
    maxFd = 0;
}

Server::~Server(void)
{
    vector<struct s_account>::iterator i;
    
    _LoopListen = false;
    freeaddrinfo(servinfo);
    close(_Sockfd);
    i = _Accounts.begin();
    while (i != _Accounts.end())
        close(i++->_Fd);
    _Accounts.clear();
}

void    Server::readerClient(fd_set fdsCpy){
    vector<struct s_account>::iterator iter = _Accounts.begin();

    memset(_Buf, 0, SIZE);
    for(;iter != _Accounts.end(); iter++){
        if (FD_ISSET(iter->_Fd, &fdsCpy) > 0){
            recv(iter->_Fd, _Buf, SIZE, 0);
            std::cout << "iter: " << iter->_Fd << " _ ";
            std::cout << iter->_Name << ": ";
            std::cout << _Buf << std::endl;
            if (strchr(_Buf, '#'))
                _LoopListen = false;
            memset(_Buf, 0, SIZE);
        }
    }
}

void    Server::run() {
    struct s_account account;
    struct timeval tm;
    fd_set    fdsCpy;
    int        retSelect;

    tm.tv_sec = 5;
    tm.tv_usec = 0;
    std::cout << "Waiting first connect..." << std::endl;
    while(_LoopListen){
        memset(&account, 0, sizeof(struct s_account));
        account._Fd = accept(_Sockfd, servinfo->ai_addr, &_Socklen);
        if (account._Fd < 0 && errno != EAGAIN)
            throw std::runtime_error("Fatality! accept " + 4);//std::to_string(account._Fd));
        if (account._Fd > 0){
            if (account._Fd > maxFd) maxFd = account._Fd;
            fcntl(account._Fd, F_SETFD, fcntl(account._Fd, F_GETFD) | O_NONBLOCK);
            FD_SET(account._Fd, &fds);
            send(account._Fd, "=> Server connected!\n", 22, 0);

            //* Выяняем кто подключился
            account._Socklen = sizeof(account._SaddrClient);
            getpeername(account._Fd, (struct sockaddr *)&account._SaddrClient, &account._Socklen);
            std::cout << "<<<<<<<" << inet_ntoa(account._SaddrClient.sin_addr) << std::endl;

            _Accounts.push_back(account);
        }
        retSelect = 1;
        while(retSelect && maxFd){
            fdsCpy = fds;
            retSelect = select(maxFd + 1, &fdsCpy, NULL, NULL, &tm);
            if (retSelect > 0)
                readerClient(fdsCpy);
            else if (retSelect < 0)
                throw std::runtime_error("Error: Select");
        }
    }
}
