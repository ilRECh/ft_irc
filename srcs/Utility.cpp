#include "ft.hpp"

std::vector<std::string> ft::split(
        std::string const& tosplit,
        std::string const& delimiters) {
    std::vector<std::string> ret;
    char *str = new char[tosplit.size() + 1];
    char *tmp = NULL;

    str[tosplit.size()] = '\0';
    std::memmove(str, tosplit.c_str(), tosplit.size());
    tmp = std::strtok(str, delimiters.c_str());
    while (tmp not_eq NULL) {
        ret.push_back(tmp);
        tmp = std::strtok(NULL, delimiters.c_str());
    }
    delete [] str;
    return ret;
}

void ft::deleteSpaces(std::string &string, std::string const &symbolsToDelete)
{
    size_t strBegin = string.find_first_not_of(symbolsToDelete);
    if (strBegin not_eq string.npos) {
        string.erase(0, strBegin);
    }
    size_t strEnd = string.find_last_not_of(symbolsToDelete);
    if (strEnd not_eq string.npos and strEnd + 1 < string.length()) {
        string.erase(strEnd+1, string.length() - strEnd);
    } 
}

std::string ft::SplitOneTimes(std::string &str, std::string delimiter)
{
    size_t pos = 0;
    std::string token;

    if (delimiter.empty())
        return (NULL);
    while ((pos = str.find(delimiter)) not_eq std::string::npos) {
        token = str.substr(0, pos);
        str.erase(0, pos + delimiter.size());
        if (!token.empty())
            return (token);
    }
    token = str.substr(0, str.size());
    str.erase(0, str.size());
    return (token);
}

bool ft::wildcard(std::string wExpression, std::string toCompare)
{
	typedef std::string::size_type size_type;
	
	std::vector<std::string> splitedByStar;
	std::vector<std::string> tmp = ft::split(wExpression, "*");

	size_type	lenWord = 0;
	size_type	pos1 = 0;
	size_type	pos2 = 0;

	if (wExpression[0] == '*')
		splitedByStar.push_back("*");
	for (size_t i = 0; i < tmp.size(); i++)
	{
		splitedByStar.push_back(tmp[i]);
		splitedByStar.push_back("*");
	}
	if (wExpression[wExpression.size() -1] not_eq '*')
		splitedByStar.pop_back();

	for (size_type i = 0; i < splitedByStar.size(); i++)
	{
		if (splitedByStar[i][0] == '*')
			continue;
		pos2 = std::string(toCompare.begin() + pos1 + lenWord, toCompare.end()).find(splitedByStar[i]);
		pos1 = pos2 + pos1 + lenWord;
		if ((pos2 == std::string::npos) || (pos2 && (!i || splitedByStar[i - 1][0] != '*')))
			return false;
		lenWord = splitedByStar[i].size();
		if (i + 1 == splitedByStar.size())
			if (wExpression[wExpression.size() - 1] not_eq '*')
				if (toCompare.size() not_eq pos1 + lenWord)
					--i;
	}
	return true;
}

std::string ft::tolowerString(std::string toLowStr)
{
    std::string::iterator i, end;

    i = toLowStr.begin();
    end = toLowStr.end();
    while(i not_eq end)
    {
        if ((*i) >= 'A' && (*i) <= 'Z')
            (*i) += 'a' - 'A';
        ++i;
    }
    return toLowStr;
}
