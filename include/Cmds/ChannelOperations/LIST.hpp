#pragma once
#include "ACommand.hpp"

class LIST : public ACommand {
private:
    LIST();
    LIST(LIST const &that);
    LIST& operator=(LIST const &that);
public:
    LIST(Server &Server) : ACommand("LIST", Server) {}
    virtual ~LIST() {}
    virtual int run(){
        std::vector<std::set<Channel *> > channels;
        std::vector<std::string> argsNameChan;
        std::set<Channel *>::iterator beginChan, endChan;
        _Initiator->updateReplyMessage(RPL_LISTSTART);
        if (_Arguments.empty()) {
            channels.push_back(_Server.getChannelsByChannelName("*"));
        }
        else
        {
            argsNameChan = ft::split(_Arguments[0], ",");
            for(uint i = 0; i < argsNameChan.size(); ++i)
                channels.push_back(_Server.getChannelsByChannelName(argsNameChan[i], false));
        }
        for(uint i = 0; i < channels.size(); ++i)
        {
            endChan = channels[i].end();
            beginChan = channels[i].begin();
            for(;beginChan not_eq endChan; ++beginChan)
            {
                if ((*beginChan)->getModeIsExist(*beginChan, 's'))
                    continue ;
                if ((*beginChan)->getModeIsExist(*beginChan, 'p')
                and not (*beginChan)->isOnChannel(_Initiator))
                {
                    _Initiator->updateReplyMessage(RPL_LIST((*beginChan)->getChannelName(), "*", "Prv"));
                }
                else
                {
                    _Initiator->updateReplyMessage
                    (
                        RPL_LIST
                        (
                            (*beginChan)->getChannelName(), 
                            ft::to_string((*beginChan)->getCountClients()),
                            (*beginChan)->getTopic()
                        )
                    );
                }
            }
        }
        _Initiator->updateReplyMessage(RPL_LISTEND);
        return 0;
    }
};/*
   Parameters: [<channel>{,<channel>} [<server>]]

   The list message is used to list channels and their topics.  If  the
   <channel>  parameter  is  used,  only  the  status  of  that  channel
   is displayed.  Private  channels  are  listed  (without  their
   topics)  as channel "Prv" unless the client generating the query is
   actually on that channel.  Likewise, secret channels are not listed

   at  all  unless  the client is a member of the channel in question.

   Numeric Replies:

           ERR_NOSUCHSERVER                RPL_LISTSTART
           RPL_LIST                        RPL_LISTEND

   Examples:

   LIST                            ; List all channels.

   LIST #twilight_zone,#42         ; List channels #twilight_zone and #42

*/
