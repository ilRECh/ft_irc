#pragma once

#include "Defines.hpp"
#include "Server.hpp"

class ICommand {
private:
    std::string _Name;
    std::vector<std::string> _Tokens;
    User& _User;
    Server& _Server;
public:
    virtual status execute();
};
