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

void ft::deleteSpaces(std::string &string)
{
    size_t strBegin = string.find_first_not_of(' ');
    size_t strEnd = string.find_last_not_of(' ');
    string.erase(strEnd+1, string.size() - strEnd);
    string.erase(0, strBegin);
}

std::string ft::SplitOneTimes(std::string &str, std::string delimiter)
{
    size_t pos = 0;
    std::string token;

    if (delimiter.empty())
        return (NULL);
    while ((pos = str.find(delimiter)) != std::string::npos) {
        token = str.substr(0, pos);
        str.erase(0, pos + delimiter.size());
        if (!token.empty())
            return (token);
    }
    token = str.substr(0, str.size());
    str.erase(0, str.size());
    return (token);
}

