#include "Modes.hpp"
#include "Channel.hpp"
#include "Client.hpp"

Modes::Modes(Channel *Channel) : _Channel(Channel) {}

Modes::~Modes() {
    for (clients_modes::iterator it = _ClientsModes.begin(); it != _ClientsModes.end(); ++it) {
        delete it->second;
    }
}

bool Modes::getModeIsExist(Channel const * Channel, std::string SomeModes) const {
    if (Channel != _Channel) {
        throw (std::runtime_error("You cannot peek or change modes of " +
            Channel->getChannelName() + " from " + _Channel->getChannelName()));
    }
    return getModeIsExist(reinterpret_cast<Client const *>(Channel), SomeModes);
}

bool Modes::getModeIsExist(Channel const * Channel, char mode) const {
    if (Channel != _Channel) {
        throw (std::runtime_error("You cannot peek or change modes of " +
            Channel->getChannelName() + " from " + _Channel->getChannelName()));
    }
    return getModeIsExist(reinterpret_cast<Client const *>(Channel), mode);
}

void Modes::setMode(Channel const * Channel, char mode) {
    if (Channel != _Channel) {
        throw (std::runtime_error("You cannot peek or change modes of " +
            Channel->getChannelName() + " from " + _Channel->getChannelName()));
    }
    setMode(reinterpret_cast<Client const *>(Channel), mode);
}

void Modes::unsetMode(Channel const * Channel, char mode) {
    if (Channel != _Channel) {
        throw (std::runtime_error("You cannot peek or change modes of " +
            Channel->getChannelName() + " from " + _Channel->getChannelName()));
    }
    unsetMode(reinterpret_cast<Client const *>(Channel), mode);
}

bool Modes::getModeIsExist(Client const * Client, std::string SomeModes) const {
    clients_modes::const_iterator Modes = _ClientsModes.find(Client);
    if (Modes != _ClientsModes.end()) {
        for (size_t i = 0; i < SomeModes.size(); ++i) {
            if (Modes->second->find(SomeModes[i]) == Modes->second->end()) {
                return false;
            }
        }
    } else {
        return false;
    }
    return true;
}

bool Modes::getModeIsExist(Client const * Client, char mode) const {
    clients_modes::const_iterator Modes = _ClientsModes.find(Client);
    if (Modes != _ClientsModes.end()) {
        return Modes->second->find(mode) != Modes->second->end();
    }
    return false;
}

void Modes::setMode(Client const * Client, char mode) {
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

void Modes::unsetMode(Client const * Client, char mode) {
    clients_modes::iterator Modes = _ClientsModes.find(Client);
    if (Modes != _ClientsModes.end()) {
        Modes->second->erase(mode);
    }
}

void Modes::eraseClientFromModes(Client const * Client) {
    clients_modes::iterator ToBeErasedFromModes = _ClientsModes.find(Client);
    if (ToBeErasedFromModes != _ClientsModes.end()) {
        delete ToBeErasedFromModes->second;
        _ClientsModes.erase(ToBeErasedFromModes);
    }
}
