#5. OPTIONALS
   This section describes **OPTIONAL** messages.  They are not required in a
   working server implementation of the protocol described herein.  In
   the absence of the option, an error reply message must be generated
   or an unknown command error.  If the message is destined for another
   server to answer then it must be passed on (elementary parsing
   required) The allocated numerics for this are listed with the
   messages below.
---
- 5.1 [AWAY](AWAY.hpp)
- 5.2 [REHASH](REHASH.hpp)
- 5.3 [RESTART](RESTART.hpp)
- 5.4 [SUMMON](SUMMON.hpp)
- 5.5 [USERS](USERS.hpp)
- 5.6 [WALLOPS](WALLOPS.hpp)
- 5.7 [USERHOST](USERHOST.hpp)
- 5.8 [ISON](ISON.hpp)

[Source](https://www.rfc-editor.org/rfc/inline-errata/rfc1459.html)