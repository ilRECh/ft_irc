#include "Bot.hpp"

#define AUTH_REPLY "PASS " + _PasswordToServer + "\r\n"\
        "NICK " + _Name + "\r\n"\
        "USER * * * :I'm alive! YES, I AM!\r\n"

static void Error(std::string ErrorMsg) {
    std::cout << "Fatal error: " << ErrorMsg << std::endl;
    exit(1); 
}

static std::string HelloMessages[] = {
    "Hey",
    "Hello",
    "Hi",
    "Privet",
};

static std::string GoodbyeMessages[] = {
    "Goodbye",
    "See you",
    "See ya",
    "Bye",
    "Poka",
};

bool Bot::find(std::string *arr, int size, std::string const &ToFind) {
    for (int i = 0; i < size; ++i) {
        if (ToFind.find(arr[i]) != ToFind.npos) {
            return true;
        }
    }
    return false;
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
    if (_IncomingBuffer.find_first_not_of(" \n\t\v") == _IncomingBuffer.npos) {
        _IncomingBuffer.clear();
        return ;
    }
    if (_IncomingBuffer.end()[-1] not_eq '\n') {
        return ;
    } else {
        _IncomingBuffer.erase(_IncomingBuffer.end()-1);
        if (_IncomingBuffer.end()[-1] == '\r') {
            _IncomingBuffer.erase(_IncomingBuffer.end()-1);
        }
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
    } else if (_IncomingBuffer.find(" INVITE ") not_eq _IncomingBuffer.npos) {
        _CurrentIncomingType = INVITE;
    } else {
        _CurrentIncomingType = UNPROCEEDING;
    }
}

void Bot::Proceed() {
    switch(_CurrentIncomingType) {
        case PRIVMSG: {
            static bool isGoodBye = false;
            size_t MessagePos = _IncomingBuffer.rfind(':');
            std::string MessageGet;
            if (MessagePos != _IncomingBuffer.npos and
                MessagePos != _IncomingBuffer.length() - 1) {
                MessageGet = _IncomingBuffer.substr(MessagePos + 1);
            }
            if (Bot::find(HelloMessages, 4, MessageGet) and
                MessageGet.find(_Name) not_eq MessageGet.npos) {
                std::srand(std::time(NULL));
                updateReplyMessage(" :" + HelloMessages[std::rand() % 4] + "!");
            } else if (Bot::find(GoodbyeMessages, 5, MessageGet) and
                MessageGet.find(_Name) not_eq MessageGet.npos) {
                std::srand(std::time(NULL));
                updateReplyMessage(" :" + GoodbyeMessages[std::rand() % 5] + "!");
                isGoodBye = true;
            } else {
                updateReplyMessage(" : Wanna play a game?");
            }
            size_t FirstSpacePos = _IncomingBuffer.find(' ');
            std::string WhoSent;
            if (FirstSpacePos != _IncomingBuffer.npos) {
                WhoSent = _IncomingBuffer.substr(1, FirstSpacePos);
                if (WhoSent.find('!') != WhoSent.npos) {
                    WhoSent = WhoSent.substr(0, WhoSent.find('!'));
                } else {
                    WhoSent = "irc.WIP.ru";
                }
            } else {
                WhoSent = "irc.WIP.ru";
            }
            std::string Where;
            size_t LastSemiCol = _IncomingBuffer.rfind(':');
            if (LastSemiCol != _IncomingBuffer.npos and
                _IncomingBuffer.substr(0, LastSemiCol).find(_Name) == _IncomingBuffer.npos) {
                size_t Sharp = _IncomingBuffer.find('#');
                if (Sharp != _IncomingBuffer.npos) {
                    size_t SymbolAfterChannelName = _IncomingBuffer.find(' ', Sharp);
                    Where = _IncomingBuffer.substr(Sharp, SymbolAfterChannelName - Sharp);
                }
            }
            _ReplyMessage = "NOTICE " + (Where.empty() ? WhoSent : Where) + _ReplyMessage;
            if (isGoodBye) {
                if (not _CurrentChannel.empty()) {
                    updateReplyMessage("PART " + _CurrentChannel);
                }
                updateReplyMessage("QUIT :So long, pal!");
            }
        } break ;
        case PING: {
            size_t PongArgPos = _IncomingBuffer.find_first_not_of(" \n\r\t\v", _IncomingBuffer.find("PING") + 4);
            if (PongArgPos != _IncomingBuffer.npos) {
                updateReplyMessage(_IncomingBuffer.substr(PongArgPos));
            }
            _ReplyMessage = "PONG " + _ReplyMessage;
        } break ;
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
        case INVITE: {
            size_t ChannelNameStart = _IncomingBuffer.rfind(':');
            if (not _CurrentChannel.empty()) {
                updateReplyMessage("PART " + _CurrentChannel);
            }
            if (ChannelNameStart != _IncomingBuffer.npos and
                ChannelNameStart != _IncomingBuffer.length() - 1) {
                std::string JoinTo = _IncomingBuffer.substr(ChannelNameStart + 1);
                _CurrentChannel = JoinTo;
                updateReplyMessage("JOIN " + JoinTo);
            }
        } break ;
        default:
            break ;
    }
    _IncomingBuffer.clear();
    sleep(2);
}

void Bot::Reply() {
    if (not _ReplyMessage.empty()) {
        std::cout << "+=======================out=========================+" << std::endl;
        std::cout << _ReplyMessage;
        std::cout << "+===================================================+" << std::endl;
        send(_BotSock, _ReplyMessage.c_str(), _ReplyMessage.length(), MSG_NOSIGNAL);
        _ReplyMessage.clear();
    }
}

void Bot::updateReplyMessage(std::string const &Rpl) {
    _ReplyMessage += Rpl + "\r\n";
}
