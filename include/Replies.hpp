#pragma once

/* -------------------------------------------------------------------------- */
/*                               Error Replies.                               */
/* -------------------------------------------------------------------------- */

#define	ERR_NOSUCHNICK(NickName) "(401) " + NickName + " :No such nick/channel"
/*
"<nickname> :No such nick/channel"

- Used to indicate the nickname parameter supplied to a
command is currently unused.
*/

#define	ERR_NOSUCHSERVER(ServerName) "(402) " + ServerName + " :No such server" 
/*"<server name> :No such server"

- Used to indicate the server name given currently
doesn`t exist.
*/

#define	ERR_NOSUCHCHANNEL(ChannelName) "(403) " + ChannelName + " :No such channel" 
/*
"<channel name> :No such channel"

- Used to indicate the given channel name is invalid.
*/

#define	ERR_CANNOTSENDTOCHAN(ChannelName) "(404) " + ChannelName + " :Cannot send to channel" 
/*
"<channel name> :Cannot send to channel"

- Sent to a user who is either (a) not on a channel
which is mode +n or (b) not a chanop (or mode +v) on
a channel which has mode +m set and is trying to send
a PRIVMSG message to that channel.
*/

#define	ERR_TOOMANYCHANNELS(ChannelName) "(405) " + ChannelName + " :You have joined too many"
/*
"<channel name> :You have joined too many \
channels"

- Sent to a user when they have joined the maximum
number of allowed channels and they try to join
another channel.
*/

#define	ERR_WASNOSUCHNICK(NickName)	"(406) " + NickName + " :There was no such nickname"
/*
"<nickname> :There was no such nickname"

- Returned by WHOWAS to indicate there is no history
information for that nickname.
*/

#define	ERR_TOOMANYTARGETS(Target) "(407) " + Target + " :Duplicate recipients. No message \
delivered"

/*
"<target> :Duplicate recipients. No message \
delivered"

- Returned to a client which is attempting to send a
PRIVMSG/NOTICE using the user@host destination format
and for a user@host which has several occurrences.
*/

#define	ERR_NOORIGIN "(409) :No origin specified"
/*
":No origin specified"

- PING or PONG message missing the originator parameter
which is required since these commands must work
without valid prefixes.
*/

#define	ERR_NORECIPIENT(Command) "(411) :No recipient given (" + Command + ")"
/*
":No recipient given (<command>)"
*/

#define	ERR_NOTEXTTOSEND "(412) :No text to send"
/*
":No text to send"
*/

#define	ERR_NOTOPLEVEL(Mask) "(413) " + Mask + " :No toplevel domain specified"
/*
"<mask> :No toplevel domain specified"
*/

#define	ERR_WILDTOPLEVEL(Mask) "(414) " + Mask + " :Wildcard in toplevel domain"
/*
"<mask> :Wildcard in toplevel domain"

- 412 - 414 are returned by PRIVMSG to indicate that
the message wasn`t delivered for some reason.
ERR_NOTOPLEVEL and ERR_WILDTOPLEVEL are errors that
are returned when an invalid use of
"PRIVMSG $<server>" or "PRIVMSG #<host>" is attempted.
*/

#define	ERR_UNKNOWNCOMMAND(Command)		"(421) " + Command + " :Unknown command"
/*
"<command> :Unknown command"

- Returned to a registered client to indicate that the
command sent is unknown by the server.
*/

#define	ERR_NOMOTD "(422) :MOTD File is missing"
/*
":MOTD File is missing"

- Server`s MOTD file could not be opened by the server.
*/

#define	ERR_NOADMININFO(Server) "(423) " + Server + " :No administrative info available"
/*
"<server> :No administrative info available"

- Returned by a server in response to an ADMIN message
when there is an error in finding the appropriate
information.
*/

#define	ERR_FILEERROR(FileOp, File) "(424) :File error doing " + FileOp + " on " + File
/*
":File error doing <file op> on <file>"

- Generic error message used to report a failed file
operation during the processing of a message.
*/

#define	ERR_NONICKNAMEGIVEN "(431) :No nickname given"
/*
":No nickname given"

- Returned when a nickname parameter expected for a
command and isn`t found.
*/

