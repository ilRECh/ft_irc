#pragma once
#include "ACommand.hpp"

class USER : public ACommand {
private:
    USER();
    USER(USER const &that);
    USER& operator=(USER const &that);
public:
    USER(Server & Server) : ACommand("USER", Server) {}
    virtual ~USER() {}
    virtual int run(){
        if (not _Initiator->_RealName.empty()) {
            return _Initiator->updateReplyMessage(ERR_ALREADYREGISTRED);
        } else if (not _Argument.empty()) {
            size_t scFound = _Argument.find(':');
            if (scFound not_eq _Argument.npos and scFound > 0 and _Argument[scFound + 1] not_eq '\0') {
                std::string left = _Argument.substr(0, scFound);
                std::string right = _Argument.substr(scFound + 1);
                std::vector<std::string> NewArguments = ft::split(left, " ");
                if (NewArguments.size() == 3) {
                    NewArguments.push_back(right);
                    _Arguments = NewArguments;
                } else {
                    return _Initiator->updateReplyMessage(ERR_NEEDMOREPARAMS(_Name));
                }
            } else {
                return _Initiator->updateReplyMessage(ERR_NEEDMOREPARAMS(_Name));
            }
        } else {
            return _Initiator->updateReplyMessage(ERR_NEEDMOREPARAMS(_Name));
        }
        std::string UserName = _Arguments[0];
        if(UserName == "*") {
            UserName = "~" + _Initiator->_NickName;
        } else if (UserName.find('*') not_eq UserName.npos) {
            std::string RemoveAsterisks(UserName);
            while (RemoveAsterisks.find('*') not_eq RemoveAsterisks.npos) {
                RemoveAsterisks.erase(RemoveAsterisks.find('*'));
            }
            UserName = "~" + RemoveAsterisks;
        }
        _Initiator->_UserName = UserName;
        _Initiator->_RealName = _Arguments[3];
        if (not _Initiator->_Registration.IsRegistered and 
            _Initiator->_PasswordCorrect and not _Initiator->_NickName.empty()) {
            _Initiator->_Registration.IsRegistered = true;
            _Initiator->updateReplyMessage(RPL_MOTDSTART(SERVER_NAME));
            _Initiator->updateReplyMessage(RPL_MOTD(std::string("Privet peer")));
            _Initiator->updateReplyMessage(RPL_ENDOFMOTD);
        }
        return 0;
    }
};/*
   Parameters: <username> <hostname> <servername> <realname>

   The USER message is used at the beginning of connection to specify
   the username, hostname, servername and realname of s new user.  It is
   also used in communication between servers to indicate new user
   arriving on IRC, since only after both USER and NICK have been
   received from a client does a user become registered.

   Between servers USER must to be prefixed with client's NICKname.
   Note that hostname and servername are normally ignored by the IRC
   server when the USER command comes from a directly connected client
   (for security reasons), but they are used in server to server
   communication.  This means that a NICK must always be sent to a
   remote server when a new user is being introduced to the rest of the
   network before the accompanying USER is sent.

   It must be noted that realname parameter must be the last parameter,
   because it may contain space characters and must be prefixed with a
   colon (':') to make sure this is recognised as such.

   Since it is easy for a client to lie about its username by relying
   solely on the USER message, the use of an "Identity Server" is
   recommended.  If the host which a user connects from has such a
   server enabled the username is set to that as in the reply from the
   "Identity Server".

   Numeric Replies:

           ERR_NEEDMOREPARAMS              ERR_ALREADYREGISTRED

   Examples:


   USER guest tolmoon tolsun :Ronnie Reagan

                                   ; User registering themselves with a
                                   username of "guest" and real name
                                   "Ronnie Reagan".


   :testnick USER guest tolmoon tolsun :Ronnie Reagan
                                   ; message between servers with the
                                   nickname for which the USER command
                                   belongs to

*/
