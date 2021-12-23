#pragma once

#include "Server.hpp"
#include "Password.hpp"

class User: public Password {
private:
    std::string _Name;
public:
    User();
    User(User& that);
    ~User();
    User& operator=(User& that);
};