#define	ERR_ERRONEUSNICKNAME(Nick) "(432) " + Nick + " :Erroneus nickname"
/*
"<nick> :Erroneus nickname"

- Returned after receiving a NICK message which contains
characters which do not fall in the defined set.  See
section x.x.x for details on valid nicknames.
*/

#define	ERR_NICKNAMEINUSE(Nick) "(433) " + Nick + " :Nickname is already in use"
/*
"<nick> :Nickname is already in use"

- Returned when a NICK message is processed that results
in an attempt to change to a currently existing
nickname.
*/

#define	ERR_NICKCOLLISION(Nick) "(436) " + Nick + " :Nickname collision KILL"
/*
"<nick> :Nickname collision KILL"

- Returned by a server to a client when it detects a
nickname collision (registered of a NICK that
already exists by another server).
*/

#define	ERR_USERNOTINCHANNEL(Nick, Channel) "(441) " + Nick + Channel + " :They aren`t on that channel"
/*
"<nick> <channel> :They aren`t on that channel"

- Returned by the server to indicate that the target
user of the command is not on the given channel.
*/

#define	ERR_NOTONCHANNEL(Channel) "(442) " + Channel + " :You're not on that channel"
/*
"<channel> :You're not on that channel"

- Returned by the server whenever a client tries to
perform a channel effecting command for which the
client isn`t a member.
*/

#define	ERR_USERONCHANNEL(User, Channel) "(443) " + User + Channel + " :is already on channel"
/*
"<user> <channel> :is already on channel"

- Returned when a client tries to invite a user to a
channel they are already on.
*/

#define	ERR_NOLOGIN(User) "(444) " + User + " :User not logged in"
/*
"<user> :User not logged in"

- Returned by the summon after a SUMMON command for a
user was unable to be performed since they were not
logged in.
*/

#define	ERR_SUMMONDISABLED "(445) :SUMMON has been disabled"
/*
":SUMMON has been disabled"

- Returned as a response to the SUMMON command.  Must be
returned by any server which does not implement it.
*/

#define	ERR_USERSDISABLED "(446) :USERS has been disabled"
/*
":USERS has been disabled"

- Returned as a response to the USERS command.  Must be
returned by any server which does not implement it.
*/

#define	ERR_NOTREGISTERED "(451) :You have not registered"
/*
":You have not registered"

- Returned by the server to indicate that the client
must be registered before the server will allow it
to be parsed in detail.
*/

#define	ERR_NEEDMOREPARAMS(Command) "(461) " + Command + " :Not enough parameters"
/*
"<command> :Not enough parameters"

- Returned by the server by numerous commands to
indicate to the client that it didn`t supply enough
parameters.
*/

#define	ERR_ALREADYREGISTRED "(462) :You may not reregister"
/*
":You may not reregister"

- Returned by the server to any link which tries to
change part of the registered details (such as
password or user details from second USER message).
*/


#define	ERR_NOPERMFORHOST "(463) :Your host isn`t among the privileged"
/*
":Your host isn`t among the privileged"

- Returned to a client which attempts to register with
a server which does not been setup to allow
connections from the host the attempted connection
is tried.
*/

#define	ERR_PASSWDMISMATCH "(464) :Password incorrect"
/*
":Password incorrect"

- Returned to indicate a failed attempt at registering
a connection for which a password was required and
was either not given or incorrect.
*/

#define	ERR_YOUREBANNEDCREEP "(465) :You are banned from this server"
/*
":You are banned from this server"

- Returned after an attempt to connect and register
yourself with a server which has been setup to
explicitly deny connections to you.
*/

#define	ERR_KEYSET(Channel) "(467) " + Channel + " :Channel key already set"
/*
"<channel> :Channel key already set"
*/

#define	ERR_CHANNELISFULL(Channel) "(471) " + Channel + " :Cannot join channel (+l)"
/*
"<channel> :Cannot join channel (+l)"
*/

#define	ERR_UNKNOWNMODE(Char) "(472) " + Char + " :is unknown mode char to me"
/*
"<char> :is unknown mode char to me"
*/

#define	ERR_INVITEONLYCHAN(Channel) "(473) " + Channel + " :Cannot join channel (+i)"
/*
"<channel> :Cannot join channel (+i)"
*/

#define	ERR_BANNEDFROMCHAN(Channel) "(474) " + Channel + " :Cannot join channel (+b)"
/*
"<channel> :Cannot join channel (+b)"
*/

