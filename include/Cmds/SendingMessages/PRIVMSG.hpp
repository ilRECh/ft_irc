#pragma once
#include "ACommand.hpp"
#include <set>

class PRIVMSG : public ACommand {
private:
    PRIVMSG();
    PRIVMSG(PRIVMSG const &that);
    PRIVMSG& operator=(PRIVMSG const &that);
public:
    PRIVMSG(Server &Server) : ACommand("PRIVMSG", Server) {}
    virtual ~PRIVMSG() {}
    virtual int run(){
        std::string targets = ft::SplitOneTimes(_Argument, ":");
        ft::deleteSpaces(targets, SPACE_SYMBOLS);
        ft::deleteSpaces(_Argument, SPACE_SYMBOLS);
        if (targets.empty()) {
            return _Initiator->updateReplyMessage(ERR_NORECIPIENT(_Name));
        }
        if (_Argument.empty())
            return _Initiator->updateReplyMessage(ERR_NOTEXTTOSEND);
        std::set<std::string> recipients;
        for (std::string last_target; !targets.empty();)
        {
            last_target = ft::SplitOneTimes(targets, " ");
            if (!last_target.empty() && !recipients.insert(last_target).second) {
                recipients.erase(last_target);
                _Initiator->updateReplyMessage(ERR_TOOMANYTARGETS(last_target));
            }
        }
        std::set<Client *> ClientsToReply;
        std::set<Channel *> ChannelsToReply;
        for (std::set<std::string>::iterator it = recipients.begin(); it != recipients.end(); ++it) {
            if ((*it)[0] != '#') {
                ClientsToReply = _Server.getClientsByName(*it);
                if (ClientsToReply.empty()) {
                    _Initiator->updateReplyMessage(ERR_NOSUCHNICK(*it));
                    continue ;
                }
                for (std::set<Client *>::iterator CurClient = ClientsToReply.begin(); CurClient != ClientsToReply.end(); ++CurClient) {
                    if ((*CurClient)->updateReplyMessage(_Initiator->_NickName + " PRIVMSG " + (*CurClient)->_NickName + " :" + _Argument)) {
                        _Initiator->updateReplyMessage(RPL_AWAY((*CurClient)->_Away, (*CurClient)->_NickName));
                    }
                }
            } else {
                ChannelsToReply = _Server.getChannelsByChannelName(*it);
                if (ChannelsToReply.empty()) {
                    _Initiator->updateReplyMessage(ERR_NOSUCHCHANNEL(*it));
                    continue ;
                }
                for (std::set<Channel *>::iterator CurChannel = ChannelsToReply.begin(); CurChannel != ChannelsToReply.end(); ++CurChannel) {
                    (*CurChannel)->replyToAllMembers(_Initiator->_NickName + " PRIVMSG " + (*CurChannel)->getChannelName() + " :" + _Argument, _Initiator);
                }
            }
        }
        return 0;
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
