#pragma once

/* -------------------------------------------------------------------------- */
/*                               Error Replies.                               */
/* -------------------------------------------------------------------------- */

#define ERR_NOSUCHNICK(Initiator, NickName) "401 " + Initiator + " " + NickName + " :No such nick/channel"
/*
"<nickname> :No such nick/channel"

- Used to indicate the nickname parameter supplied to a
command is currently unused.
*/

#define ERR_NOSUCHSERVER(Initiator, ServerName) "402 " + Initiator + " " + ServerName + " :No such server"
/*"<server name> :No such server"

- Used to indicate the server name given currently
doesn`t exist.
*/

#define ERR_NOSUCHCHANNEL(Initiator, ChannelName) "403 " + Initiator + " " + ChannelName + " :No such channel"
/*
"<channel name> :No such channel"

- Used to indicate the given channel name is invalid.
*/

#define ERR_CANNOTSENDTOCHAN(Initiator, ChannelName) "404 " + Initiator + " " + ChannelName + " :Cannot send to channel"
/*
"<channel name> :Cannot send to channel"

- Sent to a user who is either (a) not on a channel
which is mode +n or (b) not a chanop (or mode +v) on
a channel which has mode +m set and is trying to send
a PRIVMSG message to that channel.
*/

#define ERR_TOOMANYCHANNELS(Initiator, ChannelName) "405 " + Initiator + " " + ChannelName + " :You have joined too many"
/*
"<channel name> :You have joined too many \
channels"

- Sent to a user when they have joined the maximum
number of allowed channels and they try to join
another channel.
*/

#define ERR_WASNOSUCHNICK(Initiator, NickName) "406 " + Initiator + " " + NickName + " :There was no such nickname"
/*
"<nickname> :There was no such nickname"

- Returned by WHOWAS to indicate there is no history
information for that nickname.
*/

#define ERR_TOOMANYTARGETS(Initiator, Target) "407 " + Initiator + " " + Target + " :Duplicate recipients. No message \
delivered"

/*
"<target> :Duplicate recipients. No message \
delivered"

- Returned to a client which is attempting to send a
PRIVMSG/NOTICE using the user@host destination format
and for a user@host which has several occurrences.
*/

#define ERR_NOORIGIN (Initiator) "409 " + Initiator + " No origin specified"
/*
":No origin specified"

- PING or PONG message missing the originator parameter
which is required since these commands must work
without valid prefixes.
*/

#define ERR_NORECIPIENT(Initiator, Command) "411 " + Initiator + " No recipient given (" + Command + ")"
/*
":No recipient given (<command>)"
*/

#define ERR_NOTEXTTOSEND (Initiator) "412 " + Initiator + " No text to send"
/*
":No text to send"
*/

#define ERR_NOTOPLEVEL(Initiator, Mask) "413 " + Initiator + " " + Mask + " :No toplevel domain specified"
/*
"<mask> :No toplevel domain specified"
*/

#define ERR_WILDTOPLEVEL(Initiator, Mask) "414 " + Initiator + " " + Mask + " :Wildcard in toplevel domain"
/*
"<mask> :Wildcard in toplevel domain"

- 412 - 414 are returned by PRIVMSG to indicate that
the message wasn`t delivered for some reason.
ERR_NOTOPLEVEL and ERR_WILDTOPLEVEL are errors that
are returned when an invalid use of
"PRIVMSG $<server>" or "PRIVMSG #<host>" is attempted.
*/

#define ERR_UNKNOWNCOMMAND(Initiator, Command) "421 " + Initiator + " " + Command + " :Unknown command"
/*
"<command> :Unknown command"

- Returned to a registered client to indicate that the
command sent is unknown by the server.
*/

#define ERR_NOMOTD (Initiator) "422 " + Initiator + " MOTD File is missing"
/*
":MOTD File is missing"

- Server`s MOTD file could not be opened by the server.
*/

#define ERR_NOADMININFO(Initiator, Server) "423 " + Initiator + " " + Server + " :No administrative info available"
/*
"<server> :No administrative info available"

- Returned by a server in response to an ADMIN message
when there is an error in finding the appropriate
information.
*/

