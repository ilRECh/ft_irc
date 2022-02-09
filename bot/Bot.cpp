#include "Bot.hpp"

#define AUTH_REPLY "PASS " + _PasswordToServer + "\r\n"\
        "NICK " + _Name + "\r\n"\
        "USER * * * :I'm alive! YES, I AM!\r\n"

static void Error(std::string ErrorMsg) {
    std::cout << "Fatal error: " << ErrorMsg << std::endl;
    exit(1); 
}

Bot::Bot(std::string const &Domain_or_Ip,
        std::string const &Port,
        std::string const &PasswordToServer)
    :   _Name("SimpleBot"),
        _PasswordToServer(PasswordToServer),
        _CurrentIncomingType(UNPROCEEDING) {
    if (1024 > std::atoi(Port.c_str()) || std::atoi(Port.c_str()) > 49151) {
        Error("wrong port number. Please, provide a correct one in the range [1024, 49151].");
    }
    hostent *ghbn = NULL;
    if ((ghbn = gethostbyname(Domain_or_Ip.c_str())) == NULL) {
        Error("resolving to resolve the hostname.");
    }
    sockaddr_in Address = {0, 0, {0}, {0}};
    Address.sin_family = AF_INET;
    Address.sin_port = htons(std::atoi(Port.c_str()));
	if (inet_aton(ghbn->h_name, &Address.sin_addr) == 0) {
		Error("Incorrect domain or IP address has been passed.");
	}
	if ((_BotSock = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		Error("cannot get a socket.");
	}
	if (connect(_BotSock, (sockaddr*)&Address, sizeof(Address)) == -1) {
        std::cout << errno << " ";
		Error(std::string("Cannot connect to Server. Please, try again. ") + strerror(errno));
	}
}

Bot::~Bot() {
    std::cout << "Goodbye! Thank you for using our services!" << std::endl;
    close(_BotSock);
}

void Bot::run() {
    _ReplyMessage = AUTH_REPLY;
    while (true) {
        Reply();
        Receive();
        Parse();
        Proceed();
    }
}

void Bot::Receive() {
    ssize_t BytesReceived;
    char Buffer[1001] = {0};
    if ((BytesReceived = recv(_BotSock, Buffer, sizeof(Buffer) - 1, 0)) > 0) {
        _IncomingBuffer += Buffer;
        std::cout << "Received: |" << _IncomingBuffer << "|" << std::endl;
    } else {
        throw("goodbye");
    }
}

void Bot::Parse() {
    if (_IncomingBuffer.end()[-1] not_eq '\n') {
        return ;
    }
    if (_IncomingBuffer.find(" PRIVMSG ") not_eq _IncomingBuffer.npos or
        _IncomingBuffer.find(" NOTICE ") not_eq _IncomingBuffer.npos) {
        _CurrentIncomingType = PRIVMSG;
    } else if (_IncomingBuffer.find (" PING ") not_eq _IncomingBuffer.npos) {
        _CurrentIncomingType = PING;
    } else if (_IncomingBuffer.find("You have not registered") not_eq _IncomingBuffer.npos) {
        _CurrentIncomingType = AUTH;
    } else if (_IncomingBuffer.find("KILL") not_eq _IncomingBuffer.npos) {
        std::cout << "Oops! My friend is here already, I'll be gone then!" << std::endl;
        throw("goodbye");
    } else {
        _CurrentIncomingType = UNPROCEEDING;
    }
}

void Bot::Proceed() {
    switch(_CurrentIncomingType) {
        case PRIVMSG:
            
            break ;
        case PING:
            size_t PongArgPos = _IncomingBuffer.find_first_not_of(" \n\r\t\v", _IncomingBuffer.find("PING") + 4);
            if (PongArgPos != _IncomingBuffer.npos) {
                _ReplyMessage = _IncomingBuffer.substr(PongArgPos);
            }
            _ReplyMessage = "PONG " + _ReplyMessage;
            break ;
        case AUTH:
            static int AttemptsLeft = 3;
            if (AttemptsLeft < 0) {
                std::cout << "Well, not this time, I guess. See ya around!" << std::endl;
                throw("goodbye");
            }
            std::cout << "I think you have provided wrong password. Let's try this again:" << std::endl;
            std::cin >> _PasswordToServer;
            std::cout << "You have entered:|" << _PasswordToServer << "|" << std::endl;
            _ReplyMessage = AUTH_REPLY;
            break ;
        default:
            break ;
    }
    _IncomingBuffer.clear();
}

void Bot::Reply() {
    if (not _ReplyMessage.empty()) {
        send(_BotSock, _ReplyMessage.c_str(), _ReplyMessage.length(), MSG_NOSIGNAL);
        _ReplyMessage.clear();
    }
}
