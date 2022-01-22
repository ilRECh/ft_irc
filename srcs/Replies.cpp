#include "ft.hpp"
#include "Replies.hpp"

status reply(
        int Rplcode,
        int const UserSocketFd,
        std::string const & To,
        std::vector<std::string> const & MsgTokens,
        std::string const & From) {
    std::vector<std::string>::const_iterator CurToken = MsgTokens.begin();
    std::string msg = "(" + From + " " + ft::to_string(Rplcode) + " " + To + ") ";
    switch (Rplcode) {
        case 0:
            msg += *CurToken++ + " :No such nick/channel\n";
            break ;
        case 1:
            msg += *CurToken++ + " :No such server\n";
            break ;
        case ERR_NOSUCHCHANNEL:
            msg += *CurToken++ + " :No such channel\n";
            break ;
        case ERR_CANNOTSENDTOCHAN:
            msg += *CurToken++ + " :Cannot send to channel\n";
            break ;
        case ERR_TOOMANYCHANNELS:
            msg += *CurToken++ + " :You have joined too many channels\n";
            break ;
        case ERR_WASNOSUCHNICK:
            msg += *CurToken++ + " :There was no such nickname\n";
            break ;
        case ERR_TOOMANYTARGETS:
            msg += *CurToken++ + " :Duplicate recipients. No message delivered\n";
            break ;
        case ERR_NOORIGIN:
            msg += ":No origin specified\n";
            break ;
        case ERR_NORECIPIENT:
            msg += ":No recipients given (" + *CurToken++ + ")\n";
            break ;
        case ERR_NOTEXTTOSEND:
            msg += ":No text to send\n";
            break ;
        case ERR_NOTOPLEVEL:
            msg += *CurToken++ + " :No toplevel domain specified\n";
            break ;
        case ERR_WILDTOPLEVEL:
            msg += *CurToken++ + " :Wildcard in toplevel domain\n";
            break ;
        case ERR_UNKNOWNCOMMAND:
            msg += *CurToken++ + " :Unknown command\n";
            break ;
        case ERR_NOMOTD:
            msg += ":MOTD File is missing\n";
            break ;
        case ERR_NOADMININFO:
            msg += *CurToken++ + " :No administrative info available\n";
            break ;
        case ERR_FILEERROR:
            msg += ":File error doing " + *CurToken++;
            msg += " on " + *CurToken++ + "\n";
            break ;
        case ERR_NONICKNAMEGIVEN:
            msg += ":No nickname given\n";
            break ;
        case ERR_ERRONEUSNICKNAME:
            msg += *CurToken++ + " :Erroneus nickname\n";
            break ;
        case ERR_NICKNAMEINUSE:
            msg += *CurToken++ + " :Nickname is already in use\n";
            break ;
        case ERR_NICKCOLLISION:
            msg += *CurToken++ + " :Nickname collision KILL\n";
            break ;
        case ERR_USERNOTINCHANNEL:
            msg += *CurToken++ + " ";
            msg += *CurToken++ + " :They aren't on that channel\n";
            break ;
        case ERR_NOTONCHANNEL:
            msg += *CurToken++ + " :You're not on that channel\n";
            break ;
        case ERR_USERONCHANNEL:
            msg += *CurToken++ + " ";
            msg += *CurToken++ + " :is already on channel\n";
            break ;
        case ERR_NOLOGIN:
            msg += *CurToken++ + " :User not logged in\n";
            break ;
        case ERR_SUMMONDISABLED:
            msg += ":SUMMON has been disabled\n";
            break ;
        case ERR_USERSDISABLED:
            msg += ":USERS has been disabled\n";
            break ;
        case ERR_NOTREGISTERED:
            msg += ":You have not registered\n";
            break ;
        case ERR_NEEDMOREPARAMS:
            msg += *CurToken++ + " :Not enough parameters\n";
            break ;
        case ERR_ALREADYREGISTRED:
            msg += ":You may not reregister\n";
            break ;
        case ERR_NOPERMFORHOST:
            msg += ":Your host isn't among the privileged\n";
            break ;
        case ERR_PASSWDMISMATCH:
            msg += ":Password incorrect\n";
            break ;
        case ERR_YOUREBANNEDCREEP:
            msg += ":You are banned from this server\n";
            break ;
        case ERR_KEYSET:
            msg += *CurToken++ + " :Channel key already set\n";
            break ;
        case ERR_CHANNELISFULL:
            msg += *CurToken++ + " :Cannot join channel (+l)\n";
            break ;
        case ERR_UNKNOWNMODE:
            msg += *CurToken++ + " :is unknown mode char to me\n";
            break ;
        case ERR_INVITEONLYCHAN:
            msg += *CurToken++ + " :Cannot join channel (+i)\n";
            break ;
        case ERR_BANNEDFROMCHAN:
            msg += *CurToken++ + " :Cannot join channel (+b)\n";
            break ;
        case ERR_BADCHANNELKEY:
            msg += *CurToken++ + " :Cannot join channel (+k)\n";
            break ;
        case ERR_NOPRIVILEGES:
            msg += ":Permission Denied- You're not an IRC operator\n";
            break ;
        case ERR_CHANOPRIVSNEEDED:
            msg += *CurToken++ + " :You're not channel operator\n";
            break ;
        case ERR_CANTKILLSERVER:
            msg += ":You cant kill a server!\n";
            break ;
        case ERR_NOOPERHOST:
            msg += ":No O-lines for your host\n";
            break ;
        case ERR_UMODEUNKNOWNFLAG:
            msg += ":Unknown MODE flag\n";
            break ;
        case ERR_USERSDONTMATCH:
            msg += ":Cant change mode for other users\n";
            break ;
        case RPL_NONE:
            break ;
        case RPL_USERHOST:
            msg += ":";
            if (not MsgTokens.empty() /* it's optional */) {
                msg += *CurToken++ + "{ ";
                msg += *CurToken++ + "}\n";
            }
            msg += "\n";
            break ;
        case RPL_ISON:
            msg += ":";
            if (not MsgTokens.empty() /* it's optional */) {
                msg += *CurToken++ + " { ";
                msg += *CurToken++ + "}\n";
            }
            msg += "\n";
            break ;
        case RPL_AWAY:
            msg += *CurToken++ + " :";
            msg += *CurToken++ + "\n";
            break ;
        case RPL_UNAWAY:
            msg += ":You are no longer marked as being away\n";
            break ;
        case RPL_NOWAWAY:
            msg += ":You have been marked as being away\n";
            break ;
        case RPL_WHOISUSER:
            msg += *CurToken++ + " ";
            msg += *CurToken++ + " ";
            msg += *CurToken++ + " * :";
            msg += *CurToken++ + "\n";
            break ;
        case RPL_WHOISSERVER:
            msg += *CurToken++ + " ";
            msg += *CurToken++ + " :";
            msg += *CurToken++ + "\n";
            break ;
        case RPL_WHOISOPERATOR:
            msg += *CurToken++ + " :is an IRC operator\n";
            break ;
        case RPL_WHOISIDLE:
            msg += *CurToken++ + " ";
            msg += *CurToken++ + " :seconds idle\n";
            break ;
        case RPL_ENDOFWHOIS:
            msg += *CurToken++ + " :End of /WHOIS list\n";
            break ;
        case RPL_WHOISCHANNELS:
            msg += *CurToken++ + " :{";
            msg += (MsgTokens.size() == 3 /* [@|+] */) ? (*CurToken++) : ("");
            msg += *CurToken++ + " }\n";
            break ;
        case RPL_WHOWASUSER:
            msg += *CurToken++ + " ";
            msg += *CurToken++ + " ";
            msg += *CurToken++ + " * :";
            msg += *CurToken++ + "\n";
            break ;
        case RPL_ENDOFWHOWAS:
            msg += *CurToken++ + " :End of WHOWAS\n";
            break ;
        case RPL_LISTSTART:
            msg += "Channel :Users Name\n";
            break ;
        case RPL_LIST:
            msg += *CurToken++ + " # ";
            msg += *CurToken++ + " :";
            msg += *CurToken++ + "\n";
            break ;
        case RPL_LISTEND:
            msg += ":End of /LIST\n";
            break ;
        case RPL_CHANNELMODEIS:
            msg += *CurToken++ + " ";
            msg += *CurToken++ + " ";
            msg += *CurToken++ + "\n";
            break ;
        case RPL_NOTOPIC:
            msg += *CurToken++ + " :No topic is set\n";
            break ;
        case RPL_TOPIC:
            msg += *CurToken++ + " :";
            msg += *CurToken++ + "\n";
            break ;
        case RPL_INVITING:
            msg += *CurToken++ + " ";
            msg += *CurToken++ + "\n";
            break ;
        case RPL_SUMMONING:
            msg += *CurToken++ + " :Summoning user to IRC\n";
            break ;
        case RPL_VERSION:
            msg += *CurToken++ + ".";
            msg += *CurToken++ + " ";
            msg += *CurToken++ + " :";
            msg += *CurToken++ + "\n";
            break ;
        case RPL_WHOREPLY:
            msg += *CurToken++ + " ";
            msg += *CurToken++ + " ";
            msg += *CurToken++ + " ";
            msg += *CurToken++ + " ";
            msg += *CurToken++ + " \n";
            msg += *CurToken++;
            msg += (MsgTokens.size() == 9 /* [*] */) ? (*CurToken++) : ("");
            msg += (MsgTokens.size() == 10 /* [@|+] */) ? (*CurToken++) : ("");
            msg += " :" + *CurToken++ + " ";
            msg += *CurToken++ + "\n";
            break ;
        case RPL_ENDOFWHO:
            msg += *CurToken++ + " :End of /WHO list\n";
            break ;
        case RPL_NAMREPLY:
            msg += *CurToken++ + " :";
            while (CurToken != MsgTokens.end()) {
                if ((CurToken->size() == 1 && (*CurToken)[0] == '@') ||
                    (CurToken->size() == 1 && (*CurToken)[0] == '+') /* if [@|+] before <nick> */) {
                    msg += *CurToken++;
                    msg += *CurToken++ + " ";
                } else {
                    msg += *CurToken++ + " ";
                }
            }
            msg += "\n";
            break ;
        case RPL_ENDOFNAMES:
            msg += *CurToken++ + " :End of /NAMES list\n";
            break ;
        case RPL_LINKS:
            msg += *CurToken++ + " ";
            msg += *CurToken++ + " :";
            msg += *CurToken++ + " ";
            msg += *CurToken++ + "\n";           
            break ;
        case RPL_ENDOFLINKS:
            msg += *CurToken++ + " :End of /LINKS list\n";
            break ;
        case RPL_BANLIST:
            msg += *CurToken++ + " ";
            msg += *CurToken++ + "\n";
            break ;
        case RPL_ENDOFBANLIST:
            msg += *CurToken++ + " :End of channel ban list\n";
            break ;
        case RPL_INFO:
            msg += ":" + *CurToken++;
            break ;
        case RPL_ENDOFINFO:
            msg += ":End of /INFO list\n";
            break ;
        case RPL_MOTDSTART:
            msg += ":- " + *CurToken++ + " Message of the day - \n";
            break ;
        case RPL_MOTD:
            msg += ":- " + *CurToken++ + "\n";
            break ;
        case RPL_ENDOFMOTD:
            msg += ":End of /MOTD command\n";
            break ;
        case RPL_YOUREOPER:
            msg += ":You are now an IRC operator\n";
            break ;
        case RPL_REHASHING:
            msg += *CurToken++ + " :Rehasing\n";
            break ;
        case RPL_TIME:
            msg += *CurToken++ + " :";
            msg += *CurToken++ + "\n";
            break ;
        case RPL_USERSSTART:
            msg += ":UserID   Terminal  Host\n";
            break ;
        case RPL_USERS:
            msg += ":%-8s %-9s %-8s\n"; //What to do here?
            break ;
        case RPL_ENDOFUSERS:
            msg += ":End of users\n";
            break ;
        case RPL_NOUSERS:
            msg += ":Nobody logged in\n";
            break ;
        case RPL_TRACELINK:
            msg += "Link " + *CurToken++ + " ";
            msg += *CurToken++ + "\n";
            msg += *CurToken++ + "\n";
            break ;
        case RPL_TRACECONNECTING:
            msg += "Try. " + *CurToken++ + " ";
            msg += *CurToken++ + "\n";
            break ;
        case RPL_TRACEHANDSHAKE:
            msg += "H.S. " + *CurToken++ + " ";
            msg += *CurToken++ + "\n";
            break ;
        case RPL_TRACEUNKNOWN:
            msg += "???? " + *CurToken++ + " ";
            if (CurToken != MsgTokens.end()) {
                msg += *CurToken++;
            }
            msg += "\n";
            break ;
        case RPL_TRACEOPERATOR:
            msg += "Oper " + *CurToken++ + " ";
            msg += *CurToken++ + "\n";
            break ;
        case RPL_TRACEUSER:
            msg += "User " + *CurToken++ + " ";
            msg += *CurToken++ + "\n";
            break ;
        case RPL_TRACESERVER:
            msg += "Serv " + *CurToken++ + " ";
            msg += *CurToken++ + "S ";
            msg += *CurToken++ + "C ";
            msg += *CurToken++ + " \n";
            msg += *CurToken++ + "@";
            msg += *CurToken++ + "\n";
            break ;
        case RPL_TRACENEWTYPE:
            msg += *CurToken++ + " 0 ";
            msg += *CurToken++ + "\n";
            break ;
        case RPL_TRACELOG:
            msg += "File " + *CurToken++ + " ";
            msg += *CurToken++ + "\n";
            break ;
        case RPL_STATSLINKINFO:
            msg += *CurToken++ + " ";
            msg += *CurToken++ + " ";
            msg += *CurToken++ + " \n";
            msg += *CurToken++ + " ";
            msg += *CurToken++ + " \n";
            msg += *CurToken++ + " ";
            msg += *CurToken++ + "\n";
            break ;
        case RPL_STATSCOMMANDS:
            msg += *CurToken++ + " ";
            msg += *CurToken++ + "\n";
            break ;
        case RPL_STATSCLINE:
            msg += "C " + *CurToken++ + " * ";
            msg += *CurToken++ + " ";
            msg += *CurToken++ + " ";
            msg += *CurToken++ + "\n";
            break ;
        case RPL_STATSNLINE:
            msg += "N " + *CurToken++ + " * ";
            msg += *CurToken++ + " ";
            msg += *CurToken++ + " ";
            msg += *CurToken++ + "\n";
            break ;
        case RPL_STATSILINE:
            msg += "I " + *CurToken++ + " * ";
            msg += *CurToken++ + " ";
            msg += *CurToken++ + " ";
            msg += *CurToken++ + "\n";
            break ;
        case RPL_STATSKLINE:
            msg += "K " + *CurToken++ + " * ";
            msg += *CurToken++ + " ";
            msg += *CurToken++ + " ";
            msg += *CurToken++ + "\n";
            break ;
        case RPL_STATSYLINE:
            msg += "Y " + *CurToken++ + " ";
            msg += *CurToken++ + " \n";
            msg += *CurToken++ + " ";
            msg += *CurToken++ + "\n";
            break ;
        case RPL_ENDOFSTATS:
            msg += *CurToken++ + " :End of /STATS report\n";
            break ;
        case RPL_STATSLLINE:
            msg += "L " + *CurToken++ + " * ";
            msg += *CurToken++ + " ";
            msg += *CurToken++ + " ";
            msg += *CurToken++ + "\n";
            break ;
        case RPL_STATSUPTIME:
            msg += ":Server Up %d days %d:%02d:%02d\n";
            break ;
        case RPL_STATSOLINE:
            msg += "O " + *CurToken++ + " * ";
            msg += *CurToken++ + "\n";
            break ;
        case RPL_STATSHLINE:
            msg += "H " + *CurToken++ + " * ";
            msg += *CurToken++ + "\n";
            break ;
        case RPL_UMODEIS:
            msg += *CurToken++ + "\n";
            break ;
        case RPL_LUSERCLIENT:
            msg += ":There are " + *CurToken++ + " users and ";
            msg += *CurToken++ + " \n";
            msg += "invisible on " + *CurToken++ + " servers\n";
            break ;
        case RPL_LUSEROP:
            msg += *CurToken++ + " :operator(s) online\n";
            break ;
        case RPL_LUSERUNKNOWN:
            msg += *CurToken++ + " :unknown connection(s)\n";
            break ;
        case RPL_LUSERCHANNELS:
            msg += *CurToken++ + " :channels formed\n";
            break ;
        case RPL_LUSERME:
            msg += ":I have " + *CurToken++ + " clients and ";
            msg += *CurToken++ + " \n";
            msg += "servers\n";
            break ;
        case RPL_ADMINME:
            msg += *CurToken++ + " :Administrative info\n";
            break ;
        case RPL_ADMINLOC1:
            msg += ":" + *CurToken++ + "\n";
            break ;
        case RPL_ADMINLOC2:
            msg += ":" + *CurToken++ + "\n";
            break ;
        case RPL_ADMINEMAIL:
            msg += ":" + *CurToken++ + "\n";
            break ;
        default:
            while (CurToken != MsgTokens.end()) {
                msg += *CurToken++;
            }
            msg += "\n";
            break ;
    }
    send(UserSocketFd, msg.c_str(), msg.size(), 0/*MSG_NOSIGNAL*/);
    return Rplcode;
}

status reply(
    int const UserSocketFd,
    std::string const & To,
    std::vector<std::string> const & MsgTokens,
    std::string const & From) {
    return reply(0, UserSocketFd, To, MsgTokens, From);
}