#define ERR_FILEERROR(Initiator, FileOp, File) "424 " + Initiator + " File error doing " + FileOp + " on " + File
/*
":File error doing <file op> on <file>"

- Generic error message used to report a failed file
operation during the processing of a message.
*/

#define ERR_NONICKNAMEGIVEN (Initiator) "431 " + Initiator + " No nickname given"
/*
":No nickname given"

- Returned when a nickname parameter expected for a
command and isn`t found.
*/

#define ERR_ERRONEUSNICKNAME(Initiator, Nick) "432 " + Initiator + " " + Nick + " :Erroneus nickname"
/*
"<nick> :Erroneus nickname"

- Returned after receiving a NICK message which contains
characters which do not fall in the defined set.  See
section x.x.x for details on valid nicknames.
*/

#define ERR_NICKNAMEINUSE(Initiator, Nick) "433 " + Initiator + " " + Nick + " :Nickname is already in use"
/*
"<nick> :Nickname is already in use"

- Returned when a NICK message is processed that results
in an attempt to change to a currently existing
nickname.
*/

#define ERR_NICKCOLLISION(Initiator, Nick) "436 " + Initiator + " " + Nick + " :Nickname collision KILL"
/*
"<nick> :Nickname collision KILL"

- Returned by a server to a client when it detects a
nickname collision (registered of a NICK that
already exists by another server).
*/

#define ERR_USERNOTINCHANNEL(Initiator, Nick, Channel) "441 " + Initiator + " " + Nick + Channel + " :They aren`t on that channel"
/*
"<nick> <channel> :They aren`t on that channel"

- Returned by the server to indicate that the target
user of the command is not on the given channel.
*/

#define ERR_NOTONCHANNEL(Initiator, Channel) "442 " + Initiator + " " + Channel + " :You're not on that channel"
/*
"<channel> :You're not on that channel"

- Returned by the server whenever a client tries to
perform a channel effecting command for which the
client isn`t a member.
*/

#define ERR_USERONCHANNEL(Initiator, User, Channel) "443 " + Initiator + " " + User + Channel + " :is already on channel"
/*
"<user> <channel> :is already on channel"

- Returned when a client tries to invite a user to a
channel they are already on.
*/

#define ERR_NOLOGIN(Initiator, User) "444 " + Initiator + " " + User + " :User not logged in"
/*
"<user> :User not logged in"

- Returned by the summon after a SUMMON command for a
user was unable to be performed since they were not
logged in.
*/

#define ERR_SUMMONDISABLED (Initiator) "445 " + Initiator + " SUMMON has been disabled"
/*
":SUMMON has been disabled"

- Returned as a response to the SUMMON command.  Must be
returned by any server which does not implement it.
*/

#define ERR_USERSDISABLED (Initiator) "446 " + Initiator + " USERS has been disabled"
/*
":USERS has been disabled"

- Returned as a response to the USERS command.  Must be
returned by any server which does not implement it.
*/

#define ERR_NOTREGISTERED (Initiator) "451 " + Initiator + " You have not registered"
/*
":You have not registered"

- Returned by the server to indicate that the client
must be registered before the server will allow it
to be parsed in detail.
*/

#define ERR_NEEDMOREPARAMS(Initiator, Command) "461 " + Initiator + " " + Command + " :Not enough parameters"
/*
"<command> :Not enough parameters"

- Returned by the server by numerous commands to
indicate to the client that it didn`t supply enough
parameters.
*/

#define ERR_ALREADYREGISTRED (Initiator) "462 " + Initiator + " You may not reregister"
/*
":You may not reregister"

- Returned by the server to any link which tries to
change part of the registered details (such as
password or user details from second USER message).
*/

#define ERR_NOPERMFORHOST (Initiator) "463 " + Initiator + " Your host isn`t among the privileged"
/*
":Your host isn`t among the privileged"

- Returned to a client which attempts to register with
a server which does not been setup to allow
connections from the host the attempted connection
is tried.
*/

#define ERR_PASSWDMISMATCH (Initiator) "464 " + Initiator + " Password incorrect"
/*
":Password incorrect"

- Returned to indicate a failed attempt at registering
a connection for which a password was required and
was either not given or incorrect.
*/

