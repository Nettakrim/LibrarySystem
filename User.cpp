#include "User.h"

#include "Util.h"

User::User(std::string filename)
{
	this->filename = filename;
}

std::string User::getFilename()
{
	return filename;
}

bool User::usernameMatches(std::string username) const
{
	return this->username == username;
}

bool User::passwordMatches(std::string password) const
{
	return this->password == password;
}

void User::accountInfoUI()
{
	std::cout << "\n" << username;
	Util::awaitEnter();
}