#define	ERR_BADCHANNELKEY(Channel) "(475) " + Channel + " :Cannot join channel (+k)"
/*
"<channel> :Cannot join channel (+k)"
*/

#define	ERR_NOPRIVILEGES "(481) :Permission Denied- You're not an IRC operator"
/*
":Permission Denied- You're not an IRC operator"

- Any command requiring operator privileges to operate
must return this error to indicate the attempt was
unsuccessful.
*/

#define	ERR_CHANOPRIVSNEEDED(Channel) "(482) " + Channel + " :You're not channel operator"
/*
"<channel> :You're not channel operator"

- Any command requiring 'chanop' privileges (such as
MODE messages) must return this error if the client
making the attempt is not a chanop on the specified
channel.
*/

#define	ERR_CANTKILLSERVER "(483) :You cant kill a server!"
/*
":You cant kill a server!"

- Any attempts to use the KILL command on a server
are to be refused and this error returned directly
to the client.
*/

#define	ERR_NOOPERHOST "(491) :No O-lines for your host"
/*
":No O-lines for your host"

- If a client sends an OPER message and the server has
not been configured to allow connections from the
client`s host as an operator, this error must be
returned.
*/

#define	ERR_UMODEUNKNOWNFLAG "(501) :Unknown MODE flag"
/*
":Unknown MODE flag"

- Returned by the server to indicate that a MODE
message was sent with a nickname parameter and that
the a mode flag sent was not recognized.
*/

#define	ERR_USERSDONTMATCH "(502) :Cant change mode for other users"
/*
":Cant change mode for other users"

- Error sent to any user trying to view or change the
user mode for a user other than themselves.
*/

/* -------------------------------------------------------------------------- */
/*                             Command responses.                             */
/* -------------------------------------------------------------------------- */

#define	RPL_NONE		300 /*
Dummy reply number. Not used.
*/

#define	RPL_USERHOST(Reply1, Reply2) "(302) :" + \
    (not Reply1.empty() and not Reply2.empty()) ? Reply1 + "{ " + Reply2 + "}" : ""
/*
":[<reply>{<space><reply>}]"

- Reply format used by USERHOST to list replies to
the query list.  The reply string is composed as
follows:

<reply> ::= <nick>['*'] '=' <'+'|'-'><hostname>

The '*' indicates whether the client has registered
as an Operator.  The '-' or '+' characters represent
whether the client has set an AWAY message or not
respectively.
*/

#define	RPL_ISON(Nick1, Nick2) "(302) :" + \
    (not Nick1.empty() and not Nick2.empty()) ? Nick1 + " { " + Nick2 + "}" : ""
/*
":[<nick> {<space><nick>}]"

- Reply format used by ISON to list replies to the
query list.
*/

#define	RPL_AWAY(Nick, AwayMessage) "(301) " + Nick + " :" + AwayMessage
/*
"<nick> :<away message>"
*/

#define	RPL_UNAWAY "(305) :You are no longer marked as being away"
/*
":You are no longer marked as being away"
*/

#define	RPL_NOWAWAY "(306) :You have been marked as being away"
/*
":You have been marked as being away"

- These replies are used with the AWAY command (if
allowed).  RPL_AWAY is sent to any client sending a
PRIVMSG to a client which is away.  RPL_AWAY is only
sent by the server to which the client is connected.
Replies RPL_UNAWAY and RPL_NOWAWAY are sent when the
client removes and sets an AWAY message.
*/

#define	RPL_WHOISUSER(Nick, User, Host, RealName) "(311) " + Nick + " " + User + " " + Host + " * :" + RealName
/* 
"<nick> <user> <host> * :<real name>"
*/

#define	RPL_WHOISSERVER(Nick, Server, ServerInfo) "(312) " + Nick + " " + Server + " :" + ServerInfo
/*
"<nick> <server> :<server info>"
*/

#define	RPL_WHOISOPERATOR(Nick)	"(313) " + Nick + " :is an IRC operator"
/*
"<nick> :is an IRC operator"
*/

#define	RPL_WHOISIDLE(Nick, Integer) "(317) " + Nick + " " + Integer + " :seconds idle"
/*
"<nick> <integer> :seconds idle"
*/

