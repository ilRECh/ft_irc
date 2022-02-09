#include "Bot.hpp"

#define AUTH_REPLY(passwd) "PASS " + _PasswordToServer + "\r\n"\
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
    _ReplyMessage = AUTH_REPLY(_PasswordToServer);
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
    if (_IncomingBuffer.end()[-1] != '\n') {
        return ;
    }
    if (_IncomingBuffer.find(" PRIVMSG ") != _IncomingBuffer.npos or
        _IncomingBuffer.find(" NOTICE ") != _IncomingBuffer.npos) {
        _CurrentIncomingType = PRIVMSG;
    } else if (_IncomingBuffer.find (" PING ") != _IncomingBuffer.npos) {
        _CurrentIncomingType = PING;
    } else if (_IncomingBuffer.find("You have not registered") != _IncomingBuffer.npos) {
        _CurrentIncomingType = AUTH;
    } else {
        _CurrentIncomingType = UNPROCEEDING;
    }
}

void Bot::Proceed() {
    switch(_CurrentIncomingType) {
        case PRIVMSG:
            break ;
        case PING:
            break ;
        case AUTH:
            static int AttemptsLeft = 3;
            std::cout << "I think you have provided wrong password. Let's try this again:\n";
            break ;
        default:
            break ;
    }
}

void Bot::Reply() {
    send(_BotSock, _ReplyMessage.c_str(), _ReplyMessage.length(), 0);
}
