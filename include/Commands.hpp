#pragma once

#include "Mandatory.hpp"

class Server;
class User;

class ACommand {
private:
    ACommand& operator=(ACommand const & that);
    ACommand(ACommand const & that);
    ACommand();
protected:
    ACommand(std::string Name);
public:
    virtual ~ACommand();
private:
    User *_User;
    Server *_Server;
    std::vector<std::string> _Tokens;
public:
    std::string const _Name;
    virtual void run() = 0;
    std::string assembleMsg();
};

class USER : public ACommand {
private:
public:
    USER(): ACommand("USER") {} ;
    virtual void run() {} ; //override
};
//Server || User?
//Nick
//Join
//Privmsg
//-Channel
//-Operators
