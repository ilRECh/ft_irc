#pragma once
#include <string>
#include <string.h>
#include <unistd.h>

#include <netdb.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "Account.hpp"

using   std::string;
class   Client:public Account{
private:
    Account operator=(Account);
    struct  sockaddr_in socket_address;
    int     *count_share;
    int     fd_sock;
    int     port;
public:
    Client(int domain/*, int port, const char * ip_addr*/);
    Client(const Client & oth);
    virtual ~Client( void );
    int     getFD( void ) const;
    Account getAccount( void ) const;
    class ClientException: public std::exception
    {
        string  reason;
    public:
        ClientException(const string reason);
        virtual ~ClientException();
        const char * what( void ) const throw();
    };    
};