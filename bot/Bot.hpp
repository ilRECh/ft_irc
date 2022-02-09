#pragma once

#include "ft.hpp"
#include <unistd.h>
#include <cerrno>
#include <cstdlib>
#include <string>
#include <cstring>
#include <iostream>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

class Bot {
private:
    Bot();
    Bot(Bot const &that);
    Bot& operator=(Bot const &that);
    std::string const _Name;
    std::string _PasswordToServer;
    std::string _IncomingBuffer;
    std::string _ReplyMessage;
    int _BotSock;
    enum e_incoming_type {
        PRIVMSG,
        PING,
        AUTH,
        UNPROCEEDING
    } _CurrentIncomingType;
    void Receive();
    void Parse();
    void Proceed();
    void Reply();
public:
    Bot(std::string const &Domain_or_Ip,
        std::string const &Port,
        std::string const &PasswordToServer);
    ~Bot();
    void run();
};
