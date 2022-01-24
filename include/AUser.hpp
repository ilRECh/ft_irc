#pragma once

#include "ft.hpp"

class AUser {
private:
    AUser();
    AUser(AUser& that);
    AUser& operator=(AUser& that);
protected:
    std::string _Name;
    std::string _Password;
public:
    AUser(std::string const Name) { 
        setName(Name); 
    }
    virtual ~AUser() {} ;
    virtual bool setName(std::string const & Name) {
        for (size_t i = 0; i < Name.length(); ++i) {
            if (!std::isalnum(Name[i]))
                return true;
        }
        _Name = Name;
        return false;
    }
    std::string const & getName( void ) const {
        return _Name;
    }
    void setPassword(std::string const & Password) {
        _Password = Password;
    }
    std::string const & getPassword() const {
        return _Password;
    }
};
