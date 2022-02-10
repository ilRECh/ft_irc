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
            last_target = ft::SplitOneTimes(targets, ",");
            if (!last_target.empty() && !recipients.insert(last_target).second) {
                recipients.erase(last_target);
                _Initiator->updateReplyMessage(ERR_TOOMANYTARGETS(last_target));
            }
        }
        std::set<Client *> ClientsToReply;
        std::set<Channel *> ChannelsToReply;
        for (std::set<std::string>::iterator it = recipients.begin(); it not_eq recipients.end(); ++it) {
            if ((*it)[0] not_eq '#') {
                ClientsToReply = _Server.getClientsByName(*it);
                if (ClientsToReply.empty()) {
                    _Initiator->updateReplyMessage(ERR_NOSUCHNICK(*it));
                    continue ;
                }
                for (std::set<Client *>::iterator CurClient = ClientsToReply.begin(); CurClient not_eq ClientsToReply.end(); ++CurClient) {
                    if ((*CurClient)->updateReplyMessage(" PRIVMSG " + (*CurClient)->_NickName + " :" + _Argument, _Initiator->getFull())) {
                        _Initiator->updateReplyMessage(RPL_AWAY((*CurClient)->_Away, (*CurClient)->_NickName));
                    }
                }
            } else {
                ChannelsToReply = _Server.getChannelsByChannelName(*it);
                if (ChannelsToReply.empty()) {
                    _Initiator->updateReplyMessage(ERR_NOSUCHCHANNEL(*it));
                    continue ;
                }
                for (std::set<Channel *>::iterator CurChannel = ChannelsToReply.begin(); CurChannel not_eq ChannelsToReply.end(); ++CurChannel) {
                    if ((*CurChannel)->getModeIsExist(*CurChannel, 'm') and not (*CurChannel)->getModeIsExist(_Initiator, 'v')) {
                        return _Initiator->updateReplyMessage(ERR_CANNOTSENDTOCHAN((*CurChannel)->getChannelName()));
                    }
                    (*CurChannel)->replyToAllMembers(_Initiator->getFull() + " PRIVMSG " + (*CurChannel)->getChannelName() + " :" + _Argument, _Initiator);
                }
            }
        }
        return 0;
    }
};/*
        Parameters: <receiver>{,<receiver>} <text to be sent>

        PRIVMSG is used to send private messages between users.  <receiver>
        is the nickname of the receiver of the message.  <receiver> can also
        be a list of names or channels separated with commas.

        Numeric Replies:

        ERR_NORECIPIENT                 ERR_NOTEXTTOSEND
        ERR_CANNOTSENDTOCHAN
        ERR_TOOMANYTARGETS
        ERR_NOSUCHNICK
        RPL_AWAY

        Examples:
        :Angel PRIVMSG Wiz :Hello are you receiving this message ?
        ; Message from Angel to Wiz.
*/
