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

#define SIZE 256
#define HOST_PORTNETWORK_PASSWORDNETWORK_PORT_PASSWORD 4
#define PORT_PASSWORD 3
#define PASSWORD_NETWORK 2
#define PORT_NETWORK 1
#define HOST 0

#define L(x) std::vector<std::string>(x, x + (sizeof(x) / sizeof(std::string)))

typedef int status;

namespace ft {
    std::vector<std::string> split(
        std::string const& tosplit,
        std::string const& delimiters);
    std::vector<std::string> splitByCmds(
        std::string const& tosplit,
        std::string const& DelimiterWord);
    
    template <typename T>
    std::string to_string(T to_convert) {
        std::stringstream ss;
        ss << to_convert;
        return ss.str();
    }
} // namespace ft

status reply(
    int const Rplcode,
    int const UserSocketFd,
    std::string const & To,
    std::vector<std::string> const & MsgTokens = std::vector<std::string>(),
    std::string const & From = "Server");

status reply(
    int const UserSocketFd,
    std::string const & To,
    std::vector<std::string> const & MsgTokens = std::vector<std::string>(),
    std::string const & From = "Server");