#define ERR_YOUREBANNEDCREEP (Initiator) "465 " + Initiator + " You are banned from this server"
/*
":You are banned from this server"

- Returned after an attempt to connect and register
yourself with a server which has been setup to
explicitly deny connections to you.
*/

#define ERR_KEYSET(Initiator, Channel) "467 " + Initiator + " " + Channel + " :Channel key already set"
/*
"<channel> :Channel key already set"
*/

#define ERR_CHANNELISFULL(Initiator, Channel) "471 " + Initiator + " " + Channel + " :Cannot join channel (+l)"
/*
"<channel> :Cannot join channel (+l)"
*/

#define ERR_UNKNOWNMODE(Initiator, Char) "472 " + Initiator + " " + Char + " :is unknown mode char to me"
/*
"<char> :is unknown mode char to me"
*/

#define ERR_INVITEONLYCHAN(Initiator, Channel) "473 " + Initiator + " " + Channel + " :Cannot join channel (+i)"
/*
"<channel> :Cannot join channel (+i)"
*/

#define ERR_BANNEDFROMCHAN(Initiator, Channel) "474 " + Initiator + " " + Channel + " :Cannot join channel (+b)"
/*
"<channel> :Cannot join channel (+b)"
*/

#define ERR_BADCHANNELKEY(Initiator, Channel) "475 " + Initiator + " " + Channel + " :Cannot join channel (+k)"
/*
"<channel> :Cannot join channel (+k)"
*/

#define ERR_BADCHANMASK(Initiator, Channel) "476 " + Initiator + " " + Channel + " :Bad parse, use"
/*
"<channel> :Bad parse & #"
*/

#define ERR_NOPRIVILEGES (Initiator) "481 " + Initiator + " Permission Denied- You're not an IRC operator"
/*
":Permission Denied- You're not an IRC operator"

- Any command requiring operator privileges to operate
must return this error to indicate the attempt was
unsuccessful.
*/

#define ERR_CHANOPRIVSNEEDED(Initiator, Channel) "482 " + Initiator + " " + Channel + " :You're not channel operator"
/*
"<channel> :You're not channel operator"

- Any command requiring 'chanop' privileges (such as
MODE messages) must return this error if the client
making the attempt is not a chanop on the specified
channel.
*/

#define ERR_CANTKILLSERVER (Initiator) "483 " + Initiator + " You cant kill a server!"
/*
":You cant kill a server!"

- Any attempts to use the KILL command on a server
are to be refused and this error returned directly
to the client.
*/

#define ERR_NOOPERHOST (Initiator) "491 " + Initiator + " No O-lines for your host"
/*
":No O-lines for your host"

- If a client sends an OPER message and the server has
not been configured to allow connections from the
client`s host as an operator, this error must be
returned.
*/

#define ERR_UMODEUNKNOWNFLAG (Initiator) "501 " + Initiator + " Unknown MODE flag"
/*
":Unknown MODE flag"

- Returned by the server to indicate that a MODE
message was sent with a nickname parameter and that
the a mode flag sent was not recognized.
*/

#define ERR_USERSDONTMATCH (Initiator) "502 " + Initiator + " Cant change mode for other users"
/*
":Cant change mode for other users"

- Error sent to any user trying to view or change the
user mode for a user other than themselves.
*/

/* -------------------------------------------------------------------------- */
/*                             Command responses.                             */
/* -------------------------------------------------------------------------- */

#define	RPL_NONE	Initiator, 	300 /*
Dummy reply number. Not used.
*/

#define RPL_USERHOST(Initiator, Reply1, Reply2) "302 " + Initiator + " " +                                         \
											 (not Reply1.empty() and not Reply2.empty()) \
										 ? Reply1 + "{ " + Reply2 + "}"                  \
										 : ""
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

#define RPL_ISON(Initiator, Nick1, Nick2) "302 " + Initiator + " " +                                       \
									   (not Nick1.empty() and not Nick2.empty()) \
								   ? Nick1 + " { " + Nick2 + "}"                 \
								   : ""
/*
":[<nick> {<space><nick>}]"

- Reply format used by ISON to list replies to the
query list.
*/

#define RPL_AWAY(Initiator, Away, Nick, Target) "301 " + Nick + " " + Target + " " + Away
/*
"<nick> :<away message>"
*/

