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

//*		*123*123*		3 2
//*		123*123*123*	3 3
//*		123*123*123*321 3 4


std::string::size_type ft::find_word(
	std::string const & needle, 
	std::string::iterator hstackBegin, 
	std::string::iterator hstackEnd)
{
	std::string::size_type res = 0;
	for (std::string::iterator i = hstackBegin; i != hstackEnd; ++i, ++res)
	{
		for (std::string::size_type j = 0; j < needle.size() && i + j != hstackEnd; ++j)
		{
			if (*(i + j) != needle[j])
				break ;
			if (j + 1 == needle.size())
				return res;
		}
	}
	return std::string::npos;
}


std::vector<std::string> uniSplit(std::string & toUnite){
	std::vector<std::string> result;
	std::vector<std::string> tmp = ft::split(toUnite, "*");

	if (toUnite[0] == '*')
		result.push_back("*");
	for (size_t i = 0; i < tmp.size(); i++)
	{
		result.push_back(tmp[i]);
		result.push_back("*");
	}
	if (toUnite[toUnite.size() -1] != '*')
		result.pop_back();
	return (result);
}

bool ft::compareSimpleWildcard(
	std::string wExpression, 
	std::string ToCompare)
{
	typedef std::string::size_type size_type;
	std::vector<std::string> splitedByStar;
	size_type	lenWord = 0;
	size_type	pos1 = 0;
	size_type	pos2 = 0;

	splitedByStar = uniSplit(wExpression);

	for (size_type i = 0; i < splitedByStar.size(); i++)
	{
		if (splitedByStar[i][0] == '*')
			continue;
		pos2 = find_word(splitedByStar[i], ToCompare.begin() + pos1 + lenWord, ToCompare.end());
		pos1 = pos2 + pos1 + lenWord;
		if ((pos2 == std::string::npos) || (pos2 && (!i || (i && splitedByStar[i - 1][0] != '*'))))
			return false;
		lenWord = splitedByStar[i].size();
		if (i + 1 == splitedByStar.size())
			if (wExpression[wExpression.size() - 1] != '*')
				if (ToCompare.size() != pos1 + lenWord)
					--i;
	}
	return true;
}
