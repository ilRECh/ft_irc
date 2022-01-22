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
    std::string _ReplyMessage;
public:
    AUser(std::string const & Name) { 
        setName(Name); 
    }
    virtual ~AUser() {} ;
    virtual void setName(std::string const & Name) {
        // for (size_t i = 0; i < Name.length(); ++i) {
        //     if (!std::isalnum(Name[i]))
        //         throw std::runtime_error("Name " + Name + " is not valid, use A-Z, a-z, 0-9");
        // }
        _Name = Name;
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
    void setReplyMessage(std::string const & Msg) {
        _ReplyMessage = Msg;
    }
    std::string const getReplyMessage() {
        std::string ret(_ReplyMessage);
        _ReplyMessage.clear();
        return ret;
    }
};
