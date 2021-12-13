#include "Server.hpp"

//* Domain can be AF_INET
Server::Server(const string & ip_addres, const int port, const int domain){
	if (port < 1024 || port > 49151)
		throw sExcept("wrong port!");
	this->ip_addres = ip_addres;
	this->domain = domain;
	this->port = port;
	cout << "Server will be bound to port: " << port << endl;
}

void    Server::addClient( void ){
	clients.push_back(Client(domain));
}

bool Server::binding() {
	struct sockaddr_in ServerAddr;
	int optValue = 1;

	if (clients.size() == 0)
		throw sExcept("Client list is empty!!");
	fd_servs.push_back(socket(AF_INET, SOCK_STREAM, 0));
	if (fd_servs.end()[-1] < 0) 
		throw sExcept("opening socket");
	if (setsockopt(fd_servs.end()[-1], SOL_SOCKET, SO_REUSEADDR, &optValue, sizeof(int)) == -1)
		throw sExcept("setting socket options");

	bzero((char *) &ServerAddr, sizeof(ServerAddr));
	ServerAddr.sin_family = domain;
	ServerAddr.sin_addr.s_addr = INADDR_ANY;
	ServerAddr.sin_port = htons(port);

	if (bind(fd_servs.end()[-1], (struct sockaddr *) &ServerAddr, sizeof(ServerAddr)) < 0)
		throw sExcept("fatal bind");
	listen(fd_servs.end()[-1], SOMAXCONN);
	fcntl(fd_servs.end()[-1], F_SETFL, O_NONBLOCK);
	return true;
}

Server::~Server( void ){
    vector<int>::iterator i = fd_servs.begin();
    while(i != fd_servs.end()){
        close(*i);
        i++;
    }
}

Server::sExcept::sExcept( const string reason){
	this->reason = reason;
}
const char * Server::sExcept::what( void ) const throw(){
	return (reason.c_str());
}
Server::sExcept::~sExcept( void ){}
