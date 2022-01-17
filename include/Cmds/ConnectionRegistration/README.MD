#4.1 Connection Registration

The commands described here are used to register a connection with an
IRC server as either a user or a server as well as correctly
disconnect.

A **"PASS"** command is not required for either client or server
connection to be registered, but it must precede the server message
or the latter of the **NICK/USER** combination.  It is strongly
recommended that all server connections have a password in order to
give some level of security to the actual connections.  The
recommended order for a client to register is as follows:

           1. Pass message
           2. Nick message
           3. User message

---
- 4.1.1 [Password message](PASS.hpp)

      Command: PASS
- 4.1.2 [Nick message](NICK.hpp)

      Command: NICK
- 4.1.3 [User message](USER.hpp)

      Command: USER
- 4.1.4 [Server message](SERVER.hpp)

      Command: SERVER
- 4.1.5 [Oper](OPER.hpp)

      Command: OPER
- 4.1.6 [Quit](QUIT.hpp)

      Command: QUIT
- 4.1.7 [Server quit message](SQUIT.hpp)

      Command: SQUIT