#define	RPL_ENDOFWHOIS(Nick) "(318) " + Nick + " :End of /WHOIS list"
/*
"<nick> :End of /WHOIS list"
*/

#define	RPL_WHOISCHANNELS(Nick, Symbol, Channel) "(319) " + Nick + " :{" + Symbol + Channel + " }"
/*
"<nick> :{[@|+]<channel><space>}"

- Replies 311 - 313, 317 - 319 are all replies
generated in response to a WHOIS message.  Given that
there are enough parameters present, the answering
server must either formulate a reply out of the above
numerics (if the query nick is found) or return an
error reply.  The '*' in RPL_WHOISUSER is there as
the literal character and not as a wild card.  For
each reply set, only RPL_WHOISCHANNELS may appear
more than once (for long lists of channel names).
The '@' and '+' characters next to the channel name
indicate whether a client is a channel operator or
has been granted permission to speak on a moderated
channel.  The RPL_ENDOFWHOIS reply is used to mark
the end of processing a WHOIS message.
*/

#define	RPL_WHOWASUSER(Nick, User, Host, RealName)	"(314) " + Nick + " " + User + " " + Host + " * :" + RealName
/*
"<nick> <user> <host> * :<real name>"
*/

#define	RPL_ENDOFWHOWAS(Nick) "(369) " + Nick + " :End of WHOWAS"
/*
"<nick> :End of WHOWAS"

- When replying to a WHOWAS message, a server must use
the replies RPL_WHOWASUSER, RPL_WHOISSERVER or
ERR_WASNOSUCHNICK for each nickname in the presented

list.  At the end of all reply batches, there must
be RPL_ENDOFWHOWAS (even if there was only one reply
and it was an error).
*/

#define	RPL_LISTSTART "(321) ""Channel :Users  Name"
/*
"Channel :Users  Name"
*/

#define	RPL_LIST(Channel, Visible, Topic) "(322) " + Channel + " # " + Visible + " :" + Topic
/*
"<channel> <# visible> :<topic>"
*/

#define	RPL_LISTEND "(323) :End of /LIST"
/*
":End of /LIST"

- Replies RPL_LISTSTART, RPL_LIST, RPL_LISTEND mark
the start, actual replies with data and end of the
server`s response to a LIST command.  If there are
no channels available to return, only the start
and end reply must be sent.
*/

#define	RPL_CHANNELMODEIS(Channel, Mode, ModeParams) "(324) " + Channel + " " + Mode + " " + ModeParams
/*
"<channel> <mode> <mode params>"
*/

#define	RPL_NOTOPIC(Channel) "(331) " + Channel + " :No topic is set"
/*
"<channel> :No topic is set"
*/

#define	RPL_TOPIC(Channel, Topic) "(332) " + Channel + " :" + Topic
/*
"<channel> :<topic>"

- When sending a TOPIC message to determine the
channel topic, one of two replies is sent.  If
the topic is set, RPL_TOPIC is sent back else
RPL_NOTOPIC.
*/

#define	RPL_INVITING(Channel, Nick)	"(341) " + Channel + " " + Nick
/*
"<channel> <nick>"

- Returned by the server to indicate that the
attempted INVITE message was successful and is
being passed onto the end client.
*/

#define	RPL_SUMMONING(User)	"(342) " + User + " :Summoning user to IRC"
/*
"<user> :Summoning user to IRC"

- Returned by a server answering a SUMMON message to
indicate that it is summoning that user.
*/

#define	RPL_VERSION(Version, Debuglevel, Server, Comments) "(351) " + Version + "." + Debuglevel + " " + Server + " :" + Comments
/*
"<version>.<debuglevel> <server> :<comments>"

- Reply by the server showing its version details.
The <version> is the version of the software being

used (including any patchlevel revisions) and the
<debuglevel> is used to indicate if the server is
running in "debug mode".

The "comments" field may contain any comments about
the version or further version details.
*/

#define	RPL_WHOREPLY(Channel, User, Host, Server, Nick, H_or_G, optionalAsterisk, optional_At_or_Plus, Hopcount, RealName) \
"(352) " + Channel + " " + Client + " " + Host + " " + Server + " " + Nick \
+ "\n" + H_or_G + optionalAsterisk + optional_At_or_Plus + " :" + Hopcount + " " + RealName
/*
"<channel> <user> <host> <server> <nick> \
<H|G>[*][@|+] :<hopcount> <real name>"
*/

