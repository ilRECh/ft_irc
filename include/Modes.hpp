#pragma once

#include "ft.hpp"

class Client;
class Channel;

class Modes {
private:
	typedef std::map<Client const *, std::set<char> *> clients_modes;
	clients_modes _ClientsModes;
    Channel *_Channel;
public:
    Modes(Channel *Channel = NULL);
    ~Modes();
    bool getModeIsExist(Channel const * Channel, std::string SomeModes) const;
    bool getModeIsExist(Channel const * Channel, char mode) const;
    void setMode(Channel const * Channel, char mode);
    void unsetMode(Channel const * Channel, char mode);
    bool getModeIsExist(Client const * Client, std::string SomeModes) const;
    bool getModeIsExist(Client const * Client, char mode) const;
    void setMode(Client const * Client, char mode);
    void unsetMode(Client const * Client, char mode);
    void eraseClientFromModes(Client const * Client);
};
