#include "../../Commands.hpp"
#include <set>

class PRIVMSG : public ACommand {
private:
    PRIVMSG();
    PRIVMSG(PRIVMSG const &that);
    PRIVMSG& operator=(PRIVMSG const &that);
public:
    PRIVMSG(Server const *Server):   ACommand("PRIVMSG", Server) {}
    virtual ~PRIVMSG() {}
    virtual int run(){
        std::string targets = ft::SplitOneTimes(_Argument, ":");
        ft::deleteSpaces(targets);
        ft::deleteSpaces(_Argument);
        if (targets.empty()) {
            {
                std::string arr[] = { _Name };
                return reply(ERR_NORECIPIENT, _User->_Fd, _User->getName(), L(arr));
            }
        }
        if (_Argument.empty())
            return reply(ERR_NOTEXTTOSEND, _User->_Fd, _User->getName());
        std::set<std::string> recipients;
        for (std::string last_target, size_t set_size; !targets.empty();
            last_target = ft::SplitOneTimes(targets, " "))
        {
            set_size = recipients.size();
            recipients.insert(last_target);
            if (recipients.size() == set_size) {
                recipients.erase(last_target);
                {
                    std::string arr[] = {last_target};
                    reply(ERR_TOOMANYTARGETS, _User->_Fd, _User->getName(), L(arr));
                }
            }
        }
        for (std::set<std::string>::iterator it = recipients.begin(),
            User *lastUser = NULL,
            Channel *lastChannel = NULL;
            it != recipients.end(); ++it) {
            lastUser = _Server.getUserByName(*it);
            if (lastUser == NULL) {
                lastChannel = _Server.getChannelByName(*it);
                if (lastChannel == NULL) {
                    {
                        std::string arr[] = {*it};
                        reply(ERR_NOSUCHNICK, _User->_Fd, _User->getName(), L(arr));
                    }
                } else if
                    /*reply*/ ERR_CANNOTSENDTOCHAN;
            }
            else {
                reply(0, lastUser->_Fd, _User->getName(), L(_Argument))
                /*if (RPL_AWAY)*/
            }
        }
/*          if ()
            return ERR_NOTOPLEVEL
            if ()
            return ERR_WILDTOPLEVEL*/
    }
};/*
        Parameters: <receiver>{,<receiver>} <text to be sent>

        PRIVMSG is used to send private messages between users.  <receiver>
        is the nickname of the receiver of the message.  <receiver> can also
        be a list of names or channels separated with commas.

        The <receiver> parameter may also me a host mask  (#mask)  or  server
        mask  ($mask).   In  both cases the server will only send the PRIVMSG
        to those who have a server or host matching the mask.  The mask  must
        have at  least  1  (one)  "."  in it and no wildcards following the
        last ".".  This requirement exists to prevent people sending messages
        to  "#*"  or "$*",  which  would  broadcast  to  all  users; from
        experience, this is abused more than used responsibly and properly.
        Wildcards are  the  '*' and  '?'   characters.   This  extension  to
        the PRIVMSG command is only available to Operators.

        Numeric Replies:

        ERR_NORECIPIENT                 ERR_NOTEXTTOSEND
        ERR_CANNOTSENDTOCHAN            ERR_NOTOPLEVEL
        ERR_WILDTOPLEVEL                ERR_TOOMANYTARGETS
        ERR_NOSUCHNICK
        RPL_AWAY

        Examples:
        :Angel PRIVMSG Wiz :Hello are you receiving this message ?
        ; Message from Angel to Wiz.

        PRIVMSG Angel :yes I'm receiving it !receiving it !'u>(768u+1n) .br ;
        Message to Angel.

        PRIVMSG jto@tolsun.oulu.fi :Hello !
        ; Message to a client on server

                                        tolsun.oulu.fi with username of "jto".

        PRIVMSG $*.fi :Server tolsun.oulu.fi rebooting.
        ; Message to everyone on a server which
        has a name matching *.fi.

        PRIVMSG #*.edu :NSFNet is undergoing work, expect interruptions
        ; Message to all users who come from a
        host which has a name matching *.edu.

*/