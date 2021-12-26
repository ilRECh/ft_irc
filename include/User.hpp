#pragma once

#include "Server.hpp"
#include "Password.hpp"

using std::string;

class User: public Password {
private:
    string _Name;
public:
    User(string const & name);
    User(User& that);
    ~User();
    void setName(string const & name);
    User& operator=(User& that);
    bool operator==(const User& that) const;
    bool operator!=(const User& that) const;
};
