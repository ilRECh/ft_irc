#pragma once

#include "ft.hpp"
#include "Server.hpp"
#include "User.hpp"
#include "Replies.hpp"

class Server;
class User;

class ACommand {
private:
    ACommand& operator=(ACommand const & that);
    ACommand(ACommand const & that);
    ACommand();
protected:
    ACommand(
        std::string const Name,
        Server & Server)
        :   _Initiator(NULL),
            _Name(Name),
            _Server(Server) {}
    User *_Initiator;
    std::string _Argument;
    Server & _Server;
public:
    std::string const & _Name;
    virtual ~ACommand() {} 
    void setArgument(std::string const & Argument) {
        _Argument = Argument;
    }
    bool setInitiator(User *User) {
        _Initiator = User;
        return true;
    }
    virtual int run() = 0;
};
