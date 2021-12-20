#pragma once

#include "default.hpp"
#include "Server.hpp"
#include "User.hpp"

class ICommand {
private:
    std::string _Name;
    std::vector<std::string> _Tokens;
    User& _User;
    Server& _Server;
public:
    virtual status execute();
};