#define	RPL_ENDOFWHO(Name) "(315) " + Name + " :End of /WHO list"
/*
"<name> :End of /WHO list"

- The RPL_WHOREPLY and RPL_ENDOFWHO pair are used
to answer a WHO message.  The RPL_WHOREPLY is only
sent if there is an appropriate match to the WHO
query.  If there is a list of parameters supplied
with a WHO message, a RPL_ENDOFWHO must be sent
after processing each list item with <name> being
the item.
*/

#define	RPL_NAMREPLY		353 /*
"<channel> :[[@|+]<nick> [[@|+]<nick> [...]]]"
*/

#define	RPL_ENDOFNAMES(Channel) "(366) " + Channel + " :End of /NAMES list"
/*
"<channel> :End of /NAMES list"

- To reply to a NAMES message, a reply pair consisting
of RPL_NAMREPLY and RPL_ENDOFNAMES is sent by the
server back to the client.  If there is no channel
found as in the query, then only RPL_ENDOFNAMES is
returned.  The exception to this is when a NAMES
message is sent with no parameters and all visible
channels and contents are sent back in a series of
RPL_NAMEREPLY messages with a RPL_ENDOFNAMES to mark
the end.
*/

#define	RPL_LINKS(Mask, Server, Hopcount, ServerInfo) "(364) " + Mask + " " + Server + " :" + Hopcount + " " + ServerInfo
/*
"<mask> <server> :<hopcount> <server info>"
*/

#define	RPL_ENDOFLINKS(Mask) "(365) " + Mask + " :End of /LINKS list"
/*
"<mask> :End of /LINKS list"

- In replying to the LINKS message, a server must send
replies back using the RPL_LINKS numeric and mark the
end of the list using an RPL_ENDOFLINKS reply.
*/

#define	RPL_BANLIST(Channel, Banid) "(367) " + Channel + " " + Banid
/*
"<channel> <banid>"
*/

#define	RPL_ENDOFBANLIST(Channel) "(368) " + Channel + " :End of channel ban list"
/*
"<channel> :End of channel ban list"

- When listing the active 'bans' for a given channel,
a server is required to send the list back using the
RPL_BANLIST and RPL_ENDOFBANLIST messages.  A separate
RPL_BANLIST is sent for each active banid.  After the
banids have been listed (or if none present) a
RPL_ENDOFBANLIST must be sent.
*/

#define	RPL_INFO(String) "(371) :" + String
/*
":<string>"
*/

#define	RPL_ENDOFINFO "(374) :End of /INFO list"
/*
":End of /INFO list"

- A server responding to an INFO message is required to
send all its 'info' in a series of RPL_INFO messages
with a RPL_ENDOFINFO reply to indicate the end of the
replies.
*/

#define	RPL_MOTDSTART(Server) "(375) :- " + Server + " Message of the day - "
/*
":- <server> Message of the day - "
*/

#define	RPL_MOTD(Text) "(372) :- " + Text
/*
":- <text>"
*/

#define	RPL_ENDOFMOTD "(376) :End of /MOTD command"
/*
":End of /MOTD command"

- When responding to the MOTD message and the MOTD file
is found, the file is displayed line by line, with
each line no longer than 80 characters, using
RPL_MOTD format replies.  These should be surrounded
by a RPL_MOTDSTART (before the RPL_MOTDs) and an
RPL_ENDOFMOTD (after).
*/

#define	RPL_YOUREOPER "(381) :You are now an IRC operator"
/*
":You are now an IRC operator"

- RPL_YOUREOPER is sent back to a client which has
just successfully issued an OPER message and gained
operator status.
*/

#define	RPL_REHASHING(ConfigFile) "(382) " + ConfigFile + " :Rehashing"
/*
"<config file> :Rehashing"

- If the REHASH option is used and an operator sends
a REHASH message, an RPL_REHASHING is sent back to
the operator.
*/

#define	RPL_TIME(Server, ServerLocalTime) "(391) " + Server + " :" + ServerLocalTime
/*
"<server> :<string showing server`s local time>"

- When replying to the TIME message, a server must send
the reply using the RPL_TIME format above.  The string
showing the time need only contain the correct day and
time there.  There is no further requirement for the
time string.
*/