#define RPL_UNAWAY (Initiator) "305 " + Initiator + " You are no longer marked as being away"
/*
":You are no longer marked as being away"
*/

#define RPL_NOWAWAY (Initiator) "306 " + Initiator + " You have been marked as being away"
/*
":You have been marked as being away"

- These replies are used with the AWAY command (if
allowed).  RPL_AWAY is sent to any client sending a
PRIVMSG to a client which is away.  RPL_AWAY is only
sent by the server to which the client is connected.
Replies RPL_UNAWAY and RPL_NOWAWAY are sent when the
client removes and sets an AWAY message.
*/

#define RPL_WHOISUSER(Initiator, Nick, User, Host, RealName) "311 " + Initiator + " " + Nick + " " + User + " " + Host + " * :" + RealName
/* 
"<nick> <user> <host> * :<real name>"
*/

#define RPL_WHOISSERVER(Initiator, Nick, Server, ServerInfo) "312 " + Initiator + " " + Nick + " " + Server + " :" + ServerInfo
/*
"<nick> <server> :<server info>"
*/

#define RPL_WHOISOPERATOR(Initiator, Nick) "313 " + Initiator + " " + Nick + " :is an IRC operator"
/*
"<nick> :is an IRC operator"
*/

#define RPL_WHOISIDLE(Initiator, Nick, Integer) "317 " + Initiator + " " + Nick + " " + Integer + " :seconds idle"
/*
"<nick> <integer> :seconds idle"
*/

#define RPL_ENDOFWHOIS(Initiator, Nick) "318 " + Initiator + " " + Nick + " :End of /WHOIS list"
/*
"<nick> :End of /WHOIS list"
*/

#define RPL_WHOISCHANNELS(Initiator, Nick, Symbol, Channel) "319 " + Initiator + " " + Nick + " :{" + Symbol + Channel + " }"
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

#define RPL_WHOWASUSER(Initiator, Nick, User, Host, RealName) "314 " + Initiator + " " + Nick + " " + User + " " + Host + " * :" + RealName
/*
"<nick> <user> <host> * :<real name>"
*/

#define RPL_ENDOFWHOWAS(Initiator, Nick) "369 " + Initiator + " " + Nick + " :End of WHOWAS"
/*
"<nick> :End of WHOWAS"

- When replying to a WHOWAS message, a server must use
the replies RPL_WHOWASUSER, RPL_WHOISSERVER or
ERR_WASNOSUCHNICK for each nickname in the presented

list.  At the end of all reply batches, there must
be RPL_ENDOFWHOWAS (even if there was only one reply
and it was an error).
*/

#define RPL_LISTSTART (Initiator) "321 " + Initiator + " " \
					  "Channel :Users  Name"
/*
"Channel :Users  Name"
*/

#define RPL_LIST(Initiator, Channel, Visible, Topic) "322 " + Initiator + " " + Channel + " # " + Visible + " :" + Topic
/*
"<channel> <# visible> :<topic>"
*/

#define RPL_LISTEND (Initiator) "323 " + Initiator + " End of /LIST"
/*
":End of /LIST"

- Replies RPL_LISTSTART, RPL_LIST, RPL_LISTEND mark
the start, actual replies with data and end of the
server`s response to a LIST command.  If there are
no channels available to return, only the start
and end reply must be sent.
*/

#define RPL_CHANNELMODEIS(Initiator, Channel, Mode, ModeParams) "324 " + Initiator + " " + Channel + " " + Mode + " " + ModeParams
/*
"<channel> <mode> <mode params>"
*/

#define RPL_NOTOPIC(Initiator, Channel) "331 " + Initiator + " " + Channel + " :No topic is set"
/*
"<channel> :No topic is set"
*/

#define RPL_TOPIC(Initiator, Channel, Topic) "332 " + Initiator + " " + Channel + " :" + Topic
/*
"<channel> :<topic>"

- When sending a TOPIC message to determine the
channel topic, one of two replies is sent.  If
the topic is set, RPL_TOPIC is sent back else
RPL_NOTOPIC.
*/

