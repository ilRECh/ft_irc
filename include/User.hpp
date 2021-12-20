#pragma once

#include "Server.hpp"

class User {
private:
    std::string _Name;
public:
    User();
    User(User& that);
    ~User();
    User& operator=(User& that);
};
