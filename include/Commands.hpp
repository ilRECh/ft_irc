#pragma once

#include "Mandatory.hpp"
#include "Server.hpp"
#include "Replies.hpp"

class Server;
class User;

class ACommand {
private:
    ACommand& operator=(ACommand const & that);
    ACommand(ACommand const & that);
    ACommand();
protected:
    ACommand(std::string Name, Server const *Server);
    User *_User;
    std::string _Argument;
public:
    virtual ~ACommand();
    std::string const _Name;
    Server const *_Server;
    // void setTokens(std::vector<std::string> const & Tokens);
    void setArgument(std::string const & Argument);
    void setUser(User *_User);
    virtual int run() = 0;
};

class PASS : public ACommand {
private:
    PASS();
    PASS(PASS const &that);
    PASS& operator=(PASS const &that);
public:
    PASS(Server const *Server);
    virtual ~PASS();
    virtual int run(); //override
};