#define RPL_INVITING(Initiator, Channel, Nick) "341 " + Initiator + " " + Channel + " " + Nick
/*
"<channel> <nick>"

- Returned by the server to indicate that the
attempted INVITE message was successful and is
being passed onto the end client.
*/

#define RPL_SUMMONING(Initiator, User) "342 " + Initiator + " " + User + " :Summoning user to IRC"
/*
"<user> :Summoning user to IRC"

- Returned by a server answering a SUMMON message to
indicate that it is summoning that user.
*/

#define RPL_VERSION(Initiator, Version, Debuglevel, Server, Comments) "351 " + Initiator + " " + Version + "." + Debuglevel + " " + Server + " :" + Comments
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

#define RPL_WHOREPLY(Initiator, Channel, User, Host, Server, Nick, H_or_G, optionalAsterisk, optional_At_or_Plus, Hopcount, RealName) \
	": 352 " + Channel + " " + Client + " " + Host + " " + Server + " " + Nick + "\n" + H_or_G + optionalAsterisk + optional_At_or_Plus + " :" + Hopcount + " " + RealName
/*
"<channel> <user> <host> <server> <nick> \
<H|G>[*][@|+] :<hopcount> <real name>"
*/

#define RPL_ENDOFWHO(Initiator, Name) "315 " + Initiator + " " + Name + " :End of /WHO list"
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

#define	RPL_NAMREPLY(Initiator, Channel)		": 353 " + Channel /*
"<channel> :[[@|+]<nick> [[@|+]<nick> [...]]]"
*/

#define RPL_ENDOFNAMES(Initiator, Channel) "366 " + Initiator + " " + Channel + " :End of /NAMES list"
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

#define RPL_LINKS(Initiator, Mask, Server, Hopcount, ServerInfo) "364 " + Initiator + " " + Mask + " " + Server + " :" + Hopcount + " " + ServerInfo
/*
"<mask> <server> :<hopcount> <server info>"
*/

#define RPL_ENDOFLINKS(Initiator, Mask) "365 " + Initiator + " " + Mask + " :End of /LINKS list"
/*
"<mask> :End of /LINKS list"

- In replying to the LINKS message, a server must send
replies back using the RPL_LINKS numeric and mark the
end of the list using an RPL_ENDOFLINKS reply.
*/

#define RPL_BANLIST(Initiator, Channel, Banid) "367 " + Initiator + " " + Channel + " " + Banid
/*
"<channel> <banid>"
*/

#define RPL_ENDOFBANLIST(Initiator, Channel) "368 " + Initiator + " " + Channel + " :End of channel ban list"
/*
"<channel> :End of channel ban list"

- When listing the active 'bans' for a given channel,
a server is required to send the list back using the
RPL_BANLIST and RPL_ENDOFBANLIST messages.  A separate
RPL_BANLIST is sent for each active banid.  After the
banids have been listed (or if none present) a
RPL_ENDOFBANLIST must be sent.
*/

#define RPL_INFO(Initiator, String) "371 " + Initiator + " " + String
/*
":<string>"
*/

#define RPL_ENDOFINFO (Initiator) "374 " + Initiator + " End of /INFO list"
/*
":End of /INFO list"

- A server responding to an INFO message is required to
send all its 'info' in a series of RPL_INFO messages
with a RPL_ENDOFINFO reply to indicate the end of the
replies.
*/

#define	RPL_MOTDSTART(Initiator, Server) "375 " + Initiator + " - " + Server + " Message of the day - "
/*
":- <server> Message of the day - "
*/

#define RPL_MOTD(Initiator, Text) "372 " + Initiator + " - " + Text
/*
":- <text>"
*/

#define	RPL_ENDOFMOTD(Initiator, Nick) "376 " + Initiator + " " + Nick + " End of /MOTD command"
/*
":End of /MOTD command"

- When responding to the MOTD message and the MOTD file
is found, the file is displayed line by line, with
each line no longer than 80 characters, using
RPL_MOTD format replies.  These should be surrounded
by a RPL_MOTDSTART (before the RPL_MOTDs) and an
RPL_ENDOFMOTD (after).
*/

#define RPL_YOUREOPER (Initiator) "381 " + Initiator + " You are now an IRC operator"
/*
":You are now an IRC operator"

- RPL_YOUREOPER is sent back to a client which has
just successfully issued an OPER message and gained
operator status.
*/

