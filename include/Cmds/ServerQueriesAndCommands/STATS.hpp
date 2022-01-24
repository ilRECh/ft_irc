#include "ACommand.hpp"

class STATS : public ACommand {
private:
    STATS();
    STATS(STATS const &that);
    STATS& operator=(STATS const &that);
public:
    STATS(Server &Server) : Acommand("STATS", Server) {}
    virtual ~STATS() {}
    virtual int run(){
        if (_Argument.empty()) {
            return _Initiator->setReplyMessage(ERR_NEEDMOREPARAMS(_Name));
            
        }
        //code
    }
};/*
   Parameters: [<query> [<server>]]

   The stats message is used to query statistics of certain server.  If
   <server> parameter is omitted, only the end of stats reply is sent
   back.  The implementation of this command is highly dependent on the
   server which replies, although the server must be able to supply
   information as described by the queries below (or similar).

   A query may be given by any single letter which is only checked by
   the destination server (if given as the <server> parameter) and is
   otherwise passed on by intermediate servers, ignored and unaltered.
   The following queries are those found in the current IRC
   implementation and provide a large portion of the setup information
   for that server.  Although these may not be supported in the same way
   by other versions, all servers should be able to supply a valid reply
   to a STATS query which is consistent with the reply formats currently
   used and the purpose of the query.

   The currently supported queries are:

           c - returns a list of servers which the server may connect
               to or allow connections from;
           h - returns a list of servers which are either forced to be
               treated as leaves or allowed to act as hubs;
           i - returns a list of hosts which the server allows a client
               to connect from;
           k - returns a list of banned username/hostname combinations
               for that server;
           l - returns a list of the server's connections, showing how

               long each connection has been established and the traffic
               over that connection in bytes and messages for each
               direction;
           m - returns a list of commands supported by the server and
               the usage count for each if the usage count is non zero;
           o - returns a list of hosts from which normal clients may
               become operators;
           y - show Y (Class) lines from server's configuration file;
           u - returns a string showing how long the server has been up.

   Numeric Replies:

           ERR_NOSUCHSERVER
           RPL_STATSCLINE                  RPL_STATSNLINE
           RPL_STATSILINE                  RPL_STATSKLINE
           RPL_STATSQLINE                  RPL_STATSLLINE
           RPL_STATSLINKINFO               RPL_STATSUPTIME
           RPL_STATSCOMMANDS               RPL_STATSOLINE
           RPL_STATSHLINE                  RPL_ENDOFSTATS

   Examples:

   STATS m                         ; check the command usage for the server
                                     you are connected to

   :Wiz STATS c eff.org            ; request by WiZ for C/N line
                                    information from server eff.org

*/