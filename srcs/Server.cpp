#include "Server.hpp"



//* Domain can be AF_INET
Server::Server(const string & ip_addres, const int port, const int domain){
	if (port < 1024 || port > 49151)
		throw sExcept("wrong port!");

	memset(&_server_addres, 0, sizeof(struct sockaddr_in));
	_server_addres.sin_port = htons(port);
	_server_addres.sin_family = domain;
	_server_addres.sin_addr.s_addr = htons(INADDR_ANY);

	_ip_addres = ip_addres;
	socklen = sizeof(_server_addres);
	cout << "Server will be bound to port: " << port << endl;
}


Server::~Server( void ){
    vector<t_account>::iterator i = _accounts.begin();
    while(i != _accounts.end())
        close((i++)->_fd);
}

bool	Server::create_connect_to_client(){
	t_account	account;
	int			sockfd;
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
		throw sExcept("Фатальная ошибка, как жить дальше ?");
cout << "bind" << endl;
	if (bind(sockfd, reinterpret_cast<struct sockaddr*>(&_server_addres), socklen))
		throw sExcept("Fatality! bind");
cout << "listen" << endl;
	if (listen(sockfd, 1))
		throw sExcept("Listen error");
cout << "fcntl" << endl;

	fcntl(sockfd, F_SETFL, fcntl(sockfd, F_GETFL, 0) | O_NONBLOCK);
cout << "accept" << endl;
account._fd = accept(sockfd, reinterpret_cast<struct sockaddr*>(&_server_addres), &socklen);
	if (close(sockfd))
		throw sExcept("What the f....");
	if (account._fd == EAGAIN)
		return false;
	if (account._fd < 0)
		throw sExcept("Fatality! accept " + std::to_string(account._fd));
cout << "fcntl2" << endl;
	fcntl(account._fd, F_SETFL, fcntl(account._fd, F_GETFL, 0) | O_NONBLOCK);
cout << "send" << endl;
	send(account._fd, "=> Server connected!\n", 22, 0);
	_accounts.push_back(account);
	return true;
}

void	Server::run(){
	bool	fccheck;

	cout << "Waiting first connect..." << endl;
	do fccheck = create_connect_to_client(); while(!fccheck);
	cout << "First connect was connected!" << endl;
	//while(true){
	//}
}

//* Exception
Server::sExcept::sExcept( const string reason){
	this->reason = reason;
}
const char * Server::sExcept::what( void ) const throw(){
	return (reason.c_str());
}
Server::sExcept::~sExcept( void ) throw(){}
