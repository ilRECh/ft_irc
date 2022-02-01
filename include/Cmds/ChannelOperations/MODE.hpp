#pragma once
#include "ACommand.hpp"

class MODE : public ACommand {
private:
    MODE();
    MODE(MODE const &that);
    MODE& operator=(MODE const &that);
    int procChannel(){
        Channel *targetChannel = _Server.getChannelByChannelName(_Arguments[0]);
        if (not targetChannel)
            return _Initiator->updateReplyMessage(ERR_NOSUCHCHANNEL(_Arguments[0]));
        if (not targetChannel->isOnChannel(_Initiator))
            return _Initiator->updateReplyMessage(ERR_NOTONCHANNEL(_Arguments[0]));
        if (not targetChannel->getModeIsExist(_Initiator, 'o'))
            return _Initiator->updateReplyMessage(ERR_CHANOPRIVSNEEDED(_Arguments[0]));
        if (_Arguments.size() == 1)
            return _Initiator->updateReplyMessage(RPL_CHANNELMODEIS(_Arguments[0], "todo", "todo")); //todo:
        for (unsigned long i = 1; i < _Arguments[1].size(); ++i) {
            switch (_Arguments[1][i]) {
                case 'o':
                case 'v':
                    {
                        if ((i + 1) > _Arguments.size())
                            return _Initiator->updateReplyMessage(ERR_NEEDMOREPARAMS(_Name));
                        Client *targetNick = _Server.getUserByNickName( _Arguments[i + 1]);
                        if (not targetNick){
                            _Initiator->updateReplyMessage(ERR_NOSUCHNICK(_Arguments[i + 1]));
                            continue;
                        }
                        if (_Arguments[1][0] == '+')
                            targetChannel->setMode(targetNick, _Arguments[1][i]);
                        else
                            targetChannel->unsetMode(targetNick, _Arguments[1][i]);
                    }
                    break;
                case 'p':
                case 's':
                case 'i':
                case 't':
                case 'n':
                case 'm':
                    if (_Arguments[1][0] == '+')
                        targetChannel->setMode(targetChannel, _Arguments[1][i]);
                    else
                        targetChannel->unsetMode(targetChannel, _Arguments[1][i]);
                    break;
                case 'l':
                    if ((i + 1) > _Arguments.size())
                        return _Initiator->updateReplyMessage(ERR_NEEDMOREPARAMS(_Name));
                    if (_Arguments[1][0] == '+'){
                        targetChannel->setLimit(stoi(_Arguments[i + 1]));
                        targetChannel->setMode(targetChannel, _Arguments[1][i]);
                    }
                    else {
                        targetChannel->setLimit(0);
                        targetChannel->unsetMode(targetChannel, _Arguments[1][i]);
                    }
                    break;
                case 'b': //todo: banlist in chan
                {
                    if ((i + 1) > _Arguments.size())
                        return _Initiator->updateReplyMessage(ERR_NEEDMOREPARAMS(_Name));
                    
                    if (_Arguments[1][0] == '+')
                        ;
                    else
                        ;
                }
                    break;
                case 'k':
                    if ((i + 1) > _Arguments.size())
                        return _Initiator->updateReplyMessage(ERR_NEEDMOREPARAMS(_Name));
                    if (_Arguments[1][0] == '+'){
                        if (not targetChannel->getKey().empty())
                            _Initiator->updateReplyMessage(ERR_KEYSET(_Arguments[0]));
                        targetChannel->setKey(_Arguments[i + 1]);
                        targetChannel->setMode(targetChannel, _Arguments[1][i]);
                    }
                    else {
                        targetChannel->setKey("");
                        targetChannel->unsetMode(targetChannel, _Arguments[1][i]);
                    }
                    break;
                default:
                    _Initiator->updateReplyMessage(ERR_UNKNOWNMODE(std::string(1, _Arguments[1][i])));
            }
        }
        return 0;
    }
    int procClient() {
        if (_Initiator->getNickName() != _Arguments[0])
            return _Initiator->updateReplyMessage(ERR_USERSDONTMATCH);
//        if (_Arguments.size() == 1)
//            return _Initiator->updateReplyMessage(RPL_UMODEIS("todo")); //todo:
        for (unsigned long i = 1; i < _Arguments[1].size(); ++i) {
            switch (_Arguments[1][i]) {
                case 'o':
                    if (_Arguments[1][0] == '-')
                        _Server.unsetMode(_Initiator, _Arguments[1][i]);
                    break;
                case 'i':
                case 's':
                case 'w':
                    if (_Arguments[1][0] == '+')
                        _Server.setMode(_Initiator, _Arguments[1][i]);
                    else
                        _Server.unsetMode(_Initiator, _Arguments[1][i]);
                    break;
                default:
                    _Initiator->updateReplyMessage(ERR_UMODEUNKNOWNFLAG);
            }
        }
        return 0;
    }
public:
    MODE(Server &Server) : ACommand("MODE", Server) {}
    virtual ~MODE() {}
    virtual int run(){
        if (_Arguments.empty()) {
            return _Initiator->updateReplyMessage(ERR_NEEDMOREPARAMS(_Name));
        }
        if (not _Arguments[1].empty() && (_Arguments[1][0] != '-' || _Arguments[1][0] != '+'))
            return _Initiator->updateReplyMessage(ERR_UMODEUNKNOWNFLAG);
        if (_Arguments[0][0] == '#' || _Arguments[0][0] == '&')
            procChannel();
        else
            procClient();
        return 0;
    }
};/*
   The MODE command is a dual-purpose command in IRC.  It allows both
   usernames and channels to have their mode changed.  The rationale for
   this choice is that one day nicknames will be obsolete and the
   equivalent property will be the channel.

   When parsing MODE messages, it is recommended that the entire message
   be parsed first and then the changes which resulted then passed on.

4.2.3.1 Channel modes

   Parameters: <channel> {[+|-]|o|p|s|i|t|n|b|v} [<limit>] [<user>]
               [<ban mask>]

   The MODE command is provided so that channel operators may change the
   characteristics of `their' channel.  It is also required that servers
   be able to change channel modes so that channel operators may be
   created.

   The various modes available for channels are as follows:

           o - give/take channel operator privileges;
           p - private channel flag;
           s - secret channel flag;
           i - invite-only channel flag;
           t - topic settable by channel operator only flag;
           n - no messages to channel from clients on the outside;
           m - moderated channel;
           l - set the user limit to channel;

           b - set a ban mask to keep users out;
           v - give/take the ability to speak on a moderated channel;
           k - set a channel key (password).

   When using the 'o' and 'b' options, a restriction on a total of three
   per mode command has been imposed.  That is, any combination of 'o'
   and

4.2.3.2 User modes

   Parameters: <nickname> {[+|-]|i|w|s|o}

   The user MODEs are typically changes which affect either how the
   client is seen by others or what 'extra' messages the client is sent.
   A user MODE command may only be accepted if both the sender of the
   message and the nickname given as a parameter are both the same.

   The available modes are as follows:

           i - marks a users as invisible;
           s - marks a user for receipt of server notices;
           w - user receives wallops;
           o - operator flag.

   Additional modes may be available later on.

   If a user attempts to make themselves an operator using the "+o"
   flag, the attempt should be ignored.  There is no restriction,
   however, on anyone `deopping' themselves (using "-o").  Numeric
   Replies:

           ERR_NEEDMOREPARAMS              RPL_CHANNELMODEIS
           ERR_CHANOPRIVSNEEDED            ERR_NOSUCHNICK
           ERR_NOTONCHANNEL                ERR_KEYSET
           RPL_BANLIST                     RPL_ENDOFBANLIST
           ERR_UNKNOWNMODE                 ERR_NOSUCHCHANNEL

           ERR_USERSDONTMATCH              RPL_UMODEIS
           ERR_UMODEUNKNOWNFLAG

   Examples:

           Use of Channel Modes:

MODE #Finnish +im               ; Makes #Finnish channel moderated and
                                'invite-only'.

MODE #Finnish +o Kilroy         ; Gives 'chanop' privileges to Kilroy on

                                channel #Finnish.

MODE #Finnish +v Wiz            ; Allow WiZ to speak on #Finnish.

MODE #Fins -s                   ; Removes 'secret' flag from channel
                                #Fins.

MODE #42 +k oulu                ; Set the channel key to "oulu".

MODE #eu-opers +l 10            ; Set the limit for the number of users
                                on channel to 10.

MODE &oulu +b                   ; list ban masks set for channel.

MODE &oulu +b *!*@*             ; prevent all users from joining.

MODE &oulu +b *!*@*.edu         ; prevent any user from a hostname
                                matching *.edu from joining.

        Use of user Modes:

:MODE WiZ -w                    ; turns reception of WALLOPS messages
                                off for WiZ.

:Angel MODE Angel +i            ; Message from Angel to make themselves
                                invisible.

MODE WiZ -o                     ; WiZ 'deopping' (removing operator
                                status).  The plain reverse of this
                                command ("MODE WiZ +o") must not be
                                allowed from users since would bypass
                                the OPER command.

*/
