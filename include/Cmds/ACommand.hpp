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
            _Server(Server),
            _Name(Name) {}
    User *_Initiator;
    std::vector<std::string> _Arguments;
    std::string _Argument;
    Server & _Server;
    void setArguments(std::string const & Argument) {
        _Arguments = ft::split(Argument, " \b\t\n\v\f\r");
    }
public:
    std::string const _Name;
    virtual ~ACommand() {}
    void setArgument(std::string const & Argument) {
        _Argument = Argument;
        setArguments(Argument);
    }
    bool setInitiator(User *User) {
        _Initiator = User;
        return true;
    }
    virtual int run() = 0;
};
