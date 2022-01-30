#pragma once
#include "ACommand.hpp"

class NOTICE : public ACommand {
private:
    NOTICE();
    NOTICE(NOTICE const &that);
    NOTICE& operator=(NOTICE const &that);
public:
    NOTICE(Server &Server) : ACommand("NOTICE", Server) {}
    virtual ~NOTICE() {}
    virtual int run(){
        std::string targets = ft::SplitOneTimes(_Argument, ":");
        ft::deleteSpaces(targets);
        ft::deleteSpaces(_Argument);
        if (targets.empty()) {
            return 0;
        }
        if (_Argument.empty())
            return 0;
        std::set<std::string> recipients;
        for (std::string last_target; !targets.empty();)
        {
            last_target = ft::SplitOneTimes(targets, " ");
            if (!last_target.empty() && !recipients.insert(last_target).second) {
                recipients.erase(last_target);
            }
        }
        Client *last_target = NULL;
        for (std::set<std::string>::iterator it = recipients.begin();
             it != recipients.end(); ++it)
        {
            last_target = _Server.getUserByNickName(*it);
            if (last_target == NULL){
//                last_target = _Server.getChannelByName(*it);
//                if (last_target == NULL)
//                else if (last_target->updateReplyMessage(_Argument))
            }
            else {
                    last_target->updateReplyMessage(_Argument);
            }
        }
        _Argument.erase();
        return 0;
    }
};/*
        Parameters: <nickname> <text>

        The NOTICE message is used similarly to PRIVMSG.  The difference
        between NOTICE and PRIVMSG is that automatic replies must never be
        sent in response to a NOTICE message.  This rule applies to servers
        too - they must not send any error reply back to the client on
        receipt of a notice.  The object of this rule is to avoid loops
        between a client automatically sending something in response to
        something it received.  This is typically used by automatons (clients
        with either an AI or other interactive program controlling their
        actions) which are always seen to be replying lest they end up in a
        loop with another automaton.

        See PRIVMSG for more details on replies and examples.

*/
