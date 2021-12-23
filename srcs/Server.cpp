#include "Server.hpp"

//* Domain can be AF_INET
Server::Server(const std::string &ip_addres, const int port)
: _LoopListen(true)
{
	if (port < 1024 || port > 49151)
		throw sExcept("wrong port!");
	//this->port = port;
	_IpStr = ip_addres;
	_Socklen = sizeof(struct sockaddr_in);
	
	memset(&_Saddr, 0, _Socklen);
	_Saddr.sin_family = AF_INET;
	_Saddr.sin_port = htons(port);
	_Saddr.sin_addr.s_addr = htons(INADDR_ANY);
	std::cout << "Server will be bound to port: " << port << std::endl;

	_Sockfd = socket(AF_INET, SOCK_STREAM/* | SOCK_NONBLOCK*/, 0);
	if (_Sockfd < 0)
		throw Server::sExcept("Фатальная ошибка, как жить дальше ?");
	if (bind(_Sockfd, (struct sockaddr *)&_Saddr, _Socklen))
		throw Server::sExcept("Fatality! bind");
	if (listen(_Sockfd, 1))
		throw Server::sExcept("Listen error");
}

Server::~Server(void)
{
	std::vector<struct s_account>::iterator i;
	
	_LoopListen = false;
	close(_Sockfd);
    i = _Accounts.begin();
	while (i != _Accounts.end())
		close((i++)->_Fd);
	_Accounts.clear();
}


void Server::run()
{
	struct s_account account;

	std::cout << "Waiting first connect..." << std::endl;
	while(_LoopListen){
		memset(&account, 0, sizeof(struct s_account));
		account._Fd = accept(_Sockfd, (struct sockaddr *)&_Saddr, &_Socklen);
		if (account._Fd < 0)
			throw Server::sExcept("Fatality! accept " + std::to_string(account._Fd));
		send(account._Fd, "=> Server connected!\n", 22, 0);
		memset(_Buf, 0, SIZE);
		recv(account._Fd, _Buf, SIZE, 0);
		std::cout << "mgs from client: " << _Buf << std::endl;
		_Accounts.push_back(account);
	}
}

//* Exception
Server::sExcept::sExcept(const std::string reason)
{
	this->reason = reason;
}
const char *Server::sExcept::what(void) const throw()
{
	return (reason.c_str());
}
Server::sExcept::~sExcept(void) throw() {}
