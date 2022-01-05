#pragma once
#include "Mandatory.hpp"
#include "Server.hpp"
#include "User.hpp"

class ACommand {
private:
    ACommand& operator=(ACommand& that);
    ACommand(ACommand& that);
    ACommand();
protected:
    ACommand(std::string Name);
    virtual ~ACommand();

private:
    User *_User;
    Server *_Server;
    std::vector<std::string> _Tokens;

public:
    const std::string _Name;
    virtual void run() = 0;
    std::string assembleMsg();
};
