#include "Client.hpp"

Client::Client(const int domain/*, const int port, const char * ip_addr*/){
	fd_sock = socket(domain, SOCK_STREAM, 0);
	if (fd_sock < 0)
		throw ClientException("socket can't create a file descriptor");
    count_share = new int;
    if (count_share == nullptr)
        throw ClientException("no memory left space for 4 bytes");
    *count_share = 0;
}

Client::Client(const Client & oth){
    this->socket_address = oth.socket_address;
    this->count_share = oth.count_share;
    this->fd_sock = oth.fd_sock;
    this->port = oth.port;
    count_share[0]++;
}

Client::~Client( void ){
    if ((*count_share) > 0)
        (*count_share)--;
    else{
        delete count_share;
        close(fd_sock);
    }
}

int Client::getFD( void ) const {return fd_sock;}
Account Client::getAccount( void ) const {return *this;}

//* Exceptions
Client::ClientException::ClientException(const string reason){
	this->reason = "ERROR: client: " + reason;
}
const char * Client::ClientException::what(void) const throw(){
	return reason.c_str();
}

Client::ClientException::~ClientException(){}
