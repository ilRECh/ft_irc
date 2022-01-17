#4.4 Sending messages

The main purpose of the IRC protocol is to provide a base for clients
to communicate with each other.  PRIVMSG and NOTICE are the only
messages available which actually perform delivery of a text message
from one client to another - the rest just make it possible and try
to ensure it happens in a reliable and structured manner.
---
- 4.4.1 [Private messages](PRIVMSG.hpp)

      Command: PRIVMSG
- 4.4.2 [Notice](NOTICE.hpp)

      Command: NOTICE
