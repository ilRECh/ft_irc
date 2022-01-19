#include "Commands.hpp"

class WHOIS : public ACommand {
private:
    WHOIS();
    WHOIS(WHOIS const &that);
    WHOIS& operator=(WHOIS const &that);
public:
    WHOIS(Server const *Server):   ACommand("WHOIS", Server) {}
    virtual ~WHOIS() {}
    virtual int run(){
        if (_Argument.empty()) {
            std::string arr[] = { _Name };
            return reply(ERR_NEEDMOREPARAMS, _User->_Fd, _User->getName(), L(arr));
        }
        //code
    }
};/*
        Parameters: [<server>] <nickmask>[,<nickmask>[,...]]

        This message is used to query information about particular user.  The
        server will answer this message with several numeric messages
        indicating different statuses of each user which matches the nickmask
        (if you are entitled to see them).  If no wildcard is present in the
        <nickmask>, any information about that nick which you are allowed to
        see is presented.  A comma (',') separated list of nicknames may be
        given.

        The latter version sends the query to a specific server.  It is
        useful if you want to know how long the user in question has been
        idle as only local server (ie. the server the user is directly
        connected to) knows that information, while everything else is
        globally known.

        Numeric Replies:

           ERR_NOSUCHSERVER                ERR_NONICKNAMEGIVEN
           RPL_WHOISUSER                   RPL_WHOISCHANNELS
           RPL_WHOISCHANNELS               RPL_WHOISSERVER
           RPL_AWAY                        RPL_WHOISOPERATOR
           RPL_WHOISIDLE                   ERR_NOSUCHNICK
           RPL_ENDOFWHOIS

        Examples:

        WHOIS wiz                       ; return available user information
                                        about nick WiZ

        WHOIS eff.org trillian          ; ask server eff.org for user
                                        information about trillian

*/