#define RPL_REHASHING(Initiator, ConfigFile) "382 " + Initiator + " " + ConfigFile + " :Rehashing"
/*
"<config file> :Rehashing"

- If the REHASH option is used and an operator sends
a REHASH message, an RPL_REHASHING is sent back to
the operator.
*/

#define RPL_TIME(Initiator, Server, ServerLocalTime) "391 " + Initiator + " " + Server + " :" + ServerLocalTime
/*
"<server> :<string showing server`s local time>"

- When replying to the TIME message, a server must send
the reply using the RPL_TIME format above.  The string
showing the time need only contain the correct day and
time there.  There is no further requirement for the
time string.
*/

#define RPL_USERSSTART (Initiator) "392 " + Initiator + " UserID   Terminal  Host"
/*
":UserID   Terminal  Host"
*/

#define RPL_USERS (Initiator) "393 " + Initiator + " %-8s %-9s %-8s"
/*
":%-8s %-9s %-8s"
*/

#define RPL_ENDOFUSERS (Initiator) "394 " + Initiator + " End of users"
/*
":End of users"
*/

#define RPL_NOUSERS (Initiator) "395 " + Initiator + " Nobody logged in"
/*
":Nobody logged in"

- If the USERS message is handled by a server, the
replies RPL_USERSTART, RPL_USERS, RPL_ENDOFUSERS and
RPL_NOUSERS are used.  RPL_USERSSTART must be sent
first, following by either a sequence of RPL_USERS
or a single RPL_NOUSER.  Following this is
RPL_ENDOFUSERS.
*/

#define RPL_TRACELINK(Initiator, VersionDebugLevel, Destination, NextServer) \
	": 200 Link " + VersionDebugLevel + " " + Destination + "\n" + NextServer
/*
"Link <version & debug level> <destination> \
<next server>"
*/

#define RPL_TRACECONNECTING(Initiator, Class, Server) "201 T + Initiator + " "ry. " + Class + " " + Server
/*
"Try. <class> <server>"
*/

#define RPL_TRACEHANDSHAKE(Initiator, Class, Server) "202 H + Initiator + " ".S. " + Class + " " + Server
/*
"H.S. <class> <server>"
*/

#define RPL_TRACEUNKNOWN(Initiator, Class, Ip) "203 ? + Initiator + " "??? " + Class + not Ip.empty() ? " " + Ip : ""
/*
"???? <class> [<client IP address in dot form>]"
*/

#define RPL_TRACEOPERATOR(Initiator, Class, Nick) "204 O + Initiator + " "per " + Class + " " + Nick
/*
"Oper <class> <nick>"
*/

#define RPL_TRACEUSER(Initiator, Class, Nick) "205 U + Initiator + " "ser " + Class + " " + Nick
/*
"User <class> <nick>"
*/

#define RPL_TRACESERVER(Initiator, Class, Int1, Int2, Server, NickUser, Host_or_server) \
	": 206 "                                                                 \
	"Serv " +                                                                \
		Class + " " + Int1 + "S " + Int2 + "C " + Server + "\n" + NickUser + "@" + Host_or_Server
/*
"Serv <class> <int>S <int>C <server> \
<nick!user|*!*>@<host|server>"
*/

#define RPL_TRACENEWTYPE(Initiator, Newtype, ClientName) "208 " + Initiator + " " + Newtype + " 0 " + ClientName
/*
"<newtype> 0 <client name>"
*/

#define RPL_TRACELOG(Initiator, Logfile, DebugLevel) "261 F + Initiator + " "ile " + Logfile + " " + DebugLevel
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

#define RPL_STATSLINKINFO(Initiator, Linkname, Sendq, SentMessages, SentBytes, ReceivedMessages, ReceivedBytes, TimeOpen) \
	": 211 " + Linkname + " " + Sendq + " " + SentMessages + " \n " + SentBytes + " " + ReceivedMessages + " \n " + ReceivedBytes + " " + TimeOpen
/*
"<linkname> <sendq> <sent messages> \
<sent bytes> <received messages> \
<received bytes> <time open>"
*/

