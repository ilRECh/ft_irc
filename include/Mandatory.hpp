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
#include <cstdlib>

#define SIZE 256

#define HOST_PORTNETWORK_PASSWORDNETWORK_PORT_PASSWORD 4
#define PORT_PASSWORD 3
#define PASSWORD_NETWORK 2
#define PORT_NETWORK 1
#define HOST 0

typedef int status;

namespace damn_basic_stuff
{
    std::vector<std::string> split(std::string const& tosplit, std::string const& delimiters);
    std::string to_string(int num);
} // namespace damn_basic_stuff

status reply(
    int const Rplcode,
    int const UserSocketFd,
    std::string const & From,
    std::string const & To,
    std::vector<std::string> const & MsgTokens =
        std::vector<std::string>());
