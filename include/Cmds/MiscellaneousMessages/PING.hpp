#include "ACommand.hpp"

class PING : public ACommand {
private:
    PING();
    PING(PING const &that);
    PING& operator=(PING const &that);
public:
    PING(Server &Server) : ACommand("PING", Server) {}
    virtual ~PING() {}
    virtual int run(){
        return 0;//_Initiator->updateReplyMessage("PING " + _Initiator->getNickName());
    }
};/*
        Parameters: <server1> [<server2>]

        The PING message is used to test the presence of an active client at
        the other end of the connection.  A PING message is sent at regular
        intervals if no other activity detected coming from a connection.  If
        a connection fails to respond to a PING command within a set amount
        of time, that connection is closed.

        Any client which receives a PING message must respond to <server1>
        (server which sent the PING message out) as quickly as possible with
        an appropriate PONG message to indicate it is still there and alive.
        Servers should not respond to PING commands but rely on PINGs from
        the other end of the connection to indicate the connection is alive.
        If the <server2> parameter is specified, the PING message gets
        forwarded there.

        Numeric Replies:

        ERR_NOORIGIN                    ERR_NOSUCHSERVER

        Examples:

        PING tolsun.oulu.fi             ; server sending a PING message to
                                       another server to indicate it is still
                                       alive.

        PING WiZ                        ; PING message being sent to nick WiZ

*/
