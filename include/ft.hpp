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
#include <list>
#include <map>
#include <limits>
#include "TimeStamp.hpp"

#define SERVER_NAME "irc.WIP.ru"
#define SIZE 512

namespace ft {
    std::vector<std::string> split(
        std::string const& tosplit,
        std::string const& delimiters);
    void deleteSpaces(std::string &string, std::string const &symbols = std::string(" "));
    std::string SplitOneTimes(std:: string &str, std::string delimiter);
	bool wildcard(std::string wildcardExpression, std::string beingToCompare);
    std::string tolowerString(std::string toLowStr);
    template <typename T>
    std::string to_string(T to_convert) {
        std::stringstream ss;
        ss << to_convert;
        return ss.str();
    }
} // namespace ft
