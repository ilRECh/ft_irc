#pragma once

#include <iostream>
#include <vector>
#include <fcntl.h>
#include <string>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <algorithm>
#include <cerrno>
#include <random>

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
} // namespace damn_basic_stuff