#define	RPL_USERSSTART "(392) :UserID   Terminal  Host"
/*
":UserID   Terminal  Host"
*/

#define	RPL_USERS "(393) :%-8s %-9s %-8s"
/*
":%-8s %-9s %-8s"
*/

#define	RPL_ENDOFUSERS "(394) :End of users"
/*
":End of users"
*/

#define	RPL_NOUSERS "(395) :Nobody logged in"
/*
":Nobody logged in"

- If the USERS message is handled by a server, the
replies RPL_USERSTART, RPL_USERS, RPL_ENDOFUSERS and
RPL_NOUSERS are used.  RPL_USERSSTART must be sent
first, following by either a sequence of RPL_USERS
or a single RPL_NOUSER.  Following this is
RPL_ENDOFUSERS.
*/

#define	RPL_TRACELINK(VersionDebugLevel, Destination, NextServer) \
"(200) Link " + VersionDebugLevel + " " + Destination + "\n" + NextServer
/*
"Link <version & debug level> <destination> \
<next server>"
*/

#define	RPL_TRACECONNECTING(Class, Server) "(201) Try. " + Class + " " + Server
/*
"Try. <class> <server>"
*/

#define	RPL_TRACEHANDSHAKE(Class, Server) "(202) H.S. " + Class + " " + Server
/*
"H.S. <class> <server>"
*/

#define	RPL_TRACEUNKNOWN(Class, Ip) "(203) ???? " + Class + not Ip.empty() ?  " " + Ip : ""
/*
"???? <class> [<client IP address in dot form>]"
*/

#define	RPL_TRACEOPERATOR(Class, Nick) "(204) Oper " + Class + " " + Nick
/*
"Oper <class> <nick>"
*/

#define	RPL_TRACEUSER(Class, Nick) "(205) User " + Class + " " + Nick
/*
"User <class> <nick>"
*/

#define	RPL_TRACESERVER(Class, Int1, Int2, Server, NickUser, Host_or_server)\
"(206) ""Serv " + Class + " " + Int1 + "S " + Int2 + "C " + Server + "\n" + NickUser + "@" + Host_or_Server 
/*
"Serv <class> <int>S <int>C <server> \
<nick!user|*!*>@<host|server>"
*/

#define	RPL_TRACENEWTYPE(Newtype, ClientName) "(208) " + Newtype + " 0 " + ClientName
/*
"<newtype> 0 <client name>"
*/

#define	RPL_TRACELOG(Logfile, DebugLevel) "(261) File " + Logfile + " " + DebugLevel
/*
"File <logfile> <debug level>"

- The RPL_TRACE* are all returned by the server in
response to the TRACE message.  How many are
returned is dependent on the the TRACE message and

whether it was sent by an operator or not.  There
is no predefined order for which occurs first.
Replies RPL_TRACEUNKNOWN, RPL_TRACECONNECTING and
RPL_TRACEHANDSHAKE are all used for connections
which have not been fully established and are either
unknown, still attempting to connect or in the
process of completing the `server handshake'.
RPL_TRACELINK is sent by any server which handles
a TRACE message and has to pass it on to another
server.  The list of RPL_TRACELINKs sent in
response to a TRACE command traversing the IRC
network should reflect the actual connectivity of
the servers themselves along that path.
RPL_TRACENEWTYPE is to be used for any connection
which does not fit in the other categories but is
being displayed anyway.
*/

#define	RPL_STATSLINKINFO(Linkname, Sendq, SentMessages, SentBytes, ReceivedMessages, ReceivedBytes, TimeOpen)\
"(211) " + Linkname + " " + Sendq + " " + SentMessages + " \n " + SentBytes + " " + ReceivedMessages\
 + " \n " + ReceivedBytes + " " + TimeOpen
/*
"<linkname> <sendq> <sent messages> \
<sent bytes> <received messages> \
<received bytes> <time open>"
*/

#define	RPL_STATSCOMMANDS(Command, Count) "(212) " + Command + " " + Count
/*
"<command> <count>"
*/

#define	RPL_STATSCLINE(Host, Name, Port, Class) "(213) C " + Host + " * " + Name + " " + Port + " " + Class
/*
"C <host> * <name> <port> <class>"
*/

