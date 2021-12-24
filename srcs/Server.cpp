#include "Server.hpp"

//* Domain can be AF_INET
Server::Server(const std::string &ip_addres, const int port)
: _LoopListen(true)
{
	if (port < 1024 || port > 49151)
		throw ExceptionUni("wrong port!");
	_IpStr = ip_addres;
	_Socklen = sizeof(struct sockaddr_in);
	
	memset(&_Saddr, 0, _Socklen);
	_Saddr.sin_family = AF_INET;
	_Saddr.sin_port = htons(port);
	_Saddr.sin_addr.s_addr = htons(INADDR_ANY);
	std::cout << "Server will be bound to port: " << port << std::endl;

	_Sockfd = socket(AF_INET, SOCK_STREAM/* | SOCK_NONBLOCK*/, 0);
	// _Sockfd = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0);
	int oldFl = fcntl(_Sockfd, F_GETFL, 0);
	if (oldFl < 0 || fcntl(_Sockfd, F_SETFL, oldFl | O_NONBLOCK) < 0)
		throw ExceptionUni("error: fcntl");
	if (_Sockfd < 0)
		throw ExceptionUni("Фатальная ошибка, как жить дальше ?");
	if (bind(_Sockfd, (struct sockaddr *)&_Saddr, _Socklen))
		throw ExceptionUni("Fatality! bind");
	if (listen(_Sockfd, 1))
		throw ExceptionUni("Listen error");
	
	FD_ZERO(&fds);
	maxFd = 0;
}

Server::~Server(void)
{
	std::vector<struct s_account>::iterator i;
	
	_LoopListen = false;
	close(_Sockfd);
	i = _Accounts.begin();
	while (i != _Accounts.end())
		close(i++->_Fd);
	_Accounts.clear();
}

void	Server::readerClient(fd_set fdsCpy){
	std::vector<struct s_account>::iterator iter = _Accounts.begin();

	memset(_Buf, 0, SIZE);
	for(;iter != _Accounts.end(); iter++){
		if (FD_ISSET(iter->_Fd, &fdsCpy) > 1){
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

void	Server::run()
{
	struct s_account account;
	struct timeval tm;
	fd_set	fdsCpy;
	int		retSelect;

	tm.tv_sec = 5;
	tm.tv_usec = 0;
	std::cout << "Waiting first connect..." << std::endl;
	while(_LoopListen){
		memset(&account, 0, sizeof(struct s_account));
		account._Fd = accept(_Sockfd, (struct sockaddr *)&_Saddr, &_Socklen);
		if (account._Fd < 0 && errno != EAGAIN)
			throw ExceptionUni("Fatality! accept " + std::to_string(account._Fd));
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
				throw ExceptionUni("Error: Select");
		}
	}
}
