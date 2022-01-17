#4.2 Channel operations

This group of messages is concerned with manipulating channels, their
properties (channel modes), and their contents (typically clients).
In implementing these, a number of race conditions are inevitable
when clients at opposing ends of a network send commands which will
ultimately clash.  It is also required that servers keep a nickname
history to ensure that wherever a `<nick>` parameter is given, the
server check its history in case it has recently been changed.
---
- 4.2.1 [JOIN](JOIN.hpp)
- 4.2.2 [PART](PART.hpp)
- 4.2.3 [MODE](MODE.hpp)
- 4.2.4 [TOPIC](TOPIC.hpp)
- 4.2.5 [NAMES](NAMES.hpp)
- 4.2.6 [LIST](LIST.hpp)
- 4.2.7 [INVITE](INVITE.hpp)
- 4.2.8 [KICK](KICK.hpp)
