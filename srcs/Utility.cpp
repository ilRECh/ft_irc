#include "Mandatory.hpp"

std::vector<std::string> ft::split(
        std::string const& tosplit,
        std::string const& delimiters) {
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

std::vector<std::string> ft::splitByCmds(
        std::string const& tosplit,
        std::string const& DelimiterWord) {
    std::vector<std::string> ret;
    size_t pos_start = 0;
    size_t pos_end = tosplit.find(DelimiterWord, pos_start);

    while (true) {
        if (pos_end != tosplit.npos) {
            ret.push_back(tosplit.substr(pos_start, pos_end - pos_start));
        } else {
            if (tosplit[pos_start]) {
                ret.push_back(tosplit.substr(pos_start, tosplit.length() - pos_start));
            }
            break ;
        }
        pos_start = pos_end + DelimiterWord.length();
        pos_end = tosplit.find(DelimiterWord, pos_start);
    }
    return ret;
}

std::string ft::assemble(
        std::vector<std::string>::iterator Start,
        std::vector<std::string>::iterator Stop) {
    std::string Result;
    while (Start != Stop) {
        Result += *Start++;
    }
    return Result;
}
