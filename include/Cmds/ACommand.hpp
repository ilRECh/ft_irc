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
        std::string Name,
        Server const *Server)
        :   _User(NULL),
            _Name(Name),
            _Server(Server) {}
    User *_User;
    std::string _Argument;
public:
    virtual ~ACommand() {} 
    std::string const _Name;
    Server const *_Server;
    void setArgument(std::string const & Argument) {
            _Argument = Argument;
        }
    void setUser(User *User) {
            _User = User;
        }
    virtual int run() = 0;
};
