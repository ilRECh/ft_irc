#pragma once

#include <iostream>
#include <vector>
#include <fcntl.h>
#include <string>
#include <sstream>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <algorithm>
#include <cerrno>
#include <sys/select.h>
#include <sys/time.h>
#include <netdb.h>
#include <ctime>
#include <set>
#include "TimeStamp.hpp"

#define SIZE 256
#define HOST_PORTNETWORK_PASSWORDNETWORK_PORT_PASSWORD 4
#define PORT_PASSWORD 3
#define PASSWORD_NETWORK 2
#define PORT_NETWORK 1
#define HOST 0

typedef int status;

namespace ft {
    std::vector<std::string> split(
        std::string const& tosplit,
        std::string const& delimiters);
    std::vector<std::string> splitByCmds(
        std::string const& tosplit,
        std::string const& DelimiterWord);
    std::string assemble(
        std::vector<std::string>::iterator Start,
        std::vector<std::string>::iterator Stop);
    void deleteSpaces(std::string &string);
    std::string SplitOneTimes(std:: string &str, std::string delimiter);


    template <typename T>
    std::string to_string(T to_convert) {
        std::stringstream ss;
        ss << to_convert;
        return ss.str();
    }
} // namespace ft