#define RPL_STATSCOMMANDS(Initiator, Command, Count) "212 " + Initiator + " " + Command + " " + Count
/*
"<command> <count>"
*/

#define RPL_STATSCLINE(Initiator, Host, Name, Port, Class) "213 C + Initiator + " " " + Host + " * " + Name + " " + Port + " " + Class
/*
"C <host> * <name> <port> <class>"
*/

#define RPL_STATSNLINE(Initiator, Host, Name, Port, Class) "214 N + Initiator + " " " + Host + " * " + Name + " " + Port + " " + Class
/*
"N <host> * <name> <port> <class>"
*/

#define RPL_STATSILINE(Initiator, Host1, Host2, Port, Class) "215 I + Initiator + " " " + Host1 + " * " + Host2 + " " + Port + " " + Class
/*
"I <host> * <host> <port> <class>"
*/

#define RPL_STATSKLINE(Initiator, Host, Username, Port, Class) "216 K + Initiator + " " " + Host + " * " + Username + " " + Port + " " + Class
/*
"K <host> * <username> <port> <class>"
*/

#define RPL_STATSYLINE(Initiator, Class, PingFrequency, ConnectFrequency, MaxSendq) \
	": 218 Y " + Class + " " + PingFrequency + " \n " + ConnectFrequency + " " + MaxSendq
/*
"Y <class> <ping frequency> <connect \
frequency> <max sendq>"
*/

#define RPL_ENDOFSTATS(Initiator, StatsLetter) "219 " + Initiator + " " + StatsLetter + " :End of /STATS report"
/*
"<stats letter> :End of /STATS report"
*/

#define RPL_STATSLLINE(Initiator, Hostmask, Servername, Maxdepth) "241 L + Initiator + " " " + Hostmask + " * " + Servername + " " + Maxdepth
/*
"L <hostmask> * <servername> <maxdepth>"
*/

#define RPL_STATSUPTIME (Initiator) "242 " + Initiator + " Server Up %d days %d:%02d:%02d"
/*
":Server Up %d days %d:%02d:%02d"
*/

#define RPL_STATSOLINE(Initiator, Hostmask, Name) "243 O + Initiator + " " " + Hostmask + " * " + Name
/*
"O <hostmask> * <name>"
*/

#define RPL_STATSHLINE(Initiator, Hostmask, Servername) "244 H + Initiator + " " " + Hostmask + " * " + Servername
/*
"H <hostmask> * <servername>"
*/

#define RPL_UMODEIS(Initiator, UserModeString) "221 " + Initiator + " " + UserModeString
/*
"<user mode string>"

- To answer a query about a client`s own mode,
RPL_UMODEIS is sent back.
*/

#define RPL_LUSERCLIENT(Initiator, Integer1, Integer2, Integer3) \
	": 251 :There are " + Integer1 + " users and " + Integer2 + " \n invisible on " + Integer3 + " servers"
/*
":There are <integer> users and <integer> \
invisible on <integer> servers"
*/

#define RPL_LUSEROP(Initiator, Integer) "252 " + Initiator + " " + Integer + " :operator(s) online"
/*
"<integer> :operator(s) online"
*/

#define RPL_LUSERUNKNOWN(Initiator, Integer) "253 " + Initiator + " " + Integer + " :unknown connection(s)"
/*
"<integer> :unknown connection(s)"
*/

#define RPL_LUSERCHANNELS(Initiator, Integer) "254 " + Initiator + " " + Integer + " :channels formed"
/*
"<integer> :channels formed"
*/

#define RPL_LUSERME(Initiator, Integer1, Integer2) "255 " + Initiator + " I have " + Integer1 + " clients and " + Integer2 + " \n servers"
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

#define RPL_ADMINME(Initiator, Server) "256 " + Initiator + " " + Server + " :Administrative info"
/*
"<server> :Administrative info"
*/

#define RPL_ADMINLOC1(Initiator, AdminInfo) "257 " + Initiator + " " + AdminInfo
/*
":<admin info>"
*/

#define RPL_ADMINLOC2(Initiator, AdminInfo) "258 " + Initiator + " " + AdminInfo
/*
":<admin info>"
*/

#define RPL_ADMINEMAIL(Initiator, AdminInfo) "259 " + Initiator + " " + AdminInfo
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
