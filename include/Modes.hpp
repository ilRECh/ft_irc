#pragma once

#include "Client.hpp"

class Modes {
private:
	typedef std::map<Client const *, std::set<char> *> clients_modes;
	clients_modes _ClientsModes;
public:
    Modes() {}
    ~Modes() {
        for (clients_modes::iterator it = _ClientsModes.begin(); it != _ClientsModes.end(); ++it) {
            delete it->second;
        }
    }
    bool getModeIsExist(Client const * Client, char mode) const {
        clients_modes::const_iterator Modes = _ClientsModes.find(Client);
        if (Modes != _ClientsModes.end()) {
            return Modes->second->find(mode) != Modes->second->end();
        }
        return false;
    }
    void setMode(Client const * Client, char mode) {
        clients_modes::iterator Modes = _ClientsModes.find(Client);
        if (Modes == _ClientsModes.end()) {
            std::pair<clients_modes::iterator, bool> IsInserted =
                _ClientsModes.insert(make_pair(Client, new std::set<char>));
            if (not IsInserted.second) {
                throw(std::runtime_error(ft::to_string(__LINE__) + " map insertion failure."));
            }
            Modes = IsInserted.first;
        }
        Modes->second->insert(mode);
    }
    void unsetMode(Client const * Client, char mode){
        clients_modes::iterator Modes = _ClientsModes.find(Client);
        if (Modes != _ClientsModes.end()) {
            Modes->second->erase(mode);
        }
    }
    void eraseClientFromModes(Client const * Client) {
        clients_modes::iterator ToBeErasedFromModes = _ClientsModes.find(Client);
        if (ToBeErasedFromModes != _ClientsModes.end()) {
            delete ToBeErasedFromModes->second;
            _ClientsModes.erase(ToBeErasedFromModes);
        }
    }
};
