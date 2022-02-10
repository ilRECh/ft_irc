#4.3 Server queries and commands

The server query group of commands has been designed to return
information about any server which is connected to the network.  All
servers connected must respond to these queries and respond
correctly.  Any invalid response (or lack thereof) must be considered
a sign of a broken server and it must be disconnected/disabled as
soon as possible until the situation is remedied.

In these queries, where a parameter appears as `<server>`, it will
usually mean it can be a nickname or a server or a wildcard name of
some sort.  For each parameter, however, only one query and set of
replies is to be generated.
---
- 4.3.7 [ADMIN](ADMIN.hpp)