#define	RPL_STATSNLINE(Host, Name, Port, Class) "(214) N " + Host + " * " + Name + " " + Port + " " + Class
/*
"N <host> * <name> <port> <class>"
*/

#define	RPL_STATSILINE(Host1, Host2, Port, Class) "(215) I " + Host1 + " * " + Host2 + " " + Port + " " + Class
/*
"I <host> * <host> <port> <class>"
*/

#define	RPL_STATSKLINE(Host, Username, Port, Class) "(216) K " + Host + " * " + Username + " " + Port + " " + Class
/*
"K <host> * <username> <port> <class>"
*/

#define	RPL_STATSYLINE(Class, PingFrequency, ConnectFrequency, MaxSendq)\
"(218) Y " + Class + " " + PingFrequency + " \n " + ConnectFrequency + " " + MaxSendq
/*
"Y <class> <ping frequency> <connect \
frequency> <max sendq>"
*/

#define	RPL_ENDOFSTATS(StatsLetter) "(219) " + StatsLetter + " :End of /STATS report"
/*
"<stats letter> :End of /STATS report"
*/

#define	RPL_STATSLLINE(Hostmask, Servername, Maxdepth) "(241) L " + Hostmask + " * " + Servername + " " + Maxdepth
/*
"L <hostmask> * <servername> <maxdepth>"
*/

#define	RPL_STATSUPTIME "(242) :Server Up %d days %d:%02d:%02d"
/*
":Server Up %d days %d:%02d:%02d"
*/

#define	RPL_STATSOLINE(Hostmask, Name) "(243) O " + Hostmask + " * " + Name
/*
"O <hostmask> * <name>"
*/

#define	RPL_STATSHLINE(Hostmask, Servername) "(244) H " + Hostmask + " * " + Servername
/*
"H <hostmask> * <servername>"
*/

#define	RPL_UMODEIS(UserModeString) "(221) " + UserModeString
/*
"<user mode string>"

- To answer a query about a client`s own mode,
RPL_UMODEIS is sent back.
*/

#define	RPL_LUSERCLIENT(Integer1, Integer2, Integer3)\
"(251) :There are " + Integer1 + " users and " + Integer2 + " \n invisible on " + Integer3 + " servers"
/*
":There are <integer> users and <integer> \
invisible on <integer> servers"
*/

#define	RPL_LUSEROP(Integer) "(252) " + Integer + " :operator(s) online"
/*
"<integer> :operator(s) online"
*/

#define	RPL_LUSERUNKNOWN(Integer) "(253) " + Integer + " :unknown connection(s)"
/*
"<integer> :unknown connection(s)"
*/

#define	RPL_LUSERCHANNELS(Integer) "(254) " + Integer + " :channels formed"
/*
"<integer> :channels formed"
*/

#define	RPL_LUSERME(Integer1, Integer2) "(255) :I have " + Integer1 + " clients and " + Integer2 + " \n servers"
/*
":I have <integer> clients and <integer> \
servers"

- In processing an LUSERS message, the server
sends a set of replies from RPL_LUSERCLIENT,
RPL_LUSEROP, RPL_USERUNKNOWN,
RPL_LUSERCHANNELS and RPL_LUSERME.  When
replying, a server must send back
RPL_LUSERCLIENT and RPL_LUSERME.  The other
replies are only sent back if a non-zero count
is found for them.
*/

#define	RPL_ADMINME(Server) "(256) " + Server + " :Administrative info"
/*
"<server> :Administrative info"
*/

#define	RPL_ADMINLOC1(AdminInfo) "(257) :" + AdminInfo
/*
":<admin info>"
*/

#define	RPL_ADMINLOC2(AdminInfo) "(258) :" + AdminInfo
/*
":<admin info>"
*/

#define	RPL_ADMINEMAIL(AdminInfo) "(259) :" + AdminInfo
/*
":<admin info>"

- When replying to an ADMIN message, a server
is expected to use replies RLP_ADMINME
through to RPL_ADMINEMAIL and provide a text
message with each.  For RPL_ADMINLOC1 a
description of what city, state and country
the server is in is expected, followed by
details of the university and department
(RPL_ADMINLOC2) and finally the administrative
contact for the server (an email address here
is required) in RPL_ADMINEMAIL.
*/
