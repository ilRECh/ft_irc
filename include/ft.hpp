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
#include "TimeStamp.hpp"

#define SIZE 512

namespace ft {
    std::vector<std::string> split(
        std::string const& tosplit,
        std::string const& delimiters);
    std::vector<std::string> splitByCmds(
        std::string const& tosplit,
        std::string const& DelimiterWord);
    void deleteSpaces(std::string &string);
    std::string SplitOneTimes(std:: string &str, std::string delimiter);

    template <typename T>
    std::string to_string(T to_convert) {
        std::stringstream ss;
        ss << to_convert;
        return ss.str();
    }
	bool	wildcard(std::string wildcardExpression, std::string beingToCompare);
} // namespace ft
