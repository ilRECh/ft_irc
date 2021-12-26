#include <string>
#include <vector>
#include <stdlib.h>
#include "User.hpp"
#include "ExceptionUni.hpp"

using std::string;
using std::vector;

class Channel
{
private:
	string			_NameChannel;
	vector<User>	_Admins;
public:
	Channel(string const & nameChannel, User const & userAdmin);
	~Channel();
	bool checkAdminPermist(User const & userAdmin) const;
	const vector<User>& getAdmins();
	void	setNameChannel(string const & newNameChannel);
	void	addAdmin(User const & name);
	void	dellAdmin(User const & name);
};