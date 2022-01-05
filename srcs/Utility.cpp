#include "Mandatory.hpp"

std::vector<std::string> damn_basic_stuff::split(std::string const& tosplit, std::string const& delimiters) {
    std::vector<std::string> ret;
    char *str = new char[tosplit.size() + 1];
    char *tmp = NULL;

    str[tosplit.size()] = '\0';
    std::memmove(str, tosplit.c_str(), tosplit.size());
    tmp = std::strtok(str, delimiters.c_str());
    while (tmp != NULL) {
        ret.push_back(tmp);
        tmp = std::strtok(NULL, delimiters.c_str());
    }
    delete [] str;
    return ret;
}
