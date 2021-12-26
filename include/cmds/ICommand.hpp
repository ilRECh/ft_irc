#pragma once

#include "default.hpp"
#include "Server.hpp"
#include "User.hpp"

using std::string;
using std::vector;

class ICommand {
private:
    string _Name;
    vector<string> _Tokens;
    User& _User;
    Server& _Server;
public:
    virtual status execute();
};
