#pragma once

#include "default.hpp"

class Director {
private:

public:
    Director();
    ~Director();
    Director(Director& that);
    Director& operator=(Director& that);
    direct(Command *command, User *user);
}
