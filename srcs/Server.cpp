#include "Server.hpp"



//* Domain can be AF_INET
Server::Server(const string & ip_addres, const int port, const int domain)
:loop_listen(false), thread_listener(&Server::listener, this){
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

	//loop_listen = false;
	thread_listener.join();
    while(i != _accounts.end())
        close((i++)->_fd);
	_accounts.clear();
}

void	Server::listener(Server * s){
	//struct timeval	tm;
	t_account	account;
	int			sockfd;

	while(!s->loop_listen)
		usleep(25000);
	while(s->loop_listen)
	{
		memset(&account, 0, sizeof(t_account));
		sockfd = socket(AF_INET, SOCK_STREAM, 0);
		fcntl(sockfd, F_SETFL, fcntl(sockfd, F_GETFL, 0), O_NONBLOCK);
		if (sockfd < 0)
			throw Server::sExcept("Фатальная ошибка, как жить дальше ?");
	//cout << "bind" << endl;
		if (bind(sockfd, reinterpret_cast<struct sockaddr*>(&s->_server_addres), s->socklen))
			throw Server::sExcept("Fatality! bind");
	//cout << "listen" << endl;
		if (listen(sockfd, 1))
			throw Server::sExcept("Listen error");
	//cout << "fcntl" << endl;

	//cout << "accept" << endl;
		account._fd = accept(sockfd, reinterpret_cast<struct sockaddr*>(&s->_server_addres), &s->socklen);
		if (close(sockfd))
			throw Server::sExcept("What the f....");
		//if (account._fd == EAGAIN)
			//return false;
		if (account._fd < 0)
			throw Server::sExcept("Fatality! accept " + std::to_string(account._fd));
	//cout << "fcntl2" << endl;
		fcntl(account._fd, F_SETFL, fcntl(account._fd, F_GETFL, 0) | O_NONBLOCK);
	//cout << "send" << endl;
		send(account._fd, "=> Server connected!\n", 22, 0);
		s->mutex_vector.lock();
		s->_accounts.push_back(account);
		s->mutex_vector.unlock();
		//return true;
	}
}


void	Server::run(){
	cout << "Waiting first connect..." << endl;
	loop_listen = true;

	while(true)
	{
		usleep(5000);
		mutex_vector.lock();
		if (_accounts.size()){
			mutex_vector.unlock();
			send(_accounts[0]._fd, "Hello world", 12, 0);
			break ;
		}
		mutex_vector.unlock();
	}
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
