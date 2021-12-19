#include "Server.hpp"

//* Domain can be AF_INET
Server::Server(const string &ip_addres, const int port)
: loop_listen(true)
{
	if (port < 1024 || port > 49151)
		throw sExcept("wrong port!");
	//this->port = port;
	ip_str = ip_addres;
	socklen = sizeof(struct sockaddr_in);
	
	memset(&saddr, 0, socklen);
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(port);
	saddr.sin_addr.s_addr = htons(INADDR_ANY);
	cout << "Server will be bound to port: " << port << endl;

	sockfd = socket(AF_INET, SOCK_STREAM/* | SOCK_NONBLOCK*/, 0);
	if (sockfd < 0)
		throw Server::sExcept("Фатальная ошибка, как жить дальше ?");
	if (bind(sockfd, (struct sockaddr *)&saddr, socklen))
		throw Server::sExcept("Fatality! bind");
	if (listen(sockfd, 1))
		throw Server::sExcept("Listen error");
}

Server::~Server(void)
{
	//vector<t_account>::iterator i;
	
	loop_listen = false;
	thread_listener.join();
	//if (close(sockfd))
	//	throw Server::sExcept("What the f....");
	//i = accounts.begin();
	//while (i != accounts.end())
	//	if (close((i++)->_fd))
	//		throw Server::sExcept("What the f.... N2");
	accounts.clear();
}


void Server::run()
{
	t_account account;

	cout << "Waiting first connect..." << endl;
	while(loop_listen){
		memset(&account, 0, sizeof(t_account));
		account._fd = accept(sockfd, (struct sockaddr *)&saddr, &socklen);
		if (account._fd < 0)
			throw Server::sExcept("Fatality! accept " + std::to_string(account._fd));
		send(account._fd, "=> Server connected!\n", 22, 0);
		memset(buf, 0, SIZE);
		recv(account._fd, buf, SIZE, 0);
		cout << "mgs from client: " << buf << endl;
		mutex_vector.lock();
		accounts.push_back(account);
		mutex_vector.unlock();
	}
}

//* Exception
Server::sExcept::sExcept(const string reason)
{
	this->reason = reason;
}
const char *Server::sExcept::what(void) const throw()
{
	return (reason.c_str());
}
Server::sExcept::~sExcept(void) throw() {